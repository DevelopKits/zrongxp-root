/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *_btn_2utf8;
    QLineEdit *_edit_result;
    QLineEdit *_edit_src;
    QPushButton *_btn_2utf16;
    QPushButton *_btn_utf8;
    QPushButton *_btn_utf16;
    QPushButton *_btn_clear;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->setEnabled(true);
        MainWindow->resize(383, 122);
        MainWindow->setMinimumSize(QSize(383, 122));
        MainWindow->setMaximumSize(QSize(383, 122));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        MainWindow->setFont(font);
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        MainWindow->setAcceptDrops(false);
        MainWindow->setWindowOpacity(1);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setDockNestingEnabled(false);
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        _btn_2utf8 = new QPushButton(centralWidget);
        _btn_2utf8->setObjectName(QStringLiteral("_btn_2utf8"));
        _btn_2utf8->setGeometry(QRect(20, 70, 51, 31));
        _btn_2utf8->setIconSize(QSize(32, 32));
        _btn_2utf8->setCheckable(true);
        _btn_2utf8->setChecked(true);
        _btn_2utf8->setAutoRepeat(true);
        _btn_2utf8->setAutoExclusive(true);
        _btn_2utf8->setFlat(false);
        _edit_result = new QLineEdit(centralWidget);
        _edit_result->setObjectName(QStringLiteral("_edit_result"));
        _edit_result->setGeometry(QRect(20, 40, 351, 20));
        _edit_result->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        _edit_src = new QLineEdit(centralWidget);
        _edit_src->setObjectName(QStringLiteral("_edit_src"));
        _edit_src->setGeometry(QRect(20, 10, 351, 20));
        _btn_2utf16 = new QPushButton(centralWidget);
        _btn_2utf16->setObjectName(QStringLiteral("_btn_2utf16"));
        _btn_2utf16->setGeometry(QRect(140, 70, 51, 31));
        _btn_2utf16->setIconSize(QSize(32, 32));
        _btn_2utf16->setCheckable(true);
        _btn_2utf16->setChecked(true);
        _btn_2utf16->setAutoRepeat(true);
        _btn_2utf16->setAutoExclusive(true);
        _btn_2utf16->setFlat(false);
        _btn_utf8 = new QPushButton(centralWidget);
        _btn_utf8->setObjectName(QStringLiteral("_btn_utf8"));
        _btn_utf8->setGeometry(QRect(80, 70, 51, 31));
        _btn_utf8->setIconSize(QSize(32, 32));
        _btn_utf8->setCheckable(true);
        _btn_utf8->setChecked(true);
        _btn_utf8->setAutoRepeat(true);
        _btn_utf8->setAutoExclusive(true);
        _btn_utf8->setFlat(false);
        _btn_utf16 = new QPushButton(centralWidget);
        _btn_utf16->setObjectName(QStringLiteral("_btn_utf16"));
        _btn_utf16->setGeometry(QRect(200, 70, 51, 31));
        _btn_utf16->setIconSize(QSize(32, 32));
        _btn_utf16->setCheckable(true);
        _btn_utf16->setChecked(true);
        _btn_utf16->setAutoRepeat(true);
        _btn_utf16->setAutoExclusive(true);
        _btn_utf16->setFlat(false);
        _btn_clear = new QPushButton(centralWidget);
        _btn_clear->setObjectName(QStringLiteral("_btn_clear"));
        _btn_clear->setGeometry(QRect(260, 70, 51, 31));
        _btn_clear->setIconSize(QSize(32, 32));
        _btn_clear->setCheckable(true);
        _btn_clear->setChecked(true);
        _btn_clear->setAutoRepeat(true);
        _btn_clear->setAutoExclusive(true);
        _btn_clear->setFlat(false);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        _btn_2utf8->setText(QApplication::translate("MainWindow", "->utf8", Q_NULLPTR));
        _btn_2utf16->setText(QApplication::translate("MainWindow", "->utf16", Q_NULLPTR));
        _btn_utf8->setText(QApplication::translate("MainWindow", "<-utf8", Q_NULLPTR));
        _btn_utf16->setText(QApplication::translate("MainWindow", "<-utf16", Q_NULLPTR));
        _btn_clear->setText(QApplication::translate("MainWindow", "clear", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
