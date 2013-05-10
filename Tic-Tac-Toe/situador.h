
#ifndef _SITUADOR_H
#define _SITUADOR_H

#include "objeto.h"

class Situador {
public:
	Situador();
	// Establece la posici�n del objeto dentro del mundo
	Situador( vertice s, float ang, vertice er, vertice t);
	void setPos(const vertice &p);
	// Escalado a aplicar al objeto en cada uno de los ejes
	void setScale(vertice s);
	// Orientaci�n del objeto (un �ngulo en grados sexagesimales y un eje
	// de rotaci�n)
	void setOrientation(float ang, const vertice &v);
	// Establece la referencia al objeto
	void setObject(Objeto *o);
	// Actualiza la matriz MODEL_VIEW y dibuja el objeto
	void Draw();
	void Draw(unsigned int r, unsigned int g, unsigned int b);
	~Situador();
private:
	// A�ade aqu?las variables miembro que necesites
	Objeto *object;
	vertice position;
	vertice newScale;
	float ori_ang;
	vertice ori;
};

#endif
