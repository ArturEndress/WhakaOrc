#include "Inimigo.h"



Inimigo::Inimigo()
{
}


Inimigo::~Inimigo()
{
}


//// SETA AS VARIAVEIS NA INICIALIZAÇÃO E UTILIZA O METODO 'CARREGAR'

void Inimigo::inicializar()
{
	carregarInimigo();
	vivo = false;
	x = -64;
	y = -64;
	hp = 1;
	v = 1;
	gold = 0;
	for (int i = 0; i < 5; i++)
	{
		sprite[i].setVelocidadeAnimacao(5);
	}
}


//// FAZ O DESENHO DO INIMIGO


void Inimigo::desenhar()
{
	sprite[tipo].desenhar(x, y);
}

////FAZ A MOVIMENTAÇÃO DO INIMIGO E MATA ELE AO SAIR DA TELA

void Inimigo::atualizar()
{
	x -= v;
	for (int i = 0; i < 5; i++)
	{
		sprite[i].avancarAnimacao();
	}
	if (x < -68)
		vivo = false;

}


/////REDUZ HP DO INIMIGO

void Inimigo::reduzirHp()
{
	hp--;
}

////SETA O TIPO DE INIMIGO, POSIÇÃO INICIAL E TORNA VIVO. TAMBÉM SETA O HP E VELOCIDADE PARA CADA TIPO DE INIMIGO


void Inimigo::criar(float x, float y, int tipo)
{
	this->x = x;
	this->y = y;
	vivo = true;
	this -> tipo = tipo;

	switch (tipo)
	{
	case 0: hp = 1,
		v = 1,
		gold = 100;
		break;
	case 1: hp = 2,
		v = 1,
		gold = 200;
		break;
	case 2: hp = 1,
		v = 2,
		gold = 200;
		break;
	case 3: hp = 2,
		v = 2,
		gold = 300;
		break;
	case 4: hp = 3,
		v = 2,
		gold = 500;
		break;
	default:
		break;
	}
	
}


//// FAZ O CARREGAMENTO DOS INIMIGOS A PARTIR DO ARQUIVO


void Inimigo::setAnim(int anim)
{
	for (int i = 0; i < 5; i++)
	{
		sprite[i].setAnimacao(anim);
	}
}

void Inimigo::carregarInimigo()
{
	string nome, path, arquivo;
	int nAnim, nFrames, nID;

	fstream arquivoInimigo;

	arquivo = "inimigos/inimigo.txt";

	arquivoInimigo.open(arquivo);
	if (arquivoInimigo.is_open())
	{
		arquivoInimigo >> nInimigos;

		for (int i = 0; i < nInimigos; i++)
		{
			arquivoInimigo >> nID >> nome >> path >> nAnim >> nFrames;
			if (!gRecursos.carregouSpriteSheet(nome))
				gRecursos.carregarSpriteSheet(nome, path, nAnim, nFrames);
			sprite[nID].setSpriteSheet(nome);
		}



		arquivoInimigo.close();
	}
	else
	{
		exit(0);
	}
}

