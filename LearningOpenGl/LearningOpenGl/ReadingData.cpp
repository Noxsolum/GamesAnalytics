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

//ifstream myLogFile;
//
//void fileOpen()
//{
//	myLogFile.open("C:\\Users\\Dan\\Desktop\\DataForReading.txt");
//}
//
//void fileClose()
//{
//	myLogFile.close();
//}

void ReadingData(glm::vec3 newArrayZero[], glm::vec3 newArrayOne[], glm::vec3 newArrayTwo[], glm::vec3 newArrayThree[], glm::vec3 newArrayFour[], glm::vec3 newArrayFive[], glm::vec3 newArraySix[], glm::vec3 newArraySeven[], glm::vec3 newArrayEight[], glm::vec3 newArrayNine[], glm::vec3 newArrayAll[])
{
	ifstream myLogFile;
	string line;
	myLogFile.open("C:\\Users\\Computing\\Desktop\\DataForReading.txt");
	int MaxNum = 0;

	cout << "Enters Reading Data" << endl;
	int i = 0;
	for (string line; getline(myLogFile, line);)
	{
		istringstream in(line);
		string type;
		in >> type;
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
					newArrayZero[i] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
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
					newArrayOne[i] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
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
					newArrayTwo[i] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
			if (ClientNum == 3)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					newArrayThree[i] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
			if (ClientNum == 4)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					newArrayFour[i] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
			if (ClientNum == 5)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					newArrayFive[i] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
			if (ClientNum == 6)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					newArraySix[i] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
			if (ClientNum == 7)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					newArraySeven[i] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
			if (ClientNum == 8)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					newArrayEight[i] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
			if (ClientNum == 9)
			{
				getline(myLogFile, line);
				istringstream in(line);
				string PosLine;
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					float x, y;
					in >> x >> y;
					newArrayNine[i] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
				}
			}
		}
	}
	i = 0;
}

void ReadingPlayer0(glm::vec3 newArray[])
{
	ifstream myLogFile;
	string line;
	myLogFile.open("C:\\Users\\Computing\\Desktop\\DataForReading.txt");
	int MaxNum = 0;

	cout << "Enters Reading Data" << endl;
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
	ifstream myLogFile;
	string line;
	myLogFile.open("C:\\Users\\Computing\\Desktop\\DataForReading.txt");
	int MaxNum = 0;

	cout << "Enters Reading Data" << endl;
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
	ifstream myLogFile;
	string line;
	myLogFile.open("C:\\Users\\Computing\\Desktop\\DataForReading.txt");
	int MaxNum = 0;

	cout << "Enters Reading Data" << endl;
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

void ReadingPlayer3(glm::vec3 newArray[])
{
	ifstream myLogFile;
	string line;
	myLogFile.open("C:\\Users\\Computing\\Desktop\\DataForReading.txt");
	int MaxNum = 0;

	cout << "Enters Reading Data" << endl;
	int i = 0;
	for (string line; getline(myLogFile, line);)
	{
		istringstream in(line);
		string type;
		in >> type;
		{
			int ClientNum;
			in >> ClientNum;
			if (ClientNum == 3)
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

void ReadingPlayerFull(glm::vec3 newArray[])
{
	ifstream myLogFile;
	string line;
	myLogFile.open("C:\\Users\\Computing\\Desktop\\DataForReading.txt");
	int MaxNum = 0;

	cout << "Enters Reading Data" << endl;
	int i = 0;
	for (string line; getline(myLogFile, line);)
	{
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
	i = 0;
};