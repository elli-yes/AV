#include <cstdio>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;

// int Answer(char YoN[2])
// {
//   if (YoN == string("Y") || YoN == string("y"))
//   {
//     return 1;
//   }
//   else if (YoN == string("N") || YoN == string("n"))
//   {
//     return 0;
//   }
//   else
//   {
//     Answer(YoN);
//   }
//   return 0;
// }
int AVKiller(char filepath[255])
{
  // char YoN[2];
  // cout << filepath << "\n"
  //      << "DELETE ? Y/N\n";
  // cin >> YoN;
  // if (Answer(YoN))
  // {
  cout << "REMOVE\n";
  remove(filepath);
  // }

  return 0;
}

int coder(string fp)
{
  char buff;
  ifstream fs(fp, ios::binary | ios::ate);
  if (fs.is_open())
  {
    int sz = fs.tellg();
    cout << sz;
    char buff[sz];
    while (!fs.eof())
    {
      fs >> buff;
    }
    cout << buff;
    fs.close();
  }
  return 0;
}
int AVQuarantine(string filepath)
{
  cout << "HEAR";

  coder(filepath);
  // copy(filepath, "/home/egor/AV/Quarantine");
  // remove(filepath);
  return 0;
}