#include <iostream>
#include "headers.hpp"
#include <sys/socket.h>
#include <cstring>
#include <algorithm>

using namespace std;

int Interface(string Command, int socket)
{
  string CMD = Command.substr(0, Command.find(":::"));
  string DATA = Command.substr(Command.find(":::") + 3, Command.length() - Command.find(":::") - 3);
  cout << "HIS: " << Command << "  RECEIVED\n";
  // if (Command == ""){}
  if (CMD == "SCAN_ALL")
  {
    cout << "SCAN ALL\n";
    MyIteraror("/home/egor/Documents/test/test1");
    cout << "Scanning\n";
    MyReader();
    MyIteraror("/home/egor/AV/zip");
    MyReader();
    system("rm -rf /home/egor/AV/zip/");
    system("mkdir /home/egor/AV/zip");
    cout << "SCAN FINISHED\n";
  }
  if (CMD == "SCAN_FILES")
  {
    MyIteraror(DATA);
    cout << "Scanning\n";
    MyReader();
    MyIteraror("/home/egor/AV/zip");
    MyReader();
    system("rm -rf /home/egor/AV/zip/");
    cout << "SCAN FINISHED\n";
  }
  if (CMD == "INFECTED")
  {
    int ln = Command.length();
    char buf[ln];
    strcpy(buf, Command.c_str());
    send(socket, buf, ln, 0);
  }
  if (CMD == "QUART")
  {
    AVQuarantine(DATA);
  }

  if (CMD == "KILL")
  {
    remove(DATA.c_str());
  }
  if (CMD == "NO_INFECTIONS")
  {

    int ln = Command.length();
    char buf[ln];
    strcpy(buf, Command.c_str());
    send(socket, buf, ln, 0);
  }
  if (CMD == "PAUSE")
  {
    cout << "pause";
    scanCallback();
  }
  // Command = "";
  // cout << Command << "  MADE\n";
  cout << socket << "SENDER\n";

  return 0;
}
// FUNCTIONS
// AVKiller(filename);