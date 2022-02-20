#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "framelesswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupMenuBar();
    QMenuBar *getMenuBar(){
        return m_menubar;
    }

public slots:
    void New();

private:
    Ui::MainWindow *ui;

    QMenuBar *m_menubar;
};
#endif // MAINWINDOW_H
