# AMPT-FHMPF

> [!IMPORTANT]
> If you use/fork this code, please use the following citation:<br><br>
> L. J. Huisman, _File handling and multiprocessing framework for AMPT_, thesis database UU (2024). https://link <br><br>
> In addition, AMPT must also be cited, because AMPT source code comes with this repository[^1].

This repositery contains code for running the single-threaded AMPT model (A Multi-Phase Transport model) on multiple cores[^1]. It includes:

- Compilation of different versions
- File handling of results
- Generation of input files

## Running AMPT

Using multiple bash scripts does not allow for a good readable code and can cause problems when it comes to file handling. For that reason a **C++** version was developed, which handles the running and compilation. Additional advantages are that command line parsing is easy to setup and that extra functionality was added with respect to the previous method.
The program is called **ampt-mp** and needs to be compiled with **C++17**. In addition the **[fmt](https://github.com/fmtlib/fmt)**, **[argparse](https://github.com/p-ranav/argparse)** and **[OMP](https://github.com/OpenMP/sources)** libraries were used. **OMP** is usually already installed on Linux.
By default it is assumed that all input files are in the directory `./input`, the source is in `./src/original` and the data is stored in `./data`. A compiled program will give the following structure to the program folder:

```
AMPT
├── bin
│   ├── ampt_1
│   ├── ampt_2
│   ├── ...
│   ├── ampt_n
│   ├── anim_1
│   └── ...
├── input
│   └── *.par
├── data
│   ├── run_1
│   ├── run_2
│   └── ...
├── src
│   ├── original
│   ├── edited
│   ├── ellipticflow
│   └── ...
└── ampt-mp
```

At first use, the following commands can be ran in the terminal.

```
./ampt-mp -h # See options for compiling AMPT</span>
./ampt-mp -h # See options for running AMPT

./ampt-mp compiler -b 1 12 # Compiles every bin with the given source code
./ampt-mp -o test -b 1 12 # Runs AMPT in every bin and stores the data in ./data/test
```

> [!NOTE]
> The program has problems with racing conditions, causing a spread in the runtime of seperate instances even when they run the exact same simulation.

## Running AMPT (Old version)

### Compiling

Compiling can be done in two ways. One way uses the script `compile.sh` in the main folder. This script compiles version `v1.26t9b-v2.26t9b` of AMPT (from [here](https://myweb.ecu.edu/linz/ampt/)) [[1]](#1) . It has one parameter to define the amount of bins that should be created. Because AMPT is inherently a single threaded program, every core needs a seperate directory in which the data is stored. . Example of use:

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

## References

<a id="1">[1]</a> Z. W. Lin, C. M. Ko, B. A. Li, B. Zhang and S. Pal, A Multi-phase transport model for relativistic heavy ion collisions. Phys. Rev. C 72, 064901 (2005). https://doi.org/10.1103/PhysRevC.72.064901

[^1]: Z. W. Lin, C. M. Ko, B. A. Li, B. Zhang and S. Pal, A Multi-phase transport model for relativistic heavy ion collisions. Phys. Rev. C 72, 064901 (2005). https://doi.org/10.1103/PhysRevC.72.064901
