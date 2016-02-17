//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Server.cpp - Responsible for sending and receiving files                           //                                                                                                          
// Object Oriented Design, Spring 2015                                                       //
//ver 2.2                                                                                                      //
// Language:    Visual C++ 11, Visual Studio 2013                                       //                       
// Platform:    MAC OSX,Core i5, Windows 7                                               //                                                                                                             
// Author:  Ankita Kashyap , Syracuse University                                        //
//              (315) 436-7059, ankashya@syr.edu                                          //
//                                                                                                             //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Server.h"

//----------<Sending client and server portnumbers to the server>-----------------------
void Server::serverupload(string clientportnumber, string serverportnumber)
{
	clientport = clientportnumber;
	thread t6(&Server::ServerSideRecev, this);
	t6.join();

}

//-------<Receiving on server side>---------------------------
void Server::ServerSideRecev()
{
	
	Receiver rv;
	rv.server_receiving(clientport);
}

//----------<Test Stub>---------------
#ifdef TEST_SERVER
#include "Server.h"
int main()
{
	Server sr;
	sr.serverupload("3040", "5060");
	return 0;
	
}
#endif

