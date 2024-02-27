#!/bin/bash
# scp -r include stage@131.211.54.64:~/Documents/AMPT/
# scp -r src stage@131.211.54.64:~/Documents/AMPT/
# scp -r main stage@131.211.54.64:~/Documents/AMPT/
scp -r utils stage@131.211.54.64:~/Documents/AMPT/
scp -r input stage@131.211.54.64:~/Documents/AMPT/
# scp ampt.job stage@131.211.54.64:~/Documents/AMPT/
# scp rampt.sh stage@131.211.54.64:~/Documents/AMPT/
# scp Makefile stage@131.211.54.64:~/Documents/AMPT/
scp server/directories.sh stage@131.211.54.64:~/Documents/AMPT/utils/
scp ampt.job stage@131.211.54.64:~/Documents/AMPT/
scp test.job stage@131.211.54.64:~/Documents/AMPT/

