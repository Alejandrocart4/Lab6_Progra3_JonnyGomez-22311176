#include "cframe.h"
#include "ui_cframe.h"
#include "QMessageBox"

#include <QCoreApplication>
#include <QApplication>


cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe),

    matriz1(nullptr),
    matriz2(nullptr),
    fil1(0), col1(0),
    fil2(0), col2(0)
{
    ui->setupUi(this);
}

cframe::~cframe()
{
    delete ui;
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

    ui->tW_Rotada->setRowCount(fil_col);
    ui->tW_Rotada->setColumnCount(fil_col);

    for (int f = 0; f < fil_col; f++) {
        for (int c = 0; c < fil_col; c++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matriz[f][c]));
            ui->tW_Rotada->setItem(f, c, item);
        }
    }

    ui->tW_Rotada->update();
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
    fil1 = ui->spinBoxFilas1->value();
    col1 = ui->spinBoxColumnas1->value();
    fil2 = ui->spinBoxFilas2->value();
    col2 = ui->spinBoxColumnas2->value();
    if(fil1 == 0 && col1 == 0 && fil2 == 0 && col2 == 0 ){
         QMessageBox::warning(this, "Matrices NO Ingresadas", "Las matrices NO han sido ingresadas correctamente.");
        return;
    }else{

    // Inicializar el generador de números aleatorios
    std::srand(static_cast<unsigned>(std::time(0)));

    // Liberar memoria
    if (matriz1 != nullptr) {
        for (int i = 0; i < fil1; ++i) {
            delete[] matriz1[i];
        }
        delete[] matriz1;
        matriz1 = nullptr;
    }


    matriz1 = new int*[fil1];
    for (int i = 0; i < fil1; ++i) {
        matriz1[i] = new int[col1];
    }


    for (int i = 0; i < fil1; ++i) {
        for (int j = 0; j < col1; ++j) {
            matriz1[i][j] = std::rand() % 100 + 1;
        }
    }

    // Mostrar matriz en QTableWidget
    ui->tableWidgetMatriz1->setRowCount(fil1);
    ui->tableWidgetMatriz1->setColumnCount(col1);
    for (int i = 0; i < fil1; ++i) {
        for (int j = 0; j < col1; ++j) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matriz1[i][j]));
            ui->tableWidgetMatriz1->setItem(i, j, item);
        }
    }




    std::srand(static_cast<unsigned>(std::time(0)));


    if (matriz2 != nullptr) {
        for (int i = 0; i < fil2; ++i) {
            delete[] matriz2[i];
        }
        delete[] matriz2;
        matriz2 = nullptr;
    }


    matriz2 = new int*[fil2];
    for (int i = 0; i < fil2; ++i) {
        matriz2[i] = new int[col2];
    }


    for (int i = 0; i < fil2; ++i) {
        for (int j = 0; j < col2; ++j) {
            matriz2[i][j] = std::rand() % 50 + 1;
        }
    }

    // Mostrar matriz en QTableWidget
    ui->tableWidgetMatriz2->setRowCount(fil2);
    ui->tableWidgetMatriz2->setColumnCount(col2);
    for (int i = 0; i < fil2; ++i) {
        for (int j = 0; j < col2; ++j) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matriz2[i][j]));
            ui->tableWidgetMatriz2->setItem(i, j, item);
        }
    }

    QMessageBox::information(this, "Matrices Ingresadas", "Las matrices han sido ingresadas correctamente.");
    }

}


void cframe::on_buttonSumar_clicked()
{
    if (matriz1 == nullptr || matriz2 == nullptr) {
        QMessageBox::warning(this, "Error", "Una o ambas matrices no están inicializadas.");
        return;
    }

    if (fil1 != fil2 || col1 != col2) {
        QMessageBox::warning(this, "Error", "Las matrices deben ser de la misma dimensión para sumar.");
        return;
    }

    int** resultado = new int*[fil1];
    for (int i = 0; i < fil1; ++i) {
        resultado[i] = new int[col1];
    }

    for (int i = 0; i < fil1; ++i) {
        for (int j = 0; j < col1; ++j) {
            resultado[i][j] = matriz1[i][j] + matriz2[i][j];
        }
    }

    ui->tableWidgetResultado->setRowCount(fil1);
    ui->tableWidgetResultado->setColumnCount(col1);
    for (int i = 0; i < fil1; ++i) {
        for (int j = 0; j < col1; ++j) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(resultado[i][j]));
            ui->tableWidgetResultado->setItem(i, j, item);
        }
    }

    for (int i = 0; i < fil1; ++i) {
        delete[] resultado[i];
    }
    delete[] resultado;
}


