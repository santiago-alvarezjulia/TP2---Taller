#include "Thread.h"
#include "Paquetes.h"
#include "File.h"

class Clasificador : public Thread {
	Paquetes& packages;
	File* file;
	File* cant_clasificaciones(File* file, size_t* cant_clasif);
	
	public:
		Clasificador(Paquetes& packages, File* file);
		virtual void run() override;
};
