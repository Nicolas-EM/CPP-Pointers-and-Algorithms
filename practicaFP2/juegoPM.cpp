// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#include "juegoPM.h"
#include "UtilidadesSYS.h"
#include <iostream>
#include <fstream>

using namespace std;

void mainJuegoPM(){
    tJuegoPM juego;
    bool jugando = true;
    while (jugando) {
        int modo = menu();
        if (iniciar(juego, modo)) {
            switch (juego.modo) {
            case 0:
                jugando = false;
                break;
            case 1:
                juego.modo = 1;
                break;
            case 2:
                juego.modo = 2;
                break;
            default:
                throw "Invalid input - menu() returned unknown value";
            }

            if (!jugar(juego) && jugando) {
                mostrar(juego);
                cout << "\n\t\t---------- GAME OVER --------\n\n";
            }
            else if (jugando) {
                mostrar(juego);
                cout << "\n\t\t---------- HAS GANADO!! -----------\n";
            }
            pausa();
        }
        else cout << "Failed to init mainJuegoPM()\n";
    }
    cout << "Bye!\n";
}

int menu(){
    int option;
    bool validInput = false;
    do{
        cout << "Que modo quieres jugar\n";
        cout << "0 - Salir\n";
        cout << "1 - Modo 1D\n";
        cout << "2 - Modo 2D\n";
        cout << "Opcion: ";
        cin >> option;
        if (option >= 0 && option < 3) validInput = true;
    }while(!validInput);
    return option;
}

bool iniciar(tJuegoPM &jpm, int modo){
    jpm.actionsUsed = 0;
    switch(modo){
        case 0:
            jpm.modo = 0;
            return true;
        case 1:
            jpm.modo = 1;
            break;
        case 2:
            jpm.modo = 2;
            break;
        default:
            throw "iniciar() - failed to assign mode\n";
    }
    return cargar(jpm);
}

bool cargar(tJuegoPM &jpm){
    string fichero;
    cout << "Introduce el nombre del fichero: ";
    cin >> fichero;
    fichero += ("_");
    fichero += (jpm.modo + 48);
    fichero += "D.txt";
    ifstream inputFichero(fichero);
    if(inputFichero.is_open()){
        return cargar(jpm.inicial, inputFichero) && cargar(jpm.objetivo, inputFichero) && cargar(jpm.MAX_ACCIONES, inputFichero);
    }
    else
        cout << "cargar() - failed to open " + fichero << "\n";
        return false;
}

void mostrar(tJuegoPM const &jpm){
    for (unsigned int x = 0; x < jpm.inicial.numFilas; x++) cout << x << " ";
    cout << "\n";
    for (unsigned int x = 0; x < jpm.inicial.numFilas; x++) {
        for (unsigned int y = 0; y < jpm.inicial.numCol; y++) {
            colorCTA(15, (jpm.inicial.matriz[x][y] - '0'));
            cout << "  ";
        }
        colorCTA(15, 0);
        cout << "\n";
    }

    cout << "\nObjetivo:\n";
    for (unsigned int x = 0; x < jpm.inicial.numFilas; x++) cout << x << " ";
    cout << "\n";
    for (unsigned int x = 0; x < jpm.objetivo.numFilas; x++) {
        for (unsigned int y = 0; y < jpm.objetivo.numCol; y++) {
            colorCTA(15, (jpm.objetivo.matriz[x][y] - '0'));
            cout << "  ";
        }
        colorCTA(15, 0);
        cout << "\n";
    }

    cout << "\nMax Acciones: " << jpm.MAX_ACCIONES << "\n";
    cout << "Acciones usadas: " << jpm.actionsUsed << "\n";
}

bool jugar(tJuegoPM &jpm){
    while (jpm.actionsUsed < jpm.MAX_ACCIONES && !(jpm.inicial == jpm.objetivo)) {
        mostrar(jpm);
        accion(jpm);
    }

    if (!(jpm.inicial == jpm.objetivo)) return false; //se pierde el juego
    return true;    // se gana el juego
}

