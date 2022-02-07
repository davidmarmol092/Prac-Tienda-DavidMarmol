#include "facturacion.h"
#include "ui_facturacion.h"


Facturacion::~Facturacion()
{
    delete ui;
}


Facturacion::Facturacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Facturacion)
{
    ui->setupUi(this);
    m_acept=false;
}

Ui::Facturacion *Facturacion::getUi() const
{
    return ui;
}

void Facturacion::setUi(Ui::Facturacion *newUi)
{
    ui = newUi;
}

const QString &Facturacion::detalles() const
{
    return m_detalles;
}

const QString &Facturacion::nombre() const
{
    return m_nombre;
}

void Facturacion::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

const QString &Facturacion::cedula() const
{
    return m_cedula;
}

void Facturacion::setCedula(const QString &newCedula)
{
    m_cedula = newCedula;
}

const QString &Facturacion::correo() const
{
    return m_correo;
}

void Facturacion::setCorreo(const QString &newCorreo)
{
    m_correo = newCorreo;
}

const QString &Facturacion::telefono() const
{
    return m_telefono;
}

void Facturacion::setTelefono(const QString &newTelefono)
{
    m_telefono = newTelefono;
}

const QString &Facturacion::direccion() const
{
    return m_direccion;
}

void Facturacion::setDireccion(const QString &newDireccion)
{
    m_direccion = newDireccion;
}

void Facturacion::insertarDatos(QString nombre, QString cedula, QString telef, QString correo, QString direccion, QString detalles)
{
    setNombre(nombre);
    setCedula(cedula);
    setTelefono(telef);
    setCorreo(correo);
    setDireccion(direccion);
    m_detalles=detalles;
    mostrar();
}

void Facturacion::mostrar()
{
    QString data="";
    QString encabezado="X----------------------------------------------------------X\n"
                       "\t- - MINIMARKET ROSITA - -\n"
                       "x----------------------------------------------------------x\n"
                       "\tRUC: 99999999999\n"
                       " No. De Factura 032718 - Autorizada el 24/01/21\n"
                       " Direccion: Av. Juan León Mera, Av. Vicente Logroño\n"
                       " E-12 Quito-Ecuador S-10-39\n"
                       " Numero Telefónico: (02) 3120-754\n"
                       "\tResponsable de llevar IVA\n"
                       "x---------------------------------------------------------x\n"
                       "\t- -  DATOS DEL CLIENTE - -\n"
                       "x---------------------------------------------------------x\n";
    data=encabezado;

    if(m_cedula!="9999999999"){
        QString name=" Nombre: "+m_nombre+"\n";
        QString cedula=" Cédula CI: "+m_cedula+"\n";
        QString telef=" Num. Telefónico: "+m_telefono+"\n";
        QString correo=" E-mail: "+m_correo+"\n";
        QString direc=" Dirección: "+m_direccion+"\n"
        "---------------------------------------------------------\n";
        data+=name+cedula+telef+correo+direc+"\n";
    }
    else{
        QString add="\t- - DATOS D´ CONSUMIDOR FINAL - -\n"
        "\nx-------------------------------------------------------x\n";
        data+=add;
    }
    QString pro;
    pro="\tCantidad.\tProducto\tP.Unitario\tSub-Total\n"+m_detalles;

    data+=pro;

    ui->outDatos->setPlainText(data);
    calcFinales();
}

void Facturacion::vizualizar()
{
    QFile archivo("C:/Users/marmo/Desktop/Minimarket/Facturas/"+m_fyh+".txt");
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream datosArchivo(&archivo);
        datosArchivo.operator<<(ui->outDatos->toPlainText());
    }
    archivo.close();
}

/**{

    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar archivo",                                                     
                                                         QDir::home().absoluteFilePath("downloads"),
                                                         "Documentos de texto (*.txt)");
    QFile archivo(nombreArchivo);
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream datosArchivo(&archivo);
        datosArchivo << ui->outDatos->toPlainText();
    }
    archivo.close();
}**/

void Facturacion::calcFinales()
{
    QString Subtotales="";
    m_fyh = QDateTime::currentDateTime().toString("ddMMyyyy_hhmmss");
    float iva=m_subtotal*m_iva/100;
    Subtotales="x----------------------------------------------------------x\n"
               "\t\tSub-Total:\t"+QString::number(m_subtotal,'f',2)+"\n"
               "\t\tIVA"+QString::number(m_iva,'f',2)+"%:\t"+QString::number(iva,'f',2)+"\n"
               "\t\tTOTAL:\t"+QString::number(m_subtotal+iva,'f',2)+"\n"
               "x----------------------------------------------------------x\n\n"
               " GRACIAS POR VISITAR 'MINIMARKET ROSITA' DONDE TODO\n"
               " ES 'BBB' BUENO, BONITO Y BARATO, Y ENCUENTRAS LOS\n"
               " MEJORES PRECIOS, VUELVE PRONTO.\n\n"
               "x----------------------------------------------------------x\n\n"
               "  RECUERDA GUARDAR ESTA FACTURA PARA PODER RECLAMAR\n"
               "  UN DESCUENTO DEL 10% EN LOCALES NACIONALES DE KFC\n"
               "  PARA ESTO DEBE PRESENTARSE CON ESTE CUPON VALIDO\n"
               "  DESDE 24-01-22/24-02-22.\n\n"
               " ******************Aplican Restricciones*************\n\n"
               "X----------------------------------------------------------X";

    ui->outDatos->appendPlainText(Subtotales);
}

void Facturacion::on_buttonBox_accepted()
{
    m_acept=true;
    vizualizar();
}
void Facturacion::on_buttonBox_rejected()
{

}
void Facturacion::setIVA(int newIva)
{
    m_iva = newIva;
}

void Facturacion::setSubtotal(float newSubtotal)
{
    m_subtotal = newSubtotal;
}

float Facturacion::subtotal() const
{
    return m_subtotal;
}





