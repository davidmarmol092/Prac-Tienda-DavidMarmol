#ifndef FACTURACION_H
#define FACTURACION_H

#include <QDebug>
#include <QDialog>
#include <QDateTime>
#include <QFileDialog>

namespace Ui {
class Facturacion;
}

class Facturacion : public QDialog
{
    Q_OBJECT

public:
    explicit Facturacion(QWidget *parent = nullptr);
    ~Facturacion();

    void setDetalles(const QString &newDetalles);

    Ui::Facturacion *getUi() const;
    void setUi(Ui::Facturacion *newUi);
    const QString &detalles() const;
    const QString &nombre() const;
    void setNombre(const QString &newNombre);
    const QString &cedula() const;
    void setCedula(const QString &newCedula);
    const QString &correo() const;
    void setCorreo(const QString &newCorreo);
    const QString &telefono() const;
    void setTelefono(const QString &newTelefono);
    const QString &direccion() const;
    void setDireccion(const QString &newDireccion);
    void insertarDatos(QString nombre,QString cedula, QString telef,QString correo,QString direccion,QString detalles);
    bool m_acept;

    float subtotal() const;

    void setSubtotal(float newSubtotal);

    void setIVA(int newIva);

private slots:
    void on_buttonBox_rejected();

public slots:
    void on_buttonBox_accepted();

    //declaro variables privadas a los datos de usuario
private:
    Ui::Facturacion *ui;
    QString m_fyh;
    QString m_correo;
    QString m_detalles;
    QString m_nombre;
    QString m_cedula;
    QString m_telefono;
    QString m_direccion;
    int m_iva;
    float m_subtotal;
    void mostrar();
    void vizualizar();
    void calcFinales();



};

#endif // FACTURACION_H
