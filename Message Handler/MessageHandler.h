#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MessageHandler.h - Responsible for message parsing and interpretation   //
//                                 of message on the server side  and storage in a file   //                                                            
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
This  file contains the MessageHandler class responsible for parsing and interpretation of the messages

Public Interface:
=================
public:
void messageparsing(string str);
void file_store();

Required Files:
===============
MessageHandler.cpp,Sender.h,FileSystem.h,Receiver.h,Sockets.h,Server.h

Build Command:
==============
cl /EHa /TEST_MESSAGEHANDLER MessageHandler.cpp

Maintenance History:
====================
ver 2.2 : 14 April 15
Created test stubs, added comments and added prologues
ver 2.1 : 10 April 15
- Integrated the modules with each other.
- Cleared the link errors
- Implemented functionality for taking arguments from the command line
- Added additional functionality according for parsing the message
ver 1.1 : 5 April 15
-  Created functionality for message parsing and storing it in a new file on server side
ver 1.0 : 3 April 15
- first release

*/

#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class MessageHandler
{
public:
	void messageparsing(string str);
	void file_store();
private:
	string temp = "";
	string filetemp = "";
};

#endif