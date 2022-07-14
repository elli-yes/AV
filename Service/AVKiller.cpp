#include <cstdio>
#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>

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
  string nfp = fp;
  while (nfp.find("*") != -1)
  {
    nfp.replace(nfp.find("*"), 1, "/");
  }
  string endpath = "/home/egor/AV/Quarantine/";
  endpath += fp;
  ifstream fs(endpath);
  cout << fp << "TRY OPEN\n";
  if (fs.is_open())
  {
    cout << " OPEN\n";
    ofstream os(nfp);
    while (!fs.eof())
    {
      char x;
      char c;
      fs.get(c);
      os.put(c);
      fs.get(x);
    }
    remove(endpath);
    fs.close();
    os.close();
  }
  return 0;
}
int decode(string fp)
{
  ifstream fs(fp, ios::binary);

  string endpath = "/home/egor/AV/Quarantine/";
  string nfp = fp;

  while (nfp.find("/") != -1)
  {
    nfp.replace(nfp.find("/"), 1, "*");
  }

  endpath += nfp;
  if (fs.is_open())
  {
    ofstream os(endpath);
    char x = 1;
    while (!fs.eof())
    {
      char c;
      fs.get(c);
      os.put(c);
      os.put(x);
    }
    fs.close();
    os.close();
  }
  return 0;
}
int QRESTORE(string filepath)
{
  string endfile;
  endfile = filepath.substr(filepath.find("*"), filepath.length() - filepath.find("*"));
  cout << endfile;
  while (endfile.find("/") != -1)
  {
    endfile.replace(endfile.find("/"), 1, "*");
  }
  coder(endfile);
}
int AVQuarantine(string filepath)
{
  decode(filepath);
  remove(filepath);

  return 0;
}