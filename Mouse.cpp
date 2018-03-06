#include "Mouse.h"



Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}


void Mouse::atualizar()
{
	if (gMouse.segurando[BOTAO_MOUSE_ESQ])
	{
		sprite.setAnimacao(1);
	}
	else
		sprite.setAnimacao(0);

}

void Mouse::inicializar()
{

	if (!gRecursos.carregouSpriteSheet("mouse"))
	{
		gRecursos.carregarSpriteSheet("mouse", "imagens/mousetemp.png", 2, 1);
	}
	sprite.setSpriteSheet("mouse");

}

void Mouse::desenhar()
{
	sprite.desenhar(gMouse.x, gMouse.y);
}



