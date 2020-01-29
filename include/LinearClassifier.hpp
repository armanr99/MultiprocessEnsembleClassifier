#ifndef _LINEAR_CLASSIFIER_H_
#define _LINEAR_CLASSIFIER_H_

#include <string>
#include <vector>
#include <stdio.h> 
#include <unistd.h> 

class LinearClassifier
{
public:
    LinearClassifier(std::string _weightVectorDirectory, std::string _weightVectorName);
    void train();
    void classify(std::string validationPath);

private:
    std::string weightVectorDirectory;
    std::string weightVectorName;
    std::vector < std::vector<double> > classWeights;
    void fillWeights();
    std::vector <int> getClassifications(std::string validationPath);
    int classifySample(const std::vector<double> &sample);
    double getScore(const std::vector<double> &sample, const std::vector <double> &weights);
    void sendClassifications(const std::vector<int> &classifications);
};

#endif