#ifndef _VOTER_H_
#define _VOTER_H_

#include <vector>
#include <string>

class Voter
{
public:
    void setupPipes();
    std::vector < std::vector<int> > readPipes();
    std::vector<int> getBestScores(const std::vector <std::vector<int> > &classifications);
    void sendBestScores(const std::vector<int> &bestScores);

private:
    std::vector<std::string> namedPipes;
};

#endif