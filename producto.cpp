#include "producto.h"

int Producto::co() const
{
    return m_co;
}

void Producto::setCo(int newCo)
{
    m_co = newCo;
}

const QString &Producto::nombre() const
{
    return m_nombre;
}

void Producto::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

float Producto::precio() const
{
    return m_precio;
}

void Producto::setPrecio(float newPrecio)
{
    m_precio = newPrecio;
}

Producto::Producto(QObject *parent) : QObject(parent)
{

}

Producto::Producto(int co, const QString &nombre, float precio, QObject *parent) : QObject(parent),
    m_co(co),
    m_nombre(nombre),
    m_precio(precio)
{}
