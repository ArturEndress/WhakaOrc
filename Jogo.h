#pragma once
#include "libUnicornio.h"
#include "Cenario.h"

enum Tela { tMenu, tJogo, tComandos, tGameOver, tSair, tTrocaFase,tFinal };
class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

	void telaMenu();
	void telaJogo();
	void telaComandos();
	void telaGameOver();
	void telaTrocaFase();
	void telaFinal();

protected:
	Cenario cenario;

	Sprite spriteMenu, spriteTelaComandos, spriteTelaPause, spriteGameOver, spriteFinal;
	Tela telaAtual;
	bool estaComPause, trocouFase;
	BotaoSprite bJogar, bSair, bComandos, bVoltar;
	Texto tGold, tFase, tHp;
};

