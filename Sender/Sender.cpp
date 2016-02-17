//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sender.cpp- Responsible for sending the messages on the client side         //
//                    and the receiver side                                                              //                                                                                                          
// Object Oriented Design, Spring 2015                                                       //
//ver 2.2                                                                                                      //
// Language:    Visual C++ 11, Visual Studio 2013                                       //                       
// Platform:    MAC OSX,Core i5, Windows 7                                               //                                                                                                             
// Author:  Ankita Kashyap , Syracuse University                                        //
//              (315) 436-7059, ankashya@syr.edu                                          //
// Source:Jim Fawcett                                                                               //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Sender.h"


//------------------<Opening the file to be sent>----------------------------

void Sender::openfile(string clientport, string serverport, string file)
{
	std::vector<std::string> stringvector;
std::string check = Path::fileSpec("./", "text2.txt");
std::string checkline = Path::getFullFileSpec(check);
for (size_t i = 0; i < checkline.size(); i++)
    {
	if (checkline[i] == '\\')
		checkline[i] = '/';
	}
	fstream file_open;
	file_open.open(checkline,ios::binary|ios::in);
	if (!file_open)
	{
		cout << "Cannot open file" << endl;
		exit(1);
	}

	std::string line;
	std::string newline;
	while (file_open.good())
	{
		getline(file_open, line);
		newline += line;
	}
	cout << "\n Contents of file are as follows:"<< newline;
	breakdown_file(newline,file,clientport,serverport);

}

//----------------<Breaks down the string block by block>------------------------------------
std::vector<std::string> Sender::breakdown_file(string newline, string file, string clientportnumber,string serverportnumber)
{
	std::vector<std::string> breakvector;
	 size_t blocksize = 10;                // Block size of 10 is assigned
	 string splitstring ;
	 size_t limit = newline.size();

	 for (size_t i = 0; i <blocksize; i++)
	 {
		 
		 if (i == limit -1)
		 {
			 breakvector.push_back(splitstring);
			 break;
		 }
		 splitstring += newline[i];
		 if (i == blocksize-1)
		 {
			 breakvector.push_back(splitstring);
			 splitstring = "";
			 blocksize += 10;
	 	 }

     }

	 cout << "\n Breakvector vector contents are as follows :\n";
	 for (auto i : breakvector)
		 cout  << i<< "\n";

	 std::vector<std::string> bodyplusattr = messageconstruction(breakvector, file, clientportnumber,serverportnumber);
	 clientsending(bodyplusattr, clientportnumber, serverportnumber,file);
	  return breakvector;

}


//--------------------<Constructing the message using attributes and body>--------------------------
std::vector<std::string> Sender::messageconstruction(std::vector<std::string> breakvector,string file,string clientportnumber,string serverportnumber)
{
	std::vector<std::string> vectorconstruct;
	
	
	string cmd = " COMMAND : Upload ";
	string filename= "FILENAME:" + file;
	string srcaddr = " SOURCE ADDRESS: localhost ";
	string srcport = " SOURCE PORT: " + clientportnumber;
	string dstaddr = " DESTINATION ADDRESS: localhost ";
	string destport = " DESTINATION PORT: " + serverportnumber;
	for (auto ptr : breakvector)
	{
		stringstream ss;
		ss << ptr.size();
		string ssgt=ss.str();
		string ptr1 = " CONTENT LENGTH: " + ssgt;
		string msg = cmd + filename + ptr1 + srcaddr + srcport + dstaddr + destport + "MESSAGE BODY:"+ptr;
		
		vectorconstruct.push_back(msg);
	}
	
	for (auto dvect : vectorconstruct)
		cout <<"\n Constructed message is as follows:=>"<< dvect;
	return vectorconstruct;

}

