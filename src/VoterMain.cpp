#include <iostream>
#include <vector>
#include "Voter.hpp"
using namespace std;

int main()
{
    Voter voter;
    voter.setupPipes();
    vector < vector<int> > classifications = voter.readPipes();
    vector <int> bestScores = voter.getBestScores(classifications);
    voter.sendBestScores(bestScores);

    return 0;
}