//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Client.cpp - Manages the sending and receiving of messages                  //
// Object Oriented Design, Spring 2015                                                       //
//ver 2.2                                                                                                      //
// Language:    Visual C++ 11, Visual Studio 2013                                       //                       
// Platform:    MAC OSX,Core i5, Windows 7                                               //                                                                                                             
// Author:  Ankita Kashyap , Syracuse University                                        //
//              (315) 436-7059, ankashya@syr.edu                                          //                                                                    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Client.h"


//---------------<Sender for client side>----------------------------------------------------
void Client::ClientSideSender()
{
	Sender send;
	send.openfile(clientprtnumber, serverprtnumber, file);
}

//<--------------------<Receiver for client side>------------------------------------------------>
void Client::ClientSideReceiver()
{
	Receiver r1;
	r1.client_receiving(serverprtnumber);
}

//<-------------------<File upload in client>--------------------------------------------------------------
void Client::clientupload(string clientportnumber, string serverportnumber, string filenm)
{
	file = filenm;
	clientprtnumber = clientportnumber;
	serverprtnumber = serverportnumber;
	thread t3(&Client::ClientSideSender, this);
	thread t4(&Client::ClientSideReceiver, this);
	t3.join();
	t4.join();

}

//--------------------<Test Stub>---------------------------------------------------------------- 

#ifdef TEST_CLIENT
#include"Client.h"
int main()
{
	Client ct;
	ct.clientupload("1027", "1028", "text2.txt");
return 0;
}
#endif


