#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

using std::string;

class File {
	std::fstream file;
	
	public:
		File(const char* name, std::ios_base::openmode flags);
		bool eof();
		void get_line(string line); // cambiar void por lo que sea que devuelve getline
		void read(char* buffer, size_t n);
		size_t tell_g();
		void seek_g(size_t a, std::ios_base::seekdir dir);
		~File();
};

#endif //FILE_H
