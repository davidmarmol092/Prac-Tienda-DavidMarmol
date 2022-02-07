#include "tienda.h"
#include "ui_tienda.h"

Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);

    anadirProductos();
    foreach(Producto *p, m_productos){
        ui->inNombre->addItem(p->nombre());
    }
    //configuracion de la cabecera de la tabla
    QStringList cabecera={tr("Cantidad. No"),tr("Producto"),tr("Prec.Unit"),tr(" SubTotal")};
    ui->outDetalle->setColumnCount(4);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    m_subtotal=0;
    m_details="";
}

Tienda::~Tienda()
{

    delete ui;
}

//productos a disposisicon para la compra
void Tienda::anadirProductos()
{
    m_productos.append(new Producto(1,tr("Leche"),0.80));
    m_productos.append(new Producto(2,tr("Pan"),0.15));
    m_productos.append(new Producto(3,tr("Queso"),2.50));
}

//funcion para los calculos finales
void Tienda::calcular()
{
    int fila=ui->outDetalle->rowCount();
    int contador=0;
    float sumatoria=0;
    while(contador!=fila){
        sumatoria+=ui->outDetalle->item(contador,3)->text().toDouble();
        contador++;
    }
    m_subtotal=sumatoria;
    float iva=m_subtotal*IVA/100;
    float total=m_subtotal+iva;
    ui->outSubtotal_13->setText("$ "+QString::number(m_subtotal,'f',2));
    ui->outIva->setText("$ "+QString::number(iva,'f',2));
    ui->outTotal->setText("$ "+QString::number(total,'f',2));
}

//verrificacion de la cedula de identidad
bool Tienda::verificarCI(QString cdi)
{
    bool est = true;
    int vcedula[10];
    int vPar[4];
    int vImpar[5]={0};
    int sumaPar=0;
    int sumaImpar=0;
    int total;
    int nveri;

    double nu;

    if(cdi=="9999999999"){
        return true;
    }

    do
    {
        nu=cdi.toInt();
        if(nu<100000000 || nu>9999999999)
        {

            est=false;
            break;
        }
        QString p1=cdi.mid(0,1);
        QString p2=cdi.mid(1,1);
        QString p3=cdi.mid(2,1);
        QString p4=cdi.mid(3,1);
        QString p5=cdi.mid(4,1);
        QString p6=cdi.mid(5,1);
        QString p7=cdi.mid(6,1);
        QString p8=cdi.mid(7,1);
        QString p9=cdi.mid(8,1);
        QString p10=cdi.mid(9,1);

        vcedula[0]=p1.toInt();
        vcedula[1]=p2.toInt();
        vcedula[2]=p3.toInt();
        vcedula[3]=p4.toInt();
        vcedula[4]=p5.toInt();
        vcedula[5]=p6.toInt();
        vcedula[6]=p7.toInt();
        vcedula[7]=p8.toInt();
        vcedula[8]=p9.toInt();
        vcedula[9]=p10.toInt();

        if(vcedula[0]>2)
        {

            est = false;
            break;
        }

        vPar[0]=vcedula[1];
        vPar[1]=vcedula[3];
        vPar[2]=vcedula[5];
        vPar[3]=vcedula[7];
        vImpar[0]=vcedula[0];
        vImpar[1]=vcedula[2];
        vImpar[2]=vcedula[4];
        vImpar[3]=vcedula[6];
        vImpar[4]=vcedula[8];

        for(int i=0; i<5; i++)
        {
            vImpar[i]=vImpar[i]*2;
            if(vImpar[i]>9)
            {
                vImpar[i]=vImpar[i]-9;
            }
            sumaImpar += vImpar[i];
        }
        for(int i=0; i<4; i++)
        {
            sumaPar += vPar[i];
        }

        total = sumaPar + sumaImpar;

        nveri = total%10;

        if(nveri==0)
        {
            if(nveri==vcedula[9])
            {
                est=true;
                break;
            }else
            {
                est=false;
                break;
            }
        }else if(nveri !=0)
        {
            nveri=10-nveri;

            if(nveri==vcedula[9])
            {
                est=true;
                break;
            }else
            {

                est=false;
                break;
            }
        }

    }while(nu<100000000 || nu>9999999999 || vcedula[0]>2);
    return est;
}

