#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include "Exception.hpp"

class Fork_Exception : public Exception
{
public: 
	Fork_Exception() : Exception("Cannot fork") {}
};

class File_Exception: public Exception
{
public: 
	File_Exception() : Exception("Cannot open file") {}
};

class Pipe_Exception: public Exception
{
public: 
	Pipe_Exception() : Exception("Cannot pipe") {}
};

#endif