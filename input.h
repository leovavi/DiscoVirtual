#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include "bloquearchivo.h"

namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:
    explicit Input(QWidget *parent = 0, BloqueArchivo * ba = 0, bool leer = false);
    ~Input();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Input *ui;
    BloqueArchivo * ba;
    bool leer;
};

#endif // INPUT_H
