#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define GLEW_STATIC
#include <GLFW\glew.h>
// GLFW
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace std;
using namespace glm;

// ========================
// --- Reading in Data ---
// ========================
// - Reading in the Player Positions -
void ReadingPositions(vec3 newArrayZero[], vec3 newArrayOne[], vec3 newArrayTwo[], vec3 newArrayThree[], vec3 newArrayFour[], vec3 newArrayFive[], vec3 newArraySix[], vec3 newArraySeven[], vec3 newArrayEight[], vec3 newArrayNine[], vec3 newArrayAll[]);

// - Reading in the Player Death Positions -
void ReadingDeath(vec3 newArrayDeath[]);