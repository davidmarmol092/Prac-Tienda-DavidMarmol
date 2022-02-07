#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QObject>

class Producto : public QObject
{
    Q_OBJECT
private:
    int m_co;
    QString m_nombre;
    float m_precio;

public:
    explicit Producto(QObject *parent = nullptr);
    Producto(int co, const QString &nombre, float precio, QObject *parent = nullptr);
    void setCo(int newCo);
    void setNombre(const QString &newNombre);
    void setPrecio(float newPrecio);
    float precio() const;
    int co() const;
    const QString &nombre() const;


signals:

};

#endif // PRODUCTO_H
