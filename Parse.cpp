#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{

  if(argc != 2)
    {
      cerr << "Sorry, need exactly one argument to run this program. " << endl << "This number designates the run number." << endl;
      cerr << "Exiting..." << endl;
      return 0;
    }

  string fileIn = "search.plot";
  string fileIn2 = "om.fro";
  string runNumber = argv[1];
  string run = "run" + runNumber;
  string fileOutData = run + "_data.dat";
  string fileOutTheory = run + "_theory.dat";
  string tempString;
  string tempStringHolder;

  float *angleData = new float[512];
  float *xsecData = new float[512];
  float *errorData = new float[512];

  float *angleTheory = new float[512];
  float *xsecTheory = new float[512];
  float *rutherfordRatio = new float[512];

  for(int i = 0; i < 512; i++)
    {
      angleData[i] = 0;
      xsecData[i] = 0;
      errorData[i] = 0;
      angleTheory[i] = 0;
      xsecTheory[i] = 0;
      rutherfordRatio[i] = 0;
    }
  

  int counterData = 0;
  int counterTheory = 0;
  int rutherCounter = 0;
  int tempCounter = 0;
  
  ifstream fileInput;
  fileInput.open(fileIn.c_str());

  while(!fileInput.eof())
    {
      getline(fileInput, tempString);
      
      if(tempString.size() == 33)
	{
	  istringstream(tempString) >> angleData[counterData] >> xsecData[counterData] >> errorData[counterData];
	  
	  counterData++;
	}

      if(tempString.size() == 21)
	{
	  istringstream(tempString) >> angleTheory[counterTheory] >> xsecTheory[counterTheory];
	  counterTheory++;
	}

      tempString.clear();
    }

  fileInput.close();

  ifstream fileInput2;
  fileInput2.open(fileIn2.c_str());

  while(!fileInput2.eof())
    {
      getline(fileInput2, tempString);

      if(tempString.size() == 59)
	{
	  tempString.erase(0, 49);
	  istringstream(tempString) >> rutherfordRatio[rutherCounter];
	  rutherCounter++;
	  tempString.clear();
	}
    }

  fileInput2.close();

  ofstream fileOutputData;
  fileOutputData.open(fileOutData.c_str());
  
  fileOutputData << "# Angle " << setfill(' ') << setw(8) << "xsec" << setfill(' ') << setw(14) << "error" << endl;
  for(int i = 0; i < counterData; i++)
    {
      fileOutputData << setiosflags(ios::fixed | ios::showpoint | ios::right) << setw(6) << setprecision(3) << angleData[i] << '\t' << setw(10) << xsecData[i] << '\t' << setw(5) << errorData[i] << endl;
    }

  fileOutputData.close();

  ofstream fileOutputTheory;
  fileOutputTheory.open(fileOutTheory.c_str());
  
  fileOutputTheory << "#Angle" << setfill(' ') << setw(25) << "xsec" << setfill(' ') << setw(15) << "/R" << endl;
  for(int i = 0; i < counterTheory; i++)
    {
      fileOutputTheory << setiosflags(ios::fixed | ios::showpoint | ios::right) << setw(7) << setprecision(3) << angleTheory[i] << '\t' << setw(30) << setprecision(7) << xsecTheory[i] << '\t' << setw(10) << rutherfordRatio[i] << endl;
    }

  fileOutputTheory.close();

  delete [] angleData;
  delete [] xsecData;
  delete [] errorData;
  delete [] angleTheory;
  delete [] xsecTheory;
  delete [] rutherfordRatio;

  return 0;
}