void accion(tJuegoPM &jpm){
    mostrarAcciones(jpm.modo);

    string accion;
    unsigned int a, b;
    tCoor coor1, coor2;

    cout << "Introduce to accion: ";
    cin >> accion;
    if (jpm.modo == 1) {
        if (accion == "SF") {
            cout << "Introduce filas: ";
            cin >> a >> b;
            if (swapF(jpm.inicial, a, b)) jpm.actionsUsed++;
            else cout << "Posiciones invalidas! Posicion maxima: " << DIM_MAX << "\n";
        }
        else if (accion == "SC") {
            cout << "Introduce columnas: ";
            cin >> a >> b;
            if (swapC(jpm.inicial, a, b)) jpm.actionsUsed++;
            else cout << "Posiciones invalidas! Posicion maxima: " << DIM_MAX << "\n";
        }
        else if (accion == "SD") {
            cout << "Introduce diagonal: ";
            cin >> a;
            if (swapD(jpm.inicial, a)) jpm.actionsUsed++;
            else cout << "Posicion invalida! Posicion maxima: " << DIM_MAX << "\n";
        }
        else if (accion == "VF") {
            cout << "Introduce fila: ";
            cin >> a;
            if (voltearF(jpm.inicial, a)) jpm.actionsUsed++;
            else cout << "Posicion invalida! Posicion maxima: " << DIM_MAX << "\n";
        }
        else if (accion == "VC") {
            cout << "Introduce columna: ";
            cin >> a;
            if (voltearC(jpm.inicial, a)) jpm.actionsUsed++;
            else cout << "Posicion invalida! Posicion maxima: " << DIM_MAX << "\n";
        }
        else if (accion == "VD") {
            cout << "Introduce diagonal: ";
            cin >> a;
            if (voltearD(jpm.inicial, a)) jpm.actionsUsed++;
            else cout << "Posicion invalida o matriz no es cuadrada! \nPosicion maxima: " << DIM_MAX << "\n";
        }
        else cout << "Invalid action\n";
    }
    else if (jpm.modo == 2) {
        if (accion == "VV") {
            voltearV(jpm.inicial);
            jpm.actionsUsed++;
        }
        else if (accion == "VH") {
            voltearH(jpm.inicial);
            jpm.actionsUsed++;
        }
        else if (accion == "RD") {
            rotarD(jpm.inicial);
            jpm.actionsUsed++;
        }
        else if (accion == "SA") {
            cout << "Introduce posiciones a, b, c y d: ";
            cin >> coor1.fila >> coor1.col >> coor2.fila >> coor2.col;
            if (swapAdy(jpm.inicial, coor1, coor2)) jpm.actionsUsed++;
            else cout << "Posiciones invalidas! Posicion maxima: " << DIM_MAX << "\n";
        }
        else if (accion == "VD") {
            if (voltearID(jpm.inicial)) jpm.actionsUsed++;
            else cout << "Matriz no es cuadrada!\n";
        }
        else cout << "Invalid action\n";
    }
    else cout << "Modo invalido - accion()\n";
}

void mostrarAcciones(const int modo) {
    switch (modo) {
    case 1:
        cout << "SF a b - intercambiar filas a y b\n";
        cout << "SC a b - intercambiar columnas a y b\n";
        cout << "SD a - intercambiar diagonales a y -a\n";
        cout << "VF a - voltear fila a\n";
        cout << "VC a - voltear columna a\n";
        cout << "VD a - voltear diagonal a\n\n";
        break;
    case 2:
        cout << "VV - dar la vuelta con respecto a eje vertical central\n";
        cout << "VH - dar la vuelta con respecto a eje horizontal central\n";
        cout << "RD - rotar 90 grados en sentido de reloj\n";
        cout << "SA a b c d - intercambiar posiciones vecines a [a,b] y [c,d]\n";
        cout << "VD - dar la vuelta completa respecto diagonal principal\n\n";
        break;
    default:
        cout << "Invalid mode - mostrarAcciones()\n";
    }
}