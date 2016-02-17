//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Receiver.cpp - Responsible for receiving the messages on the client side   //
//                       and the receiver side                                                           //                                                                                                          
// Object Oriented Design, Spring 2015                                                       //
//ver 2.2                                                                                                      //
// Language:    Visual C++ 11, Visual Studio 2013                                       //                       
// Platform:    MAC OSX,Core i5, Windows 7                                               //                                                                                                             
// Author:  Ankita Kashyap , Syracuse University                                        //
//              (315) 436-7059, ankashya@syr.edu                                          //
// Source:Jim Fawcett                                                                               //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Receiver.h"


//----< Client Handler thread starts running this function >-----------------

void ClientHandler::operator()(Socket& socket_)
{
	while (true)
	{
		// interpret test command
		std::string command = socket_.recvString();
		if (command.size() == 0)
			break;
		Verbose::show("command: " + command);
			if (testStringHandling(socket_))
				Verbose::show("----String Handling test passed", always);
			else
			{
				Verbose::show("----String Handling test failed", always);
				break;
			}
		
	 }

	// we get here if command isn't requesting a test, e.g., "TEST_STOP"
	Verbose::show("ClientHandler socket connection closing");
	socket_.shutDown();
	socket_.close();
	Verbose::show("ClientHandler thread terminating");

}

//----< test string handling >-----------------------------------------------
/*
*   Creates strings, sends to server, then reads strings server echos back.
*/
bool ClientHandler::testStringHandling(Socket& socket_)
{
	title("String handling test on server");
	MessageHandler mh;
	while (true)
	{
		
		if (socket_.bytesWaiting() == 0)
			break;
		std::string str = socket_.recvString();

		thread thread1(&BlockingQueue<string>::enQ, &bq, str);  //  Implementation of blocking queue
		promise<string> p;
		thread thread2(&ClientHandler::deqFromBQ, this, std::ref(p));
		thread1.join();
		thread2.join();

		if (str.find("TEST_STOP") != string::npos)                    // Testing the last http packet for destination port and source port
		{
			string contentstr1 = " DESTINATION PORT: ";          // Parsing destination port
			Sender sending;
			if (str.find(" DESTINATION PORT: ") != string::npos)
			{
				for (size_t i = (str.find(" DESTINATION PORT: ") + contentstr1.size()); i < str.find("FILENAME:"); i++)
					tmp += str[i];
			}

			string source_str = " SOURCE PORT: ";               // Parsing source port
			if (str.find(" SOURCE PORT: ") != string::npos)
			{
				for (size_t i = (str.find(" SOURCE PORT: ") + source_str.size()); i<str.find(" DESTINATION PORT: ");i++)
				{
					temporary += str[i];
				}
			}
			sending.sendingack(tmp, temporary);
		}
		mh.messageparsing(str);                           // Each http message packet is sent for message parsing on the server side
		if (socket_ == INVALID_SOCKET)
			return false;
		if (str.size() > 0)
		{
			Verbose::show("server recvd : " + str, always);
			
		}
		else
		{
			break;
		}
		
  }
	mh.file_store();                           
	return true;
}

//----------------< Functionality for the receipt of message by the server>----------------------
void Receiver::server_receiving(string clientportnumber)
{
	{
		title("Testing Socket Server", '=');

		try
		{
			std::istringstream ist( clientportnumber);
			size_t clientport1;
			ist >> clientport1;
			Verbose v(true);
			SocketSystem ss;
			SocketListener sl(clientport1, Socket::IP6);               //client port number is being passed
			ClientHandler cp;
			sl.start(cp);
			Verbose::show("press key to exit: ", always);
			std::cout.flush();
			std::cin.get();
		}
		catch (std::exception& ex)
		{
			Verbose::show("  Exception caught:", always);
			Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
		}
	}

}



void ServerHandler::operator()(Socket& socket_)
{
		while (true)
		{
			// interpret test command
			std::string command = socket_.recvString();
			if (command.size() == 0)
				break;
			Verbose::show("command: " + command);

			Verbose::show("Client has received succesfully");

			if (HandleString(socket_))
				Verbose::show("----String Handling test passed", always);
			else
			{
				Verbose::show("----String Handling test failed", always);
				break;
			}
						
		}
		// we get here if command isn't requesting a test, e.g., "TEST_STOP"
		Verbose::show("ServerHandler socket connection closing");
		socket_.shutDown();
		socket_.close();
		Verbose::show("ServerHandler thread terminating");
}


bool ServerHandler::HandleString(Socket& socket_)
{
	title("String handling test on client");
	while (true)
	{
		if (socket_.bytesWaiting() == 0)
			break;
		std::string str = socket_.recvString();

		thread tht1(&BlockingQueue<string>::enQ, &bq1, str);
		promise<string> p;
		thread tht2(&ServerHandler::deqFromBQ, this, std::ref(p));
		tht1.join();
		tht2.join();
				
		if (socket_ == INVALID_SOCKET)
			return false;
		if (str.size() > 0)
		{
			Verbose::show("client received : " + str, always);

		}
		else
		{
			break;
		}
   }
		return true;

}

//-----------<functionality for receiving for the client>-------------------------
void Receiver::client_receiving(string serverportnumber)
{
	{
		title("Testing Socket Server", '=');

		try
		{
			std::istringstream ist( serverportnumber);             
			size_t serverport1;
			ist >> serverport1;
			Verbose v(true);
			SocketSystem ss;
			SocketListener sl(serverport1, Socket::IP6);     // server port number is being passed
			ServerHandler cp;
			sl.start(cp);

			Verbose::show("press key to exit: ", always);
			std::cout.flush();
			std::cin.get();
		}
		catch (std::exception& ex)
		{
			Verbose::show("  Exception caught:", always);
			Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
		}
   }

}

//----------<functionality for deque from blocking queue for server>--------------
void ClientHandler::deqFromBQ(std::promise<std::string> &p)
{
	p.set_value(bq.deQ());
}


//-----------<Blocking queue Deque for client>-----------------------------
void ServerHandler::deqFromBQ(std::promise<std::string> &p)
{
	p.set_value(bq1.deQ());
}


//--------<Test Stub>-----------------------------------------------
#ifdef TEST_RECEIVER
#include"Receiver.h"
int main()
{
	Receiver rc;
	rc.server_receiving("1024");
	rc.client_receiving("2020");
	return 0;

}
#endif