//dar color a los in en los datos vacios
bool Tienda::verifiVacios()
{
    bool dato=true;
    if(verificarCI(ui->inCedula->text())==false){
        QPalette palette=ui->inCedula->palette();
        palette.setColor(ui->inCedula->backgroundRole(),Qt::red);
        palette.setColor(ui->inCedula->foregroundRole(),Qt::black);
        ui->inCedula->setPalette(palette);
        ui->statusbar->showMessage("ERROR!. Datos ingreo de cedula invalida.",3000);
        dato=false;

    }

    else{
        QPalette palette=ui->inCedula->palette();
        palette.setColor(ui->inCedula->backgroundRole(),Qt::green);
        palette.setColor(ui->inCedula->foregroundRole(),Qt::black);
        ui->inCedula->setPalette(palette);
        dato=true;
    }

    if(verificarCI(ui->inCedula->text())==true){
        if(ui->inCedula->text()=="9999999999"){
            QPalette palette=ui->inNom->palette();
            palette.setColor(ui->inNom->backgroundRole(),Qt::green);
            palette.setColor(ui->inNom->foregroundRole(),Qt::black);
            ui->inNom->setPalette(palette);
            ui->inNom->clear();
            palette=ui->inTelf->palette();
            palette.setColor(ui->inTelf->backgroundRole(),Qt::green);
            palette.setColor(ui->inTelf->foregroundRole(),Qt::black);
            ui->inTelf->setPalette(palette);
            ui->inTelf->clear();
            palette=ui->inMail->palette();
            palette.setColor(ui->inMail->backgroundRole(),Qt::green);
            palette.setColor(ui->inMail->foregroundRole(),Qt::black);
            ui->inMail->setPalette(palette);
            ui->inMail->clear();
            palette=ui->inDireccion->palette();
            palette.setColor(ui->inDireccion->backgroundRole(),Qt::green);
            palette.setColor(ui->inDireccion->foregroundRole(),Qt::black);
            ui->inDireccion->setPalette(palette);
            ui->inDireccion->clear();

            return true;
        }
    }
    if(ui->inNom->text().isEmpty()){
        QPalette palette=ui->inNom->palette();
        palette.setColor(ui->inNom->backgroundRole(),Qt::red);
        palette.setColor(ui->inNom->foregroundRole(),Qt::black);
        ui->inNom->setPalette(palette);
        ui->statusbar->showMessage("ERROR!. Coloque su nombre.!",3000);
        dato=false;
    }
    else{
        QPalette palette=ui->inNom->palette();
        palette.setColor(ui->inNom->backgroundRole(),Qt::green);
        palette.setColor(ui->inNom->foregroundRole(),Qt::black);
        ui->inNom->setPalette(palette);
    }
    if(ui->inTelf->text().isEmpty()){
        QPalette palette=ui->inTelf->palette();
        palette.setColor(ui->inTelf->backgroundRole(),Qt::red);
        palette.setColor(ui->inTelf->foregroundRole(),Qt::black);
        ui->inTelf->setPalette(palette);
        ui->statusbar->showMessage("ERROR!",3000);
        dato=false;
    }
    else{
        QPalette palette=ui->inTelf->palette();
        palette.setColor(ui->inTelf->backgroundRole(),Qt::green);
        palette.setColor(ui->inTelf->foregroundRole(),Qt::black);
        ui->inTelf->setPalette(palette);
    }

    if(ui->inMail->text().isEmpty()){
        QPalette palette=ui->inMail->palette();
        palette.setColor(ui->inMail->backgroundRole(),Qt::red);
        palette.setColor(ui->inMail->foregroundRole(),Qt::black);
        ui->inMail->setPalette(palette);
        ui->statusbar->showMessage("ERROR!",3000);
        dato=false;
    }
    else{
        QPalette palette=ui->inMail->palette();
        palette.setColor(ui->inMail->backgroundRole(),Qt::green);
        palette.setColor(ui->inMail->foregroundRole(),Qt::black);
        ui->inMail->setPalette(palette);
    }
    if(ui->inDireccion->toPlainText().isEmpty()){
        QPalette palette=ui->inDireccion->palette();
        palette.setColor(ui->inDireccion->backgroundRole(),Qt::red);
        palette.setColor(ui->inDireccion->foregroundRole(),Qt::black);
        ui->inDireccion->setPalette(palette);
        ui->statusbar->showMessage("ERROR!.",3000);
        dato=false;
    }
    else{
        QPalette palette=ui->inDireccion->palette();
        palette.setColor(ui->inDireccion->backgroundRole(),Qt::green);
        palette.setColor(ui->inDireccion->foregroundRole(),Qt::black);
        ui->inDireccion->setPalette(palette);
    }
    return dato;
}
void Tienda::colorReset()
{
    QPalette palette=ui->inCedula->palette();
    palette.setColor(ui->inCedula->backgroundRole(),Qt::white);
    palette.setColor(ui->inCedula->foregroundRole(),Qt::black);
    ui->inCedula->setPalette(palette);
    palette=ui->inNom->palette();
    palette.setColor(ui->inNom->backgroundRole(),Qt::white);
    palette.setColor(ui->inNom->foregroundRole(),Qt::black);
    ui->inNom->setPalette(palette);
    palette=ui->inTelf->palette();
    palette.setColor(ui->inTelf->backgroundRole(),Qt::white);
    palette.setColor(ui->inTelf->foregroundRole(),Qt::black);
    ui->inTelf->setPalette(palette);
    palette=ui->inMail->palette();
    palette.setColor(ui->inMail->backgroundRole(),Qt::white);
    palette.setColor(ui->inMail->foregroundRole(),Qt::black);
    ui->inMail->setPalette(palette);
    palette=ui->inDireccion->palette();
    palette.setColor(ui->inDireccion->backgroundRole(),Qt::white);
    palette.setColor(ui->inDireccion->foregroundRole(),Qt::black);
    ui->inDireccion->setPalette(palette);
}

