//保存棋子，通过文件读取各个参数。一个文件一个object。
#include <fstream>
#include "objeto.h"

#include <GL/glut.h>
#include <istream>
#include <vector>
using namespace std;

Objeto::Objeto() { 
}


void Objeto::Reset(void) { 
	vertices.clear();
	colors.clear();
	triangles.clear();
 }

bool Objeto::Load(const char *filename) {
	ifstream ifs(filename);
	if (!ifs.eof())
	{
		int nVertice;
		ifs >> nVertice;		
		for (int i = 0; i < nVertice; i++)
		{
			vertice vertemp;
			ifs >> vertemp.x >> vertemp.y >> vertemp.z;
			vertices.push_back(vertemp);
		}
		int nColor;
		ifs >> nColor;
		for (int i = 0; i < nColor; i++)
		{
			color temp;
			ifs >> temp.r >> temp.g >> temp.b;
			colors.push_back(temp);
		}
		int nTriangle;
		ifs >> nTriangle;
		number = nTriangle;
		for (int i = 0; i < nTriangle; i++)
		{
			triangulo tritemp;
			ifs >> tritemp.iv1 >> tritemp.iv2 >> tritemp.iv3 >> tritemp.ic1 >> tritemp.ic2 >> tritemp.ic3;
			triangles.push_back(tritemp);
		}
	}
	return true;
}

void Objeto::Draw() const {
	glBegin (GL_TRIANGLES);
	for (int i = 0; i <number; i++) {
		glColor3f(colors[triangles[i].ic1].r, colors[triangles[i].ic1].g, colors[triangles[i].ic1].b);
		glVertex3f(vertices[triangles[i].iv1].x, vertices[triangles[i].iv1].y, vertices[triangles[i].iv1].z);
		glColor3f(colors[triangles[i].ic2].r, colors[triangles[i].ic2].g, colors[triangles[i].ic2].b);
		glVertex3f(vertices[triangles[i].iv2].x, vertices[triangles[i].iv2].y, vertices[triangles[i].iv2].z);
		glColor3f(colors[triangles[i].ic3].r, colors[triangles[i].ic3].g, colors[triangles[i].ic3].b);
		glVertex3f(vertices[triangles[i].iv3].x, vertices[triangles[i].iv3].y, vertices[triangles[i].iv3].z);
	}
	glEnd ();
}

void Objeto::Draw(unsigned char r,unsigned char g,unsigned char b) const {
	glBegin (GL_TRIANGLES);
	glColor3ub(r,g,b);
	for (int i = 0; i <number; i++) {
		glVertex3f(vertices[triangles[i].iv1].x, vertices[triangles[i].iv1].y, vertices[triangles[i].iv1].z);
		glVertex3f(vertices[triangles[i].iv2].x, vertices[triangles[i].iv2].y, vertices[triangles[i].iv2].z);
		glVertex3f(vertices[triangles[i].iv3].x, vertices[triangles[i].iv3].y, vertices[triangles[i].iv3].z);
	}
	glEnd ();
}