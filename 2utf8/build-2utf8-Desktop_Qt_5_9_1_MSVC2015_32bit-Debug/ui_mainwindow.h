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
    QPushButton *_btn_utf;
    QLineEdit *_edit_result;
    QLineEdit *_edit_src;
    QPushButton *_btn_utf16;
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
        _btn_utf = new QPushButton(centralWidget);
        _btn_utf->setObjectName(QStringLiteral("_btn_utf"));
        _btn_utf->setGeometry(QRect(20, 70, 41, 31));
        _btn_utf->setIconSize(QSize(32, 32));
        _btn_utf->setCheckable(true);
        _btn_utf->setChecked(true);
        _btn_utf->setAutoRepeat(true);
        _btn_utf->setAutoExclusive(true);
        _btn_utf->setFlat(false);
        _edit_result = new QLineEdit(centralWidget);
        _edit_result->setObjectName(QStringLiteral("_edit_result"));
        _edit_result->setGeometry(QRect(20, 40, 351, 20));
        _edit_result->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        _edit_src = new QLineEdit(centralWidget);
        _edit_src->setObjectName(QStringLiteral("_edit_src"));
        _edit_src->setGeometry(QRect(20, 10, 351, 20));
        _btn_utf16 = new QPushButton(centralWidget);
        _btn_utf16->setObjectName(QStringLiteral("_btn_utf16"));
        _btn_utf16->setGeometry(QRect(70, 70, 41, 31));
        _btn_utf16->setIconSize(QSize(32, 32));
        _btn_utf16->setCheckable(true);
        _btn_utf16->setChecked(true);
        _btn_utf16->setAutoRepeat(true);
        _btn_utf16->setAutoExclusive(true);
        _btn_utf16->setFlat(false);
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
        _btn_utf->setText(QApplication::translate("MainWindow", "utf8", Q_NULLPTR));
        _btn_utf16->setText(QApplication::translate("MainWindow", "utf16", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
