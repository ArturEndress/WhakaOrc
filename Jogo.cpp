#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(1024, 968, true);

	cenario.inicializar();
	trocouFase = false;

	telaAtual = tMenu;

	if (!gRecursos.carregouFonte("fonte"))
	{
		gRecursos.carregarFonte("fonte", "fontes/Adorable.otf", 32);
	}

	tGold.setAncora(0, 2);
	tGold.setFonte("fonte");
	tGold.setCor(255, 255, 255);

	tFase.setAncora(0, 2);
	tFase.setFonte("fonte");
	tFase.setCor(0, 0, 0);

	tHp.setAncora(0, 2);
	tHp.setFonte("fonte");
	tHp.setCor(255, 255, 255);

	if (!gRecursos.carregouSpriteSheet("menu"))
	{
		gRecursos.carregarSpriteSheet("menu", "imagens/FundoMenu.png");
	}
	spriteMenu.setSpriteSheet("menu");

	if (!gRecursos.carregouSpriteSheet("instrucoes"))
	{
		gRecursos.carregarSpriteSheet("instrucoes", "imagens/instrucoes.png");
	}
	spriteTelaComandos.setSpriteSheet("instrucoes");

	if (!gRecursos.carregouSpriteSheet("pause"))
	{
		gRecursos.carregarSpriteSheet("pause", "imagens/FundoPause2.png");
	}
	spriteTelaPause.setSpriteSheet("pause");

	if (!gRecursos.carregouSpriteSheet("gameOver"))
	{
		gRecursos.carregarSpriteSheet("gameOver", "imagens/GameOver.png");
	}
	spriteGameOver.setSpriteSheet("gameOver");

	if (!gRecursos.carregouSpriteSheet("final"))
	{
		gRecursos.carregarSpriteSheet("final", "imagens/TelaFinal.png");
	}
	spriteFinal.setSpriteSheet("final");


	//////////////////CARREGAR MUSICA///////////////////////////
	if (!gRecursos.carregouMusica("musica"))
	{
		gRecursos.carregarMusica("musica", "sons/epico.mp3");
	}


	/////////////////////CARREGAR BOTOES/////////////////////
	if (!gRecursos.carregouSpriteSheet("bJogar"))
	{
		gRecursos.carregarSpriteSheet("bJogar", "imagens/jogar.png", 3, 1);
	}
	bJogar.setSpriteSheet("bJogar");
	bJogar.setPos(gJanela.getLargura() / 2, 360);

	if (!gRecursos.carregouSpriteSheet("bComandos"))
	{
		gRecursos.carregarSpriteSheet("bComandos", "imagens/comandos.png", 3, 1);
	}
	bComandos.setSpriteSheet("bComandos");
	bComandos.setPos(gJanela.getLargura() / 2, 460);

	if (!gRecursos.carregouSpriteSheet("bSair"))
	{
		gRecursos.carregarSpriteSheet("bSair", "imagens/sair.png", 3, 1);
	}
	bSair.setSpriteSheet("bSair");
	bSair.setPos(gJanela.getLargura() / 2, 560);


	if (!gRecursos.carregouSpriteSheet("bVoltar"))
	{
		gRecursos.carregarSpriteSheet("bVoltar", "imagens/voltar.png", 3, 1);
	}
	bVoltar.setSpriteSheet("bVoltar");
	bVoltar.setPos(200, 650);

	estaComPause = false;


	//	O resto da inicialização vem aqui!
	//	...
}

void Jogo::finalizar()
{
	//	O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
	//	...

	uniFinalizar();
}

void Jogo::telaMenu()
{
	gMouse.mostrarCursor();
	spriteMenu.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	bJogar.desenhar();
	bComandos.desenhar();
	bSair.desenhar();

	bJogar.atualizar();
	bComandos.atualizar();
	bSair.atualizar();

	if (bJogar.estaClicado())
	{
		telaAtual = tJogo;
		cenario.inicializar();
		
	}

	if (bComandos.estaClicado())
	{
		telaAtual = tComandos;
	}

	if (bSair.estaClicado())
	{
		telaAtual = tSair;
	}
}

void Jogo::telaJogo()
{
	
	

	if (gTeclado.pressionou[TECLA_ESC])
	{
		estaComPause = true;
	}


	/////////////////ATUALIZAR///////////////////////////
	if (!estaComPause)
	{
		gMouse.esconderCursor();
		cenario.atualizar();
		cenario.desenhar();
		tGold.setString("GOLD: " + to_string(cenario.getGold()));
		tGold.desenhar(10, 100);
		tHp.setString("HP: " + to_string(cenario.getHp()));
		tHp.desenhar(10, 140);

		if (cenario.getNumTumbas() == 0 && cenario.getFase() < 5)
		{
			telaAtual = tTrocaFase;
		}
		else if (cenario.getNumTumbas() == 0 && cenario.getFase() >= 5)
		{
			telaAtual = tFinal;
		}
		if (cenario.getHp() <= 0)
		{
			telaAtual = tGameOver;
		}

		///////////////////PAUSE///////////////////////////////////////
	}
	else
	{
		gMouse.mostrarCursor();
		spriteTelaPause.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
		bJogar.desenhar();
		bSair.desenhar();

		bJogar.atualizar();
		bSair.atualizar();

		if (bJogar.estaClicado())
		{
			estaComPause = false;
		}

		if (bSair.estaClicado())
		{
			telaAtual = tSair;
		}
	}
}

void Jogo::telaComandos()
{
	gMouse.mostrarCursor();
	spriteTelaComandos.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	bVoltar.desenhar();
	bVoltar.atualizar();
	if (bVoltar.estaClicado())
	{
		telaAtual = tMenu;
	}
}

void Jogo::telaGameOver()
{
	gMouse.mostrarCursor();
	spriteGameOver.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	bVoltar.desenhar();
	bVoltar.atualizar();
	if (bVoltar.estaClicado())
	{
		telaAtual = tMenu;
	}
}

void Jogo::telaTrocaFase()
{
	gMouse.mostrarCursor();
	spriteMenu.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	bJogar.desenhar();
	bSair.desenhar();

	tGold.setString("Fase: " + to_string(cenario.getFase()+1));
	tGold.desenhar(10, 100);


	bJogar.atualizar();
	bSair.atualizar();

	
	if (bJogar.estaClicado())
	{
		telaAtual = tJogo;
		trocouFase = true;
		if (trocouFase)
		{
			cenario.resetarContadores();
			cenario.aumentarFase();
			trocouFase = false;
		}
		
		cenario.inicializar();
	}
	else if (bSair.estaClicado())
	{
		telaAtual = tSair;
	}
	
}

void Jogo::telaFinal()
{
	spriteFinal.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	bVoltar.desenhar();
	bVoltar.atualizar();

	if (bVoltar.estaClicado())
	{
		telaAtual = tMenu;
	}
}

void Jogo::executar()
{
	gMusica.tocar("musica", true);

	while (!gEventos.sair)
	{
		uniIniciarFrame();

		while (!gEventos.sair)
		{
			uniIniciarFrame();
			///////////MENU////////////////////////
			switch (telaAtual)
			{
			case tMenu: telaMenu();
				break;
			case tJogo: telaJogo();
				break;
			case tComandos: telaComandos();
				break;
			case tGameOver:telaGameOver();
				break;
			case tTrocaFase: telaTrocaFase();
				break;
			case tFinal: telaFinal();
				break;
			case tSair: gEventos.sair = true;
				break;
			}




			uniTerminarFrame();
		}
	}
}