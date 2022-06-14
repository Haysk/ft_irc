#ifndef DATASEXCEPTION_HPP
#define DATASEXCEPTION_HPP

#include "utils.hpp"

class datasException : public exception
{
	const string _msg;
	const string _option;
	public:
	datasException(const string msg, const string option = "") :
		_msg(msg),
		_option(option) {
		//cout << _msg;
	}
	~datasException() throw() {}
	const char *what() const throw () { return _msg.c_str(); }
	const char *getOption() const throw() { return _option.c_str(); }
};

#endif // DATASEXCEPTION_HPP
