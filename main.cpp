#include <QWidget>
#include <QApplication>
#include<buttonWidg.h>

//------------------------------------------
//widget with 2 buttons - automatic gen || self gen
//if automatic - 3 buttons with alg choose and file type choose too
//if self gen - only file type output choose
//------------------------------------------
//start button functions
//start button disabled if no one item checked - done
//disable butoons auto and self - done
//model
//controller
//------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setFixedSize(280, 160);

    w.show();
    return a.exec();
}
