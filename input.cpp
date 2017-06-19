#include "input.h"
#include "ui_input.h"

Input::Input(QWidget *parent, BloqueArchivo * ba, bool leer) : QDialog(parent), ui(new Ui::Input)
{
    ui->setupUi(this);
    this->ba = ba;
    this->leer = leer;

    if(leer){
        ui->nombre->setText(ba->getNombre());
        ui->contenido->setText(ba->getContenido());

        ui->nombre->setReadOnly(true);
        ui->contenido->setReadOnly(true);

        QPalette * palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::gray);
        palette->setColor(QPalette::Text, Qt::darkGray);

        ui->nombre->setPalette(*palette);
        ui->contenido->setPalette(*palette);
    }
}

Input::~Input()
{
    delete ui;
}

void Input::on_buttonBox_accepted()
{
    if(!leer){
        QString nom = ui->nombre->text();
        QString cont = ui->contenido->toPlainText();

        char * nombre = new char[TAMNOMBRE];
        char * contenido = new char[cont.size()];

        memcpy(nombre, nom.toStdString().c_str(), TAMNOMBRE);
        nombre[TAMNOMBRE-1] = '\0';
        memcpy(contenido, cont.toStdString().c_str(), cont.size());

        ba->setNombre(nombre);
        ba->setContenido(contenido);
    }
}
