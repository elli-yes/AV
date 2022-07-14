#include "headers.hpp"
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
  // if (system("systemctl status AVService | grep 'dead'") == 0)
  // {
  //   system("systemctl start AVService");
  // };

  cout << "START\n";
  serverStart();
  return 0;
}
