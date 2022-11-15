#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <list>
#include <iterator>
#include <cmath>
#include <ctime>
#include <random>
#include <fstream>
#define NUM_OF_SPOTS 5

using namespace std;

class Ant
{
public:
    int ID;
    int memory[NUM_OF_SPOTS]; //each array position is a spot index
    int antPosition[2]; //Position is given by (x,y) coordinates
    double pheromone; //feromônio da formiga

    Ant();
    Ant(int antID, int standardSpot);
    int getAntID();
    void updateMemory(int t,int visitedSpot);

    /*void chooseAndMoveAntToNextSatate();
    void updateLocalPheromone();
    void updateGlobalPheromones();
    void constructAntSolution();*/
};

