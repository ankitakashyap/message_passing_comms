#ifndef SENDER_H
#define SENDER_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sender.h - Responsible for sending the messages from the client side       //
//                    andfrom the receiver side                                                       //                                                                                                          
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
This  file contains the Sender class responsible for :
1. Sending  the file
2. Opening the file
3. Construction of the message
4. Sending the acknowledgement from th server in the 2 way communication process



Public Interface:
=================
public:
void openfile(string clientport, string serverport, string file);
std::vector<std::string> breakdown_file(string newline, string file, string clientportnumber, string serverportnumber);
std::vector<std::string> messageconstruction(std::vector<std::string> breakvector, string file, string clientportnumber, string serverportnumber);
void clientsending(std::vector<std::string> bodyplusattr, string clientportnumber, string serverportnumber,string file);
void sendingack(string serverportnumber, string clientportnumber);
void deqFromBQ(std::promise<std::string> &p);

Required Files:
===============
Sender.cpp,FileSystem.h,Server.h,Sockets.h,AppHelpers.h,Receiever.h,Cpp11-BlockingQueue.h

Build Command:
==============
cl /EHa /TEST_SENDER Sender.cpp

Maintenance History:
===================
ver 2.2 : 14 April 15
Created test stubs, added comments and added prologues
ver 2.1 : 10 April 15
- Integrated the modules with each other.
- Cleared the link errors
-Added functionality for construction of http message
- Added functionality for sending acknowledgement and implementing threads
ver 1.1 : 5 April 15
-  Created functionality for opening the desired file, breaking it down in block sizes and extracting the content
ver 1.0 : 3 April 15
- first release
*/


#include"../Sockets/Sockets.h"
#include"../FileSystem/FileSystem.h"
#include"../Receiver/Receiver.h"
#include"../Application Helpers/AppHelpers.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
 #include<future>
#include<thread>
#include"../Cpp11_BlockingQueue/Cpp11_BlockingQueue.h"
using namespace FileSystem;
using namespace ApplicationHelpers;
using namespace std;



class Sender
{
public:
	
	void openfile(string clientport, string serverport, string file);
	std::vector<std::string> breakdown_file(string newline, string file, string clientportnumber, string serverportnumber);
	std::vector<std::string> messageconstruction(std::vector<std::string> breakvector, string file, string clientportnumber, string serverportnumber);
	void clientsending(std::vector<std::string> bodyplusattr, string clientportnumber, string serverportnumber,string file);
	void sendingack(string serverportnumber, string clientportnumber);
	void deqFromBQ(std::promise<std::string> &p);

	private:
	BlockingQueue<std::string> sbq;
};

#endif