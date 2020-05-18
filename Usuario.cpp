#include "Usuario.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int Usuario::MAX = 350;

Usuario::Usuario()
{
	this->guardado=0;
}
Usuario::~Usuario()
{
	delete [] nickname;
	delete [] contrasenya;
	delete [] puntuaciones;
	delete[] objects;
	
}
void Usuario::setNickname (char* n) 
{
	this->nickname = new char[strlen(n)+1];
	strcpy(this->nickname, n);
}
void Usuario::setContrasenya (char* n) 
{
	this->contrasenya = new char[strlen(n)+1];
	strcpy(this->contrasenya, n);
}
void Usuario::setPuntuaciones (float* n) 
{
	this->puntuaciones = new float [2];
	this->puntuaciones[0] = n[0];
	this->puntuaciones[1] = n[1];
}

void Usuario::setPuntuacionClasico (float f)
{
	this->puntuaciones[0] = f;
}

void Usuario::setPuntuacionSupervivencia (float f)
{
	this->puntuaciones[1] = f;
}


void Usuario::setGuardado (int n)
{
	this->guardado = n;
}

int* Usuario::getObjects() const
{
	return this->objects;
}
void Usuario::setObjects()
{
	this->objects = new int[170];
}

Usuario& Usuario::operator=(const Usuario &a)
{
	this->nickname = new char[strlen(a.nickname)+1];
	strcpy(this->nickname, a.nickname);

    this->contrasenya = new char[strlen(a.contrasenya)+1];
	strcpy(this->contrasenya, a.contrasenya);

    this->puntuaciones = new float [2];
    this->puntuaciones[0] = a.puntuaciones[0];
    this->puntuaciones[1] = a.puntuaciones[1];

    return *this;
}

Usuario* Usuario::leerUsuarios(FILE *file, int* size)
{
	char* linea = new char[MAX];
	char** items = new char*[170];

	fgets(linea, MAX, file);
	sscanf(linea, "%d", size);

	Usuario* usuarios = new Usuario [*size];

	int contador = 0;
	while(fgets(linea, MAX, file))
	{
		char* token = strtok(linea, ";");
		int i=0;
		while(token != NULL)
		{
			items[i] = token;
			token = strtok(NULL, ";");
			i++;
		}

		usuarios[contador].nickname = new char [strlen(items[0])+1];
		strcpy(usuarios[contador].nickname, items[0]);

		usuarios[contador].contrasenya = new char [strlen(items[1])+1];
		strcpy(usuarios[contador].contrasenya, items[1]);

		usuarios[contador].puntuaciones = new float [2];
		usuarios[contador].puntuaciones[0] = strtof(items[2], NULL);
		usuarios[contador].puntuaciones[1] = strtof(items[3], NULL);

		int a = atoi(items[4]);

		usuarios[contador].guardado = atoi(items[4]);
		
		if(usuarios[contador].guardado==1)
		{
			int i = 5;
			while(objects[i] != -1)
			{
				usuarios[contador].objects[i-5] = atoi(items[i]);
				i++;
			}
			/*
			usuarios[contador].setObjects();

			usuarios[contador].objects[0]=atoi(items[5]);
			usuarios[contador].objects[1]=atoi(items[6]);
			usuarios[contador].objects[2]=atoi(items[7]);
			usuarios[contador].objects[3]=atoi(items[8]);

			usuarios[contador].objects[4]=atoi(items[9]); //Metemos num asteroides

			int j = usuarios[contador].objects[4];
			int aux = 5;

			for(int i=10;i<10+j;i++)
			{
				usuarios[contador].objects[aux] = atoi(items[i]);
				aux++;
			}

			usuarios[contador].objects[aux]=atoi(items[10+j]); //Metemos num balas
			aux++;
			int k=usuarios[contador].objects[aux];

			for(int i=10+j+1;i<10+j+1+k;i++)
			{
				usuarios[contador].objects[aux] = atoi(items[i]);
				aux++;
			}

			for(int i=10+j+1+k; i <10+j+1+k+4; i++)
			{
				usuarios[contador].objects[aux] = atoi(items[i]);
				aux++;
			*/
		}

		contador++;

	}
	delete [] linea;
	delete [] items;
	
	return usuarios;
}


void Usuario::escribirUsuarios(Usuario *usuarios, int size)
{
	FILE *file = fopen("Usuarios.txt", "w");
	if (file == NULL)
	{
		cout <<"Error al abrir el fichero Usuarios.txt\n";
		exit(-1);
	}

	fprintf(file, "%d\n", size);

	for (int i=0; i<size; i++)
	{
		fprintf(file, "%s;%s;%0.2f;%0.2f", usuarios[i].nickname, usuarios[i].contrasenya, usuarios[i].puntuaciones[0], usuarios[i].puntuaciones[1]);

		int* objects = usuarios[i].getObjects();
		
		if(usuarios[i].getGuardado()==1)
		{
			int i=0;
			while(objects[i] != -1)
			{
				fprintf(file, ";%d", objects[i]);
				i++;
			}
			fprintf(file, ";-1\n");
		}
		else
			fprintf(file, ";0\n");
	}

	fclose(file);
	delete file;
}
