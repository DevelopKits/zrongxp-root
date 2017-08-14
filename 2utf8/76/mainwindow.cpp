#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	if (ui == NULL)
	{
		return;
	}
	QLineEdit *lineEdit = ui->lineEdit;
	QString str;
	char io[17] = { 0 };
	if (lineEdit != NULL)
	{
		QByteArray utf8 = lineEdit->text().toUtf8();
		for (int i = 0; i < utf8.size(); i++)
		{
			unsigned char t = utf8.at(i);
			itoa(t, io, 16);
			str = str + "\\x" + io;
		}
		if(ui->lineEdit_2 != NULL)
		{
			ui->lineEdit_2->setText(str);
		}
	}
}
