#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, const char* argv[])
{
  string filename;

  if(argc == 2)
    filename = argv[1];
  
  else
    filename = "om.fri";

  string filenameOut = "title";
  string tempString;
  string tempTarget;
  string tempIncident;
  string tempEnergy;
  string finalTitle;
  int tempCounter1 = 0;
  int tempCounter2 = 0;
  int tempCounter3 = 0;
  int tempIndexer = 0;
  ifstream fileInput;
  fileInput.open(filename.c_str());

  getline(fileInput, tempString);

  for(int i = 0; i < tempString.size(); i++)
    {
      if((int)tempString[i] == 40)
	{
	  tempCounter1 = i;
	}

      if((int)tempString[i] == 44)
	{
	  tempCounter2 = i;
	}
      
      if((int)tempString[i] == 41)
	{
	  tempCounter3 = i;
	}
    }

  fileInput.close();
  
  for(int i = 0; i < tempCounter1; i++)
    {
      tempTarget[i] = tempString[i];
    }

  //cout << tempTarget.c_str() << endl;
  
  tempIndexer = 0;
  finalTitle = "^{";
  
  while((int)tempTarget[tempIndexer] >= 48 && (int)tempTarget[tempIndexer] <= 57)
    {
      finalTitle = finalTitle + tempTarget[tempIndexer];
      tempIndexer++;
    }
  
  finalTitle = finalTitle + "}";
  
  while(tempIndexer != tempCounter1)
    {
      finalTitle = finalTitle + tempTarget[tempIndexer];
      tempIndexer++;
    }

  finalTitle = finalTitle + "(";

  //cout << "Final Title: " << finalTitle.c_str() << endl;
  tempString.erase(0,(tempCounter1+1));

  for(int i = 0; i < (tempCounter2-tempCounter1-1); i++)
    {
      tempIncident[i] = tempString[i];
    }
 
  tempIndexer = 0;

  finalTitle = finalTitle + "^{";

  while((int)tempIncident[tempIndexer] >= 48 && (int)tempIncident[tempIndexer] <= 57)
    {
      finalTitle = finalTitle + tempIncident[tempIndexer];
      tempIndexer++;
    }

  finalTitle = finalTitle + "}";

  while(tempIndexer < (tempCounter2-tempCounter1-1))
    {
      finalTitle = finalTitle + tempIncident[tempIndexer];
      tempIndexer++;
    }

  finalTitle = finalTitle + ",^{";

  //cout << finalTitle.c_str() << endl;
  //cout << tempString.c_str() << endl;
  
  tempString.erase(0, (tempCounter2 - tempCounter1));

  tempIndexer = 0;

  while((int)tempIncident[tempIndexer] >= 48 && (int)tempIncident[tempIndexer] <= 57)
    {
      finalTitle = finalTitle + tempString[tempIndexer];
      tempIndexer++;
    }

  finalTitle = finalTitle + "}";
  
   while(tempIndexer < (tempCounter3-tempCounter2-1))
    {
      finalTitle = finalTitle + tempString[tempIndexer];
      tempIndexer++;
    }

   finalTitle = finalTitle + ")^{";

 

  tempString.erase(0, (tempCounter3 - tempCounter2));

  //cout << tempString.c_str() << endl;

  tempIndexer = 0;

   while((int)tempString[tempIndexer] >= 48 && (int)tempString[tempIndexer] <= 57)
    {
      finalTitle = finalTitle + tempString[tempIndexer];
      tempIndexer++;
    }

   //cout << tempString.c_str() << endl;
   finalTitle = finalTitle + "}";
   
   tempString.erase(0, tempIndexer);

   //cout << tempString.c_str() << endl;
   //cout << "Final: " << finalTitle.c_str() << endl;

    finalTitle = finalTitle + tempString;

    //cout << "Final2: " << finalTitle.c_str() << endl;

    ofstream tempOut;
    tempOut.open(filenameOut.c_str());
    
    tempOut << finalTitle.c_str() << endl;

    tempOut.close();

  //cout << tempString << endl;
  //cout << tempTarget.c_str() << " " << tempIncident.c_str() << endl;
  
  //ofstream fileOutput;
  //fileOutput.open(filenameOut.c_str());

  //fileOutput << "^{";
  
  return 0;  
}
