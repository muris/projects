
#ifndef _OBJETO_H
#define _OBJETO_H

#include <vector>
using namespace std;
// Tipo vértice
struct vertice {
	vertice() { x = y = z = 0.0f; };
	vertice(float xx, float yy, float zz) { x = xx; y = yy; z = zz; };
	float x, y , z;
};

// Tipo color
struct color {
	float r, g, b;
};

// Tipo triángulo
struct triangulo {
	unsigned int iv1, iv2, iv3;
	unsigned int ic1, ic2, ic3;
};


class Objeto {
public:
	Objeto();
	~Objeto() { Reset(); }; 
	bool Load(const char *filename);
	void Draw() const;
	void Draw(unsigned char r, unsigned char g, unsigned char b) const;
private:
	void Reset(void); // Libera toda la memoria reservada
	vector<vertice> vertices;
	vector<color> colors;
	vector<triangulo> triangles;
	int number;
};

#endif
