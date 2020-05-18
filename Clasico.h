#ifndef CLASICO_H_
#define CLASICO_H_
#include <curses.h>
#include "Juego.h"
#include "NaveClasico.h"
#include "Asteroide.h"
#include "Bala.h"
#include "Usuario.h"

class Clasico: public Juego
{
	static const int MAX_AST;
	static const int MAX_BALAS;
	static const int MAX_LENGHT;
public:
	Clasico();
	virtual ~Clasico(){}
	virtual void pintarAsteroides(WINDOW* ventana, Asteroide* asteroides, int* num_ast);
	virtual Asteroide* subirNivel(Asteroide* asteroides, int* num_ast);
	virtual void mostrarGameOver();
	virtual int menuSalida();
	virtual WINDOW* mostrarInfo();
	virtual WINDOW* mostrarJuego();
	virtual void tamanyoTerminal();
	virtual void jugar(Usuario* usuarios, int player);
	virtual void nuevoAsteroideVertical(Asteroide* asteroide);
	virtual void nuevoAsteroideHorizontal(Asteroide* asteroide);
	virtual void pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide);
	virtual void pintarAsteroideHorizontal(WINDOW* ventana, Asteroide* asteroide);
	virtual int choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide);
	void reanudarNave (int* objects, NaveClasico* nave);
	Asteroide* reanudarAsteroides(int* objects, int* num_ast);
	Bala* reanudarBalas(int* objects, int* num_balas);
	void reanudarParametros(int* objects, float* segundos, float* tiempo, int* disparosAcertados, int* disparosConsumidos);
	void guardarPartida(Usuario* usuarios, int player, NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int segundos, int tiempo, int* disparosAcertados, int* disparosConsumidos);
	Bala* crearBalas (Bala* balas, NaveClasico* nave, int* num_balas, int* disparosConsumidos);
	void mostrarPuntuacion (Usuario* usuarios, int player, float tiempo, int* disparosAcertados);
	void pintarChoqueAsteroideBala (WINDOW* ventana, Bala* balas, int j, int* num_balas);
	int choqueBalaAsteroide(WINDOW* ventana, Bala* balas, int j, int* num_balas, Asteroide* asteroide, int* disparosAcertados);
	Bala* quitarBala(Bala* balas, int i, int* num_balas);
	Bala* pintarBala(WINDOW* ventana, Bala* balas, int i, int* num_balas);
	void actualizarDisparosAcertados (int* disparosAcertados, int* disparosConsumidos);
	void actualizarC(WINDOW* ventana, NaveClasico* nave, int* disparosAcertados, int* disparosConsumidos);
	Asteroide* crearAsteroidesHorizontales(Asteroide* asteroides, int* num_ast);
	Asteroide* crearAsteroidesVerticales(Asteroide* asteroides, int* num_ast);
	void inicializarParametrosC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, int* num_balas, int* disparosAcertados, int* disparosConsumidos);
	void liberarMemoriaC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, int* disparosConsumidos, WINDOW* ventana);
	void reestablecerValoresC(Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, int* disparosConsumidos);
	void movimientosJugadorC(int tecla, NaveClasico* nave); //Se puede poner virtual comun a los dos
};

#endif