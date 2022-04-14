#include "headers.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

string toBase(unsigned i, unsigned base)
{
  const string DIGITS = "0123456789ABCDEF";
  return i ? toBase(i / base, base) + DIGITS[i % base] : "";
}

int content(char buff[255])
{
  // cout << buff;
  string filename = buff;
  unsigned base = atoi("16");

  const int LINELENGTH = 10;

  int width = toBase(255, base).size();
  char c;
  int counter = 0;

  ifstream in(filename, ios::binary);
  // cout << "\nFILE:  ";
  // cout << filename << "NEGR\n";

  string fileSig;
  while (in.get(c))
  {
    fileSig += toBase((unsigned)c, base);
    counter++;
  }

  AVSearch(fileSig, buff);

  in.close();
  return 0;
}
vector<string> VIRUSES_MAIN;

int rdCallback(vector<string> vector)
{
  for (string v : vector)
  {
    VIRUSES_MAIN.push_back(v);
  }
}
int MyReader()
{
  VIRUSES_MAIN.clear();

  char buff[255];
  string check;
  ifstream file("/home/egor/AV/files.txt");

  while (!file.eof())
  {
    file >> buff;
    // cout << buff << " SCAN\n";

    content(buff);
  }
  file.close();
  string cmd = "INFECTED:::";
  int k = 0;
  if (VIRUSES_MAIN.size() != 0)
  {
    for (string v : VIRUSES_MAIN)
    {
      k++;
      cmd += v;
      if (k != VIRUSES_MAIN.size())
      {
        cmd += ":";
      }
    }
    callback(cmd);
    return 0;
  }

  callback("NO_INFECTIONS:::");
  return 0;
}