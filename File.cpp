#include "File.h"
#include <iostream>
#include <string>
#define ERROR_FOPEN "no se pudo conectar con el dispositivo"
using std::string;

File::File(const char* name, std::ios_base::openmode flags) {
	this->file.open(name, flags);
	if (!this->file) {
		std::cerr << name << ": " << ERROR_FOPEN << std::endl;
		throw std::exception();
	}
}

bool File::eof() {
	return this->file.eof();
}

void File::get_line(string line) {
	getline(this->file, line);
}

void File::read(char* byte_leido, size_t n) {
	this->file.read(byte_leido, n);
}

size_t File::tell_g() {
	return this->file.tellg();
} 

void File::seek_g(size_t a, std::ios_base::seekdir dir) {
	this->file.seekg(a, dir);
}

File::~File() {
	this->file.close();
}

