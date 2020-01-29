#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>
#include <exception>

class Exception : public std::exception
{
public:
	Exception(const std::string _msg) : msg(_msg) {}
	virtual ~Exception() throw() {}

	virtual const char* what() const throw()
	{
		return msg.c_str();
	}

private:
	std::string msg;
};

#endif