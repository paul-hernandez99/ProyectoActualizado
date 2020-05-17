#include "Juego.h"

Juego::Juego()
{
	initscr();
	getmaxyx(stdscr, this->alturaTerminal, this->anchuraTerminal);
}
int Juego::getAlto() const
{
	return this->ALTO;
}
void Juego::setAlto(int alto)
{
	this->ALTO = alto;
}
int Juego::getIzquierda() const
{
	return this->IZQUIERDA;
}
void Juego::setIzquierda(int izquierda)
{
	this->IZQUIERDA = izquierda;
}
int Juego::getBajo() const
{
	return this->BAJO;
}
void Juego::setBajo(int bajo)
{
	this->BAJO = bajo;
}
int Juego::getDerecha() const
{
	return this->DERECHA;
}
void Juego::setDerecha(int derecha)
{
	this->DERECHA = derecha;
}
int Juego::getAlturaTerminal() const
{
	return this->alturaTerminal;
}
void Juego::setAlturaTerminal(int altura)
{
	this->alturaTerminal = altura;
}
int Juego::getAnchuraTerminal() const
{
	return this->anchuraTerminal;
}
void Juego::setAnchuraTerminal(int anchura)
{
	this->anchuraTerminal = anchura;
}