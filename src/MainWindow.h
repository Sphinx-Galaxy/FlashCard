#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * Author: Mattis Jaksch
 */

class DataBase;

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    void create_layout();
};
#endif // MAINWINDOW_H
