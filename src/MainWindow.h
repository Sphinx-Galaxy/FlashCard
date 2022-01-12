#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * Author: Mattis Jaksch
 */

class CardContainer;
class QHBoxLayout;
class QVBoxLayout;

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    void create_layout();

    QVBoxLayout* create_status_bar();

    QHBoxLayout* create_card_overview();

private:
    CardContainer* cardContainer;
};
#endif // MAINWINDOW_H
