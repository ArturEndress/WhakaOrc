#include "libunicornio.h"
#pragma once

class Mouse
{
public:
	Mouse();
	~Mouse();

	void inicializar();
	void desenhar();
	void atualizar();
	void setCorAlpha() { sprite.setCorAlpha(rand() % 2 - 1); };
	void setCorAplhaNormal() { sprite.setCorAlpha(-1); };
protected:
	Sprite sprite;
};

