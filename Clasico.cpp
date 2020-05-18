#include "Clasico.h"
#include <iostream>
#include <list>
using namespace std;
#ifdef _WIN32
	#include <windows.h>
	void sleepC(unsigned milliseconds)
	{
		Sleep(milliseconds);
	}
#else
	#include <unistd.h>

	void sleepC(unsigned int milliseconds)
	{
		usleep(milliseconds * 1000);
	}
#endif

const int Clasico::MAX_AST = 20;
const int Clasico::MAX_LENGHT = 15;
const int Clasico::MAX_BALAS = 200;

Clasico::Clasico(): Juego()
{
	this->setAlto(this->getAlturaTerminal()*0.13);
	this->setIzquierda((this->getAnchuraTerminal()*0.074)-1);
	this->setBajo((this->getAlturaTerminal() * 0.83)-3);
	this->setDerecha((this->getAnchuraTerminal() * 0.85)-6);
}
void Clasico::pintarAsteroides(WINDOW* ventana, Asteroide* asteroides, int* num_ast)
{
	for(int i=0; i<*num_ast; i++)
    {
    	if(asteroides[i].getTipo() == 0)
    		pintarAsteroideVertical(ventana, &asteroides[i]);
    	else
    		pintarAsteroideHorizontal(ventana, &asteroides[i]);
    }
}
Asteroide* Clasico::subirNivel(Asteroide* asteroides, int* num_ast)
{
	if(*num_ast < MAX_AST)
		return crearAsteroidesHorizontales(crearAsteroidesVerticales(asteroides, num_ast), num_ast);
	else
		return asteroides;
}
void Clasico::mostrarGameOver()
{
	int alturaVentanaClasico = this->getBajo();
	int anchuraVentanaClasico = this->getDerecha()+6;
	WINDOW* gameOver = newwin(Juego::getAlturaTerminal()/6,Juego::getAnchuraTerminal()/4,alturaVentanaClasico/4.2, anchuraVentanaClasico/2.3);
	refresh();
	box(gameOver,0,0);
	wmove(gameOver,2, 6);
	wprintw(gameOver, "GAME OVER");
	wrefresh(gameOver);
	wclear(gameOver);
	delwin(gameOver);
}
int Clasico::menuSalida()
{
	WINDOW* salida = newwin(this->getAlturaTerminal()/5,this->getAnchuraTerminal()-20,this->getAlturaTerminal()-(this->getAlturaTerminal()/5)-1, this->getIzquierda()+1);
    refresh();
    box(salida,0,0);
    keypad(salida, TRUE);

    const char** opciones = new const char*[2];
    for(int i=0; i<2; i++)
    {
    	opciones[i] = new char[MAX_LENGHT];
    }
    opciones[0] = "Jugar otra vez";
    opciones[1] = "Menu";

    int eleccion;
    int seleccion = 0;

    while(1)
    {
    	for(int i=0; i<2; i++)
    	{
    		if(i==seleccion)
    			wattron(salida, A_REVERSE);
    		mvwprintw(salida, i+1, 1, "%s", opciones[i]);
    		wattroff(salida, A_REVERSE);
    	}
    	wrefresh(salida);

    	eleccion = wgetch(salida);

    	switch(eleccion)
    	{
    		case KEY_UP:
    			seleccion--;
    			if(seleccion == -1)
    				seleccion = 0;
    			break;
    		case KEY_DOWN:
    			seleccion++;
    			if(seleccion == 2)
    				seleccion = 1;
    			break;
    		default:
    			break;
    	}
    	if(eleccion == 10)
    		break;
    }
    for(int i=0; i<2; i++)
    {
    	delete[] opciones[i];
    }
    delete[] opciones;

    wclear(salida);
    wrefresh(salida);
    delwin(salida);

    return seleccion;
}
WINDOW* Clasico::mostrarInfo()
{
	WINDOW* info = newwin(this->getAlturaTerminal()/4,this->getAnchuraTerminal()/1.7,this->getAlturaTerminal()/2.5, this->getAnchuraTerminal()/4);
	refresh();
	box(info,0,0);
	mvwprintw(info,1,1,"El juego consiste en que los asteroides no choquen con la nave.");
	mvwprintw(info,2,1,"Para mover la nave usa las flechas, y para diparar el espacio.");;
	mvwprintw(info,3,1,"Tu puntuacion dependera de la duracion de la partida y de los");
	mvwprintw(info,4,1,"asteroides abatidos. Buena suerte!");
	mvwprintw(info,5,1,"El juego esta a punto de empezar...");
	wrefresh(info);
	return info;
}
WINDOW* Clasico::mostrarJuego()
{
	WINDOW* ventana = newwin(this->getBajo()+3, this->getDerecha()+6, this->getAlto(), this->getIzquierda()+1);
    refresh();
    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    wbkgd(ventana, COLOR_PAIR(1));
    return ventana;
}
void Clasico::tamanyoTerminal()
{

}

