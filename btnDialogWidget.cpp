//no need to change

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

    p_BFCheck = new QRadioButton("Bellman-Ford algorithm");

    p_FUCheck = new QRadioButton("Floyd-Warshall algorithm");

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

std::pair<QString, QString> Dialog::write_graph_in_txt_file() {
    QString strFilter = "*.txt";
    auto graph_size = model->sizeGraph();
    auto graph = model->get_boost_graph();

    QString str_to_save = QFileDialog::getSaveFileName(nullptr,
                                                       tr("Save file"),
                                                       "Graph" + QDateTime::currentDateTime().toString().remove(QRegExp("\\s")),
                                                       strFilter,
                                                       &strFilter);

    QFile file(str_to_save + strFilter);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    //std::ofstream std_out;
    //std_out.open(str_to_save.toStdString());
    out << "Vertices: " << graph_size.first << "\n";
    out << "Edges: " << graph_size.second << "\n";
    boost::graph_traits<Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
        out << "(" << int(source(*ei, graph)) << ","
            << int(target(*ei, graph)) << ")" << "\n";
    }
    file.close();

    QMessageBox msgBox; msgBox.setText("Write completed"); msgBox.exec();

    return std::make_pair(str_to_save, strFilter);
}

std::pair<QString, QString> Dialog::write_graph_in_bin_file() {
    QString strFilter = "*.bin";
    auto graph_size = model->sizeGraph();
    auto graph = model->get_boost_graph();

    QString str_to_save = QFileDialog::getSaveFileName(nullptr,
                                                       tr("Save file"),
                                                       "Graph" + QDateTime::currentDateTime().toString().remove(QRegExp("\\s")),
                                                       strFilter,
                                                       &strFilter);
    QFile file(str_to_save + strFilter);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    //std::ofstream std_out(str_to_save.toStdString(), std::ios::binary);
    out << "Vertices: " << graph_size.first << "\n";
    out << "Edges: " << int(graph_size.second) << "\n";
    boost::graph_traits<Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
        out << "(" << int(source(*ei, graph)) << ","
            << int(target(*ei, graph)) << ")" << "\n";
    }

    file.close();

    QMessageBox msgBox; msgBox.setText("Write completed"); msgBox.exec();

    return std::make_pair(str_to_save, strFilter);
}

void Dialog::read_graph_from_txt_file() {
    QString strFilter = "*.txt";
    QString str_to_open = QFileDialog::getOpenFileName(nullptr,
                                                       tr("Open file"));
                                                       //"/home",
                                                       //strFilter);
}

void Dialog::read_graph_from_bin_file() {
    QString strFilter = "*.bin";
    QString str_to_open = QFileDialog::getOpenFileName(nullptr,
                                                       tr("Open file"),
                                                       "/home",
                                                       strFilter);
}

void Dialog::write_result_in_file(std::pair<QString, QString> name, QString type) {
    boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
    auto graph = model->get_boost_graph();
    auto parent = model->get_graph_opt().first;
    auto distance = model->get_graph_opt().second;

    QFile file(name.first + type + name.second);
    file.open(QIODevice::WriteOnly);
    if (name.second == "*.bin") {
        QDataStream out(&file);
        out << "Distances and parents:" << "\n";
        for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
            out << "distance(" << int(*vi) << ") = " << int(distance[*vi]) << ", ";
            out << "parent(" << int(*vi) << ") = " << int(parent[*vi]) << "\n";
        }
    } else {
        QTextStream out(&file);
        out << "Distances and parents:" << "\n";
        for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
            out << "distance(" << *vi << ") = " << distance[*vi] << ", ";
            out << "parent(" << *vi << ") = " << parent[*vi] << "\n";
        }
    }
    file.close();
}

void Dialog::slotStartBtn() { //TODO: optimize ^D
    if (checkValidWidget == 0) {
        if (p_DCheck->isChecked()) {
            QMessageBox msgBox;
            std::pair<QString, QString> res; //auto does not work
            p_binType->isChecked() ? res = write_graph_in_bin_file() : res = write_graph_in_txt_file();
            model->boostDijkstra();
            write_result_in_file(res, QString(" Dijkstra"));
            msgBox.setText("Dijkstra completed"); msgBox.exec();

        } else if (p_BFCheck->isChecked()) {
            QMessageBox msgBox;
            std::pair<QString, QString> res;
            p_binType->isChecked() ? res = write_graph_in_bin_file() : res = write_graph_in_txt_file();
            model->boostBellman();
            write_result_in_file(res, QString(" Bellman"));
            msgBox.setText("Bellman-Ford completed"); msgBox.exec();

        } else if (p_FUCheck->isChecked()) {
            QMessageBox msgBox;
            std::pair<QString, QString> res;
            p_binType->isChecked() ? res = write_graph_in_bin_file() : res = write_graph_in_txt_file();
            model->boostFloyd();
            write_result_in_file(res, QString(" Warshall"));
            msgBox.setText("Floyd-Warshall completed"); msgBox.exec();

        }
    } else if (checkValidWidget == 1) {
        p_binType->isChecked() ? read_graph_from_bin_file() : read_graph_from_txt_file();
    }
}
