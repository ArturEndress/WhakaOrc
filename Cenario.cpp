#include "Cenario.h"




Cenario::Cenario()
{
}


Cenario::~Cenario()
{
	delete[] tumba;
	delete[] inimigo;
}

////////////////////////////////////////////////////////////////////////////////q// Carrega as fases e seta variáveis
void Cenario::inicializar()
{
	relogio.inicializar();
	contadorMachucar.inicializar();

	gTempo.inicializar();
	tempo = gTempo.getTicks();
	
	
	srand(time(0));
	
	carregarFase(faseAtual);
	
	p2x = gJanela.getLargura() / 2;
	p2y = gJanela.getAltura() / 2;
	posL = 0;
	posC = 0;
	novosInim = 1;
	nTumbas = 0;
	powerUp = false;
	debuffVel = false;
	matar = false;
	podeMachucar = true;

	gold = 0;
	hp = 5;

	for (int c = 0; c < 8; c++)
	{
		for (int l = 0; l < 6; l++)
		{
			if (mapaTumbas[c][l] >= 0)
			{
				nTumbas++;
			}
		}
	}
	totalTumbas = nTumbas;
	tumba = new Tumba[nTumbas];
	inimigo = new Inimigo[nInim];

	for (int i = 0; i < nTumbas; i++)
	{
		tumba[i].inicializar();
	}
	
	if (!gRecursos.carregouSpriteSheet("player2"))
	{
		gRecursos.carregarSpriteSheet("player2", "imagens/player2.png", 2, 1);
	}
	p2.setSpriteSheet("player2");

	if (!gRecursos.carregouSpriteSheet("guarda"))
	{
		gRecursos.carregarSpriteSheet("guarda", "imagens/guarda.png", 1, 4);
	}
	guarda.setSpriteSheet("guarda");
	guarda.setVelocidadeAnimacao(4);

	mouse.inicializar();
	podeCriar = true;

	for (int i = 0; i < nInim; i++)
	{
		inimigo[i].inicializar();
	}
	
	if (!gRecursos.carregouSpriteSheet("hud"))
	{
		gRecursos.carregarSpriteSheet("hud", "imagens/Hud.png", 1, 1);
	}
	hud.setSpriteSheet("hud");

	if (!gRecursos.carregouSpriteSheet("buffMartelo"))
	{
		gRecursos.carregarSpriteSheet("buffMartelo", "imagens/buffMarteloAnimado.png", 3, 1);
	}
	buffMartelo.setSpriteSheet("buffMartelo");
	buffMartelo.setAnimacao(0);
	
	if (!gRecursos.carregouSpriteSheet("debuffSpd"))
	{
		gRecursos.carregarSpriteSheet("debuffSpd", "imagens/debuffVel.png", 3, 1);
	}
	bDebuffVel.setSpriteSheet("debuffSpd");
	bDebuffVel.setAnimacao(0);

	if (!gRecursos.carregouSpriteSheet("matar"))
	{
		gRecursos.carregarSpriteSheet("matar", "imagens/matarInim.png", 3, 1);
	}
	morte.setSpriteSheet("matar");
	morte.setAnimacao(0);

	/* if (!gRecursos.carregouSpriteSheet("fundo"))
	{
		gRecursos.carregarSpriteSheet("fundo", "imagens/fundotemp.png");
	}
	spriteFundo.setSpriteSheet("fundo");
	*/
	
	
}

