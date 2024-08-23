#include "cframe.h"
#include "ui_cframe.h"
#include "operaciones.h"
#include "QMessageBox"


cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);
}

cframe::~cframe()
{
    delete ui;
    liberarMatriz(matriz1, m1);
    liberarMatriz(matriz2, m2);
}



void cframe::on_Buscar_n_clicked()
{
    int numeroABuscar = ui->num_buscar->text().toInt();

    int posFila = -1;
    int posColumna = -1;

    for (int fi = 0; fi < fil && posFila == -1; ++fi) {
        for (int co = 0; co < col && posColumna == -1; ++co) {
            if (matriz[fi][co] == numeroABuscar) {
                posFila = fi;
                posColumna = co;
            }
        }
    }


    QString info;


    //ui->mostrar_info->setText(info);

    if (posFila != -1 && posColumna != -1) {
        info = QString("Número %1 encontrado en fila %2, columna %3").arg(numeroABuscar).arg(posFila + 1).arg(posColumna + 1);

        ui->tW_tabla->item(posFila, posColumna)->setBackground(Qt::gray);

    } else {
        info = QString("Número %1 no encontrado.").arg(numeroABuscar);

        ui->tW_tabla->clearSelection();

    }

    ui->mostrar_info2->setText(info);
}


void cframe::on_pushButton_2_clicked()
{
    fil= ui->sB_Fil->text().toInt();
    col = ui->sB_Col->text().toInt();

    matriz = new int*[fil];

    for (int fi = 0; fi < col; fi++) {
        matriz[fi] = new int[col];
    }

    for (int fi = 0, num = 1; fi < fil; ++fi) {
        for (int co = 0; co < col; co++,num++) {
            matriz[fi][co] = num;
        }
    }

    ui->tW_tabla->setRowCount(fil);
    ui->tW_tabla->setColumnCount(col);

    for (int fi = 0; fi < fil; fi++) {
        for (int co = 0; co < col; co++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matriz[fi][co]));
            ui->tW_tabla->setItem(fi,co,item);
        }
    }


}


void cframe::on_rotar_matriz_clicked()
{
    // Crear una matriz temporal para guardar datos y no se pierdan
    int** matriz_temp = new int*[fil_col];
    for (int i = 0; i < fil_col; i++) {
        matriz_temp[i] = new int[fil_col];
    }

    // Copiar la matriz original a la matriz temporal
    for (int f = 0; f < fil_col; f++) {
        for (int c = 0; c < fil_col; c++) {
            matriz_temp[f][c] = matriz[f][c];
        }
    }

    // Rotar la matriz temporal 90 grados
    for (int f = 0; f < fil_col; f++) {
        for (int c = 0; c < fil_col; c++) {
            matriz[c][fil_col - f - 1] = matriz_temp[f][c];
        }
    }

    for (int f = 0; f < fil_col; f++) {
        for (int c = 0; c < fil_col; c++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matriz[f][c]));
            ui->tW_Mostrar->setItem(f, c, item);
        }
    }
}


void cframe::on_sB_Fil_Col_valueChanged(int arg1)
{
    fil_col = ui-> sB_Fil_Col->text().toInt();
    matriz = new int*[fil_col];// creando filas
    for (int f = 0;f<fil_col ; f++ ) {
        matriz[f]= new int[fil_col];//creando columnas

    }

    for (int f = 0,num=1;f < fil_col ; f++ ) {
        for (int c =0;c <fil_col ;c++,num++) {
            matriz[f][c] = num;
        }
    }

    ui->tW_Mostrar->setRowCount(fil_col);
    ui->tW_Mostrar->setColumnCount(fil_col);

    for (int f = 0; f < fil_col; f++) {
        for (int c = 0; c < fil_col; c++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matriz[f][c]));
            ui->tW_Mostrar->setItem(f, c, item);
        }
    }

}

void cframe::on_buttonMostrarMatrices_clicked()
{
    m1 = ui->spinBoxFilas1->value();
    n1 = ui->spinBoxColumnas1->value();
    m2 = ui->spinBoxFilas2->value();
    n2 = ui->spinBoxColumnas2->value();

    qDebug() << "Dimensiones de la matriz 1:" << m1 << "x" << n1;
    qDebug() << "Dimensiones de la matriz 2:" << m2 << "x" << n2;

    matriz1 = crearMatriz(m1, n1);
    matriz2 = crearMatriz(m2, n2);

    if (!matriz1 || !matriz2) {
        qDebug() << "Error al crear las matrices";
        return;
    }

    extraerValores(tableWidgetMatriz1, matriz1, m1, n1);
    extraerValores(tableWidgetMatriz2, matriz2, m2, n2);

    qDebug() << "Valores de la matriz 1:";
    for (int i = 0; i < m1; ++i) {
        for (int j = 0; j < n1; ++j) {
            qDebug() << matriz1[i][j];
        }
    }

    qDebug() << "Valores de la matriz 2:";
    for (int i = 0; i < m2; ++i) {
        for (int j = 0; j < n2; ++j) {
            qDebug() << matriz2[i][j];
        }
    }

    // Mostrar las matrices en los QTableWidget
    mostrarMatriz(tableWidgetMatriz1, matriz1, m1, n1);
    mostrarMatriz(tableWidgetMatriz2, matriz2, m2, n2);

    QMessageBox::information(this, "Matrices Ingresadas", "Las matrices han sido ingresadas correctamente.");
}

