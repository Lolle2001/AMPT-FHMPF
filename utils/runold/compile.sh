#!/bin/bash
NUMBEROFBINS=$1

printf "╭────────────────────────────────────────────────────────────────────────╮\n"
printf "│ %-70s │\n" "AMPT Multiprocesser - Compiler"                                    
printf "│ %-70s │\n" "Version 3.0.0"           
printf "│ %-70s │\n" "Made by Lieuwe Huisman"
printf "├────────────────────────────────────────────────────────────────────────┤\n"

mkdir -p "input"
mkdir -p "bin"
mkdir -p "data"

# You might want to change the compiler in the Makefile in the source directory
# as f77 does not work for MacOSX but gfortran does.
bash utils/createbins.sh 1 $NUMBEROFBINS original

echo "#!/bin/bash" > "utils/directories.sh"
echo 'INPUTFOLDER="'$PWD'/input"' >> "utils/directories.sh" 
echo 'DATAFOLDER="'$PWD'/data"' >> "utils/directories.sh"
echo 'BINFOLDER="'$PWD'/bin"'>> "utils/directories.sh"
echo 'MAINFOLDER="'$PWD'"' >> "utils/directories.sh"
echo 'UTILSFOLDER="'$PWD'/utils"' >> "utils/directories.sh"

source $(dirname $0)/utils/directories.sh


printf "├────────────────────────────────────────────────────────────────────────┤\n"
printf "│ Number of Bins   : %-51s │\n" $NUMBEROFBINS
printf "│ Bin Directory    : %-51s │\n" $BINFOLDER
printf "│ Input Directory  : %-51s │\n" $INPUTFOLDER
printf "│ Output Directory : %-51s │\n" $DATAFOLDER
printf "│ Utils Directory  : %-51s │\n" $UTILSFOLDER
printf "│ Main Directory   : %-51s │\n" $MAINFOLDER
printf "╰────────────────────────────────────────────────────────────────────────╯\n"
