//�ڳ����л����ӣ���Ҫ�������ӵ�λ�ã�����ȣ���ʱ����object���Դ���draw
#include "situador.h"
#include <GL/glut.h>

Situador::Situador()
{
	object = new Objeto;
}
Situador::Situador(vertice s, float ang, vertice er, vertice t)
{
	object = new Objeto;
	setPos(t);
	setOrientation(ang, er);
	setScale(s);

}
Situador::~Situador()
{
	//delete object;
}

void Situador::setObject(Objeto *o)
{
	object = o;
}

void Situador::setPos(const vertice &p)
{
	position = p;
}

void Situador::setOrientation(float ang, const vertice &v)
{
	ori_ang = ang;
	ori = v;
}

void Situador::setScale(vertice s)
{
	newScale = s;
}

void Situador::Draw()
{
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity(); //Load identity I
	glTranslatef(position.x, position.y, position.z); //translation matrix T
	glRotatef(ori_ang, ori.x, ori.y, ori.z); //rotation matrix R
	glScalef(newScale.x, newScale.y, newScale.z); //scaling matrix S
	object->Draw();
	glPopMatrix();
}

void Situador::Draw(unsigned int r, unsigned int g, unsigned int b)
{
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity(); //Load identity I
	glTranslatef(position.x, position.y, position.z); //translation matrix T
	glRotatef(ori_ang, ori.x, ori.y, ori.z); //rotation matrix R
	glScalef(newScale.x, newScale.y, newScale.z); //scaling matrix S
	object->Draw(r, g, b);
	glPopMatrix();
}