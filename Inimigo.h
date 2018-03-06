#include "libunicornio.h"
#pragma once



class Inimigo
{
public:
	Inimigo();
	~Inimigo();

	void inicializar();
	void desenhar();
	void atualizar();
	void reduzirHp();
	void criar(float x, float y, int tipo);
	void setMorto() { vivo = false; };
	void setVivo() { vivo = true; };
	bool getVivo() { return vivo; };
	float getX() { return x; };
	float getY() { return y; };
	int getHp() { return hp; };
	int getGold() { return gold; };
	void reduzirSpd() { v -= 0.5; };
	void setAnim(int anim);
	void setX(float x) { this->x = x; };

	Sprite getSprite(int s) { return sprite[s]; };

protected:
	void carregarInimigo();
	

	Sprite sprite[5];
	int nInimigos, tipo;
	int hp, gold;
	float x, y, v;
	bool vivo;
	

};

