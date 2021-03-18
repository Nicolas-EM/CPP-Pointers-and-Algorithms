// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#ifndef _MATRIZ_H
#define _MATRIZ_H
#include <iostream>

const int DIM_MAX = 64; // Dimension maxima de tMatrizChar

struct tCoor{
    unsigned int fila, col;
};

const int incF[] = { -1,-1,-1,0,0,1,1,1 };
const int incC[] = { -1,0,1,-1,1,-1,0,1 };  //8dirs.
const int numDirs = 8;

struct tMatrizChar{
    unsigned char matriz[DIM_MAX][DIM_MAX];
    unsigned int numFilas = 0, numCol = 0;
};

bool cargar(tMatrizChar &mat, std::istream &ent); //carga en matriz datos dados en flujo de entrada.Return falso si hay error de lectura
bool cargar(int &MAX_ACCIONES, std::istream& ent); // cargar numero maximo de acciones
bool operator== (const tMatrizChar  &mat1, const tMatrizChar &mat2); //Compara si las dos matrices son iguales
bool swap(tMatrizChar &mat, tCoor pos1, tCoor pos2); //intercambia coor pos1 y pos2 de la matriz.Return falso si pos no pertenecen a rg matriz
bool swapF(tMatrizChar &mat, const unsigned int f1, const unsigned int f2); //intercambia filas f1 y f2.Return falso si filas no pertenece a rg matriz
bool swapC(tMatrizChar &mat, const unsigned int c1, const unsigned int c2); //intercambia columnas c1 y c2.Return falso si columnas no pertenece a rg matriz
bool swapD(tMatrizChar &mat, const unsigned int d); //intercambia diagonales d y -d.Return falso si diagonales no pertenece a rg matriz o si no es cuadrada
bool voltearF(tMatrizChar &mat, const unsigned int f);//da vuelta fila f respecto al eje vertical central de la imagen return falso si fil no pertenece al rg matriz
bool voltearC(tMatrizChar &mat, const unsigned int c); //da vuelta columna c respecto al eje horizontal central de la imagen return falso si col no pertenece al rg matriz
bool voltearD(tMatrizChar& mat, const unsigned int d);  // da vuelta a diagonal d con respecto al centro de eje perpendicular de dicha diagonal. Devuelve falso no pertenece al rango de matriz o si matriz no es cuadrada.
void voltearV(tMatrizChar& mat);    // dar la vuelta a la imagen completa con respecto a su eje vertical central.
void voltearH(tMatrizChar& mat);    // dar la vuelta a la imagen completa con respecto a su eje horizontal central.
void rotarD(tMatrizChar& mat); // rotar una imagen 90 grados en el sentido de las agujas del reloj.
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2);    // intercambiar las celdas vecinas o adyacentes de las posiciones pos1 y pos2.
bool VoltearID(tMatrizChar& mat);  // Voltear la imagen completa respecto a la diagonal principal. Devuelve falso si la matriz no es cuadrada.

#endif