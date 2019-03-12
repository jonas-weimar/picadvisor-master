#include "error.h"


Error::Error(int status, QString error, QString message)
{
    // create new message box
    // not a pointer cause must be destroyed after constructor

    QMessageBox box;

    box.setWindowTitle("Program Error occured");
    box.setText(QString::number(status) + " " + error + ": \n\n" + message);
    box.exec();
}
