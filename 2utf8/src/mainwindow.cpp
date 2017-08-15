#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on__btn_utf_clicked()
{
    if (ui == NULL)
    {
        return;
    }
    QLineEdit *psrc = ui->_edit_src;
    QString str;
    char io[17] = { 0 };
    if (psrc != NULL)
    {
        QByteArray utf8 = psrc->text().toUtf8();
        for (int i = 0; i < utf8.size(); i++)
        {
            unsigned char t = utf8.at(i);
            _itoa(t, io, 16);
            str = str + "\\x" + io;
        }
        if(ui->_edit_result != NULL)
        {
            ui->_edit_result->setText(str);
        }
    }
}

void MainWindow::on__btn_utf16_clicked()
{
	if (ui == NULL)
	{
		return;
	}
	QLineEdit *psrc = ui->_edit_src;
	QString str;
	char io[17] = { 0 };
	if (psrc != NULL)
	{
		QString utf8 = psrc->text();
		for (int i = 0; i < utf8.size(); i++)
		{
			ushort t = utf8.at(i).unicode();
			_itoa(t, io, 16);
			str = str + "\\u" + io;
		}
		if (ui->_edit_result != NULL)
		{
			ui->_edit_result->setText(str);
		}
	}
}
