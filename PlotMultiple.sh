#!/bin/bash

if [ $# -le 1 ];
  then
    echo "Invalid number of arguments. Exiting."
    exit
fi

if [[ $1 != *x* ]] && [[ $1 != *X* ]] && [[ $1 != *r* ]] && [[ $1 != *R* ]]
    then
    echo "Invalid parameter. Need \"x\" or \"r\" as first argument"
    echo "x: Denotes cross-section for plot"
    echo "r: Denotes ratio to Rutherford for plot"
    echo "Exiting..."
    exit
fi


m=$2
i=2
j=$#+1
while [[ $i -le $j ]]; do
    cp RawData/run$m/*_theory.dat ./
    cp RawData/run$m/*_om.fri ./
    ./PullTitle.exe run"$m"_om.fri
    mv title run"$m"_title
    if [ $i -eq 2 ] 
    then
	m=$3
    fi

    if [ $i -eq 3 ] 
    then
	m=$3
    fi

    if [ $i -eq 4 ] 
    then
	m=$4
    fi

    if [ $i -eq 5 ]
    then
	m=$5
    fi

    if [ $i -eq 6 ]
    then
	m=$6
    fi

    if [ $i -eq 7 ]
    then
	m=$7
    fi

    if [ $i -eq 8 ]
    then
	m=$8
    fi

    if [ $i -eq 9 ]
    then
	m=$9
    fi

    if [ $i -eq 10 ]
    then
	m=${10}
    fi
    let i=i+1
done

./MultiPlotScript.exe $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10}
sh ./MultiPlot.sh
FILE=`cat temp.cat`
mv $FILE Plots/
gv Plots/$FILE &
rm temp.cat

while [ $i -le $# ]; do
    rm run"$m"_theory.dat
    rm run"$m"_om.fri 
    rm run"$m"_title
    if [ $i -eq 2 ] 
    then
	m=$3
    fi

    if [ $i -eq 3 ] 
    then
	m=$3
    fi

    if [ $i -eq 4 ] 
    then
	m=$4
    fi

    if [ $i -eq 5 ]
    then
	m=$5
    fi

    if [ $i -eq 6 ]
    then
	m=$6
    fi

    if [ $i -eq 7 ]
    then
	m=$7
    fi

    if [ $i -eq 8 ]
    then
	m=$8
    fi

    if [ $i -eq 9 ]
    then
	m=$9
    fi

    if [ $i -eq 10 ]
    then
	m=${10}
    fi
    let i=i+1
done
