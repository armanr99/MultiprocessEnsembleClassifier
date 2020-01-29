#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <iostream>
#include <cstring>
#include "Voter.hpp"
#include "Tools.hpp"
using namespace std;

void Voter::setupPipes()
{
    int fd = open(VOTER_FIFO_PATH, O_RDONLY);
    char buff[MAX_BUFF];
    int n = read(fd, buff, MAX_BUFF);
    buff[n] = NULL_CHAR;
    close(fd);

    string namedPipeStr = buff;
    namedPipes = Tools::splitToStrings(namedPipeStr, SPACE);
}

vector < vector<int> > Voter::readPipes()
{
    vector < vector<int> > classifications;

    for(int i = 0; i < namedPipes.size(); i++)
    {
        int fd = open(namedPipes[i].c_str(), O_RDONLY);
        char buff[MAX_BUFF];
        int n = read(fd, buff, MAX_BUFF);
        buff[n] = NULL_CHAR;

        string buffStr(buff);
        vector <int> splitted = Tools::splitToInts(buffStr, SPACE);
        classifications.push_back(splitted);

        close(fd);
    }

    return classifications;
}

vector<int> Voter::getBestScores(const vector < vector<int> > &classifications)
{
    vector<int> bestScores;
    for(int j = 0; j < classifications[0].size(); j++)
    {
        vector <int> classes;
        for(int i = 0; i < classifications.size(); i++)
            classes.push_back(classifications[i][j]);
                
        int mostFrequent = Tools::getMostFrequent(classes);
        bestScores.push_back(mostFrequent);
    }

    return bestScores;
}

void Voter::sendBestScores(const vector<int> &bestScores)
{
    string bestScoresStr = Tools::vectorToString(bestScores);

    int fd = open(ENSEMBLE_FIFO_PATH, O_WRONLY | O_CREAT, 0777);
    write(fd, bestScoresStr.c_str() , bestScoresStr.size());
    close(fd);
}