////////////////////////////////////////////////////////////////////////////////qq DESENHA ELEMENTOS DO CENARIO
void Cenario::desenhar()
{
	for (int l = 0; l < nLinhas; l++)
	{
		for (int c = 0; c < nColunas; c++)
		{
			tiles[mapaCenario[c][l]].desenhar(tiles[0].getLargura() / 2 + tiles[0].getLargura() * c,
				tiles[0].getAltura() / 2 + tiles[0].getAltura() * l);

		}
	}
	
	
	for (int c = 0; c < 8; c++)
	{
		for (int l = 0; l < 6; l++)
		{
			if (mapaTumbas[c][l] >= 0 && tumba[mapaTumbas[c][l]].getVivo())
			{
				tumba[mapaTumbas[c][l]].desenhar(64 + (128 * c), 64 + (128 * l));
			}
		}
	}
	
	
				guarda.desenhar(64 + (128 * 0), 64 + (128 * 1));
				guarda.desenhar(64 + (128 * 0), 64 + (128 * 2));
				guarda.desenhar(64 + (128 * 0), 64 + (128 * 3));
				guarda.desenhar(64 + (128 * 0), 64 + (128 * 4));
			
		
	

	for (int i = 0; i < nInim; i++)
	{
		if (inimigo[i].getVivo())
		{
			inimigo[i].desenhar();
		}
	}
	
	hud.desenhar(gJanela.getLargura()/2, 868);
	buffMartelo.desenhar(gJanela.getLargura()/2 + buffMartelo.getLargura(), 868);
	bDebuffVel.desenhar(gJanela.getLargura() / 2, 868);
	morte.desenhar(morte.getLargura()/2, 868);

	//spriteFundo.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	if (gJoysticks.player1.estaPlugado())
	{
		p2.desenhar(p2x, p2y);
	}
	mouse.desenhar();

	if (powerUp)
	{
		mouse.setCorAlpha();
		p2.setCorAlpha(rand() % 2 - 1);
	}
	else
	{
		mouse.setCorAplhaNormal();
		p2.setCorAlpha(-1);
	}
}

//////////////////////////////////////////////////////////////////////////// ATUALIZA JOGO

void Cenario::atualizar()
{
	

	criarInim();

	for (int i = 0; i < nInim; i++)
	{
		if (inimigo[i].getHp() == 0)
			inimigo[i].setMorto();
	}

	for (int i = 0; i < nInim; i++)
	{
		if (inimigo[i].getVivo() == true)
		{
			inimigo[i].atualizar();
		}
	}

	for (int c = 0; c < 8; c++)
	{
		for (int l = 0; l < 6; l++)
		{

			if (!tumba[mapaTumbas[c][l]].getVivo())
			{
				mapaTumbas[c][l] = -1;
			}
		}
	}

	mouse.atualizar();
	testarColisao();

	if (contadorBuff.tempoDecorrido() > 10)
	{
		powerUp = false;
		contadorInimigo.parar();
		contadorInimigo.resetar();
	}

	if (debuffVel)
	{
		for (int i = 0; i < nInim; i++)
		{
			inimigo[i].reduzirSpd();
		}
		debuffVel = false;
	}

	if (matar)
	{
		for (int i = 0; i < nInim; i++)
		{
			inimigo[i].setMorto();
		}
		matar = false;
	}

	guarda.avancarAnimacao();

	for (int i = 0; i < nInim; i++)
	{
		if (inimigo[i].getX() <= 128 && inimigo[i].getVivo())
		{
			inimigo[i].setMorto();
			if (podeMachucar)
			{
				hp--;
				podeMachucar = false;
				contadorMachucar.parar();
				contadorMachucar.resetar();
				contadorMachucar.inicializar();
			}
			
		}
	}
	if (contadorMachucar.tempoDecorrido() > 2)
	{
		podeMachucar = true;
	}
	if (gJoysticks.player1.estaPlugado())
	{
		if (gJoysticks.player1.segurando[BOTAO_XBOX_ESQ])
		{
			p2x -= 4;
		}
		if (gJoysticks.player1.segurando[BOTAO_XBOX_DIR])
		{
			p2x += 4;
		}
		if (gJoysticks.player1.segurando[BOTAO_XBOX_CIMA])
		{
			p2y -= 4;
		}
		if (gJoysticks.player1.segurando[BOTAO_XBOX_BAIXO])
		{
			p2y += 4;
		}
		if (gJoysticks.player1.segurando[BOTAO_XBOX_A])
		{
			p2.setAnimacao(1);
		}
		else
		{
			p2.setAnimacao(0);
		}
	}
}


	


//////////////////////////////////////SORTEIA UMA DAS TUMBAS PARA SPAWNAR INIMIGOS. TAMBEM ADICIONA NOVOS TIPOS DE INIMIGOS COM O TEMPO E SORTEIA O TIPO QUE SAI DA TUMBA

