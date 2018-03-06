#include "libUnicornio.h"
#pragma once
class Tumba
{
public:
	Tumba();
	~Tumba();

	void inicializar();
	void desenhar(float x, float y);
	float getX() { return x; };
	float getY() { return y; };
	int getHp() { return hp; };
	void reduzirHp() { hp--; };
	bool getVivo() { return vivo; };
	void setMorto() { vivo = false; };


protected:
	void carregar();
	
	Sprite sprite[1];

	int nTumbas, hp;
	float x, y;
	bool vivo;
};

