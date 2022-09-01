#include "header.h"

using namespace std;

int main()
{
    //Variable declaration section
    //string input;
    int alpha, beta,  Q, t, coordinates[2];
    float teta, eta, sigma, deltaTeta, tetaK;
    list<Ant> ants;
    list<int>::interater externalInterater;

    //Files and data reading
    /*cin >> input;
    ifstream inputFile(input, ios::in);
    string data;

    if (inputFile.is_open())
    {
        while (getline(inputFile,data) )
        {
            input.append(data + '\n');
        }
        inputFile.close();
    }
    else
        cout << "File not found\n"<< endl;*/
    //Setting parameter
    alpha = 1;
    beta = alpha;
    sigma = 0,01;
    teta = 0,1;
    Q = 10;
    t = 0;


    return 0;
}
Ant* setNewAnt(int ID)
{
    //Setting new ant
    unique_ptr<Ant> ants.push_back(new Ant());
    externalInterator.push_back(ID)
    ants.end()->ID = ID;
}

