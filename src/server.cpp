/*
 * =====================================================================================
 *
 *       Filename:  server.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/15/2017 06:51:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================

This file is part of Branches.

Branches is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Branches is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Branches.  If not, see <http://www.gnu.org/licenses/>.

 */

#include "server.hpp"
#include "branch.hpp"
#include "inet_cxx.hpp"
#include "err.hpp"
#include "shortcuts.hpp"
#include "program.hpp"
#include "splitstr.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>

#include "iswin.hpp"
#ifdef USING_WIN
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
using namespace std;

int port = 32001;
#ifdef USING_WIN
SOCKET listener;
#else
int listener;
#endif

string name = "BRANCHES BETA SERVER";
int nextId = -1;

string removeReturnFrom(string line) {
  int offset = 0;
  if (line[line.length() - 1] == '\n')
  {
    offset += 1;
    if (line[line.length() - 2] == '\r')
      offset += 1;
  }
  return line.substr(0,line.length() - offset);
}

#ifdef USING_WIN
void runServerPart(branch *root, SOCKET connection) {
#else
void runServerPart(branch *root, int connection) {
#endif
  string motd = "Welcome to " + name + "!";
  say(connection,motd + "\n");
  int connected = 1;
  branch *current = root;
  while (connected) {
    string line = readIn(connection);
    if (line.length() != 0 && line[line.length() - 1] == '\n')
      line = line.substr(0,line.length() - 1);
#ifdef DEBUG
    cout << "Received request: " << line << endl;
#endif 
    if (line == "STOP_REQ") {
      connected = 0;
#ifdef DEBUG
         cout << "Disconnecting client..." << endl;
#endif
    } 
    else if (line == "ROOT_REQ") {
      branch fkRoot (root->getText1(),root->getText2(),root->getMainText());
      say(connection,fkRoot.toString() + "\n");
#ifdef DEBUG
        cout << "Sending " << fkRoot.toString() << endl;
#endif
    }
    else if (line == "RETURN_REQ") {
          current = root;
#ifdef DEBUG
        cout << "Returning client pos to 0" << endl;
#endif
    }
    else if (line.find(":") != string::npos) {
      vector<string> arguments = splitString(line,':');
      if (arguments[0] == "NAV_REQ" || arguments[0] == "SEND_REQ") {
        int brn = atoi(arguments[1].c_str());
#ifdef DEBUG
          cout << "Identified brn as " << brn << endl;
#endif
        int unable = 0;
        if (brn == 1) {
          if (current->hasBranch1())
            current = current->getBranch1();
          else
            unable = 1;
        }
        if (brn == 2) {
          if (current->hasBranch2())
            current = current->getBranch2();
          else
            unable = 1;
        }
          
        string output;
        if (unable)
          output = "1";
        else  {
          output = "0";
          if (arguments[0] == "SEND_REQ") {
            branch *original = current;
            branch copy (original->getText1(),original->getText2(),original->getMainText());
            output += ":";
            output += copy.toString();
          }
        }
#ifdef DEBUG
            cout << "Sending: " << output << endl;
#endif
        say(connection,output + "\n");
      }
      else if (arguments[0] == "UPLOAD_REQ") {
        int brn = atoi(arguments[1].c_str());
#ifdef DEBUG
          cout << "brn determined to be " << brn << endl;
#endif 
        branch *newBranch = brFromString(arguments[2]);
#ifdef DEBUG
          cout << "Received branch: " << newBranch->toString() << endl;
#endif
        if (brn == 1) {
          if (!(current->hasBranch1()))
            current->setBranch1(newBranch);
          current = current->getBranch1();
        }
        else if (brn == 2) {
          if (!(current->hasBranch2()))
            current->setBranch2(newBranch);
          current = current->getBranch2();
        }
                  
      }
    }
    else {
      cout << "Improper symbol, closing connection..." << endl;
      connected = 0;
    }
  }
#ifdef USING_WIN
  closesocket(connection);
#else
  close(connection);
#endif
}

int runServer() {
  print_version(0);

#ifdef USING_WIN
  initialize_wininet();
#endif 
 
  branch *root;
  if (check_file("default.br")) {
    // initial branch
    root = new branch("Take the left path", "Take the right path", "You come across a fork in the road.");
    branch *br1;
    branch *br2;
 
    // other two branches
    br1 = new branch("Knock on the door","Peer through the window","You come across a house on the prarie.");
    br2 = new branch("Cross the bridge","Jump into the water","You come across a bridge crossing a river.");
    root->setBranch1(br1);
    root->setBranch2(br2);
  }
  else {
    string line;
    stringstream temp (stringstream::in | stringstream::out);
    ifstream myfile ("default.br");
    if (myfile.is_open())
    {
      while ( getline (myfile,line) )
      {
        temp << line << '\n';
      }
      myfile.close();
    }
    root = brFromString(temp.str());
  }
  
  branch *third_tree = new branch("Drop kick it","Stab someone","You pick up the fork");
  branch fkRoot (root->getText1(),root->getText2(),root->getMainText());

  listener = openListenerSocket();
  if (!(yesno(1,"Would you like to use the default configuration?"))) {
    cout << "Enter port to use: ";
    cin >> port;
  }
  cout << "Attempting to open server on port " << port << "..." << endl;
  bindToPort(listener,port);
#ifdef USING_WIN
  if (listen(listener,30) == SOCKET_ERROR)
  {
    fprintf(stderr,"Unable to listen: %ld\n",WSAGetLastError());
    closesocket(listener);
    WSACleanup();
    return 1;
  }
#else
  if (listen(listener,30) == -1)
    error("Unable to listen",1);
#endif
  struct sockaddr_storage clientAddr;
  unsigned int addressSize = sizeof(clientAddr);
  cout << "Waiting for connection..." << endl;
  while (1) {
#ifdef USING_WIN
    SOCKET connection = accept(listener,NULL,NULL);
    if (connection == INVALID_SOCKET) {
      fprintf(stderr,"Unable to accept connection: %d\n",WSAGetLastError());
      closesocket(listener);
      WSACleanup();
      return 1;
    }
#else
    int connection = accept(listener,(struct sockaddr *)&clientAddr,&addressSize);
    cout << "Accepted connection" << endl;
    if (connection == -1)
      error("Unable to open connection socket",1);
#endif
    thread th (runServerPart,root,connection);
    th.detach();
  }
  return 0;
}
