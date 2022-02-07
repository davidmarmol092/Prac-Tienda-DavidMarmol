#ifndef TIENDA_H
#define TIENDA_H

#include <QMainWindow>
#include <producto.h>
#include <QDebug>
#include <QMessageBox>
#include <QPalette>

#include "acerca.h"
#include "facturacion.h"

#define IVA 12

QT_BEGIN_NAMESPACE
namespace Ui { class Tienda; }
QT_END_NAMESPACE

class Tienda : public QMainWindow
{
    Q_OBJECT

public:
    Tienda(QWidget *parent = nullptr);
    ~Tienda();


private slots:
    void on_inNombre_currentIndexChanged(int index);

    void on_btnAdd_released();

    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_actionAcerca_triggered();

private:
    Ui::Tienda *ui;
    QList<Producto*>m_productos;
    void anadirProductos();
    float m_subtotal;
    void calcular();
    bool verificarCI(QString cdi);
    bool verifiVacios();
    void colorReset();
    void limpiarIn();
    QString m_details;
    void envCadena();
    void limpiarOut();

};
#endif // TIENDA_H
