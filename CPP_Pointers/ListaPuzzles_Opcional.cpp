// Autores: Nicolas Espinosa Mooser, Diego Chocano Ramos

#include "ListaPuzzles_Opcional.h"
#include <fstream>
using namespace std;

void init(tPuzzlesReunidos& jr) {
	// Incializar punteros tPuzzle a nullptr
	for (int i = 0; i < 2; i++) {
		for(int x = 0; x < MAX_PUZZLE; x++){
			jr[i].lista[x] =  nullptr;
		}
	}
	// Cargar datosPuzzles.txt
	if (!cargar(jr)) cout << "Failed to load datosPuzzles.txt\n";
}

bool cargar(tPuzzlesReunidos& jr) {
	ifstream in("datosPuzzles.txt");
	if (in.is_open()) {
		for (int i = 0; i < 2; i++) {
			int numPuzzles;
			in >> numPuzzles;
			// Si inicialmente hay mas Puzzles que MAX_PUZZLE, reservar mas memoria
			if (numPuzzles > MAX_PUZZLE) resize(jr[i], numPuzzles);
			jr[i].numPuzzles = numPuzzles;

			// Cargar datos de puzzle
			for (int x = 0; x < numPuzzles; x++) {
				tPtrPuzzle p = new tPuzzle;
				string nombre, fichero;
				in.get();
				getline(in, nombre);
				in >> fichero;
				p->name = nombre;
				p->file = fichero;
				p->modo = i+1;
				p->actionsUsed = 0;
				// Cargar matriz inicial y objetivo
				if(!cargar(*p)) return false;
				jr[i].lista[x] = p;
			}
		}
		in.close();
	}
	else cerr << "Failed to open datosPuzzles.txt\n";
	return true;
}

int elegirPuzzle(tListaPuzzle& lp){
	int opcion = 1;
	do {
		// Ordenar puzzles (inicialmente ordenados de menor a mayor
		mergeSort(lp, 0, lp.numPuzzles - 1, opcion);

		// Mostrar puzzles disponibles
		cout << "Puzzles disponibles:\n";
		mostrarPuzzles(lp);
		
		// Opciones
		cout << "0 Salir\n";
		cout << "-1 Mostrar lista ordenada de mayor a menor\n";
		cout << "-2 Mostrar lista ordenada de menor a mayor\n";
		cout << "Option: ";
		cin >> opcion;
		system("cls");
	} while (opcion == -1 || opcion == -2 || opcion < -2 || opcion > lp.numPuzzles);
	return --opcion;
}

void mostrarPuzzles(const tListaPuzzle& lp) {
	for (int i = 0; i < lp.numPuzzles; i++) cout << i + 1 << " " << lp.lista[i]->name << " (" << lp.lista[i]->maxMoves << " movimiento/s)\n";
}

void mergeSort(tListaPuzzle& lista, int ini, int fin, int modo) {
	if (ini >= fin) return;
	int mid = ini + (fin - ini) / 2;
	mergeSort(lista, ini, mid, modo);		// Izquierda
	mergeSort(lista, mid + 1, fin, modo);	// Derecha
	merge(lista, ini, mid, fin, modo);		// Unir
}

void merge(tListaPuzzle& lista, int ini, int mid, int fin, int modo) {
	int size_1 = mid - ini + 1, size_2 = fin - mid;

	// Array temp
	tPtrPuzzle* izq = new tPtrPuzzle[size_1];
	tPtrPuzzle* der = new tPtrPuzzle[size_2];

	// Copiando puzzles a temp
	for (int i = 0; i < size_1; i++) izq[i] = lista.lista[ini + i];
	for (int j = 0; j < size_2; j++) der[j] = lista.lista[mid + 1 + j];

	// Merge
	int i = 0, j = 0;	// Indices de arrays izq, der
	int k = ini;		// Indice de array ordenado

	while (i < size_1 && j < size_2) {
		switch (modo) {
		case -1:
			// Mayor a Menor
			if (izq[i]->maxMoves > der[j]->maxMoves || (izq[i]->maxMoves == der[j]->maxMoves && izq[i]->name >= der[j]->name)) {
				lista.lista[k] = izq[i];
				i++;
			}
			else {
				lista.lista[k] = der[j];
				j++;
			}
			k++;
			break;
		default:
			// Menor a mayor
			if (izq[i]->maxMoves < der[j]->maxMoves || (izq[i]->maxMoves == der[j]->maxMoves && izq[i]->name <= der[j]->name)) {
				lista.lista[k] = izq[i];
				i++;
			}
			else {
				lista.lista[k] = der[j];
				j++;
			}
			k++;
		}
	}

	// Copiar elementos restantes
	while (i < size_1) {
		lista.lista[k] = izq[i];
		i++;
		k++;
	}
	while (j < size_2) {
		lista.lista[k] = der[j];
		j++;
		k++;
	}

	// Liberar memoria
	delete[] izq, der;
}

