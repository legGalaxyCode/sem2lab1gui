#include<btnDialogWidget.h>

Dialog::Dialog(QWidget* parent) : QWidget(parent) {
    strWidgName = "Advanced choose options";
    this->setWindowTitle(strWidgName);

    model = Model::getInstance();

    p_lbl = new QLabel("Choose the file and algorithm type");

    p_TypeGr = new QGroupBox("File type");
    p_AlgoGr = new QGroupBox("Algorithm type");

    p_DCheck = new QRadioButton("Dijkstra algorithm");
    p_DCheck->setChecked(true);
    connect(p_DCheck, SIGNAL(clicked()), this, SLOT(slotDBtn()));

    p_BFCheck = new QRadioButton("Bellman-Ford algorithm");
    connect(p_BFCheck, SIGNAL(clicked()), this, SLOT(slotBellmanFordBtn()));

    p_FUCheck = new QRadioButton("Floyd-Uorshell algorithm");
    connect(p_FUCheck, SIGNAL(clicked()), this, SLOT(slotFloydUorshellBtn()));

    p_binType = new QRadioButton("Binary file");
    p_binType->setChecked(true);
    p_txtType = new QRadioButton("Text file");

    p_startBtn = new QPushButton("Start");
    connect(p_startBtn, SIGNAL(clicked()), this, SLOT(slotStartBtn()));

    QVBoxLayout* p_VGroupLay = new QVBoxLayout;
    p_VGroupLay->addWidget(p_binType);
    p_VGroupLay->addWidget(p_txtType);
    p_TypeGr->setLayout(p_VGroupLay);

    QVBoxLayout* p_VAlgoLay = new QVBoxLayout;
    p_VAlgoLay->addWidget(p_DCheck);
    p_VAlgoLay->addWidget(p_BFCheck);
    p_VAlgoLay->addWidget(p_FUCheck);
    p_AlgoGr->setLayout(p_VAlgoLay);

    QHBoxLayout* p_HAllGrLay = new QHBoxLayout;
    p_HAllGrLay->addWidget(p_TypeGr);
    p_HAllGrLay->addWidget(p_AlgoGr);

    QFrame* line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QVBoxLayout* p_mainLay = new QVBoxLayout;
    p_mainLay->addWidget(p_lbl);
    p_mainLay->addWidget(line);
    p_mainLay->addLayout(p_HAllGrLay);
    p_mainLay->addWidget(p_startBtn);

    this->setLayout(p_mainLay);
}

void Dialog::setValid(bool v) {
    checkValidWidget = v;
}

void Dialog::closeEvent(QCloseEvent *event) {
    emit widgetClosed();
}

void Dialog::slotStartBtn() {
    //QString strToSave = QFileDialog::getExistingDirectory(nullptr,
    //                                                     "Directory Dialog",
    //                                                      "");
    if (checkValidWidget == 0) {
        QString strFilter;
        if (p_binType->isChecked()) {
            strFilter = "*.bin";
        } else if (p_txtType->isChecked()) {
            strFilter = "*.txt";
        }
        QString strToSave = QFileDialog::getSaveFileName(nullptr,
                                                         tr("Save file"),
                                                         "Graph " + QDateTime::currentDateTime().toString(),
                                                         strFilter,
                                                         &strFilter);
        QFile file(strToSave);
        /*model->generateGraph(); //graph generates
        if (p_DCheck->isChecked()) {
            model->Dijkstra();
            //input in file like:
            //file.open(QIODevice::ReadWrite);
            //file.close();
        } else if (p_BFCheck->isChecked()) {
            model->BellmanFord();
            //input in file like:
            //file.open(QIODevice::ReadWrite);
            //file.close();
        } else if (p_FUCheck->isChecked()) {
            model->FloydUorshell();
            //input in file like:
            //file.open(QIODevice::ReadWrite);
            //file.close();
        }*/
    } else if (checkValidWidget == 1) {
        QString strFilter;
        if (p_binType->isChecked()) {
            strFilter = "*.bin";
        } else if (p_txtType->isChecked()) {
            strFilter = "*.txt";
        }
        QString strOpen = QFileDialog::getOpenFileName(nullptr,
                                                       tr("Open file"),
                                                       "",
                                                       strFilter);
        QFile file(strOpen);
        /*if (strFilter == "*.bin")
            model->readGraphFromBinFile(); //read graph
        else
            model->readGraphFromTxtFile();

        if (p_DCheck->isChecked()) {
            model->Dijkstra();
            //input in file some data like:
            //file.open(QIODevice::ReadWrite);
            //file.close();
        } else if (p_BFCheck->isChecked()) {
            model->BellmanFord();
            //input in file some data like:
            //file.open(QIODevice::ReadWrite);
            //file.close();
        } else if (p_FUCheck->isChecked()) {
            model->FloydUorshell();
            //input in file some data like:
            //file.open(QIODevice::ReadWrite);
            //file.close();
        }*/
    }
}
