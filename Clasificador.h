#include "Thread.h"
#include "Packages.h"
#include "File.h"

class Clasificador : public Thread {
	Packages& packages;
	File* file;
	File* cant_clasificaciones(File* file, size_t* cant_clasif);
	
	public:
		Clasificador(Packages& packages, File* file);
		virtual void run() override;
};
