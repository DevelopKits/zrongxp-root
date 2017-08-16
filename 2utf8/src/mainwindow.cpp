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
    QLineEdit *psrc = ui->_edit_src, *pdest = ui->_edit_result;
	if (psrc == NULL || pdest == NULL)
	{
		return;
	}
	//
    QString str;
    char io[17] = { 0 };
	str = psrc->text();
	// 文字 => utf8_code
	if (str.isEmpty())
	{
		QStringList list = pdest->text().split("\\x");
		int size = list.size();
		char *buf = new char[size + 1];
		int j = 0;
		for (int i = 0; i < list.size(); i++)
		{
			short hex = list.at(i).toShort(NULL, 16);
			if (hex != 0)
			{
				buf[j] = (char)hex;
				j++;
			}
		}
		buf[j] = '\0';
		str.append(buf);
		if (psrc != NULL)
		{
			psrc->setText(str);
		}
	}
	// utf8_code => 文字
	else
	{
		QByteArray utf8 = psrc->text().toUtf8();
		for (int i = 0; i < utf8.size(); i++)
		{
			unsigned char t = utf8.at(i);
			_itoa(t, io, 16);
			str = str + "\\x" + io;
		}
		if (ui->_edit_result != NULL)
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
