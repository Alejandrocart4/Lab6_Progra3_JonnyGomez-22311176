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

private:
    Ui::cframe *ui;
    int **matriz;
    int fil_col;
    int fil;
    int col;
    int m1, n1, m2, n2;
    int **matriz1;
    int **matriz2;
    QTableWidget *tableWidgetMatriz1;
    QTableWidget *tableWidgetMatriz2;
    QTableWidget *tableWidgetResultado;

};
#endif // CFRAME_H
