// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#include "coordenada.h"

using namespace std;


bool operator== (const tCoor c1, const tCoor c2){
	if (c1.col == c2.col && c1.fila == c2.fila) return true;
	else return false;
}

bool operator!= (const tCoor c1, const tCoor c2){
	return !(c1 == c2);
}

tCoor operator+ (const tCoor c1, const tCoor c2){
	tCoor res = c1;
	res.col += c2.col;
	res.fila += c2.fila;
	return res;
} 