// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#ifndef _JUEGOPM_H
#define _JUEGOPM_H
#include "matriz.h"

struct tJuegoPM{
    int modo = 0, MAX_ACCIONES = 0, actionsUsed = 0;
    tMatrizChar inicial, objetivo;
};

void mainJuegoPM();  // funcion principal del juego
int menu();    // Elegir entre modo 1D y 2D, o salir
bool iniciar(tJuegoPM &jpm, int modo);  // inicia parametros del juego
bool cargar(tJuegoPM &jpm);     //abre el fichero que corresponde y llama funcion cargar modulo Matriz
void mostrar(tJuegoPM const &jpm);   //muestra estado del reto utilizando modulo utilidades SYS 1 IMAGEN modificando y luego la objetivo y los intentos que quedan
bool jugar(tJuegoPM &jpm);			 //permite realizar acciones necesarias para jugar y controla si ha llegado al limite acciones permitidas
void accion(tJuegoPM &jpm);			 //segun que accion quiere el usuario llama a la accion en el modulo matriz
void mostrarAcciones(const int modo); // Muestra acciones posibles (dependiendo de jpm.modo)

#endif