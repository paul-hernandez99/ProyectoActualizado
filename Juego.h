#ifndef JUEGO_H_
#define JUEGO_H_
#include <curses.h>
#include "Asteroide.h"
#include "Nave.h"

class Juego
{
	int ALTO;
	int IZQUIERDA;
	int BAJO;
	int DERECHA;

	int alturaTerminal;
	int anchuraTerminal;
public:
	Juego();
	virtual ~Juego(){}
	virtual void pintarAsteroides(WINDOW* ventana, Asteroide* asteroides, int* num_ast) = 0;
	virtual void subirNivel(Asteroide* asteroides, int* num_ast) = 0;
	virtual void mostrarGameOver() = 0;
	virtual int menuSalida() = 0;
	virtual WINDOW* mostrarInfo() = 0;
	virtual WINDOW* mostrarJuego() = 0;
	virtual void tamanyoTerminal() = 0;
	 //virtual void jugar(Usuario* usuarios, int player);
	virtual void nuevoAsteroideVertical(Asteroide* asteroide) = 0;
	virtual void nuevoAsteroideHorizontal(Asteroide* asteroide) = 0;
	virtual void pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide) = 0;
	virtual void pintarAsteroideHorizontal(WINDOW* ventana, Asteroide* asteroide) = 0;
	virtual int choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide) = 0;

	int getAlto() const;
	void setAlto(int alto);
	int getIzquierda() const;
	void setIzquierda(int izquierda);
	int getBajo() const;
	void setBajo(int bajo);
	int getDerecha() const;
	void setDerecha(int derecha);

	int getAlturaTerminal() const;
	void setAlturaTerminal(int altura);
	int getAnchuraTerminal() const;
	void setAnchuraTerminal(int altura);
};

#endif