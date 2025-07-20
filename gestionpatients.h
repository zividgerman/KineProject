#ifndef GESTIONPATIENTS_H
#define GESTIONPATIENTS_H

#include "ajoutpatient.h"
#include <QMainWindow>
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QHeaderView>
#include <QMessageBox>
#include <QCloseEvent>

#include <QInputDialog>


namespace Ui {
class GestionPatients;
}

class GestionPatients : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionPatients(QSqlDatabase *database, QWidget *parent = nullptr);
    ~GestionPatients();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();

    void closeEvent (QCloseEvent *event);

    void genererTablePatient();

signals:
    void on_initialiserFenetreMere();

private:
    Ui::GestionPatients *ui;
    QSqlDatabase *bdd;
    QStringList headers;
    ajoutPatient *fentreAjout;
    QStringList recupererListeColonnesTable(QString nomTable);

};

#endif // GESTIONPATIENTS_H
