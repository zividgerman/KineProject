/********************************************************************************
** Form generated from reading UI file 'ajoutpatient.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AJOUTPATIENT_H
#define UI_AJOUTPATIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ajoutPatient
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit_nomPatient;
    QLineEdit *lineEdit_prenom;
    QLineEdit *lineEdit_sexe;
    QLineEdit *lineEdit_typeIntervention;
    QLineEdit *lineEdit_dateOperation;
    QLineEdit *lineEdit_taille;
    QLabel *label;
    QLabel *label_dateOperation;
    QLabel *label_typeIntervention;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_poids;
    QLineEdit *lineEdit_dateNaissance;
    QLabel *label_8;
    QLabel *label_9;
    QComboBox *comboBox;
    QFrame *line;
    QLabel *label_2;
    QComboBox *comboBox_coteBlesse;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ajoutPatient)
    {
        if (ajoutPatient->objectName().isEmpty())
            ajoutPatient->setObjectName("ajoutPatient");
        ajoutPatient->resize(634, 578);
        centralwidget = new QWidget(ajoutPatient);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(230, 480, 191, 31));
        lineEdit_nomPatient = new QLineEdit(centralwidget);
        lineEdit_nomPatient->setObjectName("lineEdit_nomPatient");
        lineEdit_nomPatient->setGeometry(QRect(230, 20, 171, 26));
        lineEdit_nomPatient->setFrame(false);
        lineEdit_prenom = new QLineEdit(centralwidget);
        lineEdit_prenom->setObjectName("lineEdit_prenom");
        lineEdit_prenom->setGeometry(QRect(230, 62, 171, 26));
        lineEdit_prenom->setFrame(false);
        lineEdit_sexe = new QLineEdit(centralwidget);
        lineEdit_sexe->setObjectName("lineEdit_sexe");
        lineEdit_sexe->setGeometry(QRect(230, 105, 41, 26));
        lineEdit_sexe->setFrame(false);
        lineEdit_typeIntervention = new QLineEdit(centralwidget);
        lineEdit_typeIntervention->setObjectName("lineEdit_typeIntervention");
        lineEdit_typeIntervention->setGeometry(QRect(230, 430, 321, 26));
        lineEdit_typeIntervention->setFrame(false);
        lineEdit_dateOperation = new QLineEdit(centralwidget);
        lineEdit_dateOperation->setObjectName("lineEdit_dateOperation");
        lineEdit_dateOperation->setGeometry(QRect(230, 393, 131, 26));
        lineEdit_dateOperation->setFrame(false);
        lineEdit_taille = new QLineEdit(centralwidget);
        lineEdit_taille->setObjectName("lineEdit_taille");
        lineEdit_taille->setGeometry(QRect(230, 200, 71, 26));
        lineEdit_taille->setFrame(false);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 105, 141, 26));
        QFont font;
        font.setBold(false);
        label->setFont(font);
        label_dateOperation = new QLabel(centralwidget);
        label_dateOperation->setObjectName("label_dateOperation");
        label_dateOperation->setGeometry(QRect(70, 393, 141, 26));
        label_dateOperation->setFont(font);
        label_typeIntervention = new QLabel(centralwidget);
        label_typeIntervention->setObjectName("label_typeIntervention");
        label_typeIntervention->setGeometry(QRect(70, 430, 141, 26));
        label_typeIntervention->setFont(font);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 240, 141, 26));
        label_4->setFont(font);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 200, 141, 26));
        label_5->setFont(font);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(70, 62, 141, 26));
        label_6->setFont(font);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 20, 141, 26));
        label_7->setFont(font);
        lineEdit_poids = new QLineEdit(centralwidget);
        lineEdit_poids->setObjectName("lineEdit_poids");
        lineEdit_poids->setGeometry(QRect(230, 240, 71, 26));
        lineEdit_poids->setFrame(false);
        lineEdit_dateNaissance = new QLineEdit(centralwidget);
        lineEdit_dateNaissance->setObjectName("lineEdit_dateNaissance");
        lineEdit_dateNaissance->setGeometry(QRect(230, 150, 131, 26));
        lineEdit_dateNaissance->setFrame(false);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(70, 145, 141, 31));
        label_8->setFont(font);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(70, 360, 141, 26));
        label_9->setFont(font);
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(230, 360, 80, 26));
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(130, 280, 321, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 310, 121, 20));
        comboBox_coteBlesse = new QComboBox(centralwidget);
        comboBox_coteBlesse->addItem(QString());
        comboBox_coteBlesse->addItem(QString());
        comboBox_coteBlesse->setObjectName("comboBox_coteBlesse");
        comboBox_coteBlesse->setGeometry(QRect(230, 310, 80, 26));
        ajoutPatient->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ajoutPatient);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 634, 26));
        ajoutPatient->setMenuBar(menubar);
        statusbar = new QStatusBar(ajoutPatient);
        statusbar->setObjectName("statusbar");
        ajoutPatient->setStatusBar(statusbar);

        retranslateUi(ajoutPatient);

        QMetaObject::connectSlotsByName(ajoutPatient);
    } // setupUi

    void retranslateUi(QMainWindow *ajoutPatient)
    {
        ajoutPatient->setWindowTitle(QCoreApplication::translate("ajoutPatient", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("ajoutPatient", "Valider", nullptr));
        label->setText(QCoreApplication::translate("ajoutPatient", "Sexe (M ou F)  :", nullptr));
        label_dateOperation->setText(QCoreApplication::translate("ajoutPatient", "Date de l operation :", nullptr));
        label_typeIntervention->setText(QCoreApplication::translate("ajoutPatient", "Type intervention :", nullptr));
        label_4->setText(QCoreApplication::translate("ajoutPatient", "Poids (kg) :", nullptr));
        label_5->setText(QCoreApplication::translate("ajoutPatient", "Taille (cm) :", nullptr));
        label_6->setText(QCoreApplication::translate("ajoutPatient", "Prenom :", nullptr));
        label_7->setText(QCoreApplication::translate("ajoutPatient", "Nom :", nullptr));
        label_8->setText(QCoreApplication::translate("ajoutPatient", "Date de naissance :", nullptr));
        label_9->setText(QCoreApplication::translate("ajoutPatient", "Intervention", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("ajoutPatient", "Oui", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("ajoutPatient", "Non", nullptr));

        label_2->setText(QCoreApplication::translate("ajoutPatient", "Cote blesse", nullptr));
        comboBox_coteBlesse->setItemText(0, QCoreApplication::translate("ajoutPatient", "Gauche", nullptr));
        comboBox_coteBlesse->setItemText(1, QCoreApplication::translate("ajoutPatient", "Droit", nullptr));

    } // retranslateUi

};

namespace Ui {
    class ajoutPatient: public Ui_ajoutPatient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AJOUTPATIENT_H
