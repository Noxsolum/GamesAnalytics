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

glm::vec3 ReadingData()
{
	string line;
	ifstream myLogFile;

	myLogFile.open("C:\\Users\\Dan\\Desktop\\DataForReading.txt");

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
			cout << endl << ClientNum << endl;
			if (ClientNum == 0)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				cout << PosLine << endl;
				if (PosLine == "CurrentPos")
				{
					cout << "Player 0:\n";
					float x, y, z;
					in >> x >> y >> z;
					glm::vec3(boob);
					cout << "CurrentPos:";
					boob = glm::vec3(x, y, z);
					cout << glm::to_string(boob) << endl;
					i++;
				}
			}
			else if (ClientNum == 1)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				cout << PosLine << endl;
				if (PosLine == "CurrentPos")
				{
					cout << "Player 1:\n";
					float x, y, z;
					in >> x >> y >> z;
					glm::vec3(boob);
					cout << "CurrentPos:";
					boob = glm::vec3(x, y, z);
					cout << glm::to_string(boob) << endl;
					i++;
				}
			}
			else if (ClientNum == 2)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				cout << PosLine << endl;
				if (PosLine == "CurrentPos")
				{
					cout << "Player 2:\n";
					float x, y, z;
					in >> x >> y >> z;
					glm::vec3(boob);
					cout << "CurrentPos:";
					boob = glm::vec3(x, y, z);
					cout << glm::to_string(boob) << endl;
					i++;
				}
			}
			else if (ClientNum == 3)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				cout << PosLine << endl;
				if (PosLine == "CurrentPos")
				{
					cout << "Player 3:\n";
					float x, y, z;
					in >> x >> y >> z;
					glm::vec3(boob);
					cout << "CurrentPos:";
					boob = glm::vec3(x, y, z);
					cout << glm::to_string(boob) << endl;
					i++;
				}
			}
			else
			{
				cout << "No player";
			}
		}

	}
	i = 0;
	return glm::vec3(0.0f, 0.0f, 0.0f);
};
