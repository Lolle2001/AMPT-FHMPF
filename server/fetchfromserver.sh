mkdir -p data/$2
sshpass -p $1 scp -r stage@131.211.54.64:~/Documents/AMPT/data/$2/processed data/$2/