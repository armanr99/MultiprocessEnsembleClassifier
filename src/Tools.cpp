#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Tools.hpp"
using namespace std;

bool Tools::endsWith(string first, string second)
{
    int firstLength = first.size();
    int secondLength = second.size();

    if (firstLength < secondLength)
        return false;

    if (first.substr(firstLength - secondLength, firstLength - 1) == second)
        return true;

    return false;
}

vector<double> Tools::splitToDoubles(string line, char separator)
{
    vector<double> result;
    stringstream ss(line);

    string doubleWord;
    while(getline(ss, doubleWord, separator))
        result.push_back(stod(doubleWord));

	return result;
}

vector<int> Tools::splitToInts(string line, char separator)
{
    vector<int> result;
    stringstream ss(line);

    string intWord;
    while(getline(ss, intWord, separator))
        result.push_back(stoi(intWord));

	return result;
}

vector<string> Tools::splitToStrings(string line, char separator)
{
    vector<string> result;
    stringstream ss(line);

    string str;
    while(getline(ss, str, separator))
        result.push_back(str);

	return result;
}

std::string Tools::getNamedFifoName(std::string weightVectorsName)
{
    string result = VOTER_FIFO_PATH;
    result += UNDERLINE;
    result += weightVectorsName;
    
    return result;
}

string Tools::vectorToString(const vector<int> &vec)
{
    string result = "";

    for(int i = 0; i < vec.size(); i++)
    {
        result += (vec[i] + '0');
        result += SPACE;
    }

    return result;
}

int Tools::getMostFrequent(vector<int> vec)
{
    sort(vec.begin(), vec.end()); 
  
    int maxCount = 1;
    int curCount = 1;
    int ans = vec[0];

    for (int i = 1; i < vec.size(); i++) 
    { 
        if (vec[i] == vec[i - 1]) 
            curCount++; 
        else 
        { 
            if (curCount > maxCount) 
            { 
                maxCount = curCount; 
                ans = vec[i - 1]; 
            } 
            curCount = 1; 
        } 
    } 
  
    if (curCount > maxCount) 
    { 
        maxCount = curCount; 
        ans = vec[vec.size() - 1]; 
    } 
  
    return ans;
}

vector < vector<double> > Tools::readDoubleCSV(string path)
{
    ifstream file;
	file.open(path);
	string line;
    vector < vector<double> > doubles;

    getline(file, line);

	while (getline(file, line))
	{
        vector<double> weight = Tools::splitToDoubles(line, COMMA);
        doubles.push_back(weight);
    }

    return doubles;
}

vector < vector<int> > Tools::readIntCSV(string path)
{
    ifstream file;
	file.open(path);
	string line;
    vector < vector<int> > ints;

    getline(file, line);

	while (getline(file, line))
	{
        vector<int> weight = Tools::splitToInts(line, SPACE);
        ints.push_back(weight);
    }

    return ints;
}