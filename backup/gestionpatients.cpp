#include "gestionpatients.h"
#include "qsqldatabase.h"
#include "ui_gestionpatients.h"

GestionPatients::GestionPatients(QSqlDatabase *database, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionPatients){
    ui->setupUi(this);

    this->bdd = database;

    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    QStringList listeColonnesPatient = this->recupererListeColonnesTable("Patient");
    foreach (QString col, listeColonnesPatient) {

        headers << col;
    }

    genererTablePatient();

    fentreAjout = new ajoutPatient(bdd);
    connect(fentreAjout, SIGNAL(on_genererTablePatient()), this, SLOT(genererTablePatient()));
}

GestionPatients::~GestionPatients(){
    delete ui;
}


void GestionPatients::closeEvent (QCloseEvent *event){
    emit on_initialiserFenetreMere();

}

void GestionPatients::genererTablePatient(){

    QList<QStringList> listesInfosPatient;
    QSqlQuery requete;

    QString texteRequete = "SELECT ";
    for (int i = 0; i < headers.count(); ++i) {
        if(i == headers.count() -1)
            texteRequete.append(headers.at(i));
        else
            texteRequete.append(headers.at(i) + ",");
    }
    texteRequete.append(" FROM Patient");


    requete.exec(texteRequete);

    while (requete.next()) {

        QStringList infosPatientCourant;
        for (int i = 0; i < headers.count(); ++i) {
            infosPatientCourant << requete.value(i).toString();
        }

        listesInfosPatient.append(infosPatientCourant);
    }

    ui->tableWidget->setRowCount(listesInfosPatient.count());
    ui->tableWidget->setColumnCount(headers.count());

    int nbLigne = 0;

    foreach (QStringList listeCourante, listesInfosPatient) {

        int nbCol = 0;
        foreach (QString infoCourante, listeCourante) {

            // allocate the widget item
            QTableWidgetItem * item = new QTableWidgetItem();
            // item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            item->setText(infoCourante);
            item->setTextAlignment(Qt::AlignHCenter);
            ui->tableWidget->setItem( nbLigne, nbCol, item );
            nbCol++;
        }
        ++nbLigne;
    }

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setStyleSheet("QHeaderView::section { color:white; background-color:grey; }");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

void GestionPatients::on_pushButton_ajouter_clicked(){

    fentreAjout->viderFormulaire();
    fentreAjout->setContexte("Ajout");

    if(!fentreAjout->isActiveWindow()){
        fentreAjout->show();
    }
}


void GestionPatients::on_pushButton_supprimer_clicked(){

    if(ui->tableWidget->selectedItems().count() == 0){

        QMessageBox::warning(this, tr("Suppression impossible"),
                    "Aucun patient n a ete selectionne, Veuillez en choisir un");
        return;
    }

    QString nomFamilleCourant = ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("nomFamille"))->text();
    QString prenomCourant = ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("prenom"))->text();

    QString textRequete = "DELETE FROM Patient WHERE nomFamille='" + nomFamilleCourant +
                          "' and prenom = '" + prenomCourant + "'";

    QSqlQuery requete;
    if (!requete.exec(textRequete))
        qDebug() << "Requete suppression ligne sans succes";

    genererTablePatient();

}


void GestionPatients::on_pushButton_modifier_clicked(){

    if(ui->tableWidget->selectedItems().count() == 0){

        int ret = QMessageBox::warning(this, tr("Modification impossible"),
                "Aucun patient n a ete selectionne, veuillez en choisir un");
        return;
    }

    fentreAjout->setPrenomCourant(ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("prenom"))->text());
    fentreAjout->setNomCourant(ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("nomFamille"))->text());

    fentreAjout->remplirInfos(ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("prenom"))->text(),
                              ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("nomFamille"))->text(),
                              ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("sexe"))->text(),
                              ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("dateNaissance"))->text(),
                              ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("dateOperation"))->text(),
                              ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("typeOperation"))->text(),
                              ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("taille"))->text(),
                              ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("poids"))->text(),
                              ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("estOpere"))->text(),
                              ui->tableWidget->item(ui->tableWidget->currentRow(), headers.indexOf("coteBlesse"))->text()
                              );

    fentreAjout->setContexte("Modification");

    if(!fentreAjout->isActiveWindow()){
        fentreAjout->show();
    }
}


//****************************************
QStringList GestionPatients::recupererListeColonnesTable(QString nomTable){

    // Recuperer la liste des colonnes
    QSqlQuery requete;
    QString texteRequete = "SELECT sql FROM sqlite_master WHERE tbl_name = '" + nomTable + "'";
    QString texteColonnes;

    requete.exec(texteRequete);
    while (requete.next()) {
        texteColonnes = requete.value(0).toString();
    }

    // application de la Regexp
    QStringList listeColonnes;
    QRegularExpression regex("\"(.*?)\"");
    QRegularExpressionMatchIterator matchI = regex.globalMatch(texteColonnes);

    while (matchI.hasNext()) {
        QRegularExpressionMatch match = matchI.next();
        listeColonnes << match.captured(1);
    }

    listeColonnes.removeFirst();
    listeColonnes.removeLast();

    return listeColonnes;
}
