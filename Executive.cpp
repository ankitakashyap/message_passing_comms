//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Executive.cpp - Handles the entire operating of the Message-Passing       //
//                          Communication                                                               //
// Object Oriented Design, Spring 2015                                                       //
//ver 2.2                                                                                                      //
// Language:    Visual C++ 11, Visual Studio 2013                                       //                       
// Platform:    MAC OSX,Core i5, Windows 7                                               //                                                                                                             
// Author:  Ankita Kashyap , Syracuse University                                        //
//              (315) 436-7059, ankashya@syr.edu                                          //                                                                    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<string>
#include<thread>
#include"Client\Client.h"
#include"Server\Server.h"
using namespace std;


void ServerSend(string source, string destination)
 {
	Server ser;
	ser.serverupload(source, destination);
 }

void ClientSend(string source, string destination, string filnm)
{
	Client clie;
	clie.clientupload(source, destination, filnm);
}

//-----------------<Program execution and flow starts from here>------------------------------------
#ifdef TEST_EXECUTIVE
int main(int argc, char* argv[])
{

	if (argc == 1)                     // If no input is provided
	{          
		cout << "Please enter the desired client port number and server port number";
	}
	

	else                                     // If input is provided
	{
		string source = argv[2];
		string destn = argv[4];
		string flnm = argv[6];
		thread t1(ClientSend, source, destn, flnm);
		thread t2(ServerSend, source, destn);
		t1.join();
		t2.join();
		
	}
	return 0;
}

#endif
