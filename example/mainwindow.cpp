#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet(".MainWindow{"
                  "background-color: #616161;"
                  "}");

    ui->pushButton->setStyleSheet("QPushButton{"
                                  "background-color: #232323;"
                                  "color: white;"
                                  "border-radius: 10px;"
                                  "}"
                                  ""
                                  "QPushButton:hover{"
                                  "border: 3px solid;"
                                  "border-radius: 10px;"
                                  "border-color: #a7dbb5;"
                                  "}");
    setupMenuBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMenuBar(){
    QMenu* fileMenu = new QMenu("File");
    QMenu* editMenu = new QMenu("Edit");

    fileMenu->addAction("New", this, SLOT(New()), Qt::CTRL | Qt::Key_N);

    editMenu->addAction("Undo");;

    m_menubar = new QMenuBar;
    m_menubar->addMenu(fileMenu);
    m_menubar->addMenu(editMenu);
}

void MainWindow::New(){
    qDebug() << "New was clicked!";
}
