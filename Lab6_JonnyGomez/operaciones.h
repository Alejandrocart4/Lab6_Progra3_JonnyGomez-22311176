#ifndef OPERACIONES_H
#define OPERACIONES_H

#include <QTableWidget>

int** crearMatriz(int m, int n);
void liberarMatriz(int **matriz, int m);
void sumarMatrices(int **matriz1, int **matriz2, int **resultado, int m, int n);
void restarMatrices(int **matriz1, int **matriz2, int **resultado, int m, int n);
void multiplicarMatrices(int **matriz1, int **matriz2, int **resultado, int m1, int n1, int m2, int n2);
void extraerValores(QTableWidget *tableWidget, int **matriz, int m, int n);
void mostrarMatriz(QTableWidget *tableWidget, int **matriz, int m, int n);
bool validarDimensionesSumaResta(int m1, int n1, int m2, int n2);
bool validarDimensionesMultiplicacion(int n1, int m2);

#endif // OPERACIONES_H
