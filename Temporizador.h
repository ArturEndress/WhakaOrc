#pragma once
#include <ctime>

class Temporizador
{
public:
	Temporizador();
	~Temporizador();
	void resetar();
	void inicializar();
	bool getContando() { return contando; };
	float tempoDecorrido();
	float parar();
private:
	clock_t tInicial, tFinal;
	bool contando, inicializado;
};