void Tienda::limpiarIn()
{
    ui->inNom->clear();
    ui->inCedula->clear();
    ui->inTelf->clear();
    ui->inDireccion->clear();
    ui->inMail->clear();
    int rows=ui->outDetalle->rowCount();
    while(rows!=-1){
        ui->outDetalle->removeRow(rows);
        rows--;
    }
}

void Tienda::envCadena()
{
    int filas=ui->outDetalle->rowCount();
    int contador=0;
    QString detalles="";

    while(contador!=filas){
        detalles+="\t"+ui->outDetalle->item(contador,0)->text()+"\t"+ui->outDetalle->item(contador,1)->text()+"\t"+ui->outDetalle->item(contador,2)->text()+"\t"+ui->outDetalle->item(contador,3)->text()+"\n";
        contador++;
    }
    m_details=detalles;


}

void Tienda::limpiarOut()
{    ui->outSubtotal_13->setText("0.00");
     ui->outIva->setText("0.00");
      ui->outTotal->setText("0.00");

}


void Tienda::on_inNombre_currentIndexChanged(int index)
{
    float precio = m_productos.at(index)->precio();
    ui->outPrecio->setText(QString::number(precio,'f',2));
    ui->inCantidad->setValue(0);
}


void Tienda::on_btnAdd_released()
{
    int cantidad= ui->inCantidad->value();
    if(cantidad==0){
        return;
    }
    int i=ui->inNombre->currentIndex();
    Producto *p =m_productos.at(i);

    float subtotal=p->precio()*cantidad;

    int fila= ui->outDetalle->rowCount();
    bool encontrado=false;
    int contador=0;
    if(fila>0){
        while(encontrado==false&&contador!=fila){
            QString nombre=ui->outDetalle->item(contador,1)->text();
            QString comparar=p->nombre();

            if(nombre==comparar){
                QString antiguaCant=(ui->outDetalle->item(contador,0)->text());
                int cant=antiguaCant.toDouble();


                cantidad+=cant;
                subtotal=p->precio()*cantidad;
                ui->outDetalle->setItem(contador,0,new QTableWidgetItem(QString::number(cantidad,'f',2)));
                ui->outDetalle->setItem(contador,3,new QTableWidgetItem(QString::number(subtotal,'f',2)));

                encontrado=true;
            }
            contador++;
        }
    }
    else{}
    if(encontrado==false){
        ui->outDetalle->insertRow(fila);
        ui->outDetalle->setItem(fila,0,new QTableWidgetItem(QString::number(cantidad,'f',2)));
        ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));
        ui->outDetalle->setItem(fila,2,new QTableWidgetItem(QString::number(p->precio(),'f',2)));
        ui->outDetalle->setItem(fila,3,new QTableWidgetItem(QString::number(subtotal,'f',2)));

    }
    ui->inCantidad->setValue(0);
    ui->inNombre->setFocus();
    calcular();

}


void Tienda::on_pushButton_released()
{
    if(verifiVacios()==true){
        Facturacion *finalizar =new Facturacion(this);
        envCadena();
        finalizar->setIVA(IVA);
        finalizar->setSubtotal(m_subtotal);
        finalizar->insertarDatos(ui->inNom->text(),ui->inCedula->text()
                                 ,ui->inTelf->text(),ui->inMail->text()
                                 ,ui->inDireccion->toPlainText(),m_details);

        finalizar->exec();
        if(finalizar->m_acept==true){
            limpiarIn();
            limpiarOut();
        }
        colorReset();
    }
}


void Tienda::on_pushButton_2_released()
{
    limpiarIn();
    limpiarOut();
    ui->inNom->setFocus();
    colorReset();
}


void Tienda::on_actionAcerca_triggered()
{
    Acerca *acerca=new Acerca(this);
    acerca->exec();
}

