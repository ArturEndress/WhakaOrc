#include "Tumba.h"



Tumba::Tumba()
{
}


Tumba::~Tumba()
{
}

void Tumba::inicializar()
{
	carregar();
	hp = 30;
	vivo = true;
}

void Tumba::desenhar(float x, float y)
{
	this->x = x;
	this->y = y;
	sprite[0].desenhar(x, y);
}

void Tumba::carregar()
{
	string name, path, arqName;
	int nID;

	fstream arquivoTumba;

	arqName = "tumba/tumba.txt";

	arquivoTumba.open(arqName);
	if (arquivoTumba.is_open())
	{
		arquivoTumba >> nTumbas;

		for (int t = 0; t < nTumbas; t++)
		{
			arquivoTumba >> nID >> name >> path;
			if (!gRecursos.carregouSpriteSheet(name))
				gRecursos.carregarSpriteSheet(name, path, 1, 1);
			sprite[nID].setSpriteSheet(name);
		}
		
		

		arquivoTumba.close();
	}
	else
	{
		exit(0);
	}
}
