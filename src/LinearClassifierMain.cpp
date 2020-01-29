#include <iostream>
#include "LinearClassifier.hpp"
#include "Tools.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    string validationPath = argv[1];
    string weightVectorDirectory = argv[2];
    string weightVectorName = argv[3];
    LinearClassifier linearClassifier(weightVectorDirectory, weightVectorName);
    linearClassifier.train();
    linearClassifier.classify(validationPath);
    
    return 0;
}