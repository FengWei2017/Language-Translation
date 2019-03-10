#!/bin/sh

if [ -f Romeo_English ]
then
    rm Romeo_leet 
    rm Romeo_English
    rm difference
fi
cd etol/
make
./run <../Romeo >../Romeo_leet
make clean
cd ../ltoe
make 
./run <../Romeo_leet >../Romeo_English
make clean
cd ..
diff Romeo Romeo_English >difference 
if [ -s difference ]
then 
    echo "Erro"
else
    echo "Great"
fi
