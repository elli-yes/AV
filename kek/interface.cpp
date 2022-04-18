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
  // cout << "HIS: " << Command << "  RECEIVED\n";
  // if (Command == ""){}
  if (CMD == "SCAN_ALL")
  {
    cout << "SCAN ALL\n";
    MyIteraror("/home/egor/", 0);
    cout << "Scanning\n";
    MyReader();
    MyIteraror("/home/egor/AV/zip", 0);
    MyReader();
    MyIteraror("/home/egor/AV/zipPas", 1);
    MyReader();
    system("rm -rf /home/egor/AV/zip/");
    system("rm -rf /home/egor/AV/zipPas/");

    system("mkdir /home/egor/AV/zip");
    system("mkdir /home/egor/AV/zipPas");

    cout << "SCAN FINISHED\n";
  }
  if (CMD == "SCAN_FILES")
  {
    cout << "SCAN FILES AT" << DATA << "\n";
    MyIteraror(DATA, 0);
    MyReader();
    cout << "FILES_END\n";

    printf("SCAN ZIPS\n");
    MyIteraror("/home/egor/AV/zip", 0);
    MyReader();
    cout << "ZIP_END\n";

    // printf("SCAN ZIPS PAS\n");
    // MyIteraror("/home/egor/AV/zipPas", 1);
    // MyReader();
    // cout << "ZIPPAS_END\n";

    system("rm -rf /home/egor/AV/zip/");
    // system("rm -rf /home/egor/AV/zipPas/");

    system("mkdir /home/egor/AV/zip");
    // system("mkdir /home/egor/AV/zipPas");

    cout << "SCAN FINISHED---------------->\n";
  }
  if (CMD == "INFECTED")
  {
    Command += "<>";
    int ln = Command.length();
    char buf[ln];
    bzero(buf, ln);
    strcpy(buf, Command.c_str());
    send(socket, buf, ln, 0);
  }
  if (CMD == "QUART")
  {
    cout << "GET_Q\n";
    AVQuarantine(DATA);
  }

  if (CMD == "KILL")
  {
    remove(DATA.c_str());
  }
  if (CMD == "Q_DEL")
  {
    remove(DATA.c_str());
  }
  if (CMD == "Q_RES")
  {
    QRESTORE(DATA.c_str());
  }
  if (CMD == "NO_INFECTIONS")
  {

    int ln = Command.length();
    char buf[ln];
    bzero(buf, ln);
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
  // cout << socket << "SENDER\n";

  return 0;
}
// FUNCTIONS
// AVKiller(filename);