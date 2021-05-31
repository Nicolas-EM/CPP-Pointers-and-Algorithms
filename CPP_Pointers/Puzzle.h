// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#ifndef PUZZLE_H
#define PUZZLE_H
#include <string>
#include "matriz.h"

typedef struct tPuzzle {
	std::string name, file;			// Nombre y archivo del Puzzle
	int modo, maxMoves, actionsUsed = 0;	// Modo (1 o 2), num movimientos maximos y acciones usadas
	tMatrizChar inicial, objetivo;		// Matrices
} tPuzzle;

void mainPuzzle(tPuzzle& p);  // funcion principal del juego
bool cargar(tPuzzle& p);     //abre el fichero que corresponde y llama funcion cargar modulo Matriz
void mostrar(const tPuzzle &jpm);   //muestra estado del reto utilizando modulo utilidades SYS 1 IMAGEN modificando y luego la objetivo y los intentos que quedan
bool jugar(tPuzzle& jpm);			 //permite realizar acciones necesarias para jugar y controla si ha llegado al limite acciones permitidas
void accion(tPuzzle& jpm);			 //segun que accion quiere el usuario llama a la accion en el modulo matriz
void mostrarAcciones(const int modo);  // mostrar acciones disponibles
void mostrar(const tMatrizChar& mat); // Mostrar cualquier matriz

#endif