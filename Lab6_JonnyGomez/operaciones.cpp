#include "operaciones.h"
#include <QTableWidget>
#include <QTableWidgetItem>

int** crearMatriz(int m, int n) {
    int **matriz = new int*[m];
    for (int i = 0; i < m; ++i) {
        matriz[i] = new int[n];
    }
    qDebug("Se crea .....................");
    return matriz;
}

void liberarMatriz(int **matriz, int m) {
    for (int i = 0; i < m; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void sumarMatrices(int **matriz1, int **matriz2, int **resultado, int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            resultado[i][j] = matriz1[i][j] + matriz2[i][j];
        }
    }
}

void restarMatrices(int **matriz1, int **matriz2, int **resultado, int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            resultado[i][j] = matriz1[i][j] - matriz2[i][j];
        }
    }
}

void multiplicarMatrices(int **matriz1, int **matriz2, int **resultado, int m1, int n1, int m2, int n2) {
    for (int i = 0; i < m1; ++i) {
        for (int j = 0; j < n2; ++j) {
            resultado[i][j] = 0;
            for (int k = 0; k < n1; ++k) {
                resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }
}

void extraerValores(QTableWidget *tableWidget, int **matriz, int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            matriz[i][j] = tableWidget->item(i, j)->text().toInt();
        }
    }
}

void mostrarMatriz(QTableWidget *tableWidget, int **matriz, int m, int n) {
    tableWidget->setRowCount(m);
    tableWidget->setColumnCount(n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(matriz[i][j])));
        }
    }
}

bool validarDimensionesSumaResta(int m1, int n1, int m2, int n2) {
    return (m1 == m2) && (n1 == n2);
}

bool validarDimensionesMultiplicacion(int n1, int m2) {
    return n1 == m2;
}
