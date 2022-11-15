#include "Ant.h"

using namespace std;

//defult constructor
Ant::Ant()
{
}
//constructor to create a new ant and initializing the memory
Ant::Ant(int antID, int standardSpotID)
{
    ID = antID;
    memory[0] = standardSpotID;
    pheromone = 0.1; //default pherome value
}
int Ant::getAntID()
{
    return ID;
}
//update ant memory by add on array memory, the ID spot
void Ant::updateMemory(int t, int spotID)
{
    memory[t] = spotID;
}



