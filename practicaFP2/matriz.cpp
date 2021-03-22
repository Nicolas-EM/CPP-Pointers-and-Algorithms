// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#include "matriz.h"
#include <iostream>

bool cargar(tMatrizChar& mat, std::istream& ent) {
    ent >> mat.numFilas >> mat.numCol;
    if (mat.numFilas < 0 || mat.numFilas > DIM_MAX || mat.numCol < 0 || mat.numCol > DIM_MAX) return false;
    for (unsigned int x = 0; x < mat.numFilas; x++) {
        for (unsigned int y = 0; y < mat.numCol; y++) {
            ent >> mat.matriz[x][y];
        }
    }
    return true;
}

bool cargar(int& MAX_ACCIONES, std::istream& ent) {
    ent >> MAX_ACCIONES;
    return MAX_ACCIONES;
}

bool operator== (const tMatrizChar& mat1, const tMatrizChar& mat2) {
    for (unsigned int x = 0; x < mat1.numCol; x++) {
        for (unsigned int y = 0; y < mat1.numCol; y++) {
            if (mat1.matriz[x][y] != mat2.matriz[x][y]) return false;
        }
    }
    return true;
}

bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
    if (pos1.col < 0 || pos1.col >= mat.numCol || pos1.fila < 0 || pos1.fila >= mat.numFilas) return false;
    if (pos2.col < 0 || pos2.col >= mat.numCol || pos2.fila < 0 || pos2.fila >= mat.numFilas) return false;

    char temp = mat.matriz[pos2.fila][pos2.col];
    mat.matriz[pos2.fila][pos2.col] = mat.matriz[pos1.fila][pos1.col];
    mat.matriz[pos1.fila][pos1.col] = temp;

    return true;
}

bool swapF(tMatrizChar& mat, const unsigned int f1, const unsigned int f2) {
    if (f1 < 0 || f1 >= mat.numFilas || f2 < 0 || f2 >= mat.numFilas) return false;

    for (unsigned int x = 0; x < mat.numCol; x++) {
        char temp = mat.matriz[f2][x];
        mat.matriz[f2][x] = mat.matriz[f1][x];
        mat.matriz[f1][x] = temp;
    }

    return true;
}

bool swapC(tMatrizChar& mat, const unsigned int c1, const unsigned int c2) {
    if (c1 < 0 || c1 >= mat.numCol || c2 < 0 || c2 >= mat.numCol) return false;

    for (unsigned int x = 0; x < mat.numFilas; x++) {
        char temp = mat.matriz[x][c2];
        mat.matriz[x][c2] = mat.matriz[x][c1];
        mat.matriz[x][c1] = temp;
    }

    return true;
}

bool swapD(tMatrizChar& mat, const unsigned int d) {        // QUE HACER EN d >= 2????
    if (d < 0 || d >= mat.numCol) return false;

    for (unsigned int x = 0; x < mat.numCol; x++) {
        char temp = mat.matriz[x][d + x];
        mat.matriz[x][d + x] = mat.matriz[d + x][x];
        mat.matriz[d + x][x] = temp;
    }

    return true;
}

bool voltearF(tMatrizChar& mat, const unsigned int f) {
    if (f < 0 || f >= mat.numFilas) return false;

    for (unsigned int x = 0; x < mat.numCol / 2; x++) {
        char temp = mat.matriz[f][mat.numCol - x - 1];
        mat.matriz[f][mat.numCol - x - 1] = mat.matriz[f][x];
        mat.matriz[f][x] = temp;
    }
    return true;
}

bool voltearC(tMatrizChar& mat, const unsigned int c) {
    if (c < 0 || c >= mat.numCol) return false;

    for (unsigned int x = 0; x < mat.numFilas / 2; x++) {
        char temp = mat.matriz[mat.numFilas - x - 1][c];
        mat.matriz[mat.numFilas - x - 1][c] = mat.matriz[x][c];
        mat.matriz[x][c] = temp;
    }
    return true;
}

bool voltearD(tMatrizChar& mat, const unsigned int d) {     // QUE HACER EN d >= 2????
    if (d < 0 || d >= mat.numCol || mat.numCol != mat.numFilas) return false;

    for (unsigned int x = 0; x < mat.numCol / 2 - d; x++) {
        char temp = mat.matriz[mat.numFilas - 1 - d][mat.numCol - 1 - x];
        mat.matriz[mat.numFilas - 1 - d][mat.numCol - 1 - x] = mat.matriz[x][d];
        mat.matriz[x][d] = temp;
    }
    return true;
}

void voltearV(tMatrizChar& mat) {
    for (unsigned int x = 0; x < mat.numFilas; x++) {
        voltearF(mat, x);
    }
}

void voltearH(tMatrizChar& mat) {
    for (unsigned int x = 0; x < mat.numCol; x++) {
        voltearC(mat, x);
    }
}

void rotarD(tMatrizChar& mat) {
    tMatrizChar temp;
    temp.numCol = mat.numFilas;
    temp.numFilas = mat.numCol;

    for (unsigned int x = 0; x < temp.numFilas; x++) {
        for (unsigned int y = 0; y < temp.numCol; y++) {
            temp.matriz[x][y] = mat.matriz[mat.numFilas - 1 - y][x];
        }
    }

    mat = temp;
}

bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
    if (pos1.fila < 1 || pos1.fila >= mat.numFilas - 1 || pos1.col < 1 || pos1.col >= mat.numCol - 1) return false;
    if (pos2.fila < 1 || pos2.fila >= mat.numFilas - 1 || pos2.col < 1 || pos2.col >= mat.numCol - 1) return false;

    tCoor vec1, vec2;
    for (int dir = 0; dir < numDirs; dir++) {
        vec1.fila = pos1.fila + incF[dir];
        vec1.col = pos1.col + incC[dir];
        
        vec2.fila = pos2.fila + incF[dir];
        vec2.col = pos2.col + incC[dir];

        swap(mat, vec1, vec2);
    }

    return true;
}

bool voltearID(tMatrizChar& mat) {
    if (mat.numCol != mat.numFilas) return false;   // matriz no es cuadrada

    for (unsigned int x = 0; x < mat.numFilas - 1; x++) {
        for (unsigned int y = 1; y < mat.numCol; y++) {
            tCoor pos1 = { x,y+x }, pos2 = { y+x,x };
            swap(mat, pos1, pos2);
        }
    }

    return true;
}