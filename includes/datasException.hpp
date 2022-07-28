#ifndef DATASEXCEPTION_HPP
#define DATASEXCEPTION_HPP

#include "utils.hpp"

class datasException : public exception
{
	const	string	_msg;

	string			_option;

	public:
	datasException(const string msg, const string option = "") : _msg(msg), _option(option) {
	}

	datasException(const string msg, int option) : _msg(msg) {
		ostringstream convert;   // stream used for the conversion
		convert << option;      // insert the textual representation of 'Number' in the characters in the stream
		_option = convert.str();
	}

	~datasException() throw() {}

	const char *what() const throw () { return _msg.c_str(); }

	const char *getOption() const throw() { return _option.c_str(); }
};

#endif // DATASEXCEPTION_HPP
