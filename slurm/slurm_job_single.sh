#!/bin/bash
#SBATCH --job-name=ampt_job        # Job name
#SBATCH --nodes=1                  # Number of nodes
#SBATCH --ntasks-per-node=1        # Number of tasks (MPI processes) per node
#SBATCH --cpus-per-task=1          # Number of CPU cores per task
#SBATCH --output=ampt_%j_%2t.out   # Standard output log file
#SBATCH --error=ampt_%j_%2t.err    # Standard error log file

# Set up environment and load modules if needed
# source /path/to/environment/setup.sh

# Set variables
I=$1
BINID=$2
RUNNUMBER=$3
RANDOM_ISEEDP=1

# Set up directories

source $(dirname $0)/timer.sh
source $(dirname $0)/directories.sh


# Random seed generation
if [ $RANDOM_ISEEDP -eq 1 ]; then
    RAND=$(( ($RANDOM % 100000000 ) + 1 ))
    sed -i "30s/.*/${RAND}/" "$BINFOLDER/ampt_$BINID/input.ampt"
fi

# Copy input file to data folder
cp "$BINFOLDER/ampt_$BINID/input.ampt" "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I/input.par"

# Change directory
cd "$BINFOLDER/ampt_$BINID"

# Create necessary directories
mkdir -p "ana"
mkdir -p "ana1"

# Record start time
STARTDATE=$(date +"%Y-%m-%d %H:%M:%S")
echo "Job $I started at: $STARTDATE"

# Run simulation
nrandom=$(date '+%d%H%M%S')
echo $nrandom > nseed
./ampt < nseed 1> "$RUNNUMBER""_""$I.log" 2> "$RUNNUMBER""_""$I.err"

# Record end time
ENDDATE=$(date +"%Y-%m-%d %H:%M:%S")
echo "Job $I finished at: $ENDDATE"

# Calculate duration
STARTDATE_S=$(date -d "$STARTDATE" +%s)
ENDDATE_S=$(date -d "$ENDDATE" +%s)
DURATION=$((ENDDATE_S - STARTDATE_S))

# Print duration
echo "Job $I finished in: $DURATION seconds"

# Save duration to file
echo "$DURATION" > "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I.time"

# Return to main folder
cd "$SLURM_SUBMIT_DIR"
