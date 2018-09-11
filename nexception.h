#ifndef _NEXCEPTION_IVM198005_H
#define _NEXCEPTION_IVM198005_H

#include<stdexcept>

class nexception : public std::exception
{
public:
	explicit nexception(const char* message) :
		msg(message)
	{
	}
	explicit nexception(const std::string& message) :
		msg(message)
	{}
	virtual ~nexception() throw () {}
	virtual const char* what() const throw () {
		return msg.c_str();
	}

protected:
	std::string msg;
};

#endif