void Clasico::nuevoAsteroideVertical(Asteroide* asteroide)
{
	asteroide->setX((rand()%(this->getDerecha()-this->getIzquierda()+1)) + this->getIzquierda());
	asteroide->setY(this->getAlto()-3);
}

void Clasico::nuevoAsteroideHorizontal(Asteroide* asteroide)
{
	asteroide->setX(this->getIzquierda()-2);
	asteroide->setY((rand()%(this->getBajo()-this->getAlto()+1)) + this->getAlto());
}
void Clasico::pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->getY(), asteroide->getX()); wprintw(ventana, "O");

	asteroide->setY(asteroide->getY()+1);

	if(asteroide->getY() == this->getBajo()+1)
	{
		nuevoAsteroideVertical(asteroide);
	}
	
}
void Clasico::pintarAsteroideHorizontal(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->getY(), asteroide->getX()); wprintw(ventana, "O");

	asteroide->setX(asteroide->getX()+1);

	if(asteroide->getX() == this->getDerecha()+1)
	{
		nuevoAsteroideHorizontal(asteroide);
	}
}
Bala* Clasico::crearBalas (Bala* balas, NaveClasico* nave, int* num_balas, int* disparosConsumidos)
{
	if(*disparosConsumidos < MAX_BALAS)
	{
		Bala* aux;

		if (*num_balas != 0)
		{
			aux = new Bala[*num_balas+2];
			for(int i=0; i<*num_balas; i++)
			{
				aux[i].setX(balas[i].getX());
				aux[i].setY(balas[i].getY());
			}
			delete[] balas;
		}
		else
			aux = new Bala[2];

		aux[*num_balas].setX(nave->getX()+1);
		aux[*num_balas].setY(nave->getY()-2);
		aux[*num_balas+1].setX(nave->getX()+2);
		aux[*num_balas+1].setY(nave->getY()-2);

		*num_balas += 2;
		*disparosConsumidos += 2;

		return aux;
	}
	else
		return balas;
}
void Clasico::mostrarPuntuacion (Usuario* usuarios, int player, float tiempo, int* disparosAcertados)
{
	float puntuacionTotal = tiempo*10 + *disparosAcertados;
	
	if(puntuacionTotal > usuarios[player].getPuntuaciones()[0])
		usuarios[player].setPuntuacionClasico(puntuacionTotal);

	WINDOW* puntuacion = newwin(7, 45, this->getAlturaTerminal()/2-3.5, this->getAnchuraTerminal()/2-22.5);
	refresh();
	box(puntuacion,0,0);
	wmove(puntuacion,1,2);
	wprintw(puntuacion, "Duracion: %0.2f",tiempo);
	wmove(puntuacion,2,2);
	wprintw(puntuacion,"Puntos por Duracion: %0.2f * 10 = %0.2f",tiempo, tiempo*10);
	wmove(puntuacion,3,2);
	wprintw(puntuacion, "Puntos por Disparos: %d",*disparosAcertados);
	wmove(puntuacion,4,2);
	wprintw(puntuacion,"----------------------------------");
	wmove(puntuacion,5,2);
	wprintw(puntuacion,"TOTAL: %0.2f", puntuacionTotal);
	wrefresh(puntuacion);
	wclear(puntuacion);
	delwin(puntuacion);
}
void Clasico::pintarChoqueAsteroideBala (WINDOW* ventana, Bala* balas, int j, int* num_balas)
{
	wmove(ventana, balas[j].getY(), balas[j].getX()); wprintw(ventana, "#");
	quitarBala(balas, j, num_balas);
}
int Clasico::choqueBalaAsteroide(WINDOW* ventana, Bala* balas, int j, int* num_balas, Asteroide* asteroide, int* disparosAcertados)
{
	if((balas[j].getX() == asteroide->getX()) && ((balas[j].getY() == asteroide->getY()+1) || (balas[j].getY() == asteroide->getY())) || (balas[j].getX()+1 == asteroide->getX()) && ((balas[j].getY() == asteroide->getY()+1) || (balas[j].getY() == asteroide->getY())))
	{
		if(asteroide->getTipo() == 0)
		{
			nuevoAsteroideVertical(asteroide);
		}
		else
		{
			nuevoAsteroideHorizontal(asteroide);
		}
		pintarChoqueAsteroideBala(ventana, balas, j, num_balas);
		(*disparosAcertados)++;
		return 1;
	}
	else
		return 0;
}
int Clasico::choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide)
{
	NaveClasico* aux = (NaveClasico*)nave;
	if((asteroide->getX() >= nave->getX()) && (asteroide->getX() <= nave->getX()+3) && (asteroide->getY() >= nave->getY()-1) && (asteroide->getY() <= nave->getY()))
	{
		aux->setCorazones(aux->getCorazones()-1);
		if(asteroide->getTipo() == 0)
		{
			nuevoAsteroideVertical(asteroide);
		}
		else
		{
			nuevoAsteroideHorizontal(asteroide);
		}
		return 1;
	}
	else
		return 0;
}

