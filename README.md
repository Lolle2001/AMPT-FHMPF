# AMPT-Processing

This repositery contains code for running AMPT on multiple cores and processing the (large amount of) data into useful results. Currently it only gives data in a format used for my bachelor thesis. The goal is to convert the AMPT data into histograms, binned into centrality, participating nuclei, transverse momentum and (pseudo)rapidity, for every particle. This converts large amounts of data into a workable format which can be stored in RAM.

## Running AMPT

### Compiling

Compiling can be done in two ways. One way uses the script `compile.sh` in the main folder. This script compiles version `v1.26t9b-v2.26t9b` of AMPT (from [here](https://myweb.ecu.edu/linz/ampt/)). It has one parameter to define the amount of bins that should be created. Because AMPT is inherently a single threaded program, every core needs a seperate directory in which the data is stored. . Example of use:

```shell
bash compile.sh numberofbins
```

The other way is to compile the code in a more advanced way. This can be done with `utils/createbins.sh`. It has three parameters: the first two designate the indices of the first and last bin that should be created. The third parameter is the name of the directory in `./src` that contains the fortran files of ampt. This way one can choose which version to use and it allows for bins to have different source codes. Example of use:

```shell
bash utils/createbins.sh startbin endbin sourcecode
```

If this second way is used, then one must define the directories in `utils/directories.sh` before running AMPT.

An overview of the different source codes included in the repo is listed below:

- currently the source code is based on version `ampt-v1.26t9b-v2.26t9b`, which can be found at this [website](https://myweb.ecu.edu/linz/ampt/).
- `original` is the original, unedited source code of the above described version.
- `ellipticflow` is an edited version which at the end calculates elliptic flow properties (from `ana/ampt.dat` and `ana/zpc.dat`) and puts them in a folder `ana1`.
- `edited` is a version that generates animation files, these can become quite large quickly and also make the simulations go very slow. These files are also put in `ana1`. For animations it is recommended to only run 1 event.

### Updating

When updating the bin directories one can use the command below in a similar fashion as above:

```shell
bash utils/recompile.sh startbin endbin sourcecode
```

### Running

The code can be run (in the background) by using the command:

```shell
bash rampt.sh inputfile runnumber startbin endbin &!
```

- `inputfile` the name of the inputfile with the specified parameters for AMPT.
- `runnumber` the identification for the run.

- `startbin` the ampt bin directory in which to start.
- `endbin` the ampt bin directory in which to end.
- Data will be moved to the directory `./datafolder/runnumber.` into subdirectories corresponding to the used bins.
- There will be three files: `runnumber.log`, `runnumber.err`, `runnumber.time`
- `runnumber.log` gives a general overview of the settings for running the code, including the total number of events, used directories and runtime.
- `runnumber.err` gives encountered errors.
- `runnumber.time` summarises the runtime.
- Similarly each subdirectory also has these log files, giving the output of the `./ampt` executable and runtime.

If one desires to run a batch of jobs one can generate a `.job` file with consecutive executions of the above. The default can be executed as:

```shell
bash ampt.job &!
```

Note that first the file must be generated with `utils/inputgen.py`, which is a selfexplanatory code, that must be edited to get desired input files. It can be ran using:

```shell
python3 utils/inputgen.py
```

## Data processing

### Processing methods

There are two methods to process data from AMPT:

- The first is that one can read all (desired) datafiles into a data-object and then combining all the events from the different bin directories. When working with a small amount of events and not generating large files (with for example the IOSCAR=3 option or animation source code) this method works quick and allows for a nice workflow with ROOT.
- A different method is needed when many events are ran, the file sizes can be too big to have them stored in memory using data objects. In that case one has to process data line by line using a parse function of the data object. Summarised data containing information about the observables listed below can then be written into files. This process can take a little longer and it would be beneficial to multiprocess this properly. This summarised data is generated per event and per particle. The form of the code should allow for trivial modification to add functions in the parse function that calculated other desired observables.

### Observables

- Particle Yields
  - Average taken over number of events.
  - Calculated for each particle seperately (gives option to combine later if desired).
  - Partitioned in centrality bins.
  - Only for the $\left \lvert\eta\right \rvert>0.5$ pseudorapidity bin.
- Pseudorapidity Distribution
  - Average taken over number of events.
  - Calculated for each particle seperately.
  - Partitioned in centrality bins.
  - Histogram has even binning.
- Transverse Momentum Distribution
  - Average taken over number of events.
  - Calculated for each particle seperately.
  - Partition in centrality bins.
  - Histogram has logarthmic binning (similar to that used in ALICE articles for easy comparison).
- Elliptic Flow (and other Flow Coëfficiënts)
  - Average taken over total number of particles in all events.
  - Calculated for all charged particles (currently).
  - Partitioned in centrality bins.
  - Only for the $\left \lvert \eta \right \rvert>0.5$ pseudorapidity bin and $0.1 < p_T < 4$ GeV/c transverse momentum bin.
- Transverse Mass Distribution
  - [WIP]
- Energy Density Evolution
  - [WIP]
- Particle Number Density Evolution
  - [WIP]
- Particle Number Evolution
  - Both for partons and hadrons.
  - [WIP]
- Collision Animation
  - Can be combind with particle number evolution.

## Remarks

- Simulations can be done seperately for different centralities or for all centralties at once. The first assures that each centrality bin has the same amount of events. The second distributes the impact parameter according to the Glauber model.
- Binning for the pseudorapidity and transverse momentum distributions can also be made in small steps. This allows for combining the bins afterwards, to allow a more flexible data processing without having to reproces the large dataset.
- Evolution data should be done for single (or if you are brave enough a small number of) events.

## New method of running AMPT

Using multiple bash scripts does not allow for a good readable code and can cause problems when it comes to directories. For that reason a **C++** version was developed, which handles the running and compilation. Additional advantages are that command line parsing is easy to setup and that extra functionality was added with respect to the previous method.
The program is called **ampt-mp** and needs to be compiled with **C++17**. In addition the **[fmt](https://github.com/fmtlib/fmt)**, **[argparse](https://github.com/p-ranav/argparse)** and **[OMP](https://github.com/OpenMP/sources)** libraries were used. **OMP** is usually already installed on Linux.
By default it is assumed that all input files are in the directory `./input`, the source is in `./src/original` and the data is stored in `./data`. At first use, the following commands can be ran in the terminal.

```shell
./ampt-mp -h # See options for compiling AMPT
./ampt-mp -h # See options for running AMPT

./ampt-mp compiler -b 1 12 # Compiles every bin with the given source code
./ampt-mp -o test -b 1 12 # Runs AMPT in every bin and stores the data in ./data/test
```
