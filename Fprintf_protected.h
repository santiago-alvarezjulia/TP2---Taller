#ifndef FPRINTF_PROTECTED_H
#define FPRINTF_PROTECTED_H

#include <iostream>
#include <string>
#include <mutex>

class Fprintf_protected {
	std::mutex mutex;
	
	public:
		Fprintf_protected();
		void fprintf_error_invalid_id(size_t id);
		void fprintf_error_atascado(std::string filename);
		~Fprintf_protected();
};

#endif // FPRINTF_PROTECTED_H
