/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/14/2017 09:29:47 AM
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

#include "err.hpp"
#include "shortcuts.hpp"
#include "program.hpp"
#include "inet_cxx.hpp"
#include "splitstr.hpp"
#include "branches_config.hpp"
#include "iswin.hpp"
#include "bscript.hpp"

#include <stdio.h>
#include <stdlib.h>
#ifdef USING_WIN
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

#define INPUT_MAX_SIZE 256
#ifndef USING_WIN
#define INVALID_SOCKET -1
#endif

// prints version information
void print_version(int verbose) {
  if (!verbose)
    cout << "====== Welcome to Branches v" << br_VERSION << "." << br_REVISION << "." << br_MINOR_REVISION << " ======" << endl;
  else
    cout << "You are using: Branches Version " <<  br_VERSION << " Revision " << br_REVISION << " Minor Revision " << br_MINOR_REVISION << endl;
}

void print_license() {
  cout << "Branches, an expandable choose-your-own-adventure game" << endl;
  cout << "Copyright (C) 2017  John Nunley" << endl << endl;

  cout << "This program is free software: you can redistribute it and/or modify" << endl;
  cout << "it under the terms of the GNU General Public License as published by" << endl;
  cout << "the Free Software Foundation, either version 3 of the License, or" << endl;
  cout << "(at your option) any later version." << endl << endl;

  cout << "This program is distributed in the hope that it will be useful," << endl;
  cout << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << endl;
  cout << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << endl;
  cout << "GNU General Public License for more details." << endl << endl;

  cout << "You should have received a copy of the GNU General Public License" << endl;
  cout << "along with this program.  If not, see <http://www.gnu.org/licenses/>." << endl;
}

// prints help menu
void print_cmds() {
  cout << "List of commands:" << endl;
  cout << "1 - select branch number one" << endl;
  cout << "2 - select branch number two" << endl;
  cout << "r - return to start" << endl;
  cout << "o - go backwards by one node" << endl;
  cout << "p - reprints the current node to the console" << endl;
  cout << "s - saves current tree to a file" << endl;
  cout << "a - reads new tree from a file" << endl;
  cout << "b - opens bscript commands" << endl;
  cout << "v - prints version information" << endl;
  cout << "c - prints change log" << endl;
  cout << "h - list this help menu again" << endl;
  cout << "e - exit the game" << endl;
  cout << "Enter the letter and press the Enter key to use the command" << endl;
}

// make a new branch from user input
branch *usr_input_branch() {
/*char main_text[INPUT_MAX_SIZE];
  char b1[INPUT_MAX_SIZE];
  char b2[INPUT_MAX_SIZE];
  char response[4];
  char dummy[4];*/

  string main_text;
  string b1;
  string b2;
  char response[4];

  do {
    newline();
    /*
    printf("Enter main text: ");
    //scanf("%s",main_text);
    fgets(main_text,INPUT_MAX_SIZE,stdin);
    if ((strlen(main_text)>0) && (main_text[strlen (main_text) - 1] == '\n'))
        main_text[strlen (main_text) - 1] = '\0';

    printf("Enter Option 1: ");
    //scanf("%s",b1);
    fgets(b1,INPUT_MAX_SIZE,stdin);
    if ((strlen(b1)>0) && (b1[strlen (b1) - 1] == '\n'))
        b1[strlen (b1) - 1] = '\0';

    printf("Enter Option 2: ");
    //scanf("%s",b2);
    fgets(b2,INPUT_MAX_SIZE,stdin);
    if ((strlen(b2)>0) && (b2[strlen (b2) - 1] == '\n'))
        b2[strlen (b2) - 1] = '\0';
    */
    cout << "Enter Main Text: ";
    getline(cin,main_text);
    cout << "Enter Option 1: ";
    getline(cin,b1);
    cout << "Enter Option 2: ";
    getline(cin,b2);
    newline();
    cout << "Here is your branch:" << endl;
    newline();
    branch *br = new branch(b1,b2,main_text);
    //branch br = brCreate("test","test",main_text);
    brPrint(*br);
    if (yesno(0,"Is this okay?")) {
      newline();
      return br;
    }
  } while (1); 
  // inaccessible code
  error("Inaccessible code",0);
  // even more inaccessible code
  return new branch("","","");
}

