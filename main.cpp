#include "Ant.h"
#define NUM_OF_ITERACTIONS 2

struct spot
{
    int distance;
    bool eligible = true;
};


int main()//int argc, char *argv[])
{
    /*First section:
     * general functions prototipe*/
    double summationOfProducts(double tau[][NUM_OF_SPOTS], double eta[][NUM_OF_SPOTS], int t);
    int pathProbabilityChoice(double tau, double eta, double sigma, double alpha, double beta);
    double euclidianDistance(double xy[][2]);
    void dataScanner(string file);
    int randomPathChoice(double pxy[][NUM_OF_SPOTS], int currentSpot/*, int numOfPossibleSpots*/);

    /* definning the tables and lists of all values*/
    int localCurrentCondition = 0, antCurrentPosition, globalCurrentCondition = 0;
    int spots[NUM_OF_SPOTS] = {0, 1, 2, 3, 4}; //spots just for test only
    double spotsCoordinate[2][2];
    //distance transitions for test only
    spot spotsDistance[NUM_OF_SPOTS][NUM_OF_SPOTS] = {{0, false, 22, true, 50, true, 48, true,29, true},
                                                {22, true, 0, false, 30, true, 34, true, 32, true},
                                                {50, true, 30, true, 0,  false, 22, true, 23, true},
                                                {48, true, 34, true, 22, true, 0, false,35, true},
                                                {29, true, 32, true, 23, true, 35, true, 0, false}};
    //standard pheromones (eta)
    double spotsPheromone[NUM_OF_SPOTS][NUM_OF_SPOTS] = {{0.1, 0.1, 0.1, 0.1, 0.1},
                                                         {0.1, 0.1, 0.1, 0.1, 0.1},
                                                         {0.1, 0.1, 0.1, 0.1, 0.1},
                                                         {0.1, 0.1, 0.1, 0.1, 0.1},
                                                         {0.1, 0.1, 0.1, 0.1, 0.1}};
    double spotsDistanceUnderOne[NUM_OF_SPOTS][NUM_OF_SPOTS]; // 1/distance (tau)
    double influenceOfDistance = 1.0, influenceOfPheromone = 1.0, sigma;
    double probabiltyTransition[NUM_OF_SPOTS][NUM_OF_SPOTS]; //transitions between sposts probabilty value

    list<Ant> antsColony; //ants list for the colony
    list<Ant>::iterator antsIterator; // iterator for ants list

    /*po*/
   // dataScanner(argv[1],);


    /*Second section:
     * generating other values and populating the colony */
    //setting the spotsDistanceUnderOne value (tau)
    for (auto i: spots)
        for (auto j: spots)
            (i != j and spotsDistance[i][j].eligible) ? spotsDistanceUnderOne[i][j] = (1 / spotsDistance[i][j].distance) : spotsDistanceUnderOne[i][j] = 0;

    //setting new ant and adding to the antsColony
    for (auto n: spots)
    {
        Ant newAnt(n, spots[n]);
        antsColony.push_back(newAnt);
    }

    //for the future Isaac: u just use this for() to see if the colony has been generated
    /*for (antsIterator = antsColony.begin(); antsIterator != antsColony.end(); antsIterator++)
    {
        cout << antsIterator->getAntID() << endl;
    }*/

    /*Third section:
     * generating, probabilistically, results for the tsp*/
    //global status to terminate the main algorithm and determinate the "iteraction t"
    while(globalCurrentCondition < NUM_OF_ITERACTIONS) // don´t know yet
    {
        cout << "\nIteraction" << globalCurrentCondition << endl;
        //calculating generic values on iteraction t
        sigma = summationOfProducts(spotsDistanceUnderOne, spotsPheromone, globalCurrentCondition);
        //generating the probability of each path be chosen
        for (auto n: spots)
            for (auto m: spots)
            probabiltyTransition[n][m] = pathProbabilityChoice(spotsDistanceUnderOne[n][m], spotsPheromone[n][m],
                                                               sigma, influenceOfDistance, influenceOfPheromone);
        //using the whole colony for each iteraction
        for (antsIterator = antsColony.begin(); antsIterator != antsColony.end(); antsIterator++)
        {
            cout << "\nAnt " << antsIterator->getAntID() << ":\n Path: " << antsIterator->memory[0] << " - ";
            //doing for each ant the whole path
            //while (localCurrentCondition != NUM_OF_SPOTS)
            //{
                //doing for each path
                for (auto n: spots)
                {
                    //getting the current position of the current ant
                    antCurrentPosition = antsIterator->memory[n];
                    //updating the ant memory
                    antsIterator->memory[n+1] = randomPathChoice(probabiltyTransition, antCurrentPosition);
                    //updating the path probability transition by desable the previous path
                    spotsDistance[antsIterator->memory[n+1]][antsIterator->memory[n]].eligible = false;
                    if (n != NUM_OF_SPOTS)
                    {
                        //setting the new spotsDistanceUnderOne value (tau) as 0
                        spotsDistanceUnderOne[antsIterator->memory[n + 1]][antsIterator->memory[n]] = 0;
                        //calculating new sigma value
                        sigma = summationOfProducts(spotsDistanceUnderOne, spotsPheromone, globalCurrentCondition);
                        //fitting the probability of each path be chosen
                        for (auto m: spots)
                            probabiltyTransition[antsIterator->memory[n+1]][m] = pathProbabilityChoice(spotsDistanceUnderOne[antsIterator->memory[n+1]][m], spotsPheromone[antsIterator->memory[n+1]][m],
                                                                                   sigma, influenceOfDistance, influenceOfPheromone);
                    }
                    cout << antsIterator->memory[n+1] << " - ";
                }
            //}

        }
        globalCurrentCondition++;
    }
    return 0;
}

/*Fourth section:
 * Methods and functions*/
double euclidianDistance(double xy[][2])
{
    double distance = hypot(xy[0][0] - xy[1][0], xy[0][1]-xy[1][1]);
    return distance;
}

/* sum of all products of the 1/distance  and pheromone value between two spots.
 *params(1/distance, pheromone value, iteraction)  */
double summationOfProducts(double tau[][NUM_OF_SPOTS], double eta[][NUM_OF_SPOTS], int t)
{
    double sumOfProducts = 0;
    for (int n = 0; n < NUM_OF_SPOTS; n++)
        sumOfProducts += (tau[t][n]) * eta[t][n];
    return sumOfProducts;
}
/*calculates probability of each path*/
int pathProbabilityChoice(double tau, double eta, double sigma, double alpha, double beta)
{
    double probabilityValue;
    probabilityValue = (pow(tau,alpha) * pow(eta, beta))/sigma;
    return probabilityValue;
}

/*simulates natural path choice*/
int randomPathChoice(double pxy[][NUM_OF_SPOTS], int currentSpot)//, int numOfPossibleSpots)
{
    double sum = 0.0, accum = 0.0;

    srand(time(0));

    for (auto n = 0; n < NUM_OF_SPOTS; n++)
        sum += pxy[currentSpot][n];

    float nextProbabilitySpot = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / sum));
    for (auto n = 0; n < NUM_OF_SPOTS; n++)
    {
        accum += (pxy[currentSpot][n]/sum);
        if (nextProbabilitySpot < accum)
            return n;
    }
    return NUM_OF_SPOTS - 1;
}

/*gets data values*/
void dataScanner(string file)
{
    ifstream dataFile(file, ios::in);
    string data;

    if (dataFile.is_open())
    {
        while (getline(dataFile,data, '\t') )
        {

        }
        dataFile.close();
    }
    else
        cout << "File not found\n"<< endl;
}