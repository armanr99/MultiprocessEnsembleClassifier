#include <iostream>
#include <fstream>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include "LinearClassifier.hpp"
#include "Tools.hpp"
using namespace std;

LinearClassifier::LinearClassifier(string _weightVectorDirectory, string _weightVectorName)
{
    weightVectorDirectory = _weightVectorDirectory;
    weightVectorName = _weightVectorName;
}

void LinearClassifier::train()
{
    fillWeights();
}

void LinearClassifier::fillWeights()
{
    string weightVectorFullPath = weightVectorDirectory + DIR_SEPERATOR + weightVectorName;
    classWeights = Tools::readDoubleCSV(weightVectorFullPath);
}

void LinearClassifier::classify(string validationPath)
{
    vector<int> classifications = getClassifications(validationPath);
    sendClassifications(classifications);
}

void LinearClassifier::sendClassifications(const vector<int> &classifications)
{
    string classificationsStr = Tools::vectorToString(classifications);
    string fifoPath = Tools::getNamedFifoName(weightVectorName);

    int namedPipe = open(fifoPath.c_str(), O_WRONLY);
    write(namedPipe, classificationsStr.c_str(), classificationsStr.size());
    close(namedPipe);
}

vector <int> LinearClassifier::getClassifications(string validationPath)
{
    vector <int> classifications;
    vector < vector<double> > samples = Tools::readDoubleCSV(validationPath);
    
    for(int i = 0; i < samples.size(); i++)
    {
        int sampleClassification = classifySample(samples[i]);
        classifications.push_back(sampleClassification);
    }

    return classifications;
}

int LinearClassifier::classifySample(const vector<double> &sample)
{
    int maxClass = 0;
    double maxScore = getScore(sample, classWeights[0]);

    for(int i = 1; i < classWeights.size(); i++)
    {
        double score = getScore(sample, classWeights[i]);
        if(score > maxScore)
        {
            maxScore = score;
            maxClass = i;
        }
    }

    return maxClass;
}

double LinearClassifier::getScore(const vector<double> &sample, const vector <double> &weights)
{
    double score = 0;
    
    int i = 0;
    for(i; i < weights.size(); i++)
    {
        if(i > sample.size() - 1)
            score += weights[i];
        else
            score += weights[i] * sample[i];
    }
    
    for(i; i < sample.size(); i++)
        score += sample[i];
    
    return score;
}