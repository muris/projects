//画整个场景，所有的object文件通过一个文件读进来，通过这些object创建situador，再把所有的situador画出来
#include "escena.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Escena::Escena() { 
}

bool Escena::AddInstance(unsigned int o_id, vertice s, float ang, vertice er, vertice t) {
	Situador _instance(s, ang, er, t);
	_instance.setObject(&(objects[o_id]));
	instances.push_back(_instance);
	return true;
}

bool Escena::Load(char *f_escena) {
	ifstream ifs(f_escena);
	//if(ifs.is_open()){
	int nFile;
	ifs >> nFile;
	for (int i = 0; i < nFile; i++)
	{
		string file_name;
		ifs >> file_name;
		Objeto obj;
		obj.Load(file_name.c_str());
		objects.push_back(obj);
	}	
	int nInstance;
	ifs >> nInstance;
	for (int i = 0; i < nInstance; i++)
	{
		int id;
		vertice scale, rotation, trans; 
		float angle;
		ifs >> id >> scale.x >> scale.y >> scale.z >> angle 
			>> rotation.x >> rotation.y >> rotation.z
			>> trans.x >> trans.y >> trans.z;
		AddInstance(id, scale, angle, rotation, trans);
	}
	return true;
	//}
	//else{
	//	cerr<<"File not opened"<<endl;
	//	return false;
	//}
}

void Escena::reset() {
//	while (!objects.empty())
//		objects.pop_back();
//	while (!instances.empty())
//		instances.pop_back();
}

void Escena::Draw(bool picking) {
	if(!picking){
		vector<Situador>::iterator it = instances.begin();
		for (; it != instances.end(); it++)
		{
			it->Draw();
		}
	}
	if(picking){
	//Draw with colors
		vector<Situador>::iterator it = instances.begin();
		unsigned int r,g,b;
		r = 20;
		g = 20;
		b = 20;
		for (; it != instances.end(); it++)
		{
			it->Draw(r, g, b);
			r += 20;
			g += 20;
			b += 20;
		}
	}
}
