#include <iostream>
#include <fstream>
#include <string>
#include "ReadingData.h"

using namespace std;


ReadingData::ReadingData()
{

}

void ReadingData::readingData()
{
	string line;
	ifstream myLogFile;
	myLogFile.open("C:\\Users\\Computing\\Documents\\GitHub\\GamesEngines\\ioq3-master\\ioq3-master\\misc\\msvc12\\5mins4players.txt");

	if (myLogFile.is_open())
	{
		while (getline(myLogFile, line))
		{
			cout << line << '\n';
		}
		myLogFile.close();
	}

	else cout << "Unable to open file";
};
