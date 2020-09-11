#include<buttonWidg.h>

Widget::Widget(QWidget* parent) : QWidget(parent) {
    dialog = new Dialog;
    dialog->setFixedSize(333, 220);

    model = Model::getInstance(); //pass parameters or random them inside model
    controller = new Controller; //useless may be

    strWidgName = "Lab GUI";
    this->setWindowTitle(strWidgName);

    QVBoxLayout* p_lay = new QVBoxLayout;
    p_lbl = new QLabel("Choose the graph generation type");
    p_lay->addWidget(p_lbl, Qt::AlignCenter, Qt::AlignJustify);

    p_autoGenBtn = new QPushButton("Auto");
    connect(p_autoGenBtn, SIGNAL(clicked()), this, SLOT(slotAutoBtnClicked()));

    p_selfGenBtn = new QPushButton("Self");
    connect(p_selfGenBtn, SIGNAL(clicked()), this, SLOT(slotSelfBtnClicked()));

    QVBoxLayout* p_btnLay = new QVBoxLayout;
    p_btnLay->addWidget(p_autoGenBtn, Qt::AlignJustify);
    p_btnLay->addWidget(p_selfGenBtn, Qt::AlignJustify);

    p_lay->addLayout(p_btnLay);
    this->setLayout(p_lay);
}

void Widget::slotAutoBtnClicked() {
    whichBtn = 0;
    dialog->setValid(whichBtn);
    dialog->show();

    connect(dialog, SIGNAL(widgetClosed()), this, SLOT(slotSetActiveGenBtn()));

    p_autoGenBtn->setDisabled(true);
    p_selfGenBtn->setDisabled(true);
}

void Widget::slotSetActiveGenBtn() {
    p_autoGenBtn->setDisabled(false);
    p_selfGenBtn->setDisabled(false);
}

void Widget::slotSelfBtnClicked() { //ctr
    whichBtn = 1;
    dialog->setValid(whichBtn);
    dialog->show();

    connect(dialog, SIGNAL(widgetClosed()), this, SLOT(slotSetActiveGenBtn()));

    p_autoGenBtn->setDisabled(true);
    p_selfGenBtn->setDisabled(true);
}
