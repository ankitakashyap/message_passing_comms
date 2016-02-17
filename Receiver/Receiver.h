#ifndef RECEIVER_H
#define RECEIVER_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Receiver.h - Module responsible for receiving the messages on the client  //
//                    side and the receiver side                                                      //                                                                                                          
// Object Oriented Design, Spring 2015                                                       //
//ver 2.2                                                                                                      //
// Language:    Visual C++ 11, Visual Studio 2013                                       //                       
// Platform:    MAC OSX,Core i5, Windows 7                                               //                                                                                                             
// Author:  Ankita Kashyap , Syracuse University                                        //
//              (315) 436-7059, ankashya@syr.edu                                          //
// Source:Jim Fawcett                                                                               //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Module Operations :
*== == == == == == == == ==
This  file contains 3 classes responsible for parsing of the messages:
Reciever
ClientHandler
Server Handler


Public Interface:
=================

void server_receiving(string clientportnumber);
void client_receiving(string serverportnumber);
void operator()(Socket& socket_);
bool testStringHandling(Socket& socket_);
void deqFromBQ(std::promise<std::string> &p);
void operator()(Socket& socket_);
bool HandleString(Socket& socket_);
void deqFromBQ(std::promise<std::string> &p);

Required Files:
===============
Receiver.cpp,Sender.h,FileSystem.h,Sockets.h,AppHelpers.h,Cpp11-BlockingQueue.h

Build Command:
==============
cl /EHa /TEST_RECEIVER Receiver.cpp

Maintenance History:
====================
ver 2.2 : 14 April 15
Created test stubs, added comments and added prologues
ver 2.1 : 10 April 15
- Integrated the modules with each other.
- Cleared the link errors
- Added new classes: Client Handler and Server Handler for handling the functionality
ver 1.1 : 5 April 15
-  Created functionality for client receving and server receiving
ver 1.0 : 3 April 15
- first release

*/

#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include<mutex>
#include<future>
#include"../Sockets/Sockets.h"
#include"../Application Helpers/AppHelpers.h"
#include"../Sender/Sender.h"
#include"../Cpp11_BlockingQueue/Cpp11_BlockingQueue.h"
#include"../Message Handler/MessageHandler.h"
using namespace std;
using namespace ApplicationHelpers;

class Receiver
{
public:
	void server_receiving(string clientportnumber);
	void client_receiving(string serverportnumber);
	
};

class ClientHandler
{
public:
	void operator()(Socket& socket_);
	bool testStringHandling(Socket& socket_);
	void deqFromBQ(std::promise<std::string> &p);
	
	private:
	BlockingQueue<string> bq;
	string tmp = "";
	string temporary = "";
	};

class ServerHandler
{
public:
	void operator()(Socket& socket_);
	bool HandleString(Socket& socket_);
	void deqFromBQ(std::promise<std::string> &p);
private:
	BlockingQueue<string> bq1;
};

#endif