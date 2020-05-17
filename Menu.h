#ifndef MENU_H_
#define MENU_H_
#include <curses.h>

class Menu
{
	private:
		static int MAX_X;
		static int MAX_Y;
		static int contadorSalida;
		static int MAX;

	public:
		virtual ~Menu(){}
		void setMAX_X(int a) {this->MAX_X = a;}
		void setMAX_Y(int a) {this->MAX_Y = a;}
		void setContadorSalida(int a) {this->contadorSalida = a;}
		void setMAX(int a) {this->MAX = a;}

		int getMAX_X()const {return this->MAX_X;}
		int getMAX_Y()const {return this->MAX_Y;}
		int getContadorSalida()const {return this->contadorSalida;}
		int getMAX()const {return this->MAX;}

		void tamanyoTerminal();

		virtual void desplegarMenu() = 0;
};


#endif