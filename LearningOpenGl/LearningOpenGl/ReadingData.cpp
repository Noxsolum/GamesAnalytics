#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define GLEW_STATIC
#include <GLFW\glew.h>
// GLFW
#include <GLFW\glfw3.h>
#include "ReadingAndAnalyzing.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\ext.hpp>
#include <glm\gtx\string_cast.hpp>

using namespace std;
using namespace glm;

// =========================================
// --- Reading in the Player Positions ---
// =========================================
void ReadingPositions(vec3 newArrayZero[], vec3 newArrayOne[], vec3 newArrayTwo[], vec3 newArrayThree[], glm::vec3 newArrayFour[], glm::vec3 newArrayFive[], glm::vec3 newArraySix[], glm::vec3 newArraySeven[], glm::vec3 newArrayEight[], glm::vec3 newArrayNine[], glm::vec3 newArrayAll[])
{
	cout << "Begins Reading Data!" << endl;

	ifstream myLogFile;
	string line;
	string PosLine;	
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	int g = 0;
	int h = 0;
	int m = 0;
	int n = 0;
	int o = 0;
	int i = 0;
	float x, y;	
	int MaxNum = 0;

	//myLogFile.open("..\\DataForReading1.txt");
	myLogFile.open("..\\DataForReading2.txt");
	//myLogFile.open("..\\DataForReading3.txt");

	// ================================================
	// --- Checks Each Line for individual Players ---
	// ================================================
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
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					in >> x >> y;
					newArrayZero[a] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
					a++;
				}
			}
			if (ClientNum == 1)
			{
				getline(myLogFile, line);
				istringstream in(line);
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					in >> x >> y;
					newArrayOne[b] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
					b++;
				}
			}
			if (ClientNum == 2)
			{
				getline(myLogFile, line);
				istringstream in(line);
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					in >> x >> y;
					newArrayTwo[c] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
					c++;
				}
			}
			if (ClientNum == 3)
			{
				getline(myLogFile, line);
				istringstream in(line);
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					in >> x >> y;
					newArrayThree[d] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
					d++;
				}
			}
			if (ClientNum == 4)
			{
				getline(myLogFile, line);
				istringstream in(line);
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					in >> x >> y;
					newArrayFour[e] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
					e++;
				}
			}
			if (ClientNum == 5)
			{
				getline(myLogFile, line);
				istringstream in(line);
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					in >> x >> y;
					newArrayFive[f] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
					f++;
				}
			}
			if (ClientNum == 6)
			{
				getline(myLogFile, line);
				istringstream in(line);
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					in >> x >> y;
					newArraySix[g] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
					g++;
				}
			}
			if (ClientNum == 7)
			{
				getline(myLogFile, line);
				istringstream in(line);
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					in >> x >> y;
					newArraySeven[h] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
					h++;
				}
			}
			if (ClientNum == 8)
			{
				getline(myLogFile, line);
				istringstream in(line);
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					in >> x >> y;
					newArrayEight[m] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
					m++;
				}
			}
			if (ClientNum == 9)
			{
				getline(myLogFile, line);
				istringstream in(line);
				in >> PosLine;
				if (PosLine == "CurrentPos")
				{
					in >> x >> y;
					newArrayNine[n] = glm::vec3(x, y, 0.0f);
					newArrayAll[i] = glm::vec3(x, y, 0.0f);
					i++;
					n++;
				}
			}
		}
	}

	i = 0;
	myLogFile.close();
	cout << "Exits Reading Data!" << endl;
}

// ==============================================
// --- Reading in the Player Death Positions ---
// ==============================================
void ReadingDeath(vec3 newArrayDeath[])
{
	cout << "Begins Reading Death Positions!" << endl;

	ifstream myLogFile;
	string line;
	int MaxNum = 0;
	float x, y;
	int o = 0;
	string type;

	//myLogFile.open("..\\DataForReading1.txt");
	myLogFile.open("..\\DataForReading2.txt");
	//myLogFile.open("..\\DataForReading3.txt");
	
	for (string line; getline(myLogFile, line);)
	{
		istringstream in(line);
		in >> type;
		if (type == "DiedAt")
		{
			in >> x >> y;
			newArrayDeath[o] = glm::vec3(x, y, 0.0f);
			o++;
		}
	}

	o = 0;
	cout << "Ends Reading Death Positions!" << endl;
}