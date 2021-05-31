// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#include "juegoPM.h"
#include "UtilidadesSYS.h"
#include "ListaPuzzles_Opcional.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void mainPuzzlesReunidos(){
    chcp1252();
    borrar();

    tPuzzlesReunidos jpm;
    bool jugando = true;

    while (jugando) {
        init(jpm);              // Inicializar listas y puzzles con datosPuzzles.txt
        int modo = menu();      // Imprimir menu de opciones
        if (modo == 0) jugando = false;     // Salir del juego si opcion == 0
        else {
            int numPuzzle;
            switch (modo) {
            case 1:
                // Elegir puzzle 1D y jugar
                numPuzzle = elegirPuzzle(jpm[0]);
                if(numPuzzle != -1) mainPuzzle((*jpm[0].lista[numPuzzle]));
                break;
            case 2:
                // Elegir puzzle 2D y jugar
                numPuzzle = elegirPuzzle(jpm[1]);
                if(numPuzzle != -1) mainPuzzle((*jpm[1].lista[numPuzzle]));
                break;
            case 3:
                // Añadir puzzle a lista
                nuevoPz(jpm);
            default:
                break;
            }
        }
    }

    // Borrar listas del juego y liberar memoria
    for (int i = 0; i < 2; i++) {
        for (int x = 0; x < jpm[i].numPuzzles; x++) delete jpm[i].lista[x];  // Borrar punteros puzzle
        delete [] jpm[i].lista; // Borrar punteros lista para parte Opcional
    }
    cout << "Bye!\n";
}

int menu(){
    int option;
    bool validInput = false;
    do{
        cout << "1. Resolver un puzzle 1D\n";
        cout << "2. Resolver un puzzle 2D\n";
        cout << "3. Agregar un puzzle al catalogo\n";
        cout << "0. Salir\n";
        cout << "Option: ";
        cin >> option;
        borrar();
        if (option >= 0 && option < 4) validInput = true;
    }while(!validInput);
    return option;
}