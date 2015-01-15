#!/bin/bash

DIRECTORY="RawData/run$1/"

if [ "$#" != 1 ]; then
    echo ""
    echo "Invalid number of arguments."
    echo "Exiting. Please try again."
    exit
fi

if [ -d "$DIRECTORY" ]; then
    echo ""
    echo "Run number already exists. Please choose another."
    echo "Exiting..."
    exit
fi

/home/kirby/fresco/source/sfresco.exe < sf.inp > sf.out
./Parse1.exe $1
./PullTitle.exe
TITLE=`cat title`
sh ./PlotData.sh $1 "$TITLE"
mkdir RawData/run$1
mv run$1_*.dat RawData/run$1/
mv run$1_plot.ps Plots/
cp sf.out RawData/run$1/run$1_sf.out
cp om.fro RawData/run$1/run$1_om.fro
cp om.fri RawData/run$1/run$1_om.fri
cp search.in RawData/run$1/run$1_search.in
cp title RawData/run$1/run$1_title
gv Plots/run$1_plot.ps&