//---------------<Functionality for client sending the message>---------------------------
void Sender::clientsending(std::vector<std::string> bodyplusattr,string clientportnumber,string serverportnumber,string file)
{
	title("Testing Socket Client", '=');

		try
		{
			Verbose v(true);
			SocketSystem ss;
			SocketConnecter si;
			std::istringstream ist(clientportnumber);
			size_t clientp;
			ist >> clientp;
			while (!si.connect("localhost", clientp))
			{
				Verbose::show("client waiting to connect");
				::Sleep(100);
			}

			title("Starting string test on client");
			si.sendString("Command:Upload Filename:file.txt Content Length:   Source Address:  Source Port: Destination Address: Message Body:  ");
			for (auto tmp : bodyplusattr)
			{

				thread th1(&BlockingQueue<string>::enQ, &sbq, tmp);    //Implementation of blocking queue
				promise<string> p;
				thread t2(&Sender::deqFromBQ, this, std::ref(p));
				th1.join();
				t2.join();
				si.sendString(tmp);
			}

			string srcport1 = " SOURCE PORT: " + clientportnumber;
			string destport1 = " DESTINATION PORT: " + serverportnumber;
			string file_name = "FILENAME:" + file;
			string cmd1 = "Upload completed !!";
			string test_stopmsg = cmd1 + srcport1 + destport1 + file_name+ " MSG:TEST_STOP "; 

		   title("Starting buffer test on client");
		   si.sendString(test_stopmsg);    // Sending the last http message packet

			Verbose::show("\n  client calling send shutdown\n");
			si.shutDownSend();
	}
		catch (std::exception& ex)
		{
			Verbose::show("  Exception caught:", always);
			Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
		}
}

//-----------<Acknowledgement to be sent from the server for two way communication to take place>-------------------
void Sender::sendingack(string serverportnumber, string clientportnumber)
{
	title("Sending acknowledgement from server side", '=');
	try
	{
		Verbose v(true);
		SocketSystem ss;
		SocketConnecter si;
		std::istringstream ist(serverportnumber);
		size_t serverp;
		ist >> serverp;
		while (!si.connect("localhost", serverp))
		{
			Verbose::show("client waiting to connect");
			::Sleep(100);
		}

		title("Starting string test on client");
		title("Starting buffer test on client");

		string src_port1 = " SOURCE PORT: " + clientportnumber;
		string dest_port1 = " DESTINATION PORT: " + serverportnumber;
		string ack_msg = " Acknowledgement Sent ";
		string gt = " File has been uploaded successfully ";
		string message_ackn = src_port1 + dest_port1 + ack_msg;
		string fileupload_sucess = src_port1 + dest_port1 + gt;

		si.sendString(message_ackn);           // Acknowledgement is being sent to the client
		si.sendString(fileupload_sucess);
		
		thread thr1(&BlockingQueue<string>::enQ, &sbq, gt);    // Implementation of blocking queue
		promise<string> p;
		thread th2(&Sender::deqFromBQ, this, std::ref(p));
		thr1.join();
		th2.join();
		si.sendString(gt);

		Verbose::show("\n  client calling send shutdown\n");
		si.shutDownSend();
	}
	catch (std::exception& ex)
	{
		Verbose::show("  Exception caught:", always);
		Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
	}
}

//-----<functionality for deque from blocking queue>---------------------
void Sender::deqFromBQ(std::promise<std::string> &p)
{
	p.set_value(sbq.deQ());
}

//----------<Test Stub>-------------------------------------------
#ifdef TEST_SENDER
#include"Sender.h"
int main()
{
	Sender snd;
	std::vector<std::string>vect;
	std::vector<std::string>cbt;
	vect.push_back("This is a test stub");
	cbt.push_back("func client sending testing");
	snd.openfile("6070", "5060", "ast.txt");
	snd.breakdown_file("Object Oriented Design Spring 2015" ,"ast.txt","6070","5060" );

	snd.messageconstruction(vect,"ast.txt","6070","5060");
	snd.clientsending(cbt, "6070", "5060", "ast.txt");
	snd.sendingack("5060", "6070");

	return 0;
}
#endif
