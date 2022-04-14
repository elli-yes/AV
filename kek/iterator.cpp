#include "headers.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <filesystem>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
using namespace std::filesystem;

#include <typeinfo>
void cleaner()
{
  ofstream ofs;
  ofs.open("/home/egor/AV/files.txt", std::ofstream::out | std::ofstream::trunc);
  ofs.close();
  ofstream ofs1;
  ofs1.open("/home/egor/AV/logs.txt", std::ofstream::out | std::ofstream::trunc);
  ofs1.close();
}
int AVWriter(vector<path> subdirs)
{
  cout << "WRITE DIRS\n";

  fstream file("/home/egor/AV/files.txt");
  int k = 0;
  for (path n : subdirs)
  {
    k++;
    file.write(n.c_str(), n.string().length());
    if (k != subdirs.size())
    {
      file.write("\n", 1);
    }
  };
  file.close();
  return 0;
}

int MyIteraror(string directory, bool pass)
{
  cout << "CREATE DIRS\n";

  fstream tru(directory);
  if (tru.is_open())
  {
    cleaner();
    tru.close();
    vector<path> dir;
    dir.push_back(directory);
    for (path n : dir)
    {
      cout << n << "\n";
      if (n.extension() == ".zip")
      {
        path p("/");
        p /= n.relative_path();
        char pt[255];
        strcpy(pt, p.c_str());
        // cout << "\n\n"
        //      << pt << "\n\n";
        if (pass)
        {
          AVZipPas(pt);
        }
        else
        {
          AVZip(pt);
        }
      }
    }
    AVWriter(dir);
    return 0;
  }

  recursive_directory_iterator begin(directory);
  recursive_directory_iterator end;

  vector<path> subdirs;

  copy_if(begin, end, back_inserter(subdirs), [](const path &path)
          { return !is_directory(path); });
  cleaner();
  cout << "SCAN ZIPS\n";

  for (path n : subdirs)
  {
    cout << n << "\n";
    if (n.extension() == ".zip")
    {
      path p("/");
      p /= n.relative_path();
      char pt[255];
      strcpy(pt, p.c_str());
      // cout << "\n\n"
      //      << pt << "\n\n";
      if (pass)
      {
        AVZipPas(pt);
      }
      else
      {
        AVZip(pt);
      }
    }
  }
  cleaner();
  AVWriter(subdirs);

  return 0;
}