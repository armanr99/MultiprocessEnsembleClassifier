#ifndef _TOOLS_H
#define _TOOLS_H

#include <string>
#include <vector>

#define COMMA ','
#define SPACE ' '
#define UNDERLINE '_'
#define DIR_SEPERATOR '/'
#define NULL_CHAR 0
#define MAX_BUFF 4096
#define DATASET_FILENAME "dataset.csv"
#define LABELS_FILENAME "labels.csv"
#define VOTER_FIFO_PATH "./fifos/voter_fifo"
#define ENSEMBLE_FIFO_PATH "./fifos/ensemble_fifo"

class Tools
{
public:
    static bool endsWith(std::string first, std::string second);

    static std::vector<std::string> splitToStrings(std::string line, char separator);
    static std::vector<double> splitToDoubles(std::string line, char separator);
    static std::vector<int> splitToInts(std::string line, char separator);

    static int getMostFrequent(std::vector<int> vec);
    static std::string getNamedFifoName(std::string weightVectorsName);

    static std::string vectorToString(const std::vector<int> &vec);
    static std::vector < std::vector<double> > readDoubleCSV(std::string path);
    static std::vector < std::vector<int> > readIntCSV(std::string path);
};

#endif