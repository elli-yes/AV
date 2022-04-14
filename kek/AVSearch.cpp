#include "headers.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <zlib.h>
#include <cstring>

using namespace std;

bool PAUSE = 0;
void scanCallback()
{
  if (PAUSE)
  {
    cout << PAUSE << "CHANGED";
    PAUSE = 0;
  }
  else
  {
    cout << "CHANGED";
    PAUSE = 1;
  }
}
int AVScanFile(string VS, string FS)
{
  // while (PAUSE)
  // {
  //   sleep(5);
  // }

  int result = FS.find(VS);
  if (result != -1)
  {
    return 1;
  }
  return 0;
}

int AVSearch(string fileSig, char filename[255])
{
  char fname[255];
  strcpy(fname, filename);
  cout << "VALIDATION\n";
  vector<string> VIRUSES;
  fstream MFD("/home/egor/AV/logs.txt", ios_base::app);
  // cout << strcat(filename, "  SCANNED\n") << "\n";
  // cout < < < < "\n";

  MFD.write(strcat(filename, "  SCANNED\n"), string(strcat(filename, "  SCANNED\n")).length());
  MFD.close();

  string buff;
  ifstream db("/home/egor/AV/base/main.ndb");
  while (!db.eof())
  {
    string VName;
    string VSignature;
    db >> buff;
    VName = buff.substr(0, buff.find(":"));
    VSignature = buff.substr(buff.find(":") + 1, buff.length());
    if (AVScanFile(VSignature, fileSig))
    {
      string virus;
      virus += fname;
      VIRUSES.push_back(virus);
    };
  }
  cout << "DONE\n";

  db.close();
  if (VIRUSES.size() != 0)
  {
    rdCallback(VIRUSES);
  }
  return 0;
}