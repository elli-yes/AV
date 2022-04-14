#include <stdio.h>
#include "headers.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
using namespace std;

void error(const char *msg)
{
  perror(msg);
  exit(0);
}
int sock;
int serverStart()
{
  char buf[1024];
  int listener;
  struct sockaddr_in addr;
  struct in_addr lh;
  int bytes_read;

  listener = socket(AF_INET, SOCK_STREAM, 0);
  if (listener < 0)
  {
    perror("socket");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // htonl(INADDR_ANY);

  if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    perror("bind");
    exit(2);
  }

  listen(listener, 1);

  while (1)
  {
    sock = accept(listener, NULL, NULL);
    if (sock < 0)
    {
      perror("accept");
      exit(3);
    }
    sleep(3);
    while (1)
    {
      bzero(buf, 256);
      bytes_read = recv(sock, buf, 1024, 0);
      if (bytes_read <= 0)
        break;
      Interface(buf, sock);
      sleep(3);
      // send(sock, buf, bytes_read, 0);
    }
    // sleep(5);
    close(sock);
  }
  return 0;
}
int callback(string str)
{
  cout << sock;
  if (!Interface(str, sock))
  {
    cout << sock;
    return 0;
  }
  cout << "ERROR\n";
  return 1;
}