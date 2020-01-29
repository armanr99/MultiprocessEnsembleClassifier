#include <iostream>
#include "EnsembleClassifier.hpp"
#include "Exceptions.hpp"
using namespace std;

#define WEIGHT_VECTORS_PATH "Assets/weight_vectors"

int main(int argc, char* argv[])
{
    string validationPath = argv[1];
    string weightVectorsPath = argv[2];

    try
    {
        EnsembleClassifier ensembleClassifier(weightVectorsPath);
        ensembleClassifier.train();
        ensembleClassifier.classify(validationPath);
    }
	catch(const exception &e)
	{
		cerr << "Error: " << e.what() << '\n';
	}

    return 0;
}