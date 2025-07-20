#include "ajoutpatient.h"
#include "ui_ajoutpatient.h"

ajoutPatient::ajoutPatient(QSqlDatabase *database, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ajoutPatient)
{
    ui->setupUi(this);
    this->bdd = database;
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    QValidator *validator = new QIntValidator(1,300, this);
    ui->lineEdit_poids->setValidator(validator);
    ui->lineEdit_taille->setValidator(validator);

    // Set date validator for date lineedit
    QRegularExpression R_date("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/(19[0-9][0-9]|20[0-9][0-9])");
    QRegularExpressionValidator *valida = new QRegularExpressionValidator(R_date, this);
    ui->lineEdit_dateNaissance->setValidator(valida);
    ui->lineEdit_dateOperation->setValidator(valida);

    // Set place holder for date lineedit
    ui->lineEdit_dateNaissance->setPlaceholderText("jj/MM/aaaa");
    ui->lineEdit_dateOperation->setPlaceholderText("jj/MM/aaaa");

    // Mettre le panneau dans une partie deroulante
    this->setFixedSize(this->width(),this->height());
}

void ajoutPatient::viderFormulaire(){
    ui->lineEdit_prenom->clear();
    ui->lineEdit_nomPatient->clear();
    ui->lineEdit_sexe->clear();
    ui->lineEdit_dateNaissance->clear();
    ui->lineEdit_dateOperation->clear();
    ui->lineEdit_typeIntervention->clear();
    ui->lineEdit_taille->clear();
    ui->lineEdit_poids->clear();
}

void ajoutPatient::setNomCourant(QString nom){

    this->nomFamilleCourant = nom;
}
void ajoutPatient::setPrenomCourant(QString prenom){

    this->prenomCourant = prenom;
}

void ajoutPatient::setContexte(QString contexte){

    this->contexte = contexte;

    if(contexte == "Ajout"){
        this->setWindowTitle("Ajout d un patient");

    }
    else if(contexte == "Modification"){
        this->setWindowTitle("Modification d un patient");
    }
}

void ajoutPatient::ajoutPatient::remplirInfos(QString nom, QString prenom, QString sexe, QString dateNaissance, QString dateOperation,
                                              QString typeIntervention, QString taille, QString poids, QString estOpere, QString coteBlesse){

    ui->lineEdit_prenom->setText(nom);
    ui->lineEdit_nomPatient->setText(prenom);
    ui->lineEdit_sexe->setText(sexe);
    ui->lineEdit_dateNaissance->setText(dateNaissance);
    ui->lineEdit_dateOperation->setText(dateOperation);
    ui->lineEdit_typeIntervention->setText(typeIntervention);
    ui->lineEdit_taille->setText(taille);
    ui->lineEdit_poids->setText(poids);

    if(estOpere == "Non"){
        ui->comboBox->setCurrentIndex(1);
    }
    else{
        ui->comboBox->setCurrentIndex(2);
    }

    if(coteBlesse == "Gauche"){
        ui->comboBox_coteBlesse->setCurrentIndex(1);
    }
    else{
        ui->comboBox_coteBlesse->setCurrentIndex(2);
    }
}



ajoutPatient::~ajoutPatient()
{
    delete ui;
}

void ajoutPatient::on_pushButton_clicked(){

    QString newPrenom = ui->lineEdit_prenom->text().toUpper();
    QString newNomFamille = ui->lineEdit_nomPatient->text().toUpper();
    QString newSexe = ui->lineEdit_sexe->text().toUpper();
    QString newDateNaissance = ui->lineEdit_dateNaissance->text().toUpper();
    QString newDateOperation = ui->lineEdit_dateOperation->text();
    QString newTypeOperation = ui->lineEdit_typeIntervention->text().toUpper();
    QString newTaille = ui->lineEdit_taille->text();
    QString newPoids = ui->lineEdit_poids->text();

    if(ui->comboBox->currentText() == "Non"){
        newDateOperation = "";
    }

    if((newPrenom.isEmpty() || newNomFamille.isEmpty() || newDateOperation.isEmpty() || newTypeOperation.isEmpty()
         || newTaille.isEmpty() || newPoids.isEmpty()) && ui->comboBox->currentText() == "Oui"){

        QMessageBox::warning(this, tr("Ajout impossible"),
                             "Une des valeurs rentree est vide");
        return;
    }
    else if((newPrenom.isEmpty() || newNomFamille.isEmpty() || newTaille.isEmpty() || newPoids.isEmpty())
               && ui->comboBox->currentText() == "Non"){

        QMessageBox::warning(this, tr("Ajout impossible"),
                             "Une des valeurs rentree est vide");
        return;
    }

    if(newSexe != "M" && newSexe != "F" ){
        QMessageBox::warning(this, tr("Ajout impossible"),
                             "La valeur sexe doit etre M ou F.");
        return;
    }

    if(this->contexte =="Ajout"){

        QString textRequete = "INSERT INTO Patient(nomFamille, prenom, sexe, dateNaissance, dateOperation, typeOperation,"
                              "taille, poids, estOpere, coteBlesse"
                              ") VALUES ('" + newNomFamille +
                              "','" + newPrenom +
                              "','" + newSexe +
                              "','" + newDateNaissance +
                              "','" + newDateOperation +
                              "','" + newTypeOperation.replace("'", "''") +
                              "','" + newTaille +
                              "','" + newPoids +
                              "','" + ui->comboBox->currentText() +
                              "','" + ui->comboBox_coteBlesse->currentText() +
                              + "')";

        QSqlQuery requete;
        if (!requete.exec(textRequete))
            QMessageBox::warning(this, tr("Ajout impossible BDD"), "Requete impossible :" + textRequete);
    }
    else if(this->contexte =="Modification"){

        QString textRequete = "UPDATE Patient SET nomFamille='" + newNomFamille +
                              "', prenom = '" + newPrenom + "', sexe='" + newSexe + "', dateOperation = '" + newDateOperation +
                              "', dateNaissance = '" + newDateNaissance + "', typeOperation = '" + newTypeOperation.replace("'", "''")
                              + "', taille = " + newTaille + ", poids = " + newPoids + ", estOpere = '" + ui->comboBox->currentText() +
                              + "', coteBlesse = '" + ui->comboBox_coteBlesse->currentText() +
                              "' WHERE nomFamille='" + this->nomFamilleCourant + "' and prenom = '" + this->prenomCourant + "'";

        QSqlQuery requete;
        if (!requete.exec(textRequete))
            QMessageBox::warning(this, tr("Modification impossible BDD"), "Requete impossible :" + textRequete);
    }


    emit on_genererTablePatient();

    this->close();

}


void ajoutPatient::on_comboBox_currentTextChanged(const QString &arg1){
    if(arg1 == "Non"){
        ui->lineEdit_dateOperation->setEnabled(false);
        ui->label_typeIntervention->setText("Type de lesion");
    }
    else{
        ui->lineEdit_dateOperation->setEnabled(true);
        ui->label_typeIntervention->setText("Type d intervention");
    }
}

