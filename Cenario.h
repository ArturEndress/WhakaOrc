#pragma once
#include "libUnicornio.h"
#include "Tumba.h"
#include "Inimigo.h"
#include "Temporizador.h"
#include "Mouse.h"
#include <ctime>



class Cenario
{
public:
	Cenario();
	~Cenario();

	void inicializar();
	void desenhar();
	void atualizar();
	int getFaseAtual() { return faseAtual; };
	void setInimPos(int posInim);
	void criarInim();
	void testarColisao();
	int getGold() { return gold; };
	int getFase() { return faseAtual; };
	int getHp() { return hp; };
	void resetarContadores();
	void aumentarFase(){ faseAtual++; };
	void reiniciarJogo() { faseAtual = 1; };
	int getNumTumbas() { return nTumbas; };


	void setInimigoMorto(int i) { inimigo[i].setMorto(); };

	protected:
	void carregarFase(int f);


	Sprite tiles[3], hud, buffMartelo, bDebuffVel, morte, guarda, p2;
	int nColunas, nLinhas, nTiles, posC, posL, nInim, hp, tipoInim,
		novosInim, sorteioInim, nTumbas, totalTumbas, gold,
		mapaCenario[8][6],mapaTumbas[8][6], faseAtual = 1;
	bool podeCriar, powerUp, debuffVel, matar, podeMachucar;
	float p2x, p2y;
	Tumba *tumba;
	Mouse mouse;
	Inimigo *inimigo;
	Temporizador relogio, contadorInimigo, contadorBuff, contadorMachucar;
	Uint64 tempo;

	
	

};

