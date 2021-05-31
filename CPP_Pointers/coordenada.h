// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#ifndef _COORDENADA_H
#define _COORDENADA_H

struct tCoor{
    unsigned int fila, col;
};

bool operator== (const tCoor c1, const tCoor c2); //compara dos coordenadas si son iguales
bool operator!= (const tCoor c1, const tCoor c2); //compara dos coordenadas si son distintas
tCoor operator+ (const tCoor c1, const tCoor c2); //devuelve resultado tCoor de la suma de dos coordenadas dadas por parametros


#endif