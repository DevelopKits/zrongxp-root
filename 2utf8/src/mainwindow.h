#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>

namespace Ui {
class MainWindow;
}

class abc : public QPushButton
{

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on__btn_utf16_clicked();
    void on__btn_utf8_clicked();
    void on__btn_2utf8_clicked();

    void on__btn_2utf16_clicked();

    void on__btn_clear_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
