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

void ReadingData(glm::vec3 newArrayZero[], glm::vec3 newArrayOne[], glm::vec3 newArrayTwo[], glm::vec3 newArrayThree[], glm::vec3 newArrayFour[], glm::vec3 newArrayFive[], glm::vec3 newArraySix[], glm::vec3 newArraySeven[], glm::vec3 newArrayEight[], glm::vec3 newArrayNine[], glm::vec3 newArrayAll[]);
void ReadingDeath(glm::vec3 newArrayDeath[]);