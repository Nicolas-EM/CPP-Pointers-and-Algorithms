// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#include "Puzzle.h"
#include "UtilidadesSYS.h"
#include <fstream>
#include <time.h>
using namespace std;

void mainPuzzle(tPuzzle& p) {
    if (!jugar(p)) {    // Jugar, regresa true si pierde
        mostrar(p);     // Mostrar el puzzle
        cout << "\n\t\t---------- GAME OVER --------\n\n";
    }
    else {
        mostrar(p);     // Una celebracion ;)
        string ganar = "---------- HAS GANADO!! -----------";
        srand(time(0));
        cout << "\n\t\t";
        for (size_t i = 0; i < ganar.length(); i++) {
            colorCTA(rand() % 13 + 1, 0);
            cout << ganar[i];
        }
        colorCTA(15, 0);
        cout << "\n";
    }
    pausa();
    system("cls");
}

bool cargar(tPuzzle& p) {
	string fichero = p.file;
	ifstream in(fichero);
	if (in.is_open()) {
        // Cargar matrices, movimientos maximos y cerrar fstream
        if (cargar(p.inicial, in) && cargar(p.objetivo, in)) {
            in >> p.maxMoves;
            in.close();
            return true;
        }
		else return false;
	}
	else cout << "Failed to open " << fichero << "\n";
	return false;
}

void mostrar(const tPuzzle& jpm) {
    cout << "Inicial:\n";
    mostrar(jpm.inicial);

    cout << "\nObjetivo:\n";
    mostrar(jpm.objetivo);

    cout << "\nMax Acciones: " << jpm.maxMoves << "\n";
    cout << "Acciones usadas: " << jpm.actionsUsed << "\n";
}

void mostrar(const tMatrizChar& mat){
    // Mostrar guia - numero de columnas
    for (unsigned int x = 0; x < mat.numCol; x++) cout << x << " ";
    cout << "\n";

    // Mostrar matriz
    for (unsigned int x = 0; x < mat.numFilas; x++) {
        for (unsigned int y = 0; y < mat.numCol; y++) {
            colorCTA(15, (mat.matriz[x][y] - '0'));
            cout << "  ";
        }
        colorCTA(15, 0);
        cout << "\n";
    }
}

bool jugar(tPuzzle& p) {
    // Loop mientras queden acciones o matrizes no sean iguales
    while (p.actionsUsed < p.maxMoves && !(p.inicial == p.objetivo)) {
        mostrar(p);     // Mostrar estado actual de matrices
        accion(p);      // Usar accion
        borrar();
    }

    if (!(p.inicial == p.objetivo)) return false; //se pierde el juego
    return true;    // se gana el juego
}

void accion(tPuzzle& jpm) {
    // Mostrar acciones posibles
    mostrarAcciones(jpm.modo);

    string accion;
    unsigned int a, b;      // Posiciones
    tCoor coor1, coor2;

    cout << "Introduce to accion: ";
    cin >> accion;

    // Usar accion y modificar actionsUsed
    if (jpm.modo == 1) {
        if (accion == "SF") {
            cout << "Introduce filas: ";
            cin >> a >> b;
            if (swapF(jpm.inicial, a, b)) jpm.actionsUsed++;
            else cout << "Posiciones invalidas! Posicion maxima: " << jpm.inicial.numCol-1 << ", " << jpm.inicial.numFilas-1 << "\n";
        }
        else if (accion == "SC") {
            cout << "Introduce columnas: ";
            cin >> a >> b;
            if (swapC(jpm.inicial, a, b)) jpm.actionsUsed++;
            else cout << "Posiciones invalidas! Posicion maxima: " << jpm.inicial.numCol-1 << ", " << jpm.inicial.numFilas-1 << "\n";
        }
        else if (accion == "SD") {
            cout << "Introduce diagonal: ";
            cin >> a;
            if (swapD(jpm.inicial, a)) jpm.actionsUsed++;
            else cout << "Posiciones invalidas! Posicion maxima: " << jpm.inicial.numCol-1 << "\n";
        }
        else if (accion == "VF") {
            cout << "Introduce fila: ";
            cin >> a;
            if (voltearF(jpm.inicial, a)) jpm.actionsUsed++;
            else cout << "Posiciones invalidas! Posicion maxima: " << jpm.inicial.numFilas-1 << "\n";
        }
        else if (accion == "VC") {
            cout << "Introduce columna: ";
            cin >> a;
            if (voltearC(jpm.inicial, a)) jpm.actionsUsed++;
            else cout << "Posiciones invalidas! Posicion maxima: " << jpm.inicial.numCol-1 << "\n";
        }
        else if (accion == "VD") {
            cout << "Introduce diagonal: ";
            cin >> a;
            if (voltearD(jpm.inicial, a)) jpm.actionsUsed++;
            else cout << "Posicion invalida o matriz no es cuadrada! \nPosicion maxima: " << jpm.inicial.numCol-1 << "\n";
        }
        else {
            borrar();
            cout << "Invalid action\n";
            pausa();
        }
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
            else cout << "Posiciones invalidas! Posicion maxima: " << jpm.inicial.numCol-1 << ", " << jpm.inicial.numFilas-1 << "\n";
        }
        else if (accion == "VD") {
            if (voltearID(jpm.inicial)) jpm.actionsUsed++;
            else cout << "Matriz no es cuadrada!\n";
        }
        else {
            borrar();
            cout << "Invalid action\n";
            pausa();
        }
    }
    else cout << "Modo invalido - accion()\n";
    pausa();
}

void mostrarAcciones(const int modo) {
    switch (modo) {
    case 1:     // Modo 1D
        cout << "SF a b - intercambiar filas a y b\n";
        cout << "SC a b - intercambiar columnas a y b\n";
        cout << "SD a - intercambiar diagonales a y -a\n";
        cout << "VF a - voltear fila a\n";
        cout << "VC a - voltear columna a\n";
        cout << "VD a - voltear diagonal a\n\n";
        break;
    case 2:     // Modo 2D
        cout << "VV - dar la vuelta con respecto a eje vertical central\n";
        cout << "VH - dar la vuelta con respecto a eje horizontal central\n";
        cout << "RD - rotar 90 grados en sentido de reloj\n";
        cout << "SA a b c d - intercambiar posiciones vecinas a [a,b] y [c,d]\n";
        cout << "VD - dar la vuelta completa respecto diagonal principal\n\n";
        break;
    default:    // Error en modo
        cout << "Invalid mode - mostrarAcciones()\n";
    }
}