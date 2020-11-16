#ifndef BTNDIALOGWIDGET_H
#define BTNDIALOGWIDGET_H
#include<QWidget>
#include<QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QFileDialog>
#include <QDateTime>
#include <QStringView>
#include <QLayout>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>
#include <model.h>

//first dialog widget header

//no need to change if u wanna use this GUI

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
    void read_graph_from_txt_file();
    void read_graph_from_bin_file();
    std::pair<QString, QString> write_graph_in_bin_file();
    std::pair<QString, QString> write_graph_in_txt_file();
    void write_result_in_file(std::pair<QString, QString> name, QString type);
signals:
    void widgetClosed();
private slots:
    void slotStartBtn();
};


#endif // BTNDIALOGWIDGET_H
