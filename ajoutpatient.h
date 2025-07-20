#ifndef AJOUTPATIENT_H
#define AJOUTPATIENT_H

#include <QMainWindow>
#include <QMessageBox>
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QValidator>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

namespace Ui {
class ajoutPatient;
}

class ajoutPatient : public QMainWindow
{
    Q_OBJECT

public:
    explicit ajoutPatient(QSqlDatabase *database, QWidget *parent = nullptr);
    ~ajoutPatient();
    void setContexte(QString contexte);
    void setNomCourant(QString nom);
    void setPrenomCourant(QString prenom);
    void viderFormulaire();

    void remplirInfos(QString nom, QString prenom, QString sexe, QString dateNaissance, QString dateOperation,
                      QString typeIntervention, QString taille, QString poids, QString estOpere, QString coteBlesse);

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

signals:
    void on_genererTablePatient();

private:
    Ui::ajoutPatient *ui;
    QSqlDatabase *bdd;
    QString contexte;
    QString nomFamilleCourant;
    QString prenomCourant;

};

#endif // AJOUTPATIENT_H
