#include <iostream>
#include <fstream>
#include <list>

    //Ant's structure
    struct Ant
    {
        int ID;
        int wholeLengh;
        list<int> memory;
        list<int>::iterator internalIterator;
    };

    Ant* setNewAnt();
    void updateAntMemory();
    int getAndPosition();
    int getAntProbabilityChoise();
    void chooseAndMoveAntToNextSatate();
    void updateLocalPheromone();
    void updateGlobalPheromones();
    void constructAntSolution();