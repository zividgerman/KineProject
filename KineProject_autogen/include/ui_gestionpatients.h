/********************************************************************************
** Form generated from reading UI file 'gestionpatients.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTIONPATIENTS_H
#define UI_GESTIONPATIENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GestionPatients
{
public:
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QPushButton *pushButton_ajouter;
    QPushButton *pushButton_supprimer;
    QPushButton *pushButton_modifier;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GestionPatients)
    {
        if (GestionPatients->objectName().isEmpty())
            GestionPatients->setObjectName("GestionPatients");
        GestionPatients->resize(1174, 523);
        centralwidget = new QWidget(GestionPatients);
        centralwidget->setObjectName("centralwidget");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 40, 1121, 351));
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(0);
        pushButton_ajouter = new QPushButton(centralwidget);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(290, 420, 93, 29));
        pushButton_supprimer = new QPushButton(centralwidget);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setGeometry(QRect(750, 420, 93, 29));
        pushButton_modifier = new QPushButton(centralwidget);
        pushButton_modifier->setObjectName("pushButton_modifier");
        pushButton_modifier->setGeometry(QRect(510, 420, 93, 29));
        GestionPatients->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GestionPatients);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1174, 26));
        GestionPatients->setMenuBar(menubar);
        statusbar = new QStatusBar(GestionPatients);
        statusbar->setObjectName("statusbar");
        GestionPatients->setStatusBar(statusbar);

        retranslateUi(GestionPatients);

        QMetaObject::connectSlotsByName(GestionPatients);
    } // setupUi

    void retranslateUi(QMainWindow *GestionPatients)
    {
        GestionPatients->setWindowTitle(QCoreApplication::translate("GestionPatients", "MainWindow", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("GestionPatients", "Ajouter ", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("GestionPatients", "Supprimer", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("GestionPatients", "Modifier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GestionPatients: public Ui_GestionPatients {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTIONPATIENTS_H
