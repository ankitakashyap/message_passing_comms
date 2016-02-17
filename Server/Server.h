#ifndef SERVER_H
#define SERVER_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Server.h - Responsible for sending and receiving files                               //                                                                                                          
// Object Oriented Design, Spring 2015                                                       //
//ver 2.2                                                                                                      //
// Language:    Visual C++ 11, Visual Studio 2013                                       //                       
// Platform:    MAC OSX,Core i5, Windows 7                                               //                                                                                                             
// Author:  Ankita Kashyap , Syracuse University                                        //
//              (315) 436-7059, ankashya@syr.edu                                          //
//                                                                                                             //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Module Operations :
*== == == == == == == == ==
This  file contains the Server class responsible for upload and server side receiving



Public Interface:
=================
public:
void serverupload( string clientportnumber, string serverportnumber);
void ServerSideRecev();

Required Files:
===============
Server.cpp,FileSystem.h,Client.h,Sockets.h,Sender.h,Receiver.h

Build Command:
==============
cl /EHa /TEST_SERVER Server.cpp

Maintenance History:
====================
ver 2.2 : 14 April 15
Created test stubs, added comments and added prologues
ver 2.1 : 10 April 15
- Integrated the modules with each other.
- Cleared the link errors
- Implemented functionality with the help of threads
ver 1.1 : 5 April 15
-  Created functionality for sending the client and server port number
ver 1.0 : 3 April 15
- first release

*/


#pragma once
#include<iostream>
#include<string>
#include"../Client/Client.h"
using namespace std;

class Server
{
public:
	void serverupload( string clientportnumber, string serverportnumber);
	void ServerSideRecev();
	
private:
	string clientport = "";

};

#endif