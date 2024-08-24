#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
#include "QTableWidget"

QT_BEGIN_NAMESPACE
namespace Ui {
class cframe;
}
QT_END_NAMESPACE

class cframe : public QMainWindow
{
    Q_OBJECT

public:
    cframe(QWidget *parent = nullptr);
    ~cframe();

private slots:
    void on_Buscar_n_clicked();

    void on_pushButton_2_clicked();

    void on_rotar_matriz_clicked();

    void on_sB_Fil_Col_valueChanged(int arg1);

    void on_buttonMostrarMatrices_clicked();

    void on_buttonSumar_clicked();

    void on_buttonRestar_clicked();

    void on_buttonMultiplicar_clicked();

    void on_btnHacerMatrizTrans_clicked();

    void on_btnTransponer_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::cframe *ui;
    int **matriz;
    int fil_col;
    int fil;
    int col;
    int fil1, col1;
    int fil2, col2;
    int** matriz1;
    int** matriz2;
    int** matriz3;

};
#endif // CFRAME_H