void nuevoPz(tPuzzlesReunidos& pr) {
	// Mostrar puzzles que ya existen
	cout << "\nJuegos 1D:\n";		// Puzzles 1D
	mostrarPuzzles(pr[0]);
	cout << "\n\t---\n";

	cout << "Juegos 2D:\n";			// Puzzles 2D
	mostrarPuzzles(pr[1]);
	cin.get();

	string nombre, fichero;
	cout << "Escriba el nombre del puzzle: ";
	getline(cin, nombre);
	cout << "Escriba el nombre del fichero: ";
	cin >> fichero;

	// Calculando posicion del modo
	// Confiando que el nombre del archivo no tiene errores en ?D.txt
	// Podria verificar si el modo es 1 o 2
	int posModo = fichero.length() - 6;

	tPuzzle* p = new tPuzzle;
	p->name = nombre;
	p->file = fichero;
	p->modo = fichero[posModo] - '0';
	p->actionsUsed = 0;

	// Confirmar que existe el archivo del Puzzle y cargar matrices
	// Si no existe puzzle con mismo nombre -> añadirlo
	int pos, ini = 0, fin = pr[p->modo - 1].numPuzzles - 1;
	if (cargar(*p) && !buscar(pr[p->modo-1], p, ini, fin, pos)) {
		if (insertOrd(pr[p->modo - 1], p)) {	// Insertar puzzle
			system("cls");
			mostrarPuzzles(pr[p->modo - 1]);	// Mostrar nueva lista de puzzles
			guardar(pr);						// Guardar cambios a datosPuzzles.txt
			system("pause");
			system("cls");
			
		}
		else cout << "No se pudo insertar\n\n";
	}
	else cout << "Ese puzzle ya existe o el archivo no existe!\n";
}

bool insertOrd(tListaPuzzle& l, tPuzzle* p) {
	int size = l.numPuzzles;

	if (size == l.maxSize) resize(l, l.maxSize * 2);	// Duplicar tamaño para ser eficaz

	// Despl. a la derecha
	int i = size;
	while (i > 0 && p->maxMoves < l.lista[i - 1]->maxMoves || (p->maxMoves == l.lista[i-1]->maxMoves &&  p->name < l.lista[i-1]->name)) {
		l.lista[i] = l.lista[i - 1];
		i--;
	}
	l.lista[i] = p;
	l.numPuzzles++;

	return true;
}

bool buscar(const tListaPuzzle& lista, tPuzzle* puzzle, int ini, int fin, int& pos) {
	bool found;
	if (ini <= fin) {
		int mid = (ini + fin) / 2;
		if (puzzle->file < lista.lista[mid]->file) found = buscar(lista, puzzle, ini, mid - 1, pos);
		else if (lista.lista[mid]->file < puzzle->file) found = buscar(lista, puzzle, mid + 1, fin, pos);
		else {
			pos = mid;
			found = true;
		}
	}
	else {
		pos = ini;
		found = false;
	}
	return found;
}

void resize(tListaPuzzle& lista, int size) {
	tPtrPuzzle* nuevaLista = new tPtrPuzzle[size];

	for (int i = 0; i < size; i++) nuevaLista[i] = nullptr;

	for (int i = 0; i < lista.numPuzzles; i++) {
		nuevaLista[i] = lista.lista[i];
	}

	delete[] lista.lista;
	lista.lista = nuevaLista;
	lista.maxSize = size;
}

void guardar(const tPuzzlesReunidos& listas) {
	ofstream out("datosPuzzles.txt");
	if (out.is_open()) {
		// Lista 1D
		out << listas[0].numPuzzles << "\n";
		guardar(out, listas[0]);
		// Lista 2D
		out << listas[1].numPuzzles << "\n";
		guardar(out, listas[1]);
		out.close();
	}
}

void guardar(ofstream& out, const tListaPuzzle lista) {
	// Guardar nombre y archivo
	for (int i = 0; i < lista.numPuzzles; i++) {
		out << lista.lista[i]->name << "\n";
		out << lista.lista[i]->file << "\n";
	}
}
