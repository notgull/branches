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

#include "branches_config.hpp"
#if br_SERVER == 1

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
void runServerPart(branch *root, branch *third_tree, SOCKET connection) {
#else
void runServerPart(branch *root, branch *third_tree, int connection) {
#endif

  string s;
  stringstream motd_file (stringstream::in | stringstream::out);
  ifstream motd_filer ("motd.conf");
  if (motd_filer.is_open())
  {
    while (getline(motd_filer,s)) motd_file << s << '\n';
    motd_filer.close();
  }

  string motd = motd_file.str();
  if (motd.length() != 0 && motd[motd.length() - 1] != '\n')
    motd += "\n";
  say(connection,motd);
  int connected = 1;
  branch *current = root;
  while (connected) {
    string line = readIn(connection);
    if (line.length() != 0 && line[line.length() - 1] == '\n')
      line = line.substr(0,line.length() - 1);
#ifdef DEBUG
    cout << "Received request: " << line << endl;
#endif 
    if (line == "S") {
      connected = 0;
#ifdef DEBUG
         cout << "Disconnecting client..." << endl;
#endif
    } 
    else if (line == "R") {
      branch fkRoot (root->getText1(),root->getText2(),root->getMainText());
      say(connection,fkRoot.toString() + "\n");
#ifdef DEBUG
        cout << "Sending " << fkRoot.toString() << endl;
#endif
    }
    else if (line == "T") {
      if (third_tree) {
        branch fkTTree (third_tree->getText1(),third_tree->getText2(),third_tree->getMainText());
        say(connection,fkTTree.toString() + "\n");
      }
      else
        say(connection,"0\n");
    }
    else if (line == "Q") {
          current = root;
#ifdef DEBUG
        cout << "Returning client pos to 0" << endl;
#endif
    }
    else if (line == "P") {
      if (current->getPrevious() != NULL)
        current = current->getPrevious();
    }
    else if (line == "3") {
      if (current == root) {
        current = third_tree;
      }
    }
    else if (line.find(":") != string::npos) {
      vector<string> arguments = splitString(line,':');
      if (arguments[0] == "N" || arguments[0] == "E") {
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
          if (arguments[0] == "E") {
            branch *original = current;
            branch copy (original->getText1(),original->getText2(),original->getMainText());
            if (original->isEnding())
              copy = branch (original->getMainText());
            output += ":";
            output += copy.toString();
          }
        }
//            cout << "Sending: " << output << endl;
        say(connection,output + "\n");
      }
      else if (arguments[0] == "U") {
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
  int shutdownresult = shutdown(connection,SD_SEND);
  if (shutdownresult == SOCKET_ERROR) {
    fprintf(stderr,"Shutdown failed: %d\n",WSAGetLastError());
    closesocket(connection);
    WSACleanup();
    exit(1);
  }
  closesocket(connection);
#else
  close(connection);
#endif
}

void displayAdminCmds() {
    cout << "List of commands:" << endl;
    cout << "1 - select branch number one" << endl;
    cout << "2 - select branch number two" << endl;
    cout << "3 - select branch number three (only works at root branch)" << endl;
    cout << "r - return to start" << endl;
    cout << "f - replace a node with another node" << endl;
    cout << "d - delete a node" << endl;
    cout << "p - reprints the current node to the console" << endl;
    cout << "s - saves current tree to a file" << endl;
    cout << "v - prints version information" << endl;
    cout << "c - prints change log" << endl;
    cout << "h - list this help menu again" << endl;
    cout << "e - close the server" << endl;
    cout << "Enter the letter and press the Enter key to use the command" << endl;       
}

void adminConsole(branch *root, branch *third_tree) {
  displayAdminCmds();
  branch *current = root;
  int cont = 1;
  while (cont) {
    shell_tx();
    string answer;
    getline(cin,answer);
    switch (answer[0]) {
      case '1':
        if (current->hasBranch1()) {
          if (current->getBranch1()->isEnding()) {
            if ((yesno(0,current->getBranch1()->getMainText() + " Return to beginning?")))
            {
              current = root;
            }
            else {
              cout << "Exiting Branches..." << endl;
              cont = 0;
            }
          }
          current = current->getBranch1();
        }
        else if (yesno(0,"You have reached the end. Would you like to create a new node?")) {
          current->setBranch1(usr_input_branch());
          current = current->getBranch2();
        } 
        brPrint(*current);
        break;
      case '2':
        if (current->hasBranch2()) {
          if (current->getBranch1()->isEnding()) {
            if ((yesno(0,current->getBranch1()->getMainText() + " Return to beginning?")))
            {
              current = root;
            }
            else {
              cout << "Exiting Branches..." << endl;
            }
          }
          current = current->getBranch2();
        }
        else if (yesno(0,"You have reached the end. Would you like to create a new node?")) {
          current->setBranch2(usr_input_branch());
          current = current->getBranch2();
        }
        brPrint(*current);
        break;
      case '3':
        if (current == root) {
          current = third_tree;
          brPrint(*current);
        } else {
          cout << "Not at root branch" << endl;
        }
        break;
      case 'r':
        current = root;
        brPrint(*current);
        break;
      case 'p':
        brPrint(*current);
        break;
      case 'v':
        print_version(1);
        break;
      case 'h':
        displayAdminCmds();
        break;
      case 's':
        if (yesno(0,"Do you really want to save your progress?")) {
          string filename;
          cout << "Enter filename: ";
          getline(cin,filename);
          if (filename[filename.length() - 1] == '\n')
            filename = filename.substr(0,filename.length() - 1);
          ofstream output;
          output.open(filename);
          output << root->toString();
          output.close();
          if (third_tree) {
            output.open(filename + ".thirdtree");
            output << third_tree->toString();
            output.close();
          }
          cout << "Successfully saved file!" << endl;
        }
        break;
      case 'c':
        cout << "New in Branches v" << br_VERSION <<"." << br_REVISION <<"." << br_MINOR_REVISION << "..." << endl;
        cout << br_CHANGELOG;
        break;
      case 'e':
        cout << "Closing server..." << endl;
#ifdef USING_WIN
        closesocket(listener);
        WSACleanup();
#else
        close(listener);
#endif
        exit(0);
        break;
      case 'f':
        if (yesno(0,"Do you really want to replace this node?")) {
          branch *replacement = usr_input_branch();
          branch *previous = current->getPrevious();
          if (previous->getBranch1() == current)
            previous->setBranch1(replacement);
          else
            previous->setBranch2(replacement);
          replacement->setBranch1(current->getBranch1());
          replacement->setBranch2(current->getBranch2());
          current = replacement;
        }
        brPrint(*current);
        break;
      case 'd':
        if (yesno(0,"Do you really want to delete this node?")) {
          branch *previous = current->getPrevious();
          if (previous->getBranch1() == current)
            previous->setBranch1(NULL);
          else
            previous->setBranch2(NULL);
          current = previous;
        }
        brPrint(*current);
        break;
     default:
        cout << "Invalid command, please reenter" << endl;
        break;
    }  
  }
}

int runServer() {
  print_version(0);

#ifdef USING_WIN
  initialize_wininet();
#endif 
 
  branch *root;
  branch *third_tree;
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
    if (!(check_file("default.br.thirdtree"))) {
      temp = stringstream (stringstream::in | stringstream::out);
      myfile = ifstream ("default.br.thirdtree");
      if (myfile.is_open()) {
        while (getline(myfile,line)) temp << line << '\n';
        myfile.close();
      }
      third_tree = brFromString(temp.str());
    }
  }
 
  if (!third_tree) 
    third_tree = new branch("Drop kick it","Stab someone","You pick up the fork");
  branch fkRoot (root->getText1(),root->getText2(),root->getMainText());

  listener = openListenerSocket();
  if (!(yesno(1,"Would you like to use the default configuration?"))) {
    cout << "Enter port to use: ";
    cin >> port;
  }
  cout << "Attempting to open server on port " << port << "..." << endl;
  bindToPort(listener,port);
  cout << "Opening admin console..." << endl;
  thread administrator_console (adminConsole,root,third_tree);
  administrator_console.detach();
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
    shell_tx();
    if (connection == -1)
      error("Unable to open connection socket",1);
#endif
    thread th (runServerPart,root,third_tree,connection);
    th.detach();
  }
#ifdef USING_WIN
  closesocket(listener);
  WSACleanup();
#else
  close(listener);
#endif
  return 0;
}

#endif
