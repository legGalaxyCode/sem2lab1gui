#ifndef BTNDIALOGWIDGET_H
#define BTNDIALOGWIDGET_H
#include<QWidget>
#include<QDialog>
#include<QLabel>
#include<QPushButton>
#include<QGroupBox>
#include<QRadioButton>
#include<QFileDialog>
#include<QDateTime>
#include<QStringView>
#include<QLayout>
#include<QTextStream>
#include<QMessageBox>
#include<model.h>

//no need to change

class Dialog : public QWidget
{
    Q_OBJECT
private:
    bool checkValidWidget;
    QString strWidgName;
    QLabel* p_lbl;
    QGroupBox* p_TypeGr;
    QGroupBox* p_AlgoGr;
    QRadioButton* p_binType;
    QRadioButton* p_txtType;
    QRadioButton* p_DCheck;
    QRadioButton* p_BFCheck;
    QRadioButton* p_FUCheck;
    QPushButton* p_startBtn;
    Model* model;
public:
    Dialog(QWidget* parent = nullptr);
    ~Dialog(){};
    void closeEvent(QCloseEvent *event) override;
    void setValid(bool v);
signals:
    void widgetClosed();
private slots:
    void slotStartBtn();
};


#endif // BTNDIALOGWIDGET_H
