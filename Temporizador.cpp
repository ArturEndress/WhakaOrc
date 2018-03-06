#include "Temporizador.h"


Temporizador::Temporizador()
{
	tInicial = tFinal = contando = 0;
}

Temporizador::~Temporizador()
{
}

void Temporizador::resetar()
{
	tInicial = tFinal = contando = 0;
	inicializado = 0;
}

void Temporizador::inicializar()
{
	contando = inicializado = true;
	tInicial = clock();
}

float Temporizador::tempoDecorrido()
{
	if (inicializado)
	{
		if (contando)
			return (float)(clock() - tInicial) / CLOCKS_PER_SEC;
		else
			return (float)(tFinal - tInicial) / CLOCKS_PER_SEC;
	}
	else
		return 0.0;
}

float Temporizador::parar()
{
	if (inicializado)
	{
		contando = inicializado = false;
		tFinal = clock();
		return (float)(tFinal - tInicial) / CLOCKS_PER_SEC;
	}
	else
		return 0.0;
}