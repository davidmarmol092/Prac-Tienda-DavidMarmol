#include "tienda.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QInputDialog>
#include <QDebug>


//internacionalizacion del codigo detectando configuracion regional del idioma local
int main(int argc, char *argv[])
{
    qDebug()<<QLocale::system().name();
    QApplication a(argc, argv);
    // Objeto para manejar las traducciones
        QTranslator traducion;
        // Solicitando al usuario que seleccione un idioma
        QString idioma=QLocale::system().name();
        // Dependiendo del idioma seleccionado, carga el archivo de rtaducción
        //frances ingles, esloveno e italiano
        if (idioma == "fr_BE"){
            traducion.load(":/tienda_fr.qm");
        }else if (idioma == "en_US"){
            traducion.load(":/tienda_en.qm");
        }else if (idioma == "sl_SI"){
            traducion.load(":/tienda_pl.qm");
        }else if (idioma == "it_IT"){
            traducion.load(":/tienda_it.qm");

        }
        // Si es diferente de español, se instala la traducción en TODA la aplicación
        if (idioma != "es_US"){
            a.installTranslator(&traducion);
        }

    Tienda w;
    w.show();
    return a.exec();
}

