#include "head/GameValue.h"


float ballAngle;
float rcos;
float rsin;
float shotPower;
int score;
int combo;
int ballNum = 10;
int firstCollision = 0;

float material_ambient[4]={0.24725, 0.1995, 0.0745, 1.0};
float material_diffuse[4]={0.75164, 0.60648, 0.22648, 1.0};
float material_specular[4]={0.628281, 0.555802, 0.366065, 1.0};
float material_shinness=48;

std::string gameStateLabel = "now loading...";
std::string gameStateLabelMiss = "--";
std::string powerLabel = "power:";