void cframe::on_buttonRestar_clicked()
{
    if (matriz1 == nullptr || matriz2 == nullptr) {
        QMessageBox::warning(this, "Error", "Una o ambas matrices no están inicializadas.");
        return;
    }

    if (fil1 == fil2 && col1 == col2) {
        // Crear matriz para el resultado
        int** resultado = new int*[fil1];
        for (int i = 0; i < fil1; ++i) {
            resultado[i] = new int[col1];
        }

        // Realizar la resta
        for (int i = 0; i < fil1; ++i) {
            for (int j = 0; j < col1; ++j) {
                resultado[i][j] = matriz1[i][j] - matriz2[i][j];
            }
        }


        ui->tableWidgetResultado->setRowCount(fil1);
        ui->tableWidgetResultado->setColumnCount(col1);
        for (int i = 0; i < fil1; ++i) {
            for (int j = 0; j < col1; ++j) {
                QTableWidgetItem* item = new QTableWidgetItem(QString::number(resultado[i][j]));
                ui->tableWidgetResultado->setItem(i, j, item);
            }
        }


        for (int i = 0; i < fil1; ++i) {
            delete[] resultado[i];
        }
        delete[] resultado;
    } else {

        QMessageBox::warning(this, "Error", "Las matrices deben ser de la misma dimensión para restar.");
    }
}


void cframe::on_buttonMultiplicar_clicked()
{
    if (col1 == fil2 && matriz1 != nullptr && matriz2 != nullptr) {

        int** resultado = new int*[fil1];
        for (int i = 0; i < fil1; ++i) {
            resultado[i] = new int[col2];
        }


        for (int i = 0; i < fil1; ++i) {
            for (int j = 0; j < col2; ++j) {
                resultado[i][j] = 0;
            }
        }


        for (int i = 0; i < fil1; ++i) {
            for (int j = 0; j < col2; ++j) {
                for (int k = 0; k < col1; ++k) { // o `k < fil2` ya que `col1 == fil2`
                    resultado[i][j] += matriz1[i][k] * matriz2[k][j];
                }
            }
        }


        ui->tableWidgetResultado->setRowCount(fil1);
        ui->tableWidgetResultado->setColumnCount(col2);
        for (int i = 0; i < fil1; ++i) {
            for (int j = 0; j < col2; ++j) {
                QTableWidgetItem* item = new QTableWidgetItem(QString::number(resultado[i][j]));
                ui->tableWidgetResultado->setItem(i, j, item);
            }
        }


        for (int i = 0; i < fil1; ++i) {
            delete[] resultado[i];
        }
        delete[] resultado;
    } else {

        QMessageBox::warning(this, "Error", "Las matrices deben tener dimensiones compatibles para multiplicar y deben estar inicializadas.");
    }
}


void cframe::on_btnHacerMatrizTrans_clicked()
{
    fil= ui->sB_Fil3->value();
    col = ui->sB_Col3->value();

    matriz3 = new int*[fil];//CREANDO FILAS

    for (int fi = 0; fi < col; fi++) {
        matriz3[fi] = new int[col];//CREANDO COLUMNAS
    }

    for (int fi = 0, num = 1; fi < fil; ++fi) {
        for (int co = 0; co < col; co++,num++) {
            matriz3[fi][co] = num;
        }
    }

    ui->tW_tabla4->setRowCount(fil);
    ui->tW_tabla4->setColumnCount(col);

    for (int fi = 0; fi < fil; fi++) {
        for (int co = 0; co < col; co++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matriz3[fi][co]));
            ui->tW_tabla4->setItem(fi,co,item);
        }
    }
}


void cframe::on_btnTransponer_clicked()
{
    if (matriz3 != nullptr) {

        int** transpuesta = new int*[col];
        for (int i = 0; i < col; ++i) {
            transpuesta[i] = new int[fil];
        }


        for (int i = 0; i < fil; ++i) {
            for (int j = 0; j < col; ++j) {
                transpuesta[j][i] = matriz3[i][j];
            }
        }


        ui->tW_tabla4->setRowCount(col);
        ui->tW_tabla4->setColumnCount(fil);
        for (int i = 0; i < col; ++i) {
            for (int j = 0; j < fil; ++j) {
                QTableWidgetItem* item = new QTableWidgetItem(QString::number(transpuesta[i][j]));
                ui->tW_tabla4->setItem(i, j, item);
            }
        }


        for (int i = 0; i < col; ++i) {
            delete[] transpuesta[i];
        }
        delete[] transpuesta;
    } else {
        QMessageBox::warning(this, "Error", "La matriz no está inicializada.");
    }
}


void cframe::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void cframe::on_pushButton_6_clicked()
{
    QCoreApplication::quit();
}


void cframe::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void cframe::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void cframe::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void cframe::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void cframe::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void cframe::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void cframe::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