void Cenario::setInimPos(int posInim)
{
	if (nTumbas > 0)
	{
		if (podeCriar)
		{

			do
			{
				posC = rand() % 8;
				posL = rand() % 6;

			} while (mapaTumbas[posC][posL] < 0);

			if (inimigo[posInim].getVivo() == false)
			{
				if (novosInim < tipoInim)
				{
					if (gTempo.getTempoAteTickAtual(tempo) > 5)
					{
						tempo = gTempo.getTicks();
						

						novosInim++;

					}
				}
				sorteioInim = rand() % novosInim;


				inimigo[posInim].criar(64 + (128 * posC), 64 + (128 * posL), sorteioInim);
			}
			relogio.parar();
			relogio.resetar();
			relogio.inicializar();
			podeCriar = false;
		}

	
	}
}
//////////////////////////TESTA SE PODE-SE CRIAR INIMIGO, SE SIM, CRIA
void Cenario::criarInim()
{

	if (relogio.tempoDecorrido() >= (rand() % 20 * 0.1) + 0.8)
	{
		podeCriar = true;

		for (int i = 0; i < nInim; i++)
		{
			if (inimigo[i].getVivo() == false)
			{

				setInimPos(i);

				inimigo[i].setVivo();
				break;
			}	
		}

	}
}

void Cenario::testarColisao()
	{


		////Colisao Inimigos

		for (int i = 0; i < nInim; i++)
		{
			if (uniTestarColisaoCirculoComRetangulo(gMouse.x + 23, gMouse.y + 40, 23, inimigo[i].getX(), inimigo[i].getY(), 0, 53, 97, 0, 0))
			{
				if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
				{
					inimigo[i].reduzirHp();
					if (inimigo[i].getHp() <= 0 && inimigo[i].getVivo())
					{
						inimigo[i].setMorto();
						gold += inimigo[i].getGold();
					}
				}
			}
		}


	/////Colisao com tumbas

	for (int i = 0; i < totalTumbas; i++)
	{
		if (uniTestarColisaoCirculoComRetangulo(gMouse.x + 64, gMouse.y + 64, 23, tumba[i].getX(), tumba[i].getY(), 0, 128, 128, 0, 0) && powerUp)
		{
			if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
			{
				tumba[i].reduzirHp();
				if (tumba[i].getHp() <= 0 && tumba[i].getVivo())
				{
					tumba[i].setMorto();
					nTumbas--;
				}
			}
		}
	}

	if (uniTestarColisaoCirculoComSprite(gMouse.x, gMouse.y, 23, buffMartelo, gJanela.getLargura() / 2 + buffMartelo.getLargura(), 868, 0, true))
	{
		buffMartelo.setAnimacao(1);
		if (!powerUp)
		{
			if (gold >= 5000)
			{	
				if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
				{
					buffMartelo.setAnimacao(2);
					gold -= 5000;
					powerUp = true;
					contadorBuff.inicializar();
				}
			}
		}
	}
	else
	{
		buffMartelo.setAnimacao(0);
	}
	
	if (uniTestarColisaoCirculoComSprite(gMouse.x, gMouse.y, 23, bDebuffVel, gJanela.getLargura() / 2, 868, 0, true))
	{
		bDebuffVel.setAnimacao(1);
		if (!debuffVel)
		{
			if (gold > 1000)
			{
				if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
				{
					bDebuffVel.setAnimacao(2);
					gold -= 1000;
					debuffVel = true;
				}
			}
		}
	}
	else
	{
		 bDebuffVel.setAnimacao(0);
	}

	if (uniTestarColisaoCirculoComSprite(gMouse.x, gMouse.y, 23, morte, morte.getLargura() / 2, 868, 0, true))
	{
		morte.setAnimacao(1);
		if (!matar)
		{
			if (gold > 3000)
			{
				if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
				{
					morte.setAnimacao(2);
					gold -= 3000;
					matar = true;
				}
			}
		}
	}
	else
	{
		morte.setAnimacao(0);
	}


	//////////////COLISAO PLAYER 2

	for (int i = 0; i < nInim; i++)
	{
		if (uniTestarColisaoCirculoComRetangulo(p2x + 23, p2y + 40, 23, inimigo[i].getX(), inimigo[i].getY(), 0, 53, 97, 0, 0))
		{
			if (gJoysticks.player1.pressionou[BOTAO_XBOX_A])
			{
				inimigo[i].reduzirHp();
				if (inimigo[i].getHp() <= 0 && inimigo[i].getVivo())
				{
					inimigo[i].setMorto();
					gold += inimigo[i].getGold();
				}
			}
		}
	}

	for (int i = 0; i < totalTumbas; i++)
	{
		if (uniTestarColisaoCirculoComRetangulo(p2x + 64, p2y + 64, 23, tumba[i].getX(), tumba[i].getY(), 0, 128, 128, 0, 0) && powerUp)
		{
			if (gJoysticks.player1.pressionou[BOTAO_XBOX_A])
			{
				tumba[i].reduzirHp();
				if (tumba[i].getHp() <= 0 && tumba[i].getVivo())
				{
					tumba[i].setMorto();
					nTumbas--;
				}
			}
		}
	}

	if (uniTestarColisaoCirculoComSprite(p2x, p2y, 23, buffMartelo, gJanela.getLargura() / 2 + buffMartelo.getLargura(), 868, 0, true))
	{
		buffMartelo.setAnimacao(1);
		if (!powerUp)
		{
			if (gold >= 5000)
			{
				if (gJoysticks.player1.pressionou[BOTAO_XBOX_A])
				{
					buffMartelo.setAnimacao(2);
					gold -= 5000;
					powerUp = true;
					contadorBuff.inicializar();
				}
			}
		}
	}
	else
	{
		buffMartelo.setAnimacao(0);
	}

	if (uniTestarColisaoCirculoComSprite(p2x, p2y, 23, bDebuffVel, gJanela.getLargura() / 2, 868, 0, true))
	{
		bDebuffVel.setAnimacao(1);
		if (!debuffVel)
		{
			if (gold > 1000)
			{
				if (gJoysticks.player1.pressionou[BOTAO_XBOX_A])
				{
					bDebuffVel.setAnimacao(2);
					gold -= 1000;
					debuffVel = true;
				}
			}
		}
	}
	else
	{
		bDebuffVel.setAnimacao(0);
	}

	if (uniTestarColisaoCirculoComSprite(p2x, p2y, 23, morte, morte.getLargura() / 2, 868, 0, true))
	{
		morte.setAnimacao(1);
		if (!matar)
		{
			if (gold > 3000)
			{
				if (gJoysticks.player1.pressionou[BOTAO_XBOX_A])
				{
					morte.setAnimacao(2);
					gold -= 3000;
					matar = true;
				}
			}
		}
	}
	else
	{
		morte.setAnimacao(0);
	}
}

