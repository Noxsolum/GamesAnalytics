#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define GLEW_STATIC
#include <Cunt\glew.h>
// GLFW
#include <Cunt\glfw3.h>
#include "ReadingData.h"
#include <Cunt\glm\glm.hpp>
#include <Cunt\glm\gtc\matrix_transform.hpp>
#include <Cunt\glm\gtc\type_ptr.hpp>

using namespace std;

glm::vec3 ReadingData(glm::vec3 boobs[10])
{
	string line;
	ifstream myLogFile;

	myLogFile.open("C:\\Users\\Computing\\Desktop\\CockAndBalls.txt");

	int i = 0;
	for (string line; getline(myLogFile, line);)
	{
		istringstream in(line);
		string type;
		in >> type;

		if (type == "Current Position")
		{
			float x, y, z;
			in >> x >> y >> z;
			boobs[i] = glm::vec3(x, y, z);
			i++;
		}
	}
	i = 0;
	return glm::vec3(0.0f, 0.0f, 0.0f);

	//string line;
	//ifstream myLogFile;
	//myLogFile.open("C:\\Users\\Computing\\Documents\\GitHub\\GamesEngines\\ioq3-master\\ioq3-master\\misc\\msvc12\\5mins4players.txt");

	//if (myLogFile.is_open())
	//{
	//	while (getline(myLogFile, line))
	//	{
	//		cout << line << '\n'
	//	}
	//	myLogFile.close();
	//}

	//else cout << "Unable to open file";
};
