#ifndef BUTTONWIDG_H
#define BUTTONWIDG_H
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QWidget>
#include <btnDialogWidget.h>
#include <model.h>
#include <controller.h>

//second dialog widget header

//no need to change if u wanna use this GUI

class Widget : public QWidget //V part
{
    Q_OBJECT
private:
    bool whichBtn; // 0 - auto, 1 - self
    QString strWidgName;
    QPushButton* p_autoGenBtn;
    QPushButton* p_selfGenBtn;
    QLabel* p_lbl;
    Dialog* dialog; //work widget
    Model* model; //M part
    Controller* controller; //C part
public:
    Widget(QWidget* parent = nullptr);
    ~Widget(){};
private slots:
    void slotSetActiveGenBtn();
    void slotAutoBtnClicked(); // - opens the dialog with choose of algorithm and file type
    void slotSelfBtnClicked(); // - opens the document when graph generated
};

#endif // BUTTONWIDG_H
