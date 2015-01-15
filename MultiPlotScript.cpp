#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

void OutputScript(string &ylabel, string &ycolumn, string *colors, const char *argv[], int &argc);
void ReadTitle(int index, const char *argv[], string &title);

int main(int argc, const char* argv[])
{
  string colorsName[10] = {"red","blue","chocolate","darkgreen","lime","cornflowerblue","firebrick","fuchsia","saddlebrown","orchid"};
  string colors[10] = {"#FF0000","#0000FF","#D2691E","#006400","#00FF00","#6495ED","#B22222","#FF00FF","#8B4513","#DA70D6"};
  string ylabel;
  string ycolumn = argv[1];
  //cerr << argc << endl;
  if(argc > 11 || argc < 2)
    {
      cerr << "Invalid number of arguments. This program takes 9 run numbers at most," << endl;
      cerr << "Though more than 2" << endl;
      cerr << "Exiting..." << endl;
      return 0;
    }

  if(ycolumn == "R" || ycolumn == "r")
    {
      ylabel = "set ylabel \"{/Symbol s}/{/Symbol s}_{R}\" ";
    }

  else if(ycolumn == "X" || ycolumn == "x")
    {
      ylabel = "set ylabel \"d{/Symbol s}/d{/Symbol W} (mb/sr)\" ";
    }

  else if(ycolumn != "X" || ycolumn != "x" || ycolumn != "R" || ycolumn != "r")
    {
      cerr << "Invalid first argument. Exiting..." << endl;
      cerr << argv[1] << endl;
      return 0;
    }

  OutputScript(ylabel, ycolumn, colors, argv, argc);
 
  return 0;
}

void OutputScript(string &ylabel, string &yColumnChoice, string *colors, const char *argv[], int &argc)
{
  string outputFile = "MultiPlot.sh";
  string outputPlotName = "";
  string outputTemp = "temp.cat";
  string tempString;
  string tempStringShort;
  string temper = "";
  string title = "";
  int ycolumn = 0;
  
  if(yColumnChoice == "x" || yColumnChoice == "X")
    ycolumn = 2;
  if(yColumnChoice == "r" || yColumnChoice == "R")
    ycolumn = 3;
  
  for(int i = 2; i < argc; i++)
    {
      temper = argv[i];
      tempString = "run" + temper + "_";
      outputPlotName += tempString;
    }
  outputPlotName.append("plot.ps");
  tempString.clear();
  ofstream outputScript;
  outputScript.open(outputFile.c_str());

  outputScript << "#!/bin/sh" << endl;
  outputScript << "gnuplot -persist << PLOT" << endl;
  outputScript << "##### Normal Gnuplot Commands" << endl;
  outputScript << "set terminal postscript color enhanced" << endl;
  outputScript << "set output \"" << outputPlotName << "\"" << endl;
  outputScript << "set xlabel \"{/Symbol q}_{c.m.} (Deg.)\"" << endl;
  outputScript << ylabel << endl;
  outputScript << "set title \"Combined Overlay Plot\"" << endl;
  outputScript << "set logscale y" << endl;
  if(yColumnChoice == "x" || yColumnChoice == "X")
    {
      outputScript << "set yrange [0.001:10000]" << endl;
    }
  temper = argv[2];
  tempStringShort = "run" + temper;
  tempString = tempStringShort + "_theory.dat";
  ReadTitle(2,argv,title);
  outputScript << "plot \"" << tempString << "\" using 1:" << ycolumn << " with lines linecolor rgb \"" << colors[0] << "\" title ";
  outputScript << "\"" << title << "\", ";
  for(int i = 3; i < argc-1; i++)
    {
      ReadTitle(i,argv,title);
      temper = argv[i];
      tempStringShort = "run" + temper;
      tempString = tempStringShort + "_theory.dat";
      outputScript << "\"" << tempString << "\"" << " using 1:" << ycolumn << " with lines linecolor rgb \"" << colors[i-2] << "\" title ";
      outputScript << "\"" << title << "\", ";
    }
  ReadTitle((argc-1),argv,title);
  temper = argv[argc-1];
  tempStringShort = "run" + temper;
  tempString = tempStringShort + "_theory.dat";
  outputScript << "\"" << tempString << "\"" << " using 1:" << ycolumn << " with lines linecolor rgb \"" << colors[argc-2] << "\" title ";
  outputScript << "\"" << title << "\"" << endl;
  outputScript << "exit" << endl;
  outputScript << "##### End Gnuplot Commands" << endl;
  outputScript << "PLOT" << endl;
  outputScript.close();

  ofstream outputTitle;
  outputTitle.open(outputTemp.c_str());
  outputTitle << outputPlotName;
  outputTitle.close();

  return;
}

void ReadTitle(int index, const char *argv[], string &title)
{
  string runNumber = argv[index];
  string titleFile = "run" + runNumber + "_title";
  string tempString = "";
  ifstream titleIn;
  titleIn.open(titleFile.c_str());
  getline(titleIn,title);
  titleIn.close();
  return;
}