Bala* Clasico::quitarBala(Bala* balas, int i, int* num_balas)
{
	Bala* aux = new Bala[*num_balas-1];
	int contador = 0;
	for(int j=0; j<*num_balas; j++)
	{
		if(j!=i)
		{
			aux[contador].setX(balas[j].getX());
			aux[contador].setY(balas[j].getY());
			contador++;
		}
	}
	delete[] balas;
	(*num_balas)--;
	return aux;
}

Bala* Clasico::pintarBala(WINDOW* ventana, Bala* balas, int i, int* num_balas)
{
	mvwprintw(ventana, balas[i].getY(), balas[i].getX(), "^");

	balas[i].setY(balas[i].getY()-1);

	if(balas[i].getY() == this->getAlto()-2)
	{
		return quitarBala(balas, i, num_balas);
	}
	else
		return balas;
}
void Clasico::actualizarDisparosAcertados (int* disparosAcertados, int* disparosConsumidos)
{
	mvprintw(2, 45, "   ");
	mvprintw(2, 25, "Disparos Acertados: %d", *disparosAcertados);
	
	mvprintw(2, 62, "   ");
	mvprintw(2, 51, "Restantes: %d", (MAX_BALAS-*disparosConsumidos));
	refresh();
}
void Clasico::actualizarC(WINDOW* ventana, NaveClasico* nave, int* disparosAcertados, int* disparosConsumidos)
{
	nave->pintarVidas(0);
    actualizarDisparosAcertados(disparosAcertados, disparosConsumidos);
	werase(ventana);
	box(ventana, 0,0);
}
Asteroide* Clasico::crearAsteroidesHorizontales(Asteroide* asteroides, int* num_ast)
{
	Asteroide* aux = new Asteroide[*num_ast+2];
	for(int i=0; i<*num_ast; i++)
	{
		aux[i].setX(asteroides[i].getX());
		aux[i].setY(asteroides[i].getY());
		aux[i].setTipo(asteroides[i].getTipo());
	}
	delete[] asteroides;
	for(int i=0; i<2; i++)
	{
		aux[*num_ast].setX(this->getIzquierda()-2);
		aux[*num_ast].setY((rand()%(this->getBajo()-this->getAlto()+1)) + this->getAlto());
		aux[*num_ast].setTipo(1);
		(*num_ast)++;
	}
	return aux;
}
Asteroide* Clasico::crearAsteroidesVerticales(Asteroide* asteroides, int* num_ast)
{
	Asteroide* aux = new Asteroide[*num_ast+3];
	for(int i=0; i<*num_ast; i++)
	{
		aux[i].setX(asteroides[i].getX());
		aux[i].setY(asteroides[i].getY());
		aux[i].setTipo(asteroides[i].getTipo());
	}
	delete[] asteroides;
	for(int i=0; i<3; i++)
	{
		aux[*num_ast].setX((rand()%(this->getDerecha()-this->getIzquierda()+1)) + this->getIzquierda());
		aux[*num_ast].setY(this->getAlto()-3);
		aux[*num_ast].setTipo(0);
		(*num_ast)++;
	}
	return aux;
	cout << "yeah";
}


void Clasico::inicializarParametrosC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, int* num_balas, int* disparosAcertados, int* disparosConsumidos)
{
	nave->setX((this->getDerecha()+6)/2);
    nave->setY(3*(this->getBajo()+3)/4);
    nave->setCorazones(3);
    nave->setVidas(3);

    for(int i=0; i<5; i++)
    {
    	nuevoAsteroideVertical(&asteroides[i]);
    	asteroides[i].setTipo(0);
    }

	*num_ast = 5;
	*num_balas = 0;
	*disparosAcertados = 0;
	*disparosConsumidos = 0;
}

