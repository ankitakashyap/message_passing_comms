#ifndef CLIENT_H
#define CLIENT_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Client.h - Manages the sending and receiving of messages in a                //
//                peer-to-peer communication system                                          //
// Object Oriented Design, Spring 2015                                                       //
//ver 2.2                                                                                                      //
// Language:    Visual C++ 11, Visual Studio 2013                                       //                       
// Platform:    MAC OSX,Core i5, Windows 7                                               //                                                                                                             
// Author:  Ankita Kashyap , Syracuse University                                        //
//              (315) 436-7059, ankashya@syr.edu                                          //                                                                    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Module Operations :
*== == == == == == == == ==
This  file contains the Client class responsible for the sending and the receiving of the messages

Public Interface:
=================
public:
void clientupload(string clientportnumber, string serverportnumber,string filenm);
void ClientSideSender();
void ClientSideReceiver();

Required Files:
===============
Client.cpp,Sender.h,FileSystem.h,Receiver.h,Sockets.h,Server.h

Build Command:
==============
cl /EHa /TEST_CLIENT Client.cpp

Maintenance History:
====================
ver 2.2 : 14 April 15
Created test stubs, added comments and added prologues
ver 2.1 : 10 April 15
- Integrated the modules with each other.
- Cleared the link errors
- Implemented functionality for threads
ver 1.1 : 5 April 15
-  Created functionality for client sending the messages and sending file
ver 1.0 : 3 April 15
- first release

*/

#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"../Sender/Sender.h"
#include"../FileSystem\FileSystem.h"

using namespace std;
using namespace FileSystem;

class Client
{
public:
	void clientupload(string clientportnumber, string serverportnumber,string filenm);
	void ClientSideSender();
	void ClientSideReceiver();
private:
	string clientprtnumber = "";
	string serverprtnumber = "";
		string file = "";
};

#endif