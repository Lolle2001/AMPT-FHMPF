# AMPT-Processing
This repositery contains code for running AMPT on multiple cores and processing the (large amount of) data into useful results. Currently it only gives data in a format used for my bachelor thesis. The goal is to generate the observables in the most general manner as possible, without having to work with gigabytes of data.

## Running AMPT

### Compiling
When using the code for the first time, the bin directories have to be created using:
```shell
bash utils/createbins.sh startbin endbin sourcecode
```
* it is suggested to give ```startbin``` a value of 1 and ```endbin``` a value that equals the number of available CPU cores.
* ```sourcecode``` is the name of the directory in ```./src``` that contains the fortran files of AMPT. This way one can choose which version to use.
* make sure that in the ```exec``` file the random number generation is decommented such that the random seeds are generated correctly.
* if you desire to run this in the background add ```&!``` at the end of the command.
* currently the source code is based on version ```ampt-v1.26t9b-v2.26t9b```, which can be found at this [website](https://myweb.ecu.edu/linz/ampt/).
  * ```original``` is the original, unedited source code of the above described version.
  * ```ellipticflow``` is an edited version which at the end calculates elliptic flow properties (from ```ana/ampt.dat``` and ```ana/zpc.dat```) and puts them in a folder ```ana1```.
  * ```edited``` is a version that generates animation files, these can become quite large quickly and also make the simulations go very slow these files are also put in ```ana1```.

### Updating
When updating the bin directories one can use the command below in a similar fashion as above:
```shell
bash utils/recompile.sh startbin endbin sourcecode
```
### Running
The code can be run (in the background) by using the command: 
```shell
python3 rampt.py startbin endbin runnumber input/inputfile.ampt datafolder &!
```
* ```startbin```   the ampt bin directory in which to start.
* ```endbin```     the ampt bin directory in which to end.
* ```runnumber```  the identification for the run.
* ```inputfile```  the name of the inputfile with the specified parameters for AMPT.
* ```datafolder``` the folder in which to store the resulting files from the AMPT simulation after a bin has finished (more efficiënt use of space).
If in the input file it is specified that 1000 events have to ran, and if the startbin is 1 and endbin is 12, then 12000 events will be run in total of which thousand events will be ran simultaneously.

* Data will be moved to the directory ```./datafolder/runnumber.```
* There will be three files: ```info.out```, ```other.out```, ```runtime.out```
* ```info.out``` gives a general overview of the settings for running the code, including the total number of events, used directories and runtime.
* ```other.out``` gives the stdout and stderr of the ampt executable for every bin.
* ```runtime.out``` gives the runtime for each bindirectory.

### Example commands
To run 12 simulations simultaneously you can use the following commands. The simulation has runnumber 1, an input called input_1.ampt and the data is stored in a folder called data.
```
bash utils/createbins.sh 1 32 original
python3 rampt.py 1 12 1 input/input_1.ampt data &!
```

### Advanced
When one has many cpu cores available one can decide to run multiple input files (with for example different energies). One can use the command:
```shell
python3 multirampt.py numberofbins datafolder &!
```
* For this one has to specify the directories to the input files in the ```multirampt.txt``` file with the corresponding runnumber.
* This method is prone to errors and is only efficiënt if the simulation times are approximately the same for each input file in all other cases one would want to make a queee system which waits for the normal python script to finish before putting out another run.

### Errors
When running into errors with the code, make sure that the code that is used was compiled on the same machine and that all directories are correct. There might be some errors regarding paths in the code.

## Data processing
### Processing methods
There are two methods to process data from AMPT:
* The first is that one can read all (desired) datafiles into a data-object and then combining all the events from the different bin directories. When working with a small amount of events and not generating large files (with for example the IOSCAR=3 option or animation source code) this method works quick and allows for a nice workflow with ROOT.
* A different method is needed when many events are ran, the file sizes can be too big to have them stored in memory using data objects. In that case one has to process data line by line using a parse function of the data object. Summarised data containing information about the observables listed below can then be written into files. This process can take a little longer and it would be beneficial to multiprocess this properly. This summarised data is generated per event and per particle. The form of the code should allow for trivial modification to add functions in the parse function that calculated other desired observables.
### Observables
* Particle Yields
  * Average taken over number of events.
  * Calculated for each particle seperately (gives option to combine later if desired).
  * Partitioned in centrality bins.
  * Only for the $\left \lvert\eta\right \rvert>0.5$ pseudorapidity bin.
* Pseudorapidity Distribution
  * Average taken over number of events.
  * Calculated for each particle seperately.
  * Partitioned in centrality bins.
  * Histogram has even binning.
* Transverse Momentum Distribution
  * Average taken over number of events.
  * Calculated for each particle seperately.
  * Partition in centrality bins.
  * Histogram has logarthmic binning (similar to that used in ALICE articles for easy comparison).
* Elliptic Flow (and other Flow Coëfficiënts)
  * Average taken over total number of particles in all events.
  * Calculated for all charged particles (currently).
  * Partitioned in centrality bins.
  * Only for the $\left \lvert \eta \right \rvert>0.5$ pseudorapidity bin and $0.1 < p_T < 4$ GeV/c transverse momentum bin.
* Transverse Mass Distribution
  * [WIP]
* Energy Density Evolution
  * [WIP]
* Particle Number Density Evolution
  * [WIP]
* Particle Number Evolution
  * Both for partons and hadrons. 
  * [WIP]
* Collision Animation
  * Can be combind with particle number evolution.

## Remarks
* Simulations can be done seperately for different centralities or for all centralties at once. The first assures that each centrality bin has the same amount of events. The second distributes the impact parameter according to the Glauber model.
* Binning for the pseudorapidity and transverse momentum distributions can also be made in small steps. This allows for combining the bins afterwards, to allow a more flexible data processing without having to reproces the large dataset.
* Evolution data should be done for single (or if you are brave enough a small number of) events.