// net variables and functions
#ifdef USING_WIN
SOCKET connection = INVALID_SOCKET;
#else
int connection = -1;
#endif
int alreadyHaveIPandPort = 0;
string ipAddr;
string portAddr;
string defaultServerIP = "0.0.0.0";
string defaultServerPort = "32001";

string id;

string dummy_geturl;

// program entry point
int runProgram() {
  // introduce the help menu and version info
  print_version(0);
  newline();
  print_license();
  newline();

  cout << "Select mode:" << endl;
  char cmd[5];
  int thing = 1;
  do {
    cout << "-1: Singleplayer Mode" << endl;
    cout << "-2: Connect to TBranches Server" << endl;
    cout << "-3: Connect to other server" << endl;
    newline();
    shell_tx();
    scanf("%4s",cmd);
    switch (cmd[0]) {
      case 'e':
        cout << "Exiting branches..." << endl;
        return 0;
      case '1':
	thing = 0;
	break;
      case '3':
        thing = 0;
        getline(cin,dummy_geturl);
        cout << "Enter IP Address: ";
        getline(cin,ipAddr);
        if (ipAddr.find(":") !=  string::npos) {
          vector<string> parts = splitString(ipAddr,':');
          ipAddr = parts[0];
          portAddr = parts[1]; 
        }
        else {
          cout << "Enter port: ";
          getline(cin,portAddr);
        }
        alreadyHaveIPandPort = 1;
      case '2': {
        thing = 0;
        if (!(alreadyHaveIPandPort)) {
          ipAddr = defaultServerIP;
          portAddr = defaultServerPort;
        }
        cout << "Connecting to " << ipAddr << ":" << portAddr << "..." << endl;
        thing = 0;
#ifdef USING_WIN
        initialize_wininet();
#endif
        connection = openSocket(ipAddr,portAddr);
        string motd = readIn(connection);
        cout << motd;
        /*cout << "Saying: ID_REQ" << endl;
        say(connection,"ID_REQ");
        id = readIn(connection);
        cout << "Got ID: " << id << endl;*/
        break;
      }
      default:
        cout << "Invalid command" << endl;
        shell_tx();
	scanf("%4s",cmd);
	break;
    }
  } while (thing);
  newline();
  print_cmds();
  newline();
  
  branch *root;
  branch *third_tree;
  if (connection == -1) {
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
        while (getline(myfile,line))
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
  }
  else {
    say(connection,"ROOT_REQ\n");
    string rootString = readIn(connection);
    if (rootString.length() != 0 && rootString[rootString.length() - 1] == '\n')
      rootString = rootString.substr(0,rootString.length() - 1);
    //cout << "Received: " << rootString << endl;
    root = brFromString(rootString);
    say(connection,"TTREE_REQ\n");
    string result_thirdtree = readIn(connection);
    if (result_thirdtree.length() != 0 && result_thirdtree[0] != '0') {
      if (result_thirdtree[result_thirdtree.length() - 1] == '\n')
        result_thirdtree = result_thirdtree.substr(0,result_thirdtree.length() - 1);
      third_tree = brFromString(result_thirdtree);
    }
  }
  brPrint(*root);
 
  if (!third_tree) 
    third_tree = new branch("Drop kick it","Stab someone","You pick up the fork");

  // keep track of numbers for bscript
  vector<int> path (0);
  
  // current branch
  branch *current = root;
  branch *previous = NULL;
  
  // don't use loop.h for this; loop.h is needed for inner loops
  // this is the main loop
  int cont = 1;
  
  while (cont) {
    // this makes the > thing
    shell_tx();
    // get the command
    scanf("%s",cmd); 

    // main switch statement
    switch (cmd[0]) {
      case 'e':
        // user wants to exit the game
        printf("Exiting Branches...\n");
	cont = 0;
        if (connection != INVALID_SOCKET)
          say(connection,"STOP_REQ\n");
	break;
      case 'v':
        // print verbose game information
        print_version(1);
	break;
      case 'h':
        // reprint help information
        print_cmds();
	break;
      case '2':
        if (current->hasBranch2()) {
          previous = current;
          current = current->getBranch2();
          if (connection != INVALID_SOCKET) {
#ifdef DEBUG
            cout << "Sending NAV_REQ:2 to the server" << endl;
#endif
            say(connection,"NAV_REQ:2\n");
            string input = readIn(connection);
#ifdef DEBUG
            cout << "Received result " << input << endl;
#endif
          }
          path.push_back(2);
        }
	else {
          if (connection != INVALID_SOCKET) {
#ifdef DEBUG
            cout << "Sending SEND_REQ:2 to the server" << endl;
#endif
            say(connection,"SEND_REQ:2\n");
            string newBranch = readIn(connection);
            if (newBranch.length() != 0 && newBranch[0] == '0') {
              if (newBranch[newBranch.length() - 1] == '\n')
                newBranch = newBranch.substr(0,newBranch.length() - 1);
              string actualBranch = (splitString(newBranch,':'))[1];
#ifdef DEBUG
              cout << "Received: " << actualBranch << endl;
#endif 
              branch *newBranchPtr = brFromString(actualBranch);

              current->setBranch2(newBranchPtr);
              current = current->getBranch2();
              path.push_back(2);
              brPrint(*current);
              break;
            } 
          }
	  if (yesno(0,"You have reached the end. Would you like to create a new node?")) {
	    branch *br = usr_input_branch();
            previous = current;
	    current->setBranch2(br);
            path.push_back(2);
	    current = br;
            if (connection != INVALID_SOCKET) {
#ifdef DEBUG
              cout << "Sending UPLOAD_REQ:2:" << current->toString() << endl;
#endif
              say(connection,"UPLOAD_REQ:2:" + current->toString() + '\n');
            }
	  }
	  else {
	    current = root;
            path.clear();
            if (connection != INVALID_SOCKET)
              say(connection,"RETURN_REQ\n");
          }
	}
	brPrint(*current);
	break;
      case '1':
        if (current->hasBranch1()) {
          previous = current;
          current = current->getBranch1();
          path.push_back(1);
          if (connection != INVALID_SOCKET) {
#ifdef DEBUG
            cout << "Sending NAV_REQ:1 to the server" << endl;
#endif
            say(connection,"NAV_REQ:1\n");
            string input = readIn(connection);
#ifdef DEBUG
            cout << "Received result " << input << endl;
#endif
          }
        }
	else {
          if (connection != INVALID_SOCKET) {
#ifdef DEBUG
            cout << "Sending SEND_REQ:1 to the server" << endl;
#endif
             say(connection,"SEND_REQ:1\n");
            string newBranch = readIn(connection);
            if (newBranch.length() != 0 && newBranch[0] == '0') {
              if (newBranch[newBranch.length() - 1] == '\n')
                newBranch = newBranch.substr(0,newBranch.length() - 1);
              string actualBranch = (splitString(newBranch,':'))[1];
#ifdef DEBUG
              cout << "Received: " << actualBranch << endl;
#endif
              branch *newBranchPtr = brFromString(actualBranch);

              current->setBranch1(newBranchPtr);
              current = current->getBranch1();
              path.push_back(1);
              brPrint(*current);
              break;
           } 
         }
	 if (yesno(0,"You have reached the end. Would you like to create a new node?")) {
           branch *br = usr_input_branch();
           previous = current;
           current->setBranch1(br);
           path.push_back(1);
           current = br;
           if (connection != INVALID_SOCKET) {
#ifdef DEBUG
            cout << "Sending UPLOAD_REQ:1:" << current->toString() << " to the server" << endl;
#endif
            say(connection,"UPLOAD_REQ:1:" + current->toString() + '\n');
           }
         }
	 else {
           current = root;
           path.clear();
           if (connection != INVALID_SOCKET)
            say(connection,"RETURN_REQ\n");
	 }
	}
        brPrint(*current);
        break;
      case 'p':
        brPrint(*current);
	break;
      case 'c':
        cout << "New in Branches v" << br_VERSION <<"." << br_REVISION <<"." << br_MINOR_REVISION << "..." << endl;
        cout << br_CHANGELOG;
        break;
      case 'o':
        if (connection != INVALID_SOCKET)
        {
          say(connection,"PREV_REQ\n"); 
        }
        if (current->getPrevious() == NULL)
          cout << "Unable to return to previous node" << endl;
        else {
          current = current->getPrevious();
          path = vector<int>(path.begin(),path.end() - 1);
          brPrint(*current);
        }
      	break;
      case 'r':
        current = root;
        path.clear();
        previous = NULL;
        if (connection != INVALID_SOCKET) {
#ifdef DEBUG
          cout << "Sending RETURN_REQ to the server" << endl;
#endif
          say(connection,"RETURN_REQ\n");
        }
	brPrint(*root);
	break;
      case 's': { 
         if (yesno(0,"Do you really want to save your progress?")) {
          string filename;
          cout << "Enter filename: ";
          getline(cin,filename);
          if (filename[filename.length() - 1] == '\n')
            filename[filename.length() - 1] = '\0';
          cout << "Saving progress to " << filename << "..." << endl;
          ofstream output;
          output.open(filename);
          output << root->toString();
          output.close();
          if (third_tree) {
            output.open(filename + ".thirdtree");
            output << third_tree->toString(); 
            output.close();
          }
          cout << "Sucessfully saved file!" << endl;
        }
        
        break; }
      case 'a': {
        if (connection != INVALID_SOCKET)
        {
          cout << "You are connected to a server, and are unable to read in a saved file" << endl;
        }
        printf("");
        string filename;
        printf("Enter filename: ");
        getline(cin,filename);
        getline(cin,filename);
        if (filename[filename.length() - 1] == '\n')
          filename[filename.length() - 1] = '\0';
        if (check_file(filename)) {
          fprintf(stderr,"Read Error\n");
          break;
        }

        string line;
        stringstream temp (stringstream::in | stringstream::out);
        ifstream myfile (filename);
        if (myfile.is_open())
        {
          while (getline (myfile,line))
          {
            temp << line << '\n';
          }
          myfile.close();
        }

        string result = temp.str();
        delete root;
        root = brFromString(result);
        current = root;
        previous = NULL;
        brPrint(*root);
        //cout << "Feature currently unavailible");
        break; }
      case 'b': {
        cout << "r - read from a bscript file" << endl;
        cout << "w - write to a bscript file" << endl;
        cout << "e - return to the game" << endl;
        string bscrDummy;
        getline(cin,bscrDummy);
        shell_tx();
        string bscrResult;
        getline(cin,bscrResult);
        switch (bscrResult[0]) {
          case 'r':
            if (yesno(0,"Reading from a bscript will send you to the desired position. However, you will lose your current position. Proceed?")) {
              cout << "Enter filename: ";
              getline(cin,bscrResult);
              vector<int> bscr = bscrRead(bscrResult);
              current = bscrFollow(bscr,root,third_tree);
              path = bscr;
            }
            else 
              cout << "Returning to game..." << endl;
            brPrint(*current);
            break;
          case 'w':
            cout << "Enter filename: ";
            getline(cin,bscrResult);
#ifdef DEBUG
            cout << "path is: "; 
            for (int i : path)
              cout << i << ", ";
            cout << endl;
#endif
            bscrWrite(path,bscrResult);
            cout << "Saved file!" << endl;
            brPrint(*current);
            break;
          case 'e':
            brPrint(*current);
            break;
          default:
            cout << "Invalid command, returning to game..." << endl;
            brPrint(*current);
            break;
        }
        break; }
      case '3': {
        if (current == root)
	{
	  current = third_tree;
          if (connection != INVALID_SOCKET) {
            say(connection,"THREE_REQ\n");  
          }
	  brPrint(*current);
	  break;
	}
        cout << "Invalid command, please reenter" << endl;
        break; 
      }
      default: {
        cout << "Invalid command, please reenter" << endl;
	break; }
    
  } }
  delete root;
  return 0;
}
