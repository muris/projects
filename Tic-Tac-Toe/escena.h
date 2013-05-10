
#ifndef _ESCENA_H
#define _ESCENA_H

#include "objeto.h"
#include "situador.h"

#include <vector>
using namespace std;

class Escena {
public:
	// Constructor
	Escena();
	// Destructor
	~Escena() { reset(); };
	// Carga la definición de la escena desde un fichero de texto
	bool Load(char *f_escena);
	// Dibuja la escena
	void Draw(bool picking=false);
	// Añade una nueva instancia de un objeto existente (creando un 
	// nuevo Situador)
	bool AddInstance(unsigned int o_id, vertice s, float ang, vertice er, vertice t);
private:
	// Libera toda la memoria reservada
	void reset();
	// Define aqu?las estructuras necesarias para almacenar los objetos e instancias de la escena
	vector<Situador> instances;
	vector<Objeto> objects;
};


#endif