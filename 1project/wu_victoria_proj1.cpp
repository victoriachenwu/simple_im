/*
 * Project 1
 * CS 423
 * Victoria Wu
 *
 * IM Client + a bit of trivial FTP
 */


#ifndef DEBUG
#define DEBUG 0
#endif

#include <string>	//getline	
#include <iostream>	//cerr
#include "IM_Client.h"

//Compiled using Visual Studio's command prompt
#pragma comment(lib, "wsock32.lib")	//link winsock lib
#pragma comment(lib, "libcmt.lib")	//for process.h


int main(int argc, char **argv)	{
	
	//Take in user specifed port num and server name.
	char* serverName;
	char* portNum;

	if(argc == 3)	{
		serverName = argv[1];
		portNum = argv[2];
		std::cout << "Server IP: " << serverName << std::endl;
		std::cout << "Port Num : " << portNum << std::endl;
	}
	else	{
		serverName = "134.193.128.197";
		portNum = "3456";
		//std::cerr << "Need server name and port number.";
		//exit(1);
	}

	//Start up IM client.
	IM_Client im(serverName, portNum);
	im.signIn();

	//Display options, execute user's requests.
	std::string input;
	char command;
	bool userContinue = true;
	while(userContinue)	{
		im.displayNotifications();
		im.menuDisplay();
		//Prevent unnecessary loops with default case by using getline instead of directly reading in char.
		getline(std::cin, input);
		(input.length() == 1) ? command = input.at(0) 
			: command = 'X';
		switch (command)	{
			case 'c': im.checkMessages(); break;
			case 's': im.sendMessage(); break;
			case 'f': im.getFileNames(); break;
			case 'd': im.downloadFile(); break;
			case 'q': userContinue = false;	 break;
			default: std::cout << "Invalid input." << std::endl;
				std::cout  << "->" << std::endl;
				 std::cout << input << std:: endl << "->" << std::endl;
		}
	}		
	


	//Wrap up.
	std::cout << "Goodbye!" << std::endl;
	im.logOut();
	im.shutdown();
	return 0;
}

