# AMPT-FHMPF

> [!IMPORTANT]
> If you use/fork this code, please use the following citation for the software:<br><br>
> L. J. Huisman, _File handling and multiprocessing framework for AMPT_, version 1.0.0 (2024). https://github.com/Lolle2001/AMPT-Processing <br><br>
> In addition, AMPT must also be cited, because AMPT source code comes with this repository[^1].

#

This repositery contains code for running the single-threaded AMPT model (A Multi-Phase Transport model) on multiple cores[^1]. It includes:

- Compilation of different versions
- File handling of results
- Generation of input files

## Running AMPT

Using multiple bash scripts does not allow for a good readable code and can cause problems when it comes to file handling. For that reason a **C++** version was developed, which handles the running and compilation. Additional advantages are that command line parsing is easy to setup and that extra functionality was added with respect to the previous method.
The program is called **ampt-mp** and needs to be compiled with **C++17**. In addition the **[fmt](https://github.com/fmtlib/fmt)**, **[argparse](https://github.com/p-ranav/argparse)** and **[OMP](https://github.com/OpenMP/sources)** libraries were used. **OMP** is part of most compilers (see list [here](https://www.openmp.org/resources/openmp-compilers-tools/)) and does not have to be installed.
By default it is assumed that all input files are in the directory `./input`, the source is in `./src/original` and the data is stored in `./data`. A compiled program will give the following structure to the program folder:

```
AMPT
├── bin
│   ├── ampt-1
│   ├── ampt-2
│   ├── ...
│   ├── ampt-n
│   ├── anim-1
│   └── ...
├── input
│   └── *.par
├── data
│   ├── run-1
│   ├── run-2
│   └── ...
├── src
│   ├── original
│   ├── animation
│   ├── hijing-only
│   └── ...
└── ampt-mp
```

At first use, the following commands can be ran in the terminal.

```
./ampt-mp -h # See options for compiling AMPT
./ampt-mp -h # See options for running AMPT

./ampt-mp compiler -b 1 12 # Compiles every bin with the given source code
./ampt-mp -o test -b 1 12 # Runs AMPT in every bin and stores the data in ./data/test
```

> [!WARNING]
> The program has problems with racing conditions, causing a spread in the runtime of seperate instances even when they run the exact same simulation.

## Detailed installation

Installation of **fmt** can be done in two ways:

```shell
sudo add-apt-repository universe
sudo apt update
sudo apt install libfmt-dev
```

or

```shell
git clone https://github.com/fmtlib/fmt.git
cd fmt
mkdir build
cd build
cmake ..
make
sudo make install
```

Installation of **argparse** can be done in the following way:

```shell
git clone https://github.com/p-ranav/argparse.git
cd argparse
cd build
cmake ..
make -j 4
sudo make install
```

> [!NOTE]
> Make sure that installation with git clone is done in for example downloads or another directory. In addition, make sure that the libraries are correctly added to the path. On Ubuntu this is done automatically.

## Detailed use
#### Versions
By default this framework uses the original AMPT code of version [`v1.26t9b-v2.26t9b`](https://myweb.ecu.edu/linz/ampt/)[^1]. Various modifications have been made in this code. All the frotran files are stored in subfolders of the `src` directory. These are the current options:

- **original**: Contains the original AMPT code (_v1.26t9b-v2.26t9b_).
- **animation**: Contains a modified version, where animation output is enabled.
- **hijing-only**: Contains a modified version, where all components except for hijing have been disabled to obtain geometrical information faster.
#### Input generation
A python script has been created to generate input files. It is located in the `utils` folder. It allows for modification of the desired parameters and gives the option to generate multiple files for multiple centrality bins by using a table. The created parameter file contains the corresponding variable names and their original descriptions.


[^1]: Z. W. Lin, C. M. Ko, B. A. Li, B. Zhang and S. Pal, A Multi-phase transport model for relativistic heavy ion collisions. Phys. Rev. C 72, 064901 (2005). https://doi.org/10.1103/PhysRevC.72.064901
