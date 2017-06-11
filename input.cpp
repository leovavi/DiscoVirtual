#include "input.h"
#include "ui_input.h"

Input::Input(QWidget *parent, BloqueArchivo * ba) : QDialog(parent), ui(new Ui::Input)
{
    ui->setupUi(this);
    this->ba = ba;
}

Input::~Input()
{
    delete ui;
}

void Input::on_buttonBox_accepted()
{
    QString nom = ui->nombre->text();
    QString cont = ui->contenido->toPlainText();

    char * nombre = new char[nom.size()];
    char * contenido = new char[cont.size()];

    strcpy(nombre, nom.toStdString().c_str());
    strcpy(contenido, cont.toStdString().c_str());

    ba->setNombre(nombre);
    ba->setContenido(contenido);
}
