#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define GLEW_STATIC
#include <Cunt\glew.h>
// GLFW
#include <Cunt\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace std;

void fileOpen();
void fileClose();

void ReadingPlayer0(glm::vec3 newArray[]);
void ReadingPlayer1(glm::vec3 newArray[]);
void ReadingPlayer2(glm::vec3 newArray[]);
void ReadingPlayer3(glm::vec3 newArray[]);

void HeatMapData(glm::vec3 SquaresArray[], glm::vec3 ColorArray[]);