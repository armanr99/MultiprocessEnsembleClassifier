#include <iostream>
#include <dirent.h>
#include <cstring>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 
#include <iomanip>
#include "EnsembleClassifier.hpp"
#include "Exceptions.hpp"
#include "Tools.hpp"
using namespace std;

EnsembleClassifier::EnsembleClassifier(string _weightVectorsPath)
{
    weightVectorsPath = _weightVectorsPath;
}

EnsembleClassifier::~EnsembleClassifier()
{
    for(int i = 0; i < linearClassifiers.size(); i++)
        waitpid(linearClassifiers[i], NULL, 0);
}

void EnsembleClassifier::train()
{
    fillWeightVectorsNames();
}

void EnsembleClassifier::classify(string validationPath)
{
    createUnnamedPipes();
    fillUnnamedPipes(validationPath);
    createNamedPipes();
    runLinearClassifiers(validationPath);

    runVoter();
    sendVoterPipesInfo();

    string votes = getVotes();

    waitpid(voter, NULL, 0);

    double accuracy = getAccuracy(validationPath, votes);
    cout << "Accuracy: " << setprecision(2) << fixed << (accuracy * 100) << "%\n";
}

void EnsembleClassifier::fillWeightVectorsNames()
{
    DIR* directory = opendir(weightVectorsPath.c_str());

    if(directory == nullptr)
        throw File_Exception();
    else
    {
        struct dirent* entry;
		
		while ((entry = readdir(directory)) != nullptr)
		{
			string filename = string(entry->d_name);
            if (Tools::endsWith(filename, WEIGHT_VECTOR_SUFFIX))
                weightVectorsNames.push_back(filename);
		}
		closedir(directory);
	}
}
    
void EnsembleClassifier::createUnnamedPipes()
{
    for(int i = 0; i < weightVectorsNames.size(); i++)
    {
        int fd[2];
        if(pipe(fd) < 0)
        {
            throw Pipe_Exception();
        }
        else
        {
            vector <int> fds;
            fds.push_back(fd[0]);
            fds.push_back(fd[1]);
            unnamedPipes.push_back(fds);
        }
    }
}

void EnsembleClassifier::runLinearClassifiers(string validationPath)
{
    for(int i = 0; i < weightVectorsNames.size(); i++)
    {
        pid_t pid = fork();
        if(pid < 0)
        {
            throw Fork_Exception();
        }
        else if(pid == 0)
        {
            runLinearClassifier(i);
        }
        else
        {
            close(unnamedPipes[i][PIPE_READ]);
            linearClassifiers.push_back(pid);
        }
    }
}

void EnsembleClassifier::runLinearClassifier(int i)
{
    close(unnamedPipes[i][PIPE_WRITE]);
    char buff[MAX_BUFF];
    int n = read(unnamedPipes[i][PIPE_READ], buff, MAX_BUFF);
    buff[n] = NULL_CHAR;

    string buffString(buff);
    vector<string> buffWords = Tools::splitToStrings(buffString, SPACE);

    string validationPath = buffWords[0] + DIR_SEPERATOR + string(DATASET_FILENAME);
    string weightVectorDirectory = buffWords[1];
    string weightVectorName = buffWords[2];

    char * argv[5];
    argv[0] = (char*) LINEAR_CLASSIFIER_EXEC_PATH;
    argv[1] = (char*) validationPath.c_str();
    argv[2] = (char*) weightVectorDirectory.c_str();
    argv[3] = (char*) weightVectorName.c_str();
    argv[4] = NULL;

    execv(argv[0], argv);
}

void EnsembleClassifier::fillUnnamedPipes(string validationPath)
{
    for(int i = 0; i < weightVectorsNames.size(); i++)
    {
        string result = validationPath;
        result += SPACE;
        result += weightVectorsPath;
        result += SPACE;
        result += weightVectorsNames[i];
        write(unnamedPipes[i][PIPE_WRITE], result.c_str(), result.size());
        close(unnamedPipes[i][PIPE_WRITE]);
    }
}

void EnsembleClassifier::runVoter()
{
    pid_t pid = fork();

    if(pid < 0)
    {
        throw Fork_Exception();
    }
    else if(pid == 0)
    {
        char* argv[2];
        argv[0] = (char*) VOTER_EXEC_PATH;
        argv[1] = NULL;
        execv(argv[0], argv);
    }
    else
    {
        voter = pid;
    }
}

void EnsembleClassifier::sendVoterPipesInfo()
{
    string info = Tools::getNamedFifoName(weightVectorsNames[0]);

    for(int i = 1; i < linearClassifiers.size(); i++)
    {
        string classiferFifoPath = Tools::getNamedFifoName(weightVectorsNames[i]);
        info += (SPACE + classiferFifoPath);
    }

    int fd = open(VOTER_FIFO_PATH, O_WRONLY | O_CREAT, 0777);
    write(fd, info.c_str() , info.size());
    close(fd);
}

void EnsembleClassifier::createNamedPipes()
{
    for(int i = 0; i < weightVectorsNames.size(); i++)
    {
        string classiferFifoPath = Tools::getNamedFifoName(weightVectorsNames[i]);
        mkfifo(classiferFifoPath.c_str(), 0666);
    }

    mkfifo(ENSEMBLE_FIFO_PATH, 0666);
}

string EnsembleClassifier::getVotes()
{
    int fd = open(ENSEMBLE_FIFO_PATH, O_RDONLY);
    char buff[MAX_BUFF];
    int n = read(fd, buff, MAX_BUFF);
    buff[n] = NULL_CHAR;
    close(fd);

    string buffStr = buff;
    return buffStr;
}

double EnsembleClassifier::getAccuracy(string validationPath, string votes)
{
    string labelsPath = validationPath;
    labelsPath += DIR_SEPERATOR;
    labelsPath += LABELS_FILENAME;

    vector < vector<int> > labels = Tools::readIntCSV(labelsPath);
    vector <int> votesNums = Tools::splitToInts(votes, SPACE);

    int corrects = 0;
    for(int i = 0; i < labels.size(); i++)
        if(labels[i][0] == votesNums[i])
            corrects++;

    return ((double)corrects / (double)labels.size());
}