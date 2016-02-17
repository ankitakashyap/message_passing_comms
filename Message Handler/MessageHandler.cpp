//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MessageHandler.cpp - Responsible for message parsing on the server     //
//                                    side and storage of it in a file                                 //
// Object Oriented Design, Spring 2015                                                       //
//ver 2.2                                                                                                      //
// Language:    Visual C++ 11, Visual Studio 2013                                       //                       
// Platform:    MAC OSX,Core i5, Windows 7                                               //                                                                                                             
// Author:  Ankita Kashyap , Syracuse University                                        //
//              (315) 436-7059, ankashya@syr.edu                                          //                                                                    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MessageHandler.h"


//---------------<Parsing the message received from the server>--------------------------
void MessageHandler::messageparsing(string str)
{
		string contentstr = "MESSAGE BODY:";
	if (str.find("MESSAGE BODY:") != string::npos)  // Means the expression is present in the string , if it is thn it will go inside the if statement
	{
		
		for (size_t i = (str.find("MESSAGE BODY:") + contentstr.size()); i < str.size(); i++)    //Interpreting Message body
			temp += str[i];
	}

 if (str.find("TEST_STOP") != string::npos)
   {
     	if (str.find("FILENAME:") != string::npos)  // Checking for file name
	    {
		  string ctr = "FILENAME:";
		  for (size_t i = (str.find("FILENAME:") + ctr.size()); i < str.find(" MSG:TEST_STOP "); i++)
		  filetemp += str[i];
 	    }
   }
 
}


//--------------<Storing the message into a new file at the server side>---------------------------
void MessageHandler::file_store()
{
	std::ofstream outputfile;
	string fileser = "FileInServer/";                            // new file is created at this location
	string stringforfilestore = fileser + filetemp;
	outputfile.open(stringforfilestore);
		outputfile << temp;
}

//----------------<Test Stub>---------------------------------------------------------
#ifdef TEST_MESSAGEHANDLER
#include"MessageHandler.h"
int main()
{
	MessageHandler msgt;
	msgt.messageparsing("COMMAND : Upload CONTENT LENGTH:10 SOURCE ADDRESS: localhost SOURCE PORT:6070 DESTINATION ADDRESS: localhost DESTINATION PORT:7080 MESSAGE BODY: This is CSE 687 Object Oriented Design Course FILENAME:analysis.txt MSG:TEST_STOP ");
	msgt.file_store();
	cout << "Tested succesfully!!";
	return 0;
}

#endif