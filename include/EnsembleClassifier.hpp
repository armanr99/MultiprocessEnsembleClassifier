#ifndef _ENSEMBLE_CLASSIFIER_H_
#define _ENSEMBLE_CLASSIFIER_H_

#include <string>
#include <vector>
#include <stdio.h> 
#include <unistd.h> 

#define PIPE_READ 0
#define PIPE_WRITE 1
#define WEIGHT_VECTOR_SUFFIX ".csv"
#define LINEAR_CLASSIFIER_EXEC_PATH "LinearClassifier"
#define VOTER_EXEC_PATH "Voter"

class EnsembleClassifier
{
public:
    EnsembleClassifier(std::string _weightVectorsPath);
    ~EnsembleClassifier();
    void train();
    void classify(std::string validationPath);

private:
    pid_t voter;
    std::vector <pid_t> linearClassifiers;
    std::string weightVectorsPath;
    std::vector <std::string> weightVectorsNames;
    std::vector < std::vector<int> > unnamedPipes;
    void fillWeightVectorsNames();
    void createUnnamedPipes();
    void fillUnnamedPipes(std::string validationPath);
    void runLinearClassifier(int i);
    void runLinearClassifiers(std::string validationPath);
    void runVoter();
    void sendVoterPipesInfo();
    void createNamedPipes();
    std::string getVotes();
    double getAccuracy(std::string validationPath, std::string votes);
};

#endif