void Clasico::reanudarNave (int* objects, NaveClasico* nave)
{
	nave->setX(objects[0]);
	nave->setY(objects[1]);
	nave->setVidas(objects[2]);
	nave->setCorazones(objects[3]);
}

Asteroide* Clasico:: reanudarAsteroides(int* objects, int* num_ast)
{
	*num_ast = objects[4]/2;
	Asteroide* asteroides = new Asteroide[*num_ast];
	int contador = 5;
    for(int i=0; i<*num_ast;i++)
    {
    	asteroides[i].setX(objects[contador]);
    	asteroides[i].setY(objects[contador+1]);
    	asteroides[i].setTipo(objects[contador+2]);
    	contador += 3;
    }
    return asteroides;
}
Bala* Clasico::reanudarBalas(int* objects, int* num_balas)
{
    *num_balas = objects[5+objects[4]]/2;
    Bala* balas = new Bala[*num_balas];
    int contador = 5+objects[4] + 1; 
    for(int i=0; i<*num_balas; i++)
    {
    	balas[i].setX(objects[contador]);
    	balas[i].setX(objects[contador+1]);
    	contador += 2;
    }
    return balas;
}

void Clasico::reanudarParametros(int* objects, float* segundos, float* tiempo, int* disparosAcertados, int* disparosConsumidos)
{
	int aux = objects[5+objects[4]] + 5+objects[4] +1;

	*segundos = objects[aux];
	*tiempo = objects[aux+1];
	*disparosAcertados = objects[aux+2];
	*disparosConsumidos = objects[aux+3];
}

void Clasico::liberarMemoriaC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, int* disparosConsumidos, WINDOW* ventana)
{
	delete nave;
    delete[] asteroides;
    delete num_ast;
    delete[] balas;
    delete num_balas;
    delete disparosAcertados;
    delete disparosConsumidos;
    wclear(ventana);
    wrefresh(ventana);
    delwin(ventana);
    clear();
    refresh();
}
void Clasico::reestablecerValoresC(Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, int* disparosConsumidos)
{
	for(int i=0; i<*num_ast; i++)
	{
		asteroides[i].setX(0);
		asteroides[i].setY(0);
	}
	for(int i=0; i<*num_balas; i++)
	{
		balas[i].setX(0);
		balas[i].setY(0);
	}
	*num_ast = 0;
	*num_balas = 0;
	*disparosAcertados = 0;
	*disparosConsumidos = 0;
}
void Clasico::movimientosJugadorC(int tecla, NaveClasico* nave)
{
	switch(tecla)
    {
        case KEY_UP:

        	if(nave->getY() > this->getAlto())
        		nave->setY(nave->getY()-2);
            break;

        case KEY_DOWN:

        	if(nave->getY() < this->getBajo())
            	nave->setY(nave->getY()+2);
            break;

        case KEY_RIGHT:

        	if(nave->getX() < this->getDerecha()-1)
            	nave->setX(nave->getX()+2);
            break;

        case KEY_LEFT:

        	if(nave->getX() > this->getIzquierda())
            	nave->setX(nave->getX()-2);
            break;

        default:
        	break;
    }
}


void Clasico::guardarPartida(Usuario* usuarios, int player, NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int segundos, int tiempo, int* disparosAcertados, int* disparosConsumidos)
{
	usuarios[player].setGuardado(1);
	usuarios[player].setObjects();
	int* objects = usuarios[player].getObjects();
	int contador = 0;

	objects[0] = nave->getX();
	objects[1] = nave->getY();
	objects[2] = nave->getVidas();
	objects[3] = nave->getCorazones();

	objects[4] = (*num_ast)*2;

	contador = 5;
	if(*num_ast > 0)
	{
		for(int i=0; i<*num_ast; i++)
		{
			objects[contador] = asteroides[i].getX();
			objects[contador+1] = asteroides[i].getY();
			objects[contador+2] = asteroides[i].getTipo();
			contador+=3;
		}
	}

	objects[contador] = (*num_balas)*2;
	contador++;
	if(*num_balas > 0)
	{
		for(int i=0; i<*num_balas; i++)
		{	
			objects[contador] = balas[i].getX();
			objects[contador+1] = balas[i].getY();
			contador+=2;
		}
	}

	objects[contador] = segundos;
	contador++;
	objects[contador] = tiempo;
	contador++;
	objects[contador] = *disparosAcertados;
	contador++;
	objects[contador] = *disparosConsumidos;
	contador++;
	objects[contador] = -1;
	contador++;
}

