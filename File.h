#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

class File {
	std::fstream file;
	std::string filename;
	
	public:
		File(const char* name, std::ios_base::openmode flags);
		File(File&& other);
		File& operator=(File&& file);
		bool fail_open();
		bool eof();
		void set_name(std::string name);
		std::string get_name();
		void get_line(std::string& line);
		void read(char* buffer, size_t n);
		size_t tell_g();
		void seek_g(size_t a, std::ios_base::seekdir dir);
		~File();
};

#endif //FILE_H
