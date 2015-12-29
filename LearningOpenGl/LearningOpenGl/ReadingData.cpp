#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define GLEW_STATIC
#include <Cunt\glew.h>
// GLFW
#include <Cunt\glfw3.h>
#include "ReadingData.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\ext.hpp>
#include <glm\gtx\string_cast.hpp>

using namespace std;

ifstream myLogFile;

void fileOpen()
{
	myLogFile.open("C:\\Users\\Dan\\Desktop\\DataForReading.txt");
}

void fileClose()
{
	myLogFile.close();
}

void ReadingPlayer0(glm::vec3 newArray[])
{
	string line;
	int MaxNum = 0;

	cout << "Enters Reading Data";
	int i = 0;
	for (string line; getline(myLogFile, line);)
	{
		istringstream in(line);
		string type;
		in >> type;
		if (type == "Player")
		{
			int ClientNum;
			in >> ClientNum;
			if (ClientNum == 0)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					newArray[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
		}
	}
	i = 0;
};

void ReadingPlayer1(glm::vec3 newArray[])
{
	string line;
	int MaxNum = 0;

	cout << "Enters Reading Data";
	int i = 0;
	for (string line; getline(myLogFile, line);)
	{
		istringstream in(line);
		string type;
		in >> type;
		if (type == "Player")
		{
			int ClientNum;
			in >> ClientNum;
			if (ClientNum == 1)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					newArray[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
		}
	}
	i = 0;
};

void ReadingPlayer2(glm::vec3 newArray[])
{
	string line;
	int MaxNum = 0;

	cout << "Enters Reading Data";
	int i = 0;
	for (string line; getline(myLogFile, line);)
	{
		istringstream in(line);
		string type;
		in >> type;
		{
			int ClientNum;
			in >> ClientNum;
			if (ClientNum == 2)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					newArray[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
		}
	}
	i = 0;
};

glm::vec3 ReadingPlayer3()
{

};

void HeatMapData(glm::vec3 SquaresArray[], glm::vec3 ColorArray[])
{
	string line;
	int MaxNum = 0;

	cout << "Enters Reading Data";
	int i = 0;
	for (string line; getline(myLogFile, line);)
	{
		istringstream in(line);
		string type;
		in >> type;
		if (type == "Player")
		{
			int ClientNum;
			in >> ClientNum;
			if (ClientNum == 0)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					ColorArray[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
		}
	}
	i = 0;
};