void Cenario::resetarContadores()
{
	if (relogio.getContando())
	{
		relogio.parar();
		relogio.resetar();
	}
	if (contadorInimigo.getContando())
	{
		contadorInimigo.parar();
		contadorInimigo.resetar();

	}
	if (contadorMachucar.getContando())
	{
		contadorMachucar.parar();
		contadorMachucar.resetar();
	}	
}



//// FAZ O CARREGAMENTO DAS FASES


void Cenario::carregarFase(int f)
{
	string name, path, arqName;
	int nID, nAnim, nFrames;
	ifstream arquivoFase;

	arqName = "fases/fase" + to_string(f) + ".txt";

	arquivoFase.open(arqName);
	if (arquivoFase.is_open())
	{
		
		arquivoFase >> tipoInim;
		arquivoFase >> nInim;
		arquivoFase >> nTiles;

		for (int t = 0; t < nTiles; t++)
		{
			arquivoFase >> nID >> name >> path >> nAnim >> nFrames;
			if (!gRecursos.carregouSpriteSheet(name))
				gRecursos.carregarSpriteSheet(name, path, nAnim, nFrames);
			tiles[nID].setSpriteSheet(name);
		}

	


		arquivoFase >> nColunas >> nLinhas;

		for (int l = 0; l < nLinhas; l++)
			for (int c = 0; c < nColunas; c++)
				arquivoFase >> mapaCenario[c][l];


		for (int l = 0; l < nLinhas; l++)
			for (int c = 0; c < nColunas; c++)
				arquivoFase >> mapaTumbas[c][l];

		
		arquivoFase.close();
	}
	else
	{
		exit(0);
	}
}
