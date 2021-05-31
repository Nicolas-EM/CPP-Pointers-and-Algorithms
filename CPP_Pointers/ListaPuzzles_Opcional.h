// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#ifndef LISTAPUZZLE_OPCIONAL_H
#define LISTAPUZZLE_OPCIONAL_H
#include "Puzzle.h"

const int MAX_PUZZLE = 3;   // Numero maximo inicial de Puzzles

typedef tPuzzle* tPtrPuzzle;    // Puntero a tPuzzle

typedef struct tListaPuzzle {
    tPtrPuzzle *lista = new tPtrPuzzle[MAX_PUZZLE];     // Array dinamico a punteros tPuzzle
    int numPuzzles = 0, maxSize = MAX_PUZZLE;           // Numero de Puzzles en array y tamaño maximo de array
} tListaPuzzle;

typedef tListaPuzzle tPuzzlesReunidos[2];       // Array para listas 1D y 2D

void init(tPuzzlesReunidos& jr);        // Inicializar listas
bool cargar(tPuzzlesReunidos& jr);      // Cargar puzzles
int elegirPuzzle(tListaPuzzle& lp);     // Menu para elegir Puzzle que se quiere jugar
void mostrarPuzzles(const tListaPuzzle& lp);        // Mostrar Puzzles disponibles
void mergeSort(tListaPuzzle& lista, int ini, int fin, int modo);        // Ordenacion recursiva, separa lista en "Izq" y "Der"
void merge(tListaPuzzle& lista, int ini, int mid, int fin, int modo);   // Une "Izq" y "Der"
void nuevoPz(tPuzzlesReunidos& pr);     // Crear nuevo Puzzle
bool insertOrd(tListaPuzzle& l, tPuzzle* p);        // // Insertar nuevo puzzle en lista ordenada
bool buscar(const tListaPuzzle& lista, tPuzzle* puzzle, int ini, int fin, int& pos);	// Busqueda recursiva - un puzzle en la lista comparando FICHEROS
void resize(tListaPuzzle& lista, int size);         // Incrementa tamaño de array dinamico a punteros de tPuzzle
void guardar(const tPuzzlesReunidos& listas);       // Guardar listas
void guardar(std::ofstream& out, const tListaPuzzle lista);  // Guardar puzzles en lista a archivo de out

#endif