void Clasico::jugar(Usuario* usuarios, int player)
{
	curs_set(0);

	WINDOW* info = mostrarInfo();

	sleepC(5000);

	wclear(info);
	wrefresh(info);
	delwin(info);

	move(1,3);
	printw("Bienvenido: MODO CLASICO");	    
	move(2,1); 
	printw("Vidas: ");
	move(2,12); 
	printw("Salud: ");

    WINDOW* ventana = mostrarJuego();

    NaveClasico* nave = new NaveClasico();
    Asteroide* asteroides = new Asteroide[5];
    Bala* balas;

    int* num_ast = new int();
    int* num_balas = new int();
    int* disparosConsumidos = new int();
    int* disparosAcertados = new int();

    float* segundos = 0;
    float* tiempo = 0;

    int choqueAsteroide = 0;
    int choqueBala = 0;
    int tecla;

    while(1)
    {
    	if(usuarios[player].getGuardado())
    	{
    		cout << "yeah";
    		reanudarNave(usuarios[player].getObjects(), nave);
    		cout << "yeah";
    		delete[] asteroides;
    		asteroides = reanudarAsteroides(usuarios[player].getObjects(), num_ast);
    		cout << "yeah";
    		delete[] balas;
    		balas = reanudarBalas(usuarios[player].getObjects(), num_balas);
    		cout << "yeah";
    		reanudarParametros(usuarios[player].getObjects(), segundos, tiempo, disparosAcertados, disparosConsumidos);
    		cout << "yeah";
    	}
	    else
	    {
	    	 inicializarParametrosC(nave, asteroides, num_ast, num_balas, disparosAcertados, disparosConsumidos);
	    }

	    while(1)
	    {
	        actualizarC(ventana, nave, disparosAcertados, disparosConsumidos);

	        if(*segundos > 30)
	        {
	        	asteroides = subirNivel(asteroides, num_ast);
	        	*segundos = 0;
	        }

	        for (int i=0; i<*num_ast; i++)
	        {
	        	for (int j=0; j<*num_balas; j++)
	        	{
					if(choqueBalaAsteroide(ventana, balas, j, num_balas, &asteroides[i], disparosAcertados))
	        		{
	        			choqueBala = 1;
	        			break;
	        		}
	        	}	
	        }
	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(choque(ventana, nave, &asteroides[i]))
	        	{
	        		choqueAsteroide = 1;
	        		break;	
	        	}
	        }
	        for (int i=0; i<*num_balas; i++)
	        {
	        	balas = pintarBala(ventana, balas, i, num_balas);
	        }

	        pintarAsteroides(ventana, asteroides, num_ast);
	        
	        if(!choqueAsteroide)
	        	nave->pintarNave(ventana);
	        else
	        	nave->pintarNaveChoque(ventana);

	        wrefresh(ventana);

	        if(choqueAsteroide)
	        {
	        	sleepC(500);
	        }
	        if(choqueBala)
	        {
	        	sleepC(50);
	        }

	        if(nave->getCorazones() == 0)
        	{
        		nave->setVidas(nave->getVidas()-1);
        		nave->setCorazones(3);
        	}

	    	tecla = wgetch(ventana);
	    	movimientosJugadorC(tecla, nave);
	    	if(tecla == 32)
	    	{
	    		balas = crearBalas(balas, nave, num_balas, disparosConsumidos);
	    	}

	    	if(nave->getVidas() == 0 || tecla==115 || tecla==103)
        	{
        		if(tecla == 103)
        		{
        			//Mostrar etiqueta de Guardar partida
        			guardarPartida(usuarios, player, nave, asteroides, num_ast, balas, num_balas, *segundos, *tiempo, disparosAcertados, disparosConsumidos);
        		}
        		if(nave->getVidas() == 0)
        			mostrarGameOver();
        		mostrarPuntuacion(usuarios, player, *tiempo,disparosAcertados);
        		choqueAsteroide = 0;
	        	choqueBala = 0;
	        	*segundos = 0;
	        	*tiempo = 0;
        		break;
        	}
	    	
	        sleepC(50);
	        *segundos +=0.050;
	        *tiempo +=0.050;
	        choqueAsteroide = 0;
	        choqueBala = 0;
	    }
	    actualizarC(ventana, nave, disparosAcertados, disparosConsumidos);
	    if(menuSalida())
    		break;
    	reestablecerValoresC(asteroides, num_ast, balas, num_balas, disparosAcertados, disparosConsumidos);
    }
    liberarMemoriaC(nave, asteroides, num_ast, balas, num_balas, disparosAcertados, disparosConsumidos, ventana);
	endwin();
}