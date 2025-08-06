#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qforeach.h"
#include <QDesktopServices>
#include <QUrl>
#include <QImageReader>

// Il faudrait mettre NO a gauche et opere a droite

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initialiserDatabase();

    //*************************
    // initialiser le menu
    QMenu *menu = new QMenu();
    menu->setTitle("Gestion des patients");
    this->ui->menubar->addMenu(menu);
    connect(menu, SIGNAL(aboutToShow()), this, SLOT(actionGestionPatient_clicked()));

    ui->pushButton_editer_bilan->setEnabled(false);
    ui->pushButton_modifier_bilan->setEnabled(false);

    initialiserFenetre();

    gest = new GestionPatients(&this->database);
    gest->setWindowTitle("Gestion des patients");
    connect(gest, SIGNAL(on_initialiserFenetreMere()), this, SLOT(initialiserFenetre()));

    //*************************
    // // TEST PDF TODO
    // genererRapportPdf( QStringList() << "1" << "2" << "3");

    // //TEST BATCH
    // testCmdBat();

    // //TEST BDD
    // testDb();
    //*************************

    //*************************
    // Configuration de la fenetre
    this->setWindowTitle("Generateur de bilans");
}


MainWindow::~MainWindow(){
    database.commit();
    database.close();
    // QSqlDatabase::removeDatabase(this->connName);
    delete ui;
}


//****************************************
QString MainWindow::getValue(QString pathFichierConfig, QString groupe, QString cle){
    QString valeur;

    QSettings settings(pathFichierConfig, QSettings::IniFormat);
    settings.beginGroup(groupe);
    valeur = settings.value(cle).toString();
    settings.endGroup();

    return valeur;
}


//*****************************************************************
// TEST
//*****************************************************************

void MainWindow::testDb(){
    if (!database.open()){
        ecrireLog("Base de donnees non ouverte");
        return;
    }

    QSqlQuery query;

    QString requete = "INSERT INTO Patient(Prenom, nomFamille) VALUES ('JEAN', 'BOM')";
    if(query.exec(requete)){
        ecrireLog("requete reussie : " + requete);
    }
    else
        ecrireLog("requete non reussie : " + requete);

}

//****************************************
bool MainWindow::lancerCmdPdftk(const QStringList& fichiersEntree, const QString& pathFichierRes) {
    bool estExecute = true;
    QString pathDossierPdftk = QApplication::applicationDirPath() + "/PDFTK/";

    QStringList arguments = fichiersEntree;
    arguments << "cat" << "output" << pathFichierRes;

    QProcess proc;
    proc.start(pathDossierPdftk + "pdftk.exe", arguments);
    proc.waitForFinished();

    if (proc.exitCode() != 0) {
        qDebug() << "PDFTK error output:" << proc.readAllStandardError();
        qDebug() << "PDFTK stdout:" << proc.readAllStandardOutput();
        qDebug() << "Arguments:" << arguments.join(" ");
        estExecute = false;
    }

    return estExecute;
}

//****************************************
void MainWindow::genererRapportPdf(QString contenuHtml){

    // Generer le fichier PDF
    QTextDocument document;
    document.setHtml(contenuHtml);

    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(getValue(PATH_CONFIG, "paths", "pdfRes"));
    printer.setPageMargins(QMarginsF(0, 0, 0, 0));

    document.print(&printer);
}



//****************************************
void MainWindow::initialiserDatabase(){

    database = QSqlDatabase::addDatabase(getValue(PATH_CONFIG, "dbConfig", "driver"));
    database.setDatabaseName(getValue(PATH_CONFIG, "dbConfig", "name"));

    if (!database.open())
        ecrireLog("Impossible d ouvrir la base de donnees");
    else
        ecrireLog("la base de donnees est ouverte");
}


//****************************************
void MainWindow::initialiserFenetre(){

    QSqlQuery requete;

    // Mettre le panneau dans une partie deroulante
    this->resize(1200,900);
    this->setFixedSize(1200,900);

    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    //remove the widget in area;
    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);
    //reset widget
    ui->scrollArea->setWidget(ui->widget_genou);

    ui->scrollArea->setVisible(false);
    ui->widget_genou->setEnabled(false);
    ui->comboBox_dateBilan->setEnabled(false);
    ui->pushButton_annulerEditionBilan->setVisible(false);
    ui->pushButton_annulerModificationBilan->setVisible(false);
    ui->pushButton_generer_rapport->setVisible(false);
    ui->pushButton_annulerEditionRapport->setVisible(false);

    ui->textEdit->setAlignment(Qt::AlignCenter);

    this->ui->textEdit->setFrameStyle(QFrame::NoFrame);
    this->ui->textEdit->setAlignment(Qt::AlignCenter);

    //*************************
    // remplissage des combobox
    ui->comboBox_type_Bilan->clear();
    ui->comboBox_patient_courant->clear();

    // combobox bilan
    QStringList listeBilans;

    if(!requete.exec("SELECT libelle FROM TypeBilan")){
        ecrireLog("Requete impossible : SELECT libelle FROM TypeBilan");
    }

    while (requete.next()) {
        QString libelle = requete.value(0).toString();
        listeBilans.append(libelle);
    }

    ui->comboBox_type_Bilan->addItems(listeBilans);

    // combobox patient
    QStringList listePatients;

    if(!requete.exec("SELECT prenom, nomFamille FROM Patient")){
        ecrireLog("Requete impossible : SELECT prenom, nomFamille FROM Patient");
    }
    while (requete.next()) {
        QString prenom = requete.value(0).toString();
        QString nomFamille = requete.value(1).toString();

        mapPatient.insert(prenom, nomFamille);
        listePatients.append(nomFamille + " " + prenom);
    }

    ui->comboBox_patient_courant->addItems(listePatients);

    // Mettre labels en gras
    ui->label_amplitude_articulaire->setStyleSheet("font-weight: bold;");
    ui->label_perimetre->setStyleSheet("font-weight: bold;");
    ui->label_ration_ij_quadri->setStyleSheet("font-weight: bold;");
    ui->label_ration_add_abb->setStyleSheet("font-weight: bold;");
    ui->label_test_cmj->setStyleSheet("font-weight: bold;");
    ui->label_test_cmjB->setStyleSheet("font-weight: bold;");
    // ui->label_test_stabilisation->setStyleSheet("font-weight: bold;");
    ui->label_test_dj->setStyleSheet("font-weight: bold;");
    ui->label_test_djB->setStyleSheet("font-weight: bold;");
    ui->label_test_sjB->setStyleSheet("font-weight: bold;");
    ui->label_test_accroupissement->setStyleSheet("font-weight: bold;");

    // Mettre image du schema
    // Load the image using HTML
        QString html = "<img src=\""  + QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "schema")+
                    "\" width=\"300\" height=\"210\">";
        ui->textEdit_schemaYBT->setHtml(html);

    // Bilan performance
    this->ui->textEdit_bpc_analyseGestuelle->setPlaceholderText("Encadre analyse posture, attaque du pas, cycle, cadence, etc..");
}


//****************************************
/*
 *
 */
QMap<QString, QString>  MainWindow::recupererInfosBilanGenouBdd(QString numeroTest){

    QMap<QString, QString> mapInfos;
    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();
    QStringList listeColonnes = recupererListeColonnesTable("infosBilanGenou");

    QString textRequete = "SELECT * FROM infosBilanGenou WHERE "
                          "idPatient = (SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + nomFamilleCourant +
                          "%' and prenom LIKE '%" + prenomCourant + "%') "
                          "AND idTypeBilan = (SELECT idTypeBilan FROM TypeBilan WHERE libelle='"
                          + ui->comboBox_type_Bilan->currentText() + "') AND numeroTest='" + numeroTest + "'";

    QSqlQuery requete;
    if(!requete.exec(textRequete)){
        ecrireLog("Requete impossible : " + textRequete);
    }

    // Recuperer l ensemble des donnees du bilan courant dans la map
    while (requete.next()) {
        for (int i = 0; i < listeColonnes.count(); ++i) {
            mapInfos.insert(listeColonnes.at(i), requete.value(i).toString());
        }
    }

    return mapInfos;
}

//****************************************
/*
 *
 */
QMap<QString, QString>  MainWindow::recupererInfosBilanEpauleBdd(QString numeroTest){

    QMap<QString, QString> mapInfos;
    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();
    QStringList listeColonnes = recupererListeColonnesTable("infosBilanEpaule");

    QString textRequete = "SELECT * FROM infosBilanEpaule WHERE "
                          "idPatient = (SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + nomFamilleCourant +
                          "%' and prenom LIKE '%" + prenomCourant + "%') "
                          "AND idTypeBilan = (SELECT idTypeBilan FROM TypeBilan WHERE libelle='"
                          + ui->comboBox_type_Bilan->currentText() + "') AND numeroTest='" + numeroTest + "'";

    QSqlQuery requete;
    if(!requete.exec(textRequete)){
        ecrireLog("Requete impossible : " + textRequete);
    }

    // Recuperer l ensemble des donnees du bilan courant dans la map
    while (requete.next()) {
        for (int i = 0; i < listeColonnes.count(); ++i) {
            mapInfos.insert(listeColonnes.at(i), requete.value(i).toString());
        }
    }

    return mapInfos;
}

//****************************************
/*
 *
 */
QMap<QString, QString>  MainWindow::recupererInfosBilanChevilleBdd(QString numeroTest){

    QMap<QString, QString> mapInfos;
    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();
    QStringList listeColonnes = recupererListeColonnesTable("infosBilanCheville");

    QString textRequete = "SELECT * FROM infosBilanCheville WHERE "
                          "idPatient = (SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + nomFamilleCourant +
                          "%' and prenom LIKE '%" + prenomCourant + "%') "
                          "AND idTypeBilan = (SELECT idTypeBilan FROM TypeBilan WHERE libelle='"
                          + ui->comboBox_type_Bilan->currentText() + "') AND numeroTest='" + numeroTest + "'";

    QSqlQuery requete;
    if(!requete.exec(textRequete)){
        ecrireLog("Requete impossible : " + textRequete);
    }

    // Recuperer l ensemble des donnees du bilan courant dans la map
    while (requete.next()) {
        for (int i = 0; i < listeColonnes.count(); ++i) {
            mapInfos.insert(listeColonnes.at(i), requete.value(i).toString());
        }
    }

    return mapInfos;
}

//****************************************
/*
 *
 */
QMap<QString, QString>  MainWindow::recupererInfosBilanHancheBdd(QString numeroTest){

    QMap<QString, QString> mapInfos;
    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();
    QStringList listeColonnes = recupererListeColonnesTable("infosBilanHanche");

    QString textRequete = "SELECT * FROM infosBilanHanche WHERE "
                          "idPatient = (SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + nomFamilleCourant +
                          "%' and prenom LIKE '%" + prenomCourant + "%') "
                          "AND idTypeBilan = (SELECT idTypeBilan FROM TypeBilan WHERE libelle='"
                          + ui->comboBox_type_Bilan->currentText() + "') AND numeroTest='" + numeroTest + "'";

    QSqlQuery requete;
    if(!requete.exec(textRequete)){
        ecrireLog("Requete impossible : " + textRequete);
    }

    // Recuperer l ensemble des donnees du bilan courant dans la map
    while (requete.next()) {
        for (int i = 0; i < listeColonnes.count(); ++i) {
            mapInfos.insert(listeColonnes.at(i), requete.value(i).toString());
        }
    }

    return mapInfos;
}


//****************************************
/*
 *
 */
QMap<QString, QString>  MainWindow::recupererInfosBilanBpcBdd(QString numeroTest){

    QMap<QString, QString> mapInfos;
    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();
    QStringList listeColonnes = recupererListeColonnesTable("infosBilanCourse");

    QString textRequete = "SELECT * FROM infosBilanCourse WHERE "
                          "idPatient = (SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + nomFamilleCourant +
                          "%' and prenom LIKE '%" + prenomCourant + "%') "
                          "AND idTypeBilan = (SELECT idTypeBilan FROM TypeBilan WHERE libelle='"
                          + ui->comboBox_type_Bilan->currentText() + "') AND numeroTest='" + numeroTest + "'";

    QSqlQuery requete;
    if(!requete.exec(textRequete)){
        ecrireLog("Requete impossible : " + textRequete);
    }

    // Recuperer l ensemble des donnees du bilan courant dans la map
    while (requete.next()) {
        for (int i = 0; i < listeColonnes.count(); ++i) {
            mapInfos.insert(listeColonnes.at(i), requete.value(i).toString());
        }
    }

    return mapInfos;
}

//****************************************
/*
 *
 */
QMap<QString, QString>  MainWindow::recupererInfosBilanBpscBdd(QString numeroTest){

    QMap<QString, QString> mapInfos;
    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();
    QStringList listeColonnes = recupererListeColonnesTable("infosBilanSportCollectif");

    QString textRequete = "SELECT * FROM infosBilanSportCollectif WHERE "
                          "idPatient = (SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + nomFamilleCourant +
                          "%' and prenom LIKE '%" + prenomCourant + "%') "
                          "AND idTypeBilan = (SELECT idTypeBilan FROM TypeBilan WHERE libelle='"
                          + ui->comboBox_type_Bilan->currentText() + "') AND numeroTest='" + numeroTest + "'";

    QSqlQuery requete;
    if(!requete.exec(textRequete)){
        ecrireLog("Requete impossible : " + textRequete);
    }

    // Recuperer l ensemble des donnees du bilan courant dans la map
    while (requete.next()) {
        for (int i = 0; i < listeColonnes.count(); ++i) {
            mapInfos.insert(listeColonnes.at(i), requete.value(i).toString());
        }
    }

    return mapInfos;
}

//****************************************
/*
 *
 */
QMap<QString, QString>  MainWindow::recupererInfosBilanBpfBdd(QString numeroTest){

    QMap<QString, QString> mapInfos;
    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();
    QStringList listeColonnes = recupererListeColonnesTable("infosBilanSportCombat");

    QString textRequete = "SELECT * FROM infosBilanSportCombat WHERE "
                          "idPatient = (SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + nomFamilleCourant +
                          "%' and prenom LIKE '%" + prenomCourant + "%') "
                          "AND idTypeBilan = (SELECT idTypeBilan FROM TypeBilan WHERE libelle='"
                          + ui->comboBox_type_Bilan->currentText() + "') AND numeroTest='" + numeroTest + "'";

    QSqlQuery requete;
    if(!requete.exec(textRequete)){
        ecrireLog("Requete impossible : " + textRequete);
    }

    // Recuperer l ensemble des donnees du bilan courant dans la map
    while (requete.next()) {
        for (int i = 0; i < listeColonnes.count(); ++i) {
            mapInfos.insert(listeColonnes.at(i), requete.value(i).toString());
        }
    }

    return mapInfos;
}

//****************************************
/*
 *
 */
QMap<QString, QString>  MainWindow::recupererInfosBilanBpcfBdd(QString numeroTest){

    QMap<QString, QString> mapInfos;
    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();
    QStringList listeColonnes = recupererListeColonnesTable("infosBilanCrossfit");

    QString textRequete = "SELECT * FROM infosBilanCrossfit WHERE "
                          "idPatient = (SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + nomFamilleCourant +
                          "%' and prenom LIKE '%" + prenomCourant + "%') "
                          "AND idTypeBilan = (SELECT idTypeBilan FROM TypeBilan WHERE libelle='"
                          + ui->comboBox_type_Bilan->currentText() + "') AND numeroTest='" + numeroTest + "'";

    QSqlQuery requete;
    if(!requete.exec(textRequete)){
        ecrireLog("Requete impossible : " + textRequete);
    }

    // Recuperer l ensemble des donnees du bilan courant dans la map
    while (requete.next()) {
        for (int i = 0; i < listeColonnes.count(); ++i) {
            mapInfos.insert(listeColonnes.at(i), requete.value(i).toString());
        }
    }

    return mapInfos;
}

//****************************************
/*
 *
 */
QStringList MainWindow::recupererListeColonnesTable(QString nomTable){

    // Recuperer la liste des colonnes
    QSqlQuery requete;
    QString texteRequete = "SELECT sql FROM sqlite_master WHERE tbl_name = '" + nomTable + "'";
    QString texteColonnes;

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }
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

    return listeColonnes;
}


//****************************************
/*
 *
 */
QMap<QString, QString> MainWindow::remplirQMapInfoBilanGenou(QString typeRequete){

    QMap<QString, QString> mapRequete;
    QSqlQuery requete;

    QStringList listeColonnes = recupererListeColonnesTable("infosBilanGenou");

    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("doubleSpinBox_g")){
            QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox*>(w);
            double valeurCourante = dSpinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante,'f',1));
                    break;
                }
            }
        }
        else if(w->objectName().contains("spinBox_g")){
            QSpinBox *spinBox = dynamic_cast<QSpinBox*>(w);
            int valeurCourante = spinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante));
                    break;
                }
            }
        }
        else if(w->objectName().contains("comboBox_g")){
            QComboBox *comboBox = dynamic_cast<QComboBox*>(w);
            QString texteCourant = comboBox->currentText();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, "'" + texteCourant + "'");
                    break;
                }
            }
        }
        else if(w->objectName().contains("checkBox_g")){
            QCheckBox *checkbox = dynamic_cast<QCheckBox*>(w);
            QString texteCourant = checkbox->text();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    if(checkbox->isChecked())
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";1'");
                    else
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";0'");
                    break;
                }
            }
        }
        else if(w->objectName().contains("radioButton_g")){
            QRadioButton *radio = dynamic_cast<QRadioButton*>(w);
            QString texteCourant = radio->text();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    if(radio->isChecked())
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";1'");
                    else
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";0'");
                    break;
                }
            }
        }
    }

    QString texteRequete;

    // On recherche l idPatient a inserer
    QString idPatient;
    texteRequete = "SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").first() +
                   "%' and prenom LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").last() + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }
    while (requete.next()) {
        idPatient = requete.value(0).toString();
    }
    mapRequete.insert("idPatient", idPatient);

    // On ajoute la date du Bilan
    mapRequete.insert("dateBilan", "'" + QDate::currentDate().toString("dd/MM/yyyy") + "'");

    // Si on effectue une requete INSERT
    if(typeRequete == "insert"){

        // On recherche l idTypeBilan a inserer
        QString idTypeBilan;
        texteRequete = "SELECT idTypeBilan FROM TypeBilan WHERE  libelle='" + ui->comboBox_type_Bilan->currentText() +"'";

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            idTypeBilan = requete.value(0).toString();
        }
        mapRequete.insert("idTypeBilan", idTypeBilan);

        // On recherche le numero du bilan a inserer
        QString lastNumeroTest;

        texteRequete = "SELECT (EXISTS (SELECT idPatient FROM infosBilanGenou WHERE idPatient=" + idPatient + "))";
        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            lastNumeroTest = requete.value(0).toString();
        }

        if(lastNumeroTest == "0"){
            mapRequete.insert("numeroTest", "1");
        }
        else{
            texteRequete = "SELECT MAX(numeroTest) FROM infosBilanGenou WHERE idPatient=" + idPatient;

            if(!requete.exec(texteRequete)){
                ecrireLog("Requete impossible : " + texteRequete);
            }
            while (requete.next()) {
                lastNumeroTest = requete.value(0).toString();
            }

            mapRequete.insert("numeroTest", QString::number(lastNumeroTest.toInt() + 1));
        }
    }
    return mapRequete;
}

//****************************************
/*
 *
 */
QMap<QString, QString> MainWindow::remplirQMapInfoBilanEpaule(QString typeRequete){

    QMap<QString, QString> mapRequete;
    QSqlQuery requete;

    QStringList listeColonnes = recupererListeColonnesTable("infosBilanEpaule");

    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("doubleSpinBox_e")){
            QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox*>(w);
            double valeurCourante = dSpinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante,'f',1));
                    break;
                }
            }
        }
        else if(w->objectName().contains("spinBox_e")){
            QSpinBox *spinBox = dynamic_cast<QSpinBox*>(w);
            int valeurCourante = spinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante));
                    break;
                }
            }
        }
        else if(w->objectName().contains("comboBox_e")){
            QComboBox *comboBox = dynamic_cast<QComboBox*>(w);
            QString texteCourant = comboBox->currentText();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, "'" + texteCourant + "'");
                    break;
                }
            }
        }
        else if(w->objectName().contains("checkBox_e")){
            QCheckBox *checkbox = dynamic_cast<QCheckBox*>(w);
            QString texteCourant = checkbox->text();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    if(checkbox->isChecked())
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";1'");
                    else
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";0'");
                    break;
                }
            }
        }
        else if(w->objectName().contains("radioButton_e")){
            QRadioButton *radio = dynamic_cast<QRadioButton*>(w);
            QString texteCourant = radio->text();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    if(radio->isChecked())
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";1'");
                    else
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";0'");
                    break;
                }
            }
        }
    }

    QString texteRequete;

    // On recherche l idPatient a inserer
    QString idPatient;
    texteRequete = "SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").first() +
                   "%' and prenom LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").last() + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }
    while (requete.next()) {
        idPatient = requete.value(0).toString();
    }
    mapRequete.insert("idPatient", idPatient);

    // On ajoute la date du Bilan
    mapRequete.insert("dateBilan", "'" + QDate::currentDate().toString("dd/MM/yyyy") + "'");

    // Si on effectue une requete INSERT
    if(typeRequete == "insert"){

        // On recherche l idTypeBilan a inserer
        QString idTypeBilan;
        texteRequete = "SELECT idTypeBilan FROM TypeBilan WHERE  libelle='" + ui->comboBox_type_Bilan->currentText() +"'";

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            idTypeBilan = requete.value(0).toString();
        }
        mapRequete.insert("idTypeBilan", idTypeBilan);

        // On recherche le numero du bilan a inserer
        QString lastNumeroTest;

        texteRequete = "SELECT (EXISTS (SELECT idPatient FROM infosBilanEpaule WHERE idPatient=" + idPatient + "))";
        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            lastNumeroTest = requete.value(0).toString();
        }

        if(lastNumeroTest == "0"){
            mapRequete.insert("numeroTest", "1");
        }
        else{
            texteRequete = "SELECT MAX(numeroTest) FROM infosBilanEpaule WHERE idPatient=" + idPatient;

            if(!requete.exec(texteRequete)){
                ecrireLog("Requete impossible : " + texteRequete);
            }
            while (requete.next()) {
                lastNumeroTest = requete.value(0).toString();
            }

            mapRequete.insert("numeroTest", QString::number(lastNumeroTest.toInt() + 1));
        }
    }
    return mapRequete;
}

//****************************************
/*
 *
 */
QMap<QString, QString> MainWindow::remplirQMapInfoBilanHanche(QString typeRequete){

    QMap<QString, QString> mapRequete;
    QSqlQuery requete;

    QStringList listeColonnes = recupererListeColonnesTable("infosBilanHanche");

    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("doubleSpinBox_h")){
            QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox*>(w);
            double valeurCourante = dSpinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante,'f',1));
                    break;
                }
            }
        }
        else if(w->objectName().contains("comboBox_h")){
            QComboBox *comboBox = dynamic_cast<QComboBox*>(w);
            QString texteCourant = comboBox->currentText();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, "'" + texteCourant + "'");
                    break;
                }
            }
        }
        else if(w->objectName().contains("checkBox_h")){
            QCheckBox *checkbox = dynamic_cast<QCheckBox*>(w);
            QString texteCourant = checkbox->text();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    if(checkbox->isChecked())
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";1'");
                    else
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";0'");
                    break;
                }
            }
        }
        else if(w->objectName().contains("radioButton_h")){
            QRadioButton *radio = dynamic_cast<QRadioButton*>(w);
            QString texteCourant = radio->text();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    if(radio->isChecked())
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";1'");
                    else
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";0'");
                    break;
                }
            }
        }
    }

    QString texteRequete;

    // On recherche l idPatient a inserer
    QString idPatient;
    texteRequete = "SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").first() +
                   "%' and prenom LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").last() + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }
    while (requete.next()) {
        idPatient = requete.value(0).toString();
    }
    mapRequete.insert("idPatient", idPatient);

    // On ajoute la date du Bilan
    mapRequete.insert("dateBilan", "'" + QDate::currentDate().toString("dd/MM/yyyy") + "'");

    // Si on effectue une requete INSERT
    if(typeRequete == "insert"){

        // On recherche l idTypeBilan a inserer
        QString idTypeBilan;
        texteRequete = "SELECT idTypeBilan FROM TypeBilan WHERE  libelle='" + ui->comboBox_type_Bilan->currentText() +"'";

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            idTypeBilan = requete.value(0).toString();
        }
        mapRequete.insert("idTypeBilan", idTypeBilan);

        // On recherche le numero du bilan a inserer
        QString lastNumeroTest;

        texteRequete = "SELECT (EXISTS (SELECT idPatient FROM infosBilanHanche WHERE idPatient=" + idPatient + "))";
        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            lastNumeroTest = requete.value(0).toString();
        }

        if(lastNumeroTest == "0"){
            mapRequete.insert("numeroTest", "1");
        }
        else{
            texteRequete = "SELECT MAX(numeroTest) FROM infosBilanHanche WHERE idPatient=" + idPatient;

            if(!requete.exec(texteRequete)){
                ecrireLog("Requete impossible : " + texteRequete);
            }
            while (requete.next()) {
                lastNumeroTest = requete.value(0).toString();
            }

            mapRequete.insert("numeroTest", QString::number(lastNumeroTest.toInt() + 1));
        }
    }
    return mapRequete;
}

//****************************************
/*
 *
 */
QMap<QString, QString> MainWindow::remplirQMapInfoBilanCheville(QString typeRequete){

    QMap<QString, QString> mapRequete;
    QSqlQuery requete;

    QStringList listeColonnes = recupererListeColonnesTable("infosBilanCheville");

    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("doubleSpinBox_c")){
            QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox*>(w);
            double valeurCourante = dSpinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante,'f',1));
                    break;
                }
            }
        }
        else if(w->objectName().contains("spinBox_c")){
            QSpinBox *spinBox = dynamic_cast<QSpinBox*>(w);
            int valeurCourante = spinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante));
                    break;
                }
            }
        }
        else if(w->objectName().contains("comboBox_c")){
            QComboBox *comboBox = dynamic_cast<QComboBox*>(w);
            QString texteCourant = comboBox->currentText();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, "'" + texteCourant + "'");
                    break;
                }
            }
        }
        else if(w->objectName().contains("checkBox_c")){
            QCheckBox *checkbox = dynamic_cast<QCheckBox*>(w);
            QString texteCourant = checkbox->text();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    if(checkbox->isChecked())
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";1'");
                    else
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";0'");
                    break;
                }
            }
        }
        else if(w->objectName().contains("radioButton_c")){
            QRadioButton *radio = dynamic_cast<QRadioButton*>(w);
            QString texteCourant = radio->text();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    if(radio->isChecked())
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";1'");
                    else
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";0'");
                    break;
                }
            }
        }
    }

    QString texteRequete;

    // On recherche l idPatient a inserer
    QString idPatient;
    texteRequete = "SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").first() +
                   "%' and prenom LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").last() + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }
    while (requete.next()) {
        idPatient = requete.value(0).toString();
    }
    mapRequete.insert("idPatient", idPatient);

    // On ajoute la date du Bilan
    mapRequete.insert("dateBilan", "'" + QDate::currentDate().toString("dd/MM/yyyy") + "'");

    // Si on effectue une requete INSERT
    if(typeRequete == "insert"){

        // On recherche l idTypeBilan a inserer
        QString idTypeBilan;
        texteRequete = "SELECT idTypeBilan FROM TypeBilan WHERE  libelle='" + ui->comboBox_type_Bilan->currentText() +"'";

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            idTypeBilan = requete.value(0).toString();
        }
        mapRequete.insert("idTypeBilan", idTypeBilan);

        // On recherche le numero du bilan a inserer
        QString lastNumeroTest;

        texteRequete = "SELECT (EXISTS (SELECT idPatient FROM infosBilanCheville WHERE idPatient=" + idPatient + "))";
        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            lastNumeroTest = requete.value(0).toString();
        }

        if(lastNumeroTest == "0"){
            mapRequete.insert("numeroTest", "1");
        }
        else{
            texteRequete = "SELECT MAX(numeroTest) FROM infosBilanCheville WHERE idPatient=" + idPatient;

            if(!requete.exec(texteRequete)){
                ecrireLog("Requete impossible : " + texteRequete);
            }
            while (requete.next()) {
                lastNumeroTest = requete.value(0).toString();
            }

            mapRequete.insert("numeroTest", QString::number(lastNumeroTest.toInt() + 1));
        }
    }
    return mapRequete;
}

//****************************************
/*
 *
 */
QMap<QString, QString> MainWindow::remplirQMapInfoBilanBpc(QString typeRequete){

    QMap<QString, QString> mapRequete;
    QSqlQuery requete;

    QStringList listeColonnes = recupererListeColonnesTable("infosBilanCourse");

    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("doubleSpinBox_bpc_")){
            QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox*>(w);
            double valeurCourante = dSpinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante,'f',1));
                    break;
                }
            }
        }
        else if(w->objectName().contains("spinBox_bpc_")){
            QSpinBox *spinBox = dynamic_cast<QSpinBox*>(w);
            int valeurCourante = spinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante));
                    break;
                }
            }
        }
    }

    // texte Rachis
    mapRequete.insert("texteRachis", "'" + ui->lineEdit_bpc_textRachis->text() + "'");

    QString texteRequete;

    // On recherche l idPatient a inserer
    QString idPatient;
    texteRequete = "SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").first() +
                   "%' and prenom LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").last() + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }
    while (requete.next()) {
        idPatient = requete.value(0).toString();
    }
    mapRequete.insert("idPatient", idPatient);

    // On ajoute la date du Bilan
    mapRequete.insert("dateBilan", "'" + QDate::currentDate().toString("dd/MM/yyyy") + "'");

    // Si on effectue une requete INSERT
    if(typeRequete == "insert"){

        // On recherche l idTypeBilan a inserer
        QString idTypeBilan;
        texteRequete = "SELECT idTypeBilan FROM TypeBilan WHERE  libelle='" + ui->comboBox_type_Bilan->currentText() +"'";

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            idTypeBilan = requete.value(0).toString();
        }
        mapRequete.insert("idTypeBilan", idTypeBilan);

        // On recherche le numero du bilan a inserer
        QString lastNumeroTest;

        texteRequete = "SELECT (EXISTS (SELECT idPatient FROM infosBilanCourse WHERE idPatient=" + idPatient + "))";
        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            lastNumeroTest = requete.value(0).toString();
        }

        if(lastNumeroTest == "0"){
            mapRequete.insert("numeroTest", "1");
        }
        else{
            texteRequete = "SELECT MAX(numeroTest) FROM infosBilanCourse WHERE idPatient=" + idPatient;

            if(!requete.exec(texteRequete)){
                ecrireLog("Requete impossible : " + texteRequete);
            }
            while (requete.next()) {
                lastNumeroTest = requete.value(0).toString();
            }

            mapRequete.insert("numeroTest", QString::number(lastNumeroTest.toInt() + 1));
        }
    }
    return mapRequete;
}

//****************************************
/*
 * SETTINGS
 */
QMap<QString, QString> MainWindow::remplirQMapInfoBilanBpsc(QString typeRequete){

    QMap<QString, QString> mapRequete;
    QSqlQuery requete;

    QStringList listeColonnes = recupererListeColonnesTable("infosBilanSportCollectif");

    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("doubleSpinBox_bpsc_")){
            QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox*>(w);
            double valeurCourante = dSpinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante,'f',1));
                    break;
                }
            }
        }
        else if(w->objectName().contains("spinBox_bpsc_")){
            QSpinBox *spinBox = dynamic_cast<QSpinBox*>(w);
            int valeurCourante = spinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante));
                    break;
                }
            }
        }
        else if(w->objectName().contains("radioButton_bpsc_")){
            QRadioButton *radio = dynamic_cast<QRadioButton*>(w);
            QString texteCourant = radio->text();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    if(radio->isChecked())
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";1'");
                    else
                        mapRequete.insert(nomColonne, "'" + texteCourant + ";0'");
                    break;
                }
            }
        }
    }

    // texte Rachis
    mapRequete.insert("texteRachis", "'" + ui->lineEdit_bpsc_textRachis->text() + "'");

    QString texteRequete;

    // On recherche l idPatient a inserer
    QString idPatient;
    texteRequete = "SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").first() +
                   "%' and prenom LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").last() + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }
    while (requete.next()) {
        idPatient = requete.value(0).toString();
    }
    mapRequete.insert("idPatient", idPatient);

    // On ajoute la date du Bilan
    mapRequete.insert("dateBilan", "'" + QDate::currentDate().toString("dd/MM/yyyy") + "'");

    // Si on effectue une requete INSERT
    if(typeRequete == "insert"){

        // On recherche l idTypeBilan a inserer
        QString idTypeBilan;
        texteRequete = "SELECT idTypeBilan FROM TypeBilan WHERE  libelle='" + ui->comboBox_type_Bilan->currentText() +"'";

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            idTypeBilan = requete.value(0).toString();
        }
        mapRequete.insert("idTypeBilan", idTypeBilan);

        // On recherche le numero du bilan a inserer
        QString lastNumeroTest;

        texteRequete = "SELECT (EXISTS (SELECT idPatient FROM infosBilanSportCollectif WHERE idPatient=" + idPatient + "))";
        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            lastNumeroTest = requete.value(0).toString();
        }

        if(lastNumeroTest == "0"){
            mapRequete.insert("numeroTest", "1");
        }
        else{
            texteRequete = "SELECT MAX(numeroTest) FROM infosBilanSportCollectif WHERE idPatient=" + idPatient;

            if(!requete.exec(texteRequete)){
                ecrireLog("Requete impossible : " + texteRequete);
            }
            while (requete.next()) {
                lastNumeroTest = requete.value(0).toString();
            }

            mapRequete.insert("numeroTest", QString::number(lastNumeroTest.toInt() + 1));
        }
    }
    return mapRequete;
}

//****************************************
/*
 *
 */
QMap<QString, QString> MainWindow::remplirQMapInfoBilanBpf(QString typeRequete){

    QMap<QString, QString> mapRequete;
    QSqlQuery requete;

    QStringList listeColonnes = recupererListeColonnesTable("infosBilanSportCombat");

    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("doubleSpinBox_bpf")){
            QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox*>(w);
            double valeurCourante = dSpinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante,'f',1));
                    break;
                }
            }
        }
        else if(w->objectName().contains("spinBox_bpf_")){
            QSpinBox *spinBox = dynamic_cast<QSpinBox*>(w);
            int valeurCourante = spinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante));
                    break;
                }
            }
        }
        else if(w->objectName().contains("comboBox_bpf_")){
            QComboBox *comboBox = dynamic_cast<QComboBox*>(w);
            QString texteCourant = comboBox->currentText();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, "'" + texteCourant + "'");
                    break;
                }
            }
        }
    }

    // texte Rachis
    mapRequete.insert("texteRachis", "'" + ui->lineEdit_bpf_textRachis->text() + "'");

    QString texteRequete;

    // On recherche l idPatient a inserer
    QString idPatient;
    texteRequete = "SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").first() +
                   "%' and prenom LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").last() + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }
    while (requete.next()) {
        idPatient = requete.value(0).toString();
    }
    mapRequete.insert("idPatient", idPatient);

    // On ajoute la date du Bilan
    mapRequete.insert("dateBilan", "'" + QDate::currentDate().toString("dd/MM/yyyy") + "'");

    // Si on effectue une requete INSERT
    if(typeRequete == "insert"){

        // On recherche l idTypeBilan a inserer
        QString idTypeBilan;
        texteRequete = "SELECT idTypeBilan FROM TypeBilan WHERE  libelle='" + ui->comboBox_type_Bilan->currentText() +"'";

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            idTypeBilan = requete.value(0).toString();
        }
        mapRequete.insert("idTypeBilan", idTypeBilan);

        // On recherche le numero du bilan a inserer
        QString lastNumeroTest;

        texteRequete = "SELECT (EXISTS (SELECT idPatient FROM infosBilanSportCombat WHERE idPatient=" + idPatient + "))";
        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            lastNumeroTest = requete.value(0).toString();
        }

        if(lastNumeroTest == "0"){
            mapRequete.insert("numeroTest", "1");
        }
        else{
            texteRequete = "SELECT MAX(numeroTest) FROM infosBilanSportCombat WHERE idPatient=" + idPatient;

            if(!requete.exec(texteRequete)){
                ecrireLog("Requete impossible : " + texteRequete);
            }
            while (requete.next()) {
                lastNumeroTest = requete.value(0).toString();
            }

            mapRequete.insert("numeroTest", QString::number(lastNumeroTest.toInt() + 1));
        }
    }
    return mapRequete;
}

//****************************************
/*
 *
 */
QMap<QString, QString> MainWindow::remplirQMapInfoBilanBpcf(QString typeRequete){

    QMap<QString, QString> mapRequete;
    QSqlQuery requete;

    QStringList listeColonnes = recupererListeColonnesTable("infosBilanCrossfit");

    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("doubleSpinBox_bpcf")){
            QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox*>(w);
            double valeurCourante = dSpinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante,'f',1));
                    break;
                }
            }
        }
        else if(w->objectName().contains("spinBox_bpcf")){
            QSpinBox *spinBox = dynamic_cast<QSpinBox*>(w);
            int valeurCourante = spinBox->value();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, QString::number(valeurCourante));
                    break;
                }
            }
        }
        else if(w->objectName().contains("comboBox_bpcf")){
            QComboBox *comboBox = dynamic_cast<QComboBox*>(w);
            QString texteCourant = comboBox->currentText();

            foreach (QString nomColonne, listeColonnes) {
                if(nomColonne == w->objectName().split("_").last()){
                    mapRequete.insert(nomColonne, "'" + texteCourant + "'");
                    break;
                }
            }
        }
    }

    // texte Rachis
    mapRequete.insert("texteRachis", "'" + ui->lineEdit_bpcf_textRachis->text() + "'");

    QString texteRequete;

    // On recherche l idPatient a inserer
    QString idPatient;
    texteRequete = "SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").first() +
                   "%' and prenom LIKE '%" + ui->comboBox_patient_courant->currentText().split(" ").last() + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }
    while (requete.next()) {
        idPatient = requete.value(0).toString();
    }
    mapRequete.insert("idPatient", idPatient);

    // On ajoute la date du Bilan
    mapRequete.insert("dateBilan", "'" + QDate::currentDate().toString("dd/MM/yyyy") + "'");

    // Si on effectue une requete INSERT
    if(typeRequete == "insert"){

        // On recherche l idTypeBilan a inserer
        QString idTypeBilan;
        texteRequete = "SELECT idTypeBilan FROM TypeBilan WHERE  libelle='" + ui->comboBox_type_Bilan->currentText() +"'";

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            idTypeBilan = requete.value(0).toString();
        }
        mapRequete.insert("idTypeBilan", idTypeBilan);

        // On recherche le numero du bilan a inserer
        QString lastNumeroTest;

        texteRequete = "SELECT (EXISTS (SELECT idPatient FROM infosBilanCrossfit WHERE idPatient=" + idPatient + "))";
        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            lastNumeroTest = requete.value(0).toString();
        }

        if(lastNumeroTest == "0"){
            mapRequete.insert("numeroTest", "1");
        }
        else{
            texteRequete = "SELECT MAX(numeroTest) FROM infosBilanCrossfit WHERE idPatient=" + idPatient;

            if(!requete.exec(texteRequete)){
                ecrireLog("Requete impossible : " + texteRequete);
            }
            while (requete.next()) {
                lastNumeroTest = requete.value(0).toString();
            }

            mapRequete.insert("numeroTest", QString::number(lastNumeroTest.toInt() + 1));
        }
    }
    return mapRequete;
}

//****************************************
/*
 *
 */
void MainWindow::viderInfosBilan(){

    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("spinBox")){
            QSpinBox *spinBox = dynamic_cast<QSpinBox*>(w);
            spinBox->setValue(0);
        }

        if(w->objectName().contains("doubleSpin")){
            QDoubleSpinBox *dSpinBox = dynamic_cast<QDoubleSpinBox*>(w);
            dSpinBox->setValue(0);
        }

        if(w->objectName().contains("comboBox_test")){
            QComboBox *comboBox = dynamic_cast<QComboBox*>(w);
            comboBox->setCurrentIndex(0);
        }

        if(w->objectName().contains("radioButton")){
            QRadioButton *radio = dynamic_cast<QRadioButton*>(w);
            radio->setChecked(false);
        }

        if(w->objectName().contains("checkBox")){
            QCheckBox *check = dynamic_cast<QCheckBox*>(w);
            check->setChecked(false);
        }

        if(w->objectName().contains("textEdit")){
            QTextEdit *text = dynamic_cast<QTextEdit*>(w);
            text->setText("");
        }

        if(w->objectName().contains("lineEdit")){
            QLineEdit *line = dynamic_cast<QLineEdit*>(w);
            line->setText("");
        }
    }
}

//****************************************
/*
 *
 */
void MainWindow::viderInfosRapport(){

    //Vider les checkBox
    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("check")){
            QCheckBox *check = dynamic_cast<QCheckBox*>(w);
            check->setChecked(false);
        }

        if(w->objectName().contains("textEdit")){
            QTextEdit *text = dynamic_cast<QTextEdit*>(w);
            text->setText("");
        }

        if(w->objectName().contains("lineEdit")){
            QLineEdit *line = dynamic_cast<QLineEdit*>(w);
            line->setText("");
        }
    }
}


//****************************************
/*
 * QPair<couleur, calculAsymetrie>
 */
QPair<QString, QString> MainWindow::getPaireAsymetrie(bool inversion, double nonOpere, double opere){

    //QPair<couleur, calculAsymetrie>
    QPair<QString, QString> paireRes;

    if (nonOpere == 0 || opere == 0 ){
        paireRes.first = "#fdfefe";
        paireRes.second = "erreur";
        return paireRes;
    }

    double asymetrie =  qRound( ((opere - nonOpere) / nonOpere ) * 100);

    paireRes.second = QString::number(asymetrie) + "%";

    if(inversion){

        if(asymetrie < 10)
            paireRes.first = "#169d53";
        else if(asymetrie >= 10 && asymetrie < 25)
            paireRes.first = "#ff9929";
        else if(asymetrie > 25)
            paireRes.first = "#9f3f36";
    }
    else{
        if(asymetrie < -25)
            paireRes.first = "#9f3f36";
        else if(asymetrie >= -25 && asymetrie < -10)
            paireRes.first = "#ff9929";
        else if(asymetrie >= -10)
            paireRes.first = "#169d53";
    }


    return paireRes;
}


//****************************************
/*
 * QPair<couleur, calculAsymetrie>
 */
QPair<QString, QString> MainWindow::getPaireRatio(double numerateur, double denominateur, QString typeRatio){

    //QPair<couleur, calculAsymetrie>
    QPair<QString, QString> paireRes;

    if (denominateur == 0 ){
        paireRes.first = "#fdfefe";
        paireRes.second = "erreur";
        return paireRes;
    }

    double ratio =  numerateur / denominateur ;
    paireRes.second = QString::number(ratio,'f',2);

    if(typeRatio == "ratioIJ"){
        paireRes.first = getCouleurRatioIschio(ratio);
    }
    else if(typeRatio == "ratioAA"){
        paireRes.first = getCouleurRatioAbd(ratio);
    }
    else if(typeRatio == "rsi"){
        paireRes.first = getCouleurRsi(ratio);
    }
    else if(typeRatio == "RERIR1"){
        paireRes.first = getCouleurReRiR1(ratio);
    }
    else if(typeRatio == "RERIR2"){
        paireRes.first = getCouleurReRiR2(ratio);
    }
    else if(typeRatio == "ratioEI"){
        paireRes.first = getCouleurEI(ratio);
    }
    return paireRes;

}

//****************************************
QString MainWindow::getCouleurRatioIschio(double ratio){

    if(ratio < 0.45)
        return "#9f3f36";
    else if(ratio >= 0.45 && ratio < 0.55)
        return "#ff9929";
    else if(ratio >= 0.55 && ratio < 0.65)
        return "#169d53";
    else if(ratio >= 0.65 && ratio <= 0.75)
        return "#ff9929";
    else
        return "#9f3f36";
}

//****************************************
QString MainWindow::getCouleurRatioAbd(double ratio){

    if(ratio < 0.85)
        return "#9f3f36";
    else if(ratio >= 0.85 && ratio < 0.95)
        return "#ff9929";
    else if(ratio >= 0.95 && ratio < 1.05)
        return "#169d53";
    else if(ratio >= 1.05 && ratio <= 1.15)
        return "#ff9929";
    else
        return "#9f3f36";
}

//****************************************
QString MainWindow::getCouleurBkfo(double bkfo){

    if(bkfo <= 17)
        return "#169d53";
    else if(bkfo > 17 && bkfo <= 25)
        return "#ff9929";
    else
        return "#9f3f36";
}

//****************************************
QString MainWindow::getCouleurScoreBS(double score, int poids){

    if (score < 1.2 * poids)
        return "#9f3f36";  // red
    else if (score < 1.5 * poids)
        return "#ff9929";  // orange
    else
        return "#169d53";  // green
}

//****************************************
/*
 * QPair<couleur, calculAsymetrie>
 */
QPair<QString, QString> MainWindow::getPaireRsiModifie(double numerateur, double denominateur, QString sexe){

    //QPair<couleur, calculAsymetrie>
    QPair<QString, QString> paireRes;

    if (denominateur == 0 ){
        paireRes.first = "#fdfefe";
        paireRes.second = "erreur";
        return paireRes;
    }

    double ratio =  numerateur / denominateur ;
    paireRes.second = QString::number(ratio,'f',2);

    paireRes.first = getCouleurRsiModifie(ratio, sexe);

    return paireRes;
}


//****************************************
QString MainWindow::getCouleurRsiModifie(double rsi, QString sexe){

    if(sexe == "F"){
        if(rsi < 0.3)
            return "#9f3f36";
        else if(rsi >= 0.3 && rsi <= 0.43)
            return "#ff9929";
        else
            return "#169d53";
    }
    else if(sexe == "M"){
        if(rsi < 0.4)
            return "#9f3f36";
        else if(rsi >= 0.4 && rsi <= 0.55)
            return "#ff9929";
        else
            return "#169d53";
    }
    else{
        return "ERROR";
    }
}

//****************************************
QString MainWindow::getCouleurRsi(double rsi){

    if(rsi < 1.5)
        return "#9f3f36";
    else if(rsi >= 1.5 && rsi < 2.0)
        return "#dc7633";
    else if(rsi >= 2.0 && rsi < 2.5)
        return "#ff9929";
    else if(rsi >= 2.5 && rsi < 3.0)
        return "#f4d03f";
    else if(rsi >= 3.0)
        return "#169d53";
    else
        return "#fdfefe";

    return "#000000"; // ou une couleur par défaut, ou une gestion d'erreur
}

//****************************************
QString MainWindow::getCouleurReRiR1(double ratio){

    if(ratio < 0.55)
        return "#9f3f36";
    else if(ratio >= 0.55 && ratio < 0.65)
        return "#ff9929";
    else if(ratio >= 0.65 && ratio < 0.75)
        return "#169d53";
    else if(ratio >= 0.75 && ratio < 0.85)
        return "#ff9929";
    else if(ratio >= 0.85)
        return "#9f3f36";

    return "#000000"; // ou une couleur par défaut, ou une gestion d'erreur
}

//****************************************
QString MainWindow::getCouleurReRiR2(double ratio){

    if(ratio < 0.45)
        return "#9f3f36";
    else if(ratio >= 0.45 && ratio < 0.55)
        return "#ff9929";
    else if(ratio >= 0.55 && ratio < 0.65)
        return "#169d53";
    else if(ratio >= 0.65 && ratio < 0.75)
        return "#ff9929";
    else if(ratio >= 0.75)
        return "#9f3f36";

    return "#000000"; // ou une couleur par défaut, ou une gestion d'erreur
}

//****************************************
QString MainWindow::getCouleurEI(double ratio){

    if(ratio < 0.75)
        return "#9f3f36";
    else if(ratio >= 0.75 && ratio < 0.9)
        return "#ff9929";
    else if(ratio >= 0.9 && ratio <= 1.10)
        return "#169d53";
    else if(ratio > 1.10 && ratio <= 1.25)
        return "#ff9929";
    else if(ratio > 1.25)
        return "#9f3f36";

    return "#000000"; // ou une couleur par défaut, ou une gestion d'erreur
}


//****************************************
QString MainWindow::getCouleurIllinois(double value, QString sexe){

    if(sexe == "F"){

        if(value < 17.9)
            return "#169d53";
        else if( value >= 17.9 && value < 21.7)
            return "#ff9929";
        else
            return "#9f3f36";
    }
    else if(sexe == "M"){

        if(value < 16.1)
            return "#169d53";
        else if( value >= 16.1 && value < 18.1)
            return "#ff9929";
        else
            return "#9f3f36";
    }

    return "#000000"; // ou une couleur par défaut, ou une gestion d'erreur
}

//****************************************
QString MainWindow::getCouleurAgility(double value, QString sexe){

    if(sexe == "F"){

        if(value < 5)
            return "#169d53";
        else if( value >= 5 && value < 5.5)
            return "#ff9929";
        else
            return "#9f3f36";
    }
    else if(sexe == "M"){
        if(value < 4.5)
            return "#169d53";
        else if( value >= 4.5 && value < 5)
            return "#ff9929";
        else
            return "#9f3f36";
    }

    return "#000000"; // ou une couleur par défaut, ou une gestion d'erreur
}

//****************************************
QPair<QString, QString> MainWindow::calculerProgression(QString unite, double valeurAvant, double valeurApres){

    // Paire <QString valeurProg, QString couleur>
    QPair<QString, QString> paireRes;

    double prog = valeurApres - valeurAvant;

    if (prog > 0 ) {
        paireRes.second = "#1e8449";

        if(unite == "N" || unite == "")
            paireRes.first =  "(&uarr;" + QString::number(prog) + unite + ")";
        else if(unite != "cm")
            paireRes.first =  "(&uarr;" + QString::number(prog,'f',1) + unite + ")";
        else
            paireRes.first =  "<br>(&uarr;" + QString::number(prog) + unite + ")</br>";
    }
    else if (prog < 0 ) {
        paireRes.second = "#e74c3c";

        if(unite == "N" || unite == "")
            paireRes.first = "(&darr;" + QString::number(prog) +  unite + ")";
        else if(unite != "cm")
            paireRes.first = "(&darr;" + QString::number(prog,'f',1) +  unite + ")";
        else
            paireRes.first = "<br>(&darr;" + QString::number(prog) +  unite + ")</br>";
    }
    else{
        paireRes.second = "#fdfefe";
        paireRes.first = QString::number(prog) ;
    }

    return paireRes;
}

//****************************************
QPair<QString, QString> MainWindow::getProgressionPourcentage(bool inversion, double valeurAvant, double valeurApres){

    // Paire <QString valeurProg, QString couleur>
    QPair<QString, QString> paireRes;

    int prog = qRound(((valeurApres - valeurAvant) / valeurAvant ) * 100);

     if( valeurAvant == 0){
        paireRes.first =  "";
        paireRes.second = "#fdfefe";

        return paireRes;
     }

    if( prog < 0){

         paireRes.first =  "<br>(&darr;" + QString::number(prog) +"%)</br>";

        if(inversion){
            paireRes.second = "#27ae60";
        }
        else{
            paireRes.second = "#e74c3c";
        }
    }
    else if(prog == 0 ){
        paireRes.second = "";
        paireRes.first = "";
    }
    else if(prog > 0 ){

        paireRes.first =  "<br>(&uarr;" + QString::number(prog) +"%)</br>";

        if(inversion){
            paireRes.second = "#e74c3c";
        }
        else{
            paireRes.second = "#27ae60";
        }
    }

    return paireRes;
}

//****************************************
QString MainWindow::getCouleurPourcentageForce(double forceSain, double forceNO){

    QString res = "#169d53"; // Vert par défaut

        // Si l’un dépasse 60 % ou l’autre est < 40 % → Rouge
        if (forceSain > 60 || forceNO > 60 ||
            forceSain < 40 || forceNO < 40) {
            res = "#9f3f36"; // Rouge
        }
        // Sinon si l’un dépasse 55 % ou est < 45 % → Orange
        else if ((forceSain > 55 || forceSain < 45) ||
                 (forceNO > 55 || forceNO < 45)) {
            res = "#ff9929"; // Orange
        }
        // Sinon → Vert
        else {
            res = "#169d53"; // Vert
        }

        return res;
}

//****************************************
QPair<QString, QString> MainWindow::getPaireKstart(double kStart){

    QPair<QString, QString> res;

    if(kStart < 50){
        res.first = "#9f3f36";
        res.second = " Pas de reprise de sport";
    }
    else if(kStart >= 50 && kStart < 65){
        res.first = "#ff9929";
        res.second = " Reprise de sport seulement dans l'axe";
    }
    else if(kStart >= 65 && kStart < 80){
        res.first = "#ff9929";
        res.second = " Reprise de sport multidirectionnel, mais sans contacts";
    }
    else {
        res.first = "#169d53";
        res.second = " Reprise de sport multidirectionnel avec contact";
    }

    return res;
}

//****************************************
QPair<QString, QString> MainWindow::getPaireSstart(double sStart){

    QPair<QString, QString> res;

    if(sStart < 60){
        res.first = "#9f3f36";
        res.second = " Pas de reprise de sport";
    }
    else if(sStart >= 60 && sStart < 88){
        res.first = "#ff9929";
        res.second = " Reprise de sport seulement dans l'axe";
    }
    else {
        res.first = "#169d53";
        res.second = " Reprise de sport multidirectionnel avec contact";
    }

    return res;
}

//****************************************
QString MainWindow::getCouleurACLRsi(double aclRsi){

    if(aclRsi < 56)
        return "#9f3f36";
    else if(aclRsi >= 56 && aclRsi <= 72)
        return "#ff9929";
    else
        return "#169d53";
}

QString MainWindow::getCouleurSiRsi(double aclRsi){

    if(aclRsi < 60)
        return "#9f3f36";
    else if(aclRsi >= 60 && aclRsi <= 88)
        return "#ff9929";
    else
        return "#169d53";
}

//****************************************
/*
 * QPair<couleur, calculLSI>
 */
QPair<QString, QString> MainWindow::getPaireLSI(double dsl, double dil, double dm, double longueurBras){

    //QPair<couleur, calculLSI>
    QPair<QString, QString> paireRes;

    double numerateur = dsl + dil + dm;
    double denominateur = 3 * longueurBras;

    if (denominateur == 0 ){
        paireRes.first = "#fdfefe";
        paireRes.second = "erreur";
        return paireRes;
    }

    double pourcentage =  (numerateur*100)  / denominateur ;
    paireRes.second = QString::number(pourcentage,'f',2);

    paireRes.first = getCouleurPourcentageLSI(pourcentage);

    return paireRes;
}

//****************************************
QString MainWindow::getCouleurPourcentageLSI(double pourcentage){

    if(pourcentage < 80)
        return "#9f3f36";
    else if(pourcentage >= 80 && pourcentage <= 90)
        return "#ff9929";
    else
        return "#169d53";
}


//****************************************
QString MainWindow::getCouleurCKCuest(double nbTouches){

    if(nbTouches < 18){
        return "#9f3f36";
    }
    else if(nbTouches >= 18 && nbTouches <= 25){
        return "#ff9929";
    }
    else{
        return "#169d53";
    }
}

//****************************************
QString MainWindow::getCouleurURLT(double nbRepetitions){

    if(nbRepetitions < 10)
        return "#9f3f36";
    else if(nbRepetitions >= 10 && nbRepetitions <= 15)
        return "#ff9929";
    else
        return "#169d53";
}

//****************************************
QString MainWindow::getCouleurSautsRepetesRsi(double rsi){

    if(rsi < 1.5)
        return "#9f3f36";
    else if(rsi >= 1.5 && rsi <= 2.5)
        return "#ff9929";
    else
        return "#169d53";
}

//****************************************
QString MainWindow::ecrireLigneTableau(QStringList listeValeursLigne){
    QString ligneRes;


    return ligneRes;
}


//****************************************
QString MainWindow::ecrireAmplitudesGenou(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){
    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "flexionO" <<  "extensionO";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.size();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits== 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Amplitudes articulaires" <<  "Membre sain";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color:white; color:#002e40; border:1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row - Flexions
    texteTableauCourant = texteTableauCourant + "</tr>"
                                "<tr>"
                                "<th scope=\"row\">Flexion (°)</th>"
                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionNO") + "</td>"
                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionO") + "</td>";
    if(tailleListeFaits > 1){

        // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);


        if(tailleListeFaits == 3){
            //On ecrit Tavant dernier
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionO") + "</td>";
        }

        // on ecrit TLast plus progression
        QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("flexionO").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionO")
                              + texteEvolution + "</td>" ;
    }

    // 2e row - Extensions
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Extension (°)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("extensionNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("extensionO") + "</td>";
    if(tailleListeFaits > 1){

        // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){
            //On ecrit Tavant dernier
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("extensionO") + "</td>";
        }

        // on ecrit TLast plus progression
        QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("extensionO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("extensionO").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("extensionO")
                              + texteEvolution + "</td>" ;
    }

    texteTableauCourant.append("</tr></table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireAmplitudesHanche(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){
    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;

    for (int i = 0; i < listePairesRapport.count(); ++i) {
        listeTestFaits.append(QString::number(i+1));
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table style=\"margin-bottom:1px;\"><tr>");

    listeColonnesTab << "Amplitudes articulaires";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
    }
    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "flexion";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Flexion (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("flexionNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("flexionO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionO")
                                  + texteEvolution + "</td>" ;
        }
        else if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("flexionNO") + "</td>" ;

            // Membre sain T3
            QPair<QString, QString> prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("flexionNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, "3").value("flexionNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("flexionNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré T1
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionO") + "</td>";

            //Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("flexionO") + "</td>";

            //Membre opéré T3"
            prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("flexionO").toDouble(),
                                       getMapListeRapport(listePairesRapport, "3").value("flexionO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("flexionO")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extension";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("extensionNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("extensionO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("extensionNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("extensionNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("extensionNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("extensionO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("extensionO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("extensionO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("extensionO")
                                  + texteEvolution + "</td>" ;
        }
        else if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("extensionNO") + "</td>" ;

            // Membre sain T3
            QPair<QString, QString> prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("extensionNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, "3").value("extensionNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("extensionNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré T1
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("extensionO") + "</td>";

            //Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("extensionO") + "</td>";

            //Membre opéré T3"
            prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("extensionO").toDouble(),
                                       getMapListeRapport(listePairesRapport, "3").value("extensionO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("extensionO")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "abduction";
    // 3e row - Extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Abduction (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("abductionNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("abductionO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("abductionNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("abductionNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("abductionNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("abductionO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("abductionO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("abductionO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("abductionO")
                                  + texteEvolution + "</td>" ;
        }
        else if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("abductionNO") + "</td>" ;

            // Membre sain T3
            QPair<QString, QString> prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("abductionNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, "3").value("abductionNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("abductionNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré T1
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("abductionO") + "</td>";

            //Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("abductionO") + "</td>";

            //Membre opéré T3"
            prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("abductionO").toDouble(),
                                       getMapListeRapport(listePairesRapport, "3").value("abductionO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("abductionO")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "adduction";
    // 4e row - Adduction
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Abduction (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("adductionNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("adductionO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("adductionNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("adductionNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("adductionNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("adductionO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("adductionO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("adductionO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("adductionO")
                                  + texteEvolution + "</td>" ;
        }
        else if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("adductionNO") + "</td>" ;

            // Membre sain T3
            QPair<QString, QString> prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("adductionNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, "3").value("adductionNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("adductionNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré T1
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("adductionO") + "</td>";

            //Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("adductionO") + "</td>";

            //Membre opéré T3"
            prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("adductionO").toDouble(),
                                       getMapListeRapport(listePairesRapport, "3").value("adductionO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("adductionO")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationInterne";
    // 5e row - Rotation Interne
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Interne (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationInterneNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationInterneO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("rotationInterneNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("rotationInterneNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rotationInterneNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationInterneO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("rotationInterneO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("rotationInterneO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rotationInterneO")
                                  + texteEvolution + "</td>" ;
        }
        else if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("rotationInterneNO") + "</td>" ;

            // Membre sain T3
            QPair<QString, QString> prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("rotationInterneNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, "3").value("rotationInterneNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("rotationInterneNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré T1
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("rotationInterneO") + "</td>";

            //Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("rotationInterneO") + "</td>";

            //Membre opéré T3"
            prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("rotationInterneO").toDouble(),
                                       getMapListeRapport(listePairesRapport, "3").value("rotationInterneO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("rotationInterneO")
                                  + texteEvolution + "</td>" ;
        }
    }


    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationExterne";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Externe (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationExterneNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationExterneO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("rotationExterneNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationExterneO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("rotationExterneO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneO")
                                  + texteEvolution + "</td>" ;
        }
        else if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("rotationExterneNO") + "</td>" ;

            // Membre sain T3
            QPair<QString, QString> prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("rotationExterneNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, "3").value("rotationExterneNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("rotationExterneNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré T1
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("rotationExterneO") + "</td>";

            //Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("rotationExterneO") + "</td>";

            //Membre opéré T3"
            prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("rotationExterneO").toDouble(),
                                       getMapListeRapport(listePairesRapport, "3").value("rotationExterneO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("rotationExterneO")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "bkfo";
    // 7e row - BKFO
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Bent Knee Fall Out - BKFO* (cm)</th>";

        QString valeurCourante = getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("bkfoNO");
        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + valeurCourante + "</td>";

        if(tailleListeFaits == 1){
            valeurCourante = getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("bkfoO");
            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + valeurCourante + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            valeurCourante = getMapListeRapport(listePairesRapport, dernierTest).value("bkfoNO");
            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + valeurCourante + "</td>";

            //Membre opéré Tfirst
            valeurCourante = getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("bkfoO");
            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + valeurCourante + "</td>";

            // Membre opéré Tlast
            valeurCourante = getMapListeRapport(listePairesRapport,dernierTest).value("bkfoO");
            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + valeurCourante + "</td>";
        }
        else if(tailleListeFaits == 3){

            //Membre sain T2
            valeurCourante = getMapListeRapport(listePairesRapport, "2").value("bkfoNO");
            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + valeurCourante + "</td>";

            // Membre sain T3
            valeurCourante = getMapListeRapport(listePairesRapport, "3").value("bkfoNO");
            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + valeurCourante + "</td>";

            //Membre opéré T1
            valeurCourante = getMapListeRapport(listePairesRapport, "1").value("bkfoO");
            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + valeurCourante + "</td>";

            //Membre opéré T2
            valeurCourante = getMapListeRapport(listePairesRapport, "2").value("bkfoO");
            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + valeurCourante + "</td>";

            //Membre opéré T3
            valeurCourante = getMapListeRapport(listePairesRapport, "3").value("bkfoO");
            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + valeurCourante + "</td>";
        }
    }

    texteTableauCourant.append("</tr></table>");

    texteTableauCourant.append("<p style=\"margin-bottom:35px; text-align: justify;\">* BKFO = distance entre la tête du peronné et le sol "
                               "dans une position de flexion, abduction et rotation externe des hanches  avec les deux voûtes plantaires collées"
                               " ensembles proche des fesses, distance optimale inf. 17 cm</p>");

    texteTableauCourant.append("<p style=\"margin-bottom:50px;\"><br><br></p>");


    return texteTableauCourant;
}


//****************************************
QString MainWindow::ecrireAmplitudesCheville(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){
    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;

    for (int i = 0; i < listePairesRapport.count(); ++i) {
        listeTestFaits.append(QString::number(i+1));
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Amplitudes articulaires";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
    }
    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionPlantaire";
    // 1ere row - Flexion plantaire
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Flexion Plantaire (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionPlantaireNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionPlantaireO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionPlantaireNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("flexionPlantaireNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionPlantaireNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionPlantaireO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionPlantaireO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("flexionPlantaireO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionPlantaireO")
                                  + texteEvolution + "</td>" ;
        }
        else if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("flexionPlantaireNO") + "</td>" ;

            // Membre sain T3
            QPair<QString, QString> prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("flexionPlantaireNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, "3").value("flexionPlantaireNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("flexionPlantaireNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré T1
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionPlantaireO") + "</td>";

            //Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("flexionPlantaireO") + "</td>";

            //Membre opéré T3"
            prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("flexionPlantaireO").toDouble(),
                                       getMapListeRapport(listePairesRapport, "3").value("flexionPlantaireO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("flexionPlantaireO")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionDorsaleWBL";
    // 3e row - flexion Dorsale
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Flexion Dorsale - Test WBLT (cm)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionDorsaleWBLNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionDorsaleWBLO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionDorsaleWBLNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("flexionDorsaleWBLNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionDorsaleWBLNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionDorsaleWBLO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionDorsaleWBLO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("flexionDorsaleWBLO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionDorsaleWBLO")
                                  + texteEvolution + "</td>" ;
        }
        else if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("flexionDorsaleWBLNO") + "</td>" ;

            // Membre sain T3
            QPair<QString, QString> prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("flexionDorsaleWBLNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, "3").value("flexionDorsaleWBLNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("flexionDorsaleWBLNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré T1
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionDorsaleWBLO") + "</td>";

            //Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("flexionDorsaleWBLO") + "</td>";

            //Membre opéré T3"
            prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("flexionDorsaleWBLO").toDouble(),
                                       getMapListeRapport(listePairesRapport, "3").value("flexionDorsaleWBLO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("flexionDorsaleWBLO")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionDorsaleWBL";
    // 2e row - flexionDorsaleWBL
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Flexion Dorsale (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionDorsaleWBLNODegre") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionDorsaleWBLODegre") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionDorsaleWBLNODegre").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("flexionDorsaleWBLNODegre").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionDorsaleWBLNODegre")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("flexionDorsaleWBLODegre") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionDorsaleWBLODegre").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("flexionDorsaleWBLODegre").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionDorsaleWBLODegre")
                                  + texteEvolution + "</td>" ;
        }
        else if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("flexionDorsaleWBLNODegre") + "</td>" ;

            // Membre sain T3
            QPair<QString, QString> prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("flexionDorsaleWBLNODegre").toDouble(),
                                                               getMapListeRapport(listePairesRapport, "3").value("flexionDorsaleWBLNODegre").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("flexionDorsaleWBLNODegre")
                                  + texteEvolution + "</td>" ;

            //Membre opéré T1
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionDorsaleWBLODegre") + "</td>";

            //Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("flexionDorsaleWBLODegre") + "</td>";

            //Membre opéré T3"
            prog = calculerProgression("°",getMapListeRapport(listePairesRapport, "2").value("flexionDorsaleWBLODegre").toDouble(),
                                       getMapListeRapport(listePairesRapport, "3").value("flexionDorsaleWBLODegre").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("flexionDorsaleWBLODegre")
                                  + texteEvolution + "</td>" ;
        }
    }

    texteTableauCourant.append("</tr></table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireAmplitudesBpf(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;


    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table style=\"margin-bottom:1px;\">");

    texteTableauCourant= texteTableauCourant +  "<tr>"
                                                "<th style=\"background-color: white; color:#002e40;\">Amplitudes articulaires</th>"
                                                "<th scope=\"col\"style=\"background-color:#c0c0c0; color:#002e40;border:1px solid #023448\"></th>"
                                                "<th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">Membre G</th>"
                                                "<th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">Membre D</th>"
                                                "</tr>";

    //////////////// Cheville ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionPlantaire";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "<tr>"
                                                    "<td rowspan=\"3\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Cheville</td>"
                                                    "<th scope=\"row\">Flexion Plantaire (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionPlantaireG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionPlantaireD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionDorsaleWBL";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionDorsaleWBL";
    // 3e row - Extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Abduction (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLGDegre") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLDDegre") + "</td>";
    }

    //////////////// GENOU ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionGenou";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<td rowspan=\"2\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Genou</td>"
                                                    "<th scope=\"row\">Flexion (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionGenouG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionGenouD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extensionGenou";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionGenouG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionGenouD") + "</td>";
    }

    //////////////// HANCHE ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionHanche";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<td rowspan=\"7\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Hanche</td>"
                                                    "<th scope=\"row\">Flexion (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionHancheG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionHancheD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extensionHanche";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionHancheG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionHancheD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "abduction";
    // 3e row - Extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Abduction (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("abductionG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("abductionD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "adduction";
    // 4e row - Adduction
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Abduction (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("adductionG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("adductionD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationInterne";
    // 5e row - Rotation Interne
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Interne (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationExterne";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Externe (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "bkfo";
    // 7e row - BKFO
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Bent Knee Fall Out - BKFO* (cm)</th>";

        QString valeurCourante = getMapListeRapport(listePairesRapport,"1").value("bkfoG");
        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + valeurCourante + "</td>";

        valeurCourante = getMapListeRapport(listePairesRapport,"1").value("bkfoD");
        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + valeurCourante + "</td>";
    }

    //////////////// EPAULE ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "elevationAnterieure";
    // 1ere row - elevationAnterieure
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "<tr>"
                                                    "<td rowspan=\"8\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Epaule</td>"
                                                    "<th scope=\"row\">Elevation antérieure (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("elevationAnterieureG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("elevationAnterieureD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "elevationLaterale";
    // 6e row -elevationLaterale
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Elevation latérale (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("elevationLateraleG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("elevationLateraleD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extensionE";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionEG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionED") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "adductionHorizontale";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Adduction Horizontale (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("adductionHorizontaleG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("adductionHorizontaleD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationInterneR1";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Interne R1 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneR1G") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneR1D") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationExterneR1";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Externe R1 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneR1G") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneR1D") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationInterneR2";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Interne R2 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneR2G") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneR2D") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationExterneR2";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Externe R2 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneR2G") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneR2D") + "</td>";
    }

    //////////////// Rachis ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "texteRachis";
    // 1ere row - texteRachis
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "<tr>"
                                                    "<td style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Rachis</td>"
                                                    "<td colspan=\"3\">" + getMapListeRapport(listePairesRapport, "1").value("texteRachis") + "</td>"
                                                    "</tr>";
    }

    //////////////// END ////////////////
    texteTableauCourant.append("</tr></table>");

    texteTableauCourant.append("<p style=\"margin-bottom:35px; text-align: justify;\">* BKFO = distance entre la tête du peronné et le sol "
                               "dans une position de flexion, abduction et rotation externe des hanches  avec les deux voûtes plantaires collées"
                               " ensembles proche des fesses, distance optimale inf. 17 cm</p>");

    texteTableauCourant.append("<p style=\"text-align: justify;margin-bottom:50px;\"></p>< /br>< /br>");

    return texteTableauCourant;
}



//****************************************
QString MainWindow::ecrireAmplitudesBpcf(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;


    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table style=\"margin-bottom:1px;\">");

    texteTableauCourant= texteTableauCourant +  "<tr>"
                                                "<th style=\"background-color: white; color:#002e40;\">Amplitudes articulaires</th>"
                                                "<th scope=\"col\"style=\"background-color:#c0c0c0; color:#002e40;border:1px solid #023448\"></th>"
                                                "<th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">Membre G</th>"
                                                "<th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">Membre D</th>"
                                                "</tr>";

    //////////////// Cheville ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionPlantaire";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "<tr>"
                                                    "<td rowspan=\"3\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Cheville</td>"
                                                    "<th scope=\"row\">Flexion Plantaire (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionPlantaireG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionPlantaireD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionDorsaleWBL";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionDorsaleWBL";
    // 3e row - Extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Abduction (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLGDegre") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLDDegre") + "</td>";
    }

    //////////////// GENOU ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionGenou";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<td rowspan=\"2\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Genou</td>"
                                                    "<th scope=\"row\">Flexion (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionGenouG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionGenouD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extensionGenou";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionGenouG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionGenouD") + "</td>";
    }

    //////////////// HANCHE ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionHanche";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<td rowspan=\"7\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Hanche</td>"
                                                    "<th scope=\"row\">Flexion (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionHancheG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionHancheD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extensionHanche";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionHancheG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionHancheD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "abduction";
    // 3e row - Extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Abduction (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("abductionG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("abductionD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "adduction";
    // 4e row - Adduction
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Abduction (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("adductionG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("adductionD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationInterne";
    // 5e row - Rotation Interne
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Interne (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationExterne";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Externe (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "bkfo";
    // 7e row - BKFO
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Bent Knee Fall Out - BKFO* (cm)</th>";

        QString valeurCourante = getMapListeRapport(listePairesRapport,"1").value("bkfoG");
        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + valeurCourante + "</td>";

        valeurCourante = getMapListeRapport(listePairesRapport,"1").value("bkfoD");
        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + valeurCourante + "</td>";
    }

    //////////////// Poignet ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionPoignet";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<td rowspan=\"2\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Poignet</td>"
                                                    "<th scope=\"row\">Flexion (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionPoignetG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionPoignetD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extensionPoignet";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionPoignetG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionPoignetD") + "</td>";
    }

    //////////////// EPAULE ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "elevationAnterieure";
    // 1ere row - elevationAnterieure
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "<tr>"
                                                    "<td rowspan=\"8\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Epaule</td>"
                                                    "<th scope=\"row\">Elevation antérieure (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("elevationAnterieureG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("elevationAnterieureD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "elevationLaterale";
    // 6e row -elevationLaterale
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Elevation latérale (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("elevationLateraleG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("elevationLateraleD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extensionE";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionEG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionED") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "adductionHorizontale";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Adduction Horizontale (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("adductionHorizontaleG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("adductionHorizontaleD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationInterneR1";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Interne R1 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneR1G") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneR1D") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationExterneR1";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Externe R1 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneR1G") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneR1D") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationInterneR2";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Interne R2 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneR2G") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneR2D") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationExterneR2";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Externe R2 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneR2G") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneR2D") + "</td>";
    }

    //////////////// Rachis ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "texteRachis";
    // 1ere row - texteRachis
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "<tr>"
                                                    "<td style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Rachis</td>"
                                                    "<td colspan=\"3\">" + getMapListeRapport(listePairesRapport, "1").value("texteRachis") + "</td>"
                                                    "</tr>";
    }

    //////////////// END ////////////////
    texteTableauCourant.append("</tr></table>");

    texteTableauCourant.append("<p style=\"margin-bottom:35px; text-align: justify;\">* BKFO = distance entre la tête du peronné et le sol "
                               "dans une position de flexion, abduction et rotation externe des hanches  avec les deux voûtes plantaires collées"
                               " ensembles proche des fesses, distance optimale inf. 17 cm</p>");

    texteTableauCourant.append("<p style=\"text-align: justify;margin-bottom:50px;\"></p>< /br>< /br>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireAmplitudesBp(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;


    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table style=\"margin-bottom:1px;\">");

    texteTableauCourant= texteTableauCourant +  "<tr>"
                                                "<th style=\"background-color: white; color:#002e40;\">Amplitudes articulaires</th>"
                                                "<th scope=\"col\"style=\"background-color:#c0c0c0; color:#002e40;border:1px solid #023448\"></th>"
                                                "<th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">Membre G</th>"
                                                "<th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">Membre D</th>"
                                                "</tr>";

    //////////////// Cheville ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionPlantaire";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "<tr>"
                                                    "<td rowspan=\"3\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Cheville</td>"
                                                    "<th scope=\"row\">Flexion Plantaire (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionPlantaireG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionPlantaireD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionDorsaleWBL";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Flexion Dorsale - Test WBLT (cm)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionDorsaleWBL";
    // 3e row - Extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Flexion Dorsale (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLGDegre") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("flexionDorsaleWBLDDegre") + "</td>";
    }

    //////////////// GENOU ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionGenou";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<td rowspan=\"2\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Genou</td>"
                                                    "<th scope=\"row\">Flexion (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionGenouG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionGenouD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extensionGenou";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionGenouG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionGenouD") + "</td>";
    }

    //////////////// HANCHE ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "flexionHanche";
    // 1ere row - Flexion
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<td rowspan=\"7\" style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Hanche</td>"
                                                    "<th scope=\"row\">Flexion (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionHancheG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport, "1").value("flexionHancheD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extensionHanche";
    // 2e row - extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionHancheG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("extensionHancheD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "abduction";
    // 3e row - Extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Abduction (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("abductionG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("abductionD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "adduction";
    // 4e row - Adduction
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Abduction (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("adductionG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("adductionD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationInterne";
    // 5e row - Rotation Interne
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Interne (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationInterneD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationExterne";
    // 6e row - Rotation externe
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Externe (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneG") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,"1").value("rotationExterneD") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "bkfo";
    // 7e row - BKFO
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Bent Knee Fall Out - BKFO* (cm)</th>";

        QString valeurCourante = getMapListeRapport(listePairesRapport,"1").value("bkfoG");
        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + valeurCourante + "</td>";

        valeurCourante = getMapListeRapport(listePairesRapport,"1").value("bkfoD");
        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurBkfo(valeurCourante.toDouble()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + valeurCourante + "</td>";
    }

    //////////////// Rachis ////////////////
    listeCaracteresCol.clear();
    listeCaracteresCol << "texteRachis";
    // 1ere row - texteRachis
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "<tr>"
                                                    "<td style=\"background-color: #c0c0c0; font-weight: bold; vertical-align: middle;\">Rachis</td>"
                                                    "<td colspan=\"3\">" + getMapListeRapport(listePairesRapport, "1").value("texteRachis") + "</td>"
                                                    "</tr>";
    }


    texteTableauCourant.append("</tr></table>");

    texteTableauCourant.append("<p style=\"margin-bottom:35px; text-align: justify;\">* BKFO = distance entre la tête du peronné et le sol "
                               "dans une position de flexion, abduction et rotation externe des hanches  avec les deux voûtes plantaires collées"
                               " ensembles proche des fesses, distance optimale inf. 17 cm</p>");

    texteTableauCourant.append("<p style=\"text-align: justify;margin-bottom:50px;\"></p>< /br>< /br>");


    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrirePerimetres(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "perimetre";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Périmetres";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
    }
    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row - Perimetre Mollet
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Mollet (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("perimetreMolletNO") + "</td>";

    if(tailleListeFaits == 1){
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("perimetreMolletO") + "</td>";
    }
    else if(tailleListeFaits == 2){

        // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm", getMapListeRapport(listePairesRapport, avantDernierTest).value("perimetreMolletNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("perimetreMolletNO").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("perimetreMolletNO")
                              + texteEvolution + "</td>" ;

        //Membre opéré Tfirst
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("perimetreMolletO") + "</td>";

        // Membre opéré Tlast
        prog = calculerProgression("cm", getMapListeRapport(listePairesRapport, avantDernierTest).value("perimetreMolletO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("perimetreMolletO").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("perimetreMolletO")
                              + texteEvolution + "</td>" ;
    }
    else if(tailleListeFaits == 3){

        //Membre sain T2
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("perimetreMolletNO") + "</td>" ;

        // Membre sain T3
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, "2").value("perimetreMolletNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, "3").value("perimetreMolletNO").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("perimetreMolletNO")
                              + texteEvolution + "</td>" ;

        //Membre opéré T1
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("perimetreMolletO") + "</td>";

        //Membre opéré T2
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("perimetreMolletO") + "</td>";

        //Membre opéré T3"
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, "2").value("perimetreMolletO").toDouble(),
                                   getMapListeRapport(listePairesRapport, "3").value("perimetreMolletO").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("perimetreMolletO")
                              + texteEvolution + "</td>" ;
    }

    // 2e row - Rotule +10cm
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Sommet rotule +10(cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("perimetreRotuleDixNO") + "</td>";

    if(tailleListeFaits == 1){
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("perimetreRotuleDixO") + "</td>";
    }
    else if(tailleListeFaits == 2){

        // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm", getMapListeRapport(listePairesRapport, avantDernierTest).value("perimetreRotuleDixNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("perimetreRotuleDixNO").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("perimetreRotuleDixNO")
                              + texteEvolution + "</td>" ;

        //Membre opéré Tfirst
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("perimetreRotuleDixO") + "</td>";

        // Membre opéré Tlast
        prog = calculerProgression("cm", getMapListeRapport(listePairesRapport, avantDernierTest).value("perimetreRotuleDixO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("perimetreRotuleDixO").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("perimetreRotuleDixO")
                              + texteEvolution + "</td>" ;
    }
    else if(tailleListeFaits == 3){

        //Membre sain T2
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("perimetreRotuleDixNO") + "</td>" ;

        // Membre sain T3
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, "2").value("perimetreRotuleDixNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, "3").value("perimetreRotuleDixNO").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("perimetreRotuleDixNO")
                              + texteEvolution + "</td>" ;

        //Membre opéré T1
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("perimetreRotuleDixO") + "</td>";

        //Membre opéré T2
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("perimetreRotuleDixO") + "</td>";

        //Membre opéré T3"
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, "2").value("perimetreRotuleDixO").toDouble(),
                                   getMapListeRapport(listePairesRapport, "3").value("perimetreRotuleDixO").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("perimetreRotuleDixO")
                              + texteEvolution + "</td>" ;
    }

    // 3e row - Sommet rotule 20cm
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Sommet rotule +20(cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("perimetreRotuleVingtNO") + "</td>";

    if(tailleListeFaits == 1){
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("perimetreRotuleVingtO") + "</td>";
    }
    else if(tailleListeFaits == 2){

        // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm", getMapListeRapport(listePairesRapport, avantDernierTest).value("perimetreRotuleVingtNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("perimetreRotuleVingtNO").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("perimetreRotuleVingtNO")
                              + texteEvolution + "</td>" ;

        //Membre opéré Tfirst
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("perimetreRotuleVingtO") + "</td>";

        // Membre opéré Tlast
        prog = calculerProgression("cm", getMapListeRapport(listePairesRapport, avantDernierTest).value("perimetreRotuleVingtO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("perimetreRotuleVingtO").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("perimetreRotuleVingtO")
                              + texteEvolution + "</td>" ;
    }
    else if(tailleListeFaits == 3){

        //Membre sain T2
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("perimetreRotuleVingtNO") + "</td>" ;

        // Membre sain T3
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, "2").value("perimetreRotuleVingtNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, "3").value("perimetreRotuleVingtNO").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\" > " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("perimetreRotuleVingtNO")
                              + texteEvolution + "</td>" ;

        //Membre opéré T1
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "1").value("perimetreRotuleVingtO") + "</td>";

        //Membre opéré T2
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("perimetreRotuleVingtO") + "</td>";

        //Membre opéré T3"
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, "2").value("perimetreRotuleVingtO").toDouble(),
                                   getMapListeRapport(listePairesRapport, "3").value("perimetreRotuleVingtO").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("perimetreRotuleVingtO")
                              + texteEvolution + "</td>" ;
    }

    texteTableauCourant.append("</tr></table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireRatioIJ(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "Quadri" << "Ischio";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Ratio Ischios-jambiers / Quadriceps";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;

    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - FMax Ischios
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Ischios (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxIschioNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxIschioO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIschioNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIschioO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIschioNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIschioNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIschioNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIschioO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIschioO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIschioO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIschioNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIschioO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax Quadri
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Quadriceps (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxQuadriNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxQuadriO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxQuadriNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxQuadriO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxQuadriNO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("fmaxQuadriNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxQuadriNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxQuadriO").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("fmaxQuadriO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxQuadriO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxQuadriNO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxQuadriO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";


    // 3e row - Ratio
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th style=\"background-color:#e8e8e9; color:#002e40; border:1px solid rgb(160,160,160); padding:8px 10px;\" scope=\"row\">Ratio</th>";
;

    QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxIschioNO").toDouble(),
                                                       getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxQuadriNO").toDouble(),
                                                       "ratioIJ");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxIschioO").toDouble(),
                               getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxQuadriO").toDouble(),
                               "ratioIJ");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);
        if(tailleListeFaits == 3){

            //Membre sain T2
            QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIschioNO").toDouble()
                                                               ,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxQuadriNO").toDouble(),
                                                               "ratioIJ");

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + paireRatio.second + "</td>";

            // Membre opéré T2
            paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIschioO").toDouble(),
                                       getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxQuadriO").toDouble(),
                                       "ratioIJ");

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + paireRatio.second + "</td>";
        }

        //Membre sain TLast
        QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIschioNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("fmaxQuadriNO").toDouble(),
                                                           "ratioIJ");

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

        // Membre opéré TLast
        paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIschioO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxQuadriO").toDouble(),
                                   "ratioIJ");

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

    }

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireRatioIJBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    QStringList listeCaracteresCol;
    listeCaracteresCol << "Quadri" << "Ischio";

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">Ratio Ischios-jambiers / Quadriceps</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre G</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre D</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Asymétrie</th>";

    // 1ere row - FMax Ischios
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Ischios (N)</th>"
                                                "<td>" + mapCourante.value("fmaxIschioG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxIschioD") + "</td>";

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxIschioG").toDouble(),
                                      mapCourante.value("fmaxIschioD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax Quadri
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Quadriceps (N)</th>"
                                                "<td>" + mapCourante.value("fmaxQuadriG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxQuadriD") + "</td>";

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxQuadriG").toDouble(),
                                    mapCourante.value("fmaxQuadriD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 3e row - Ratio
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th style=\"background-color:#e8e8e9; color:#002e40; border:1px solid rgb(160,160,160); padding:8px 10px;\" scope=\"row\">Ratio</th>";
;

    QPair<QString, QString> paireRatio = getPaireRatio(mapCourante.value("fmaxIschioG").toDouble(),
                                                       mapCourante.value("fmaxQuadriG").toDouble(),
                                                       "ratioIJ");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    paireRatio = getPaireRatio(mapCourante.value("fmaxIschioD").toDouble(),
                               mapCourante.value("fmaxQuadriD").toDouble(),
                               "ratioIJ");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireMcCall(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "McCall";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test Mc Call";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + "<th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - Force isométrique du genou à 30 (N)
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Force à 30°(N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("force30McCallNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("force30McCallO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("force30McCallNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("force30McCallO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("force30McCallNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("force30McCallNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("force30McCallNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("force30McCallO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("force30McCallO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("force30McCallO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("force30McCallNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("force30McCallO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - Force isométrique du genou à 90 (N)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Force à 90°(N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("force90McCallNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("force90McCallO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("force90McCallNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("force90McCallO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("force90McCallNO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("force90McCallNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("force90McCallNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("force90McCallO").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("force90McCallO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("force90McCallO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("force90McCallNO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("force90McCallO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}


//****************************************
QString MainWindow::ecrireMcCallBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "McCall";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">Test Mc Call</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre G</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre D</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Asymétrie</th>";

    // 1ere row - Force isométrique du genou à 30 (N)
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Force à 30°(N)</th>"
                                                "<td>" + mapCourante.value("force30McCallG") + "</td>"
                                                "<td>" + mapCourante.value("force30McCallD") + "</td>";
    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("force30McCallG").toDouble(),
                                      mapCourante.value("force30McCallD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - Force isométrique du genou à 90 (N)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Force à 90°(N)</th>"
                                                "<td>" + mapCourante.value("force90McCallG") + "</td>"
                                                "<td>" + mapCourante.value("force90McCallD") + "</td>";

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, mapCourante.value("force90McCallG").toDouble(),
                                    mapCourante.value("force90McCallD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireIP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
        QString couleurCourante;
        QStringList listeColonnesTab;

        QStringList listeTestFaits;
        QStringList listeCaracteresCol;
        listeCaracteresCol << "fmaxIllio";

        for (int i = 0; i < listePairesRapport.count(); ++i) {

            if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
                listeTestFaits.append(QString::number(i+1));
            }
        }

        int tailleListeFaits = listeTestFaits.count();

        //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
        if(tailleListeFaits == 0){
            return "";
        }

        // Ecrire liste des colonnes du tableau
        texteTableauCourant.append("<table><tr>");

        listeColonnesTab << "Fmax Illio-Psoas";

        foreach (QString numeroTestFait, listeTestFaits) {
            listeColonnesTab << "Membre sain T" + numeroTestFait;
            listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;

        }

        listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

        // Ecrire les colonnes associees
        for (int i = 0; i < listeColonnesTab.count(); ++i) {

            if(i == 0){
                texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color:white; color:#002e40; border:1px solid #023448;\">"
                                      + listeColonnesTab.at(i) +"</th>";
            }
            else if(listeColonnesTab.at(i).contains(labelBlessure)){
                texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                      + listeColonnesTab.at(i) +"</th>";
            }
            else{
                texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
            }
        }
        // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
        QString dernierTest = listeTestFaits.last();

        // 1ere row - FMax Ischios
        //Membre sain T1 - Membre opere T1
        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">FMax Ischios (N)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxIllioNO") + "</td>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxIllioO") + "</td>";
        if(tailleListeFaits > 1){

            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            if(tailleListeFaits == 3){

                //Membre sain T2
                texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIllioNO") + "</td>" ;

                // Membre opéré T2
                texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIllioO") + "</td>" ;
            }

            //Membre sain TLast
            QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIllioNO").toDouble(),
                                                                          getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIllioNO").toDouble());


            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIllioNO")
                                  + texteEvolution + "</td>" ;

            // Membre opéré TLast
            prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIllioO").toDouble(),
                                                  getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIllioO").toDouble());


            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIllioO")
                                  + texteEvolution + "</td>" ;
        }

        // Asymetrie TLast
        QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIllioNO").toDouble(),
                                          getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIllioO").toDouble());

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireCourante.second+ "</td></tr>";

        texteTableauCourant.append("</table>");

        return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireIPBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxIllio";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    texteTableauCourant= texteTableauCourant + "<th style=\"border: 0px;\"></th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre G</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre D</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Asymétrie</th>";

    // 1ere row - Force isométrique du genou à 30 (N)
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Fmax Illio-Psoas</th>"
                                                "<td>" + mapCourante.value("fmaxIllioG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxIllioD") + "</td>";
    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxIllioG").toDouble(),
                                      mapCourante.value("fmaxIllioD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireRatioA(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "Adducteurs" << "Abducteurs";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Ratio Adducteurs / Abducteurs";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - FMax Adducteurs (N)
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Adducteurs (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxAdducteursNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxAdducteursO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAdducteursNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAdducteursO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAdducteursNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAdducteursNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAdducteursNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAdducteursO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAdducteursO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAdducteursO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAdducteursNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAdducteursO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax Abducteurs (N)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Abducteurs (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxAbducteursNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxAbducteursO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAbducteursNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAbducteursO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAbducteursNO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAbducteursNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAbducteursNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAbducteursO").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAbducteursO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAbducteursO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAbducteursNO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAbducteursO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";


    // 3e row - Ratio
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th style=\"background-color:#e8e8e9; color:#002e40; border:1px solid rgb(160,160,160); padding:8px 10px;\" scope=\"row\">Ratio</th>";
;

    QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxAdducteursNO").toDouble(),
                                                   getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxAbducteursNO").toDouble(),
                                                   "ratioAA");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxAdducteursO").toDouble(),
                               getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxAbducteursO").toDouble(),
                               "ratioAA");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);
        if(tailleListeFaits == 3){

            //Membre sain T2
            QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAdducteursNO").toDouble()
                                                               ,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAbducteursNO").toDouble(),
                                                               "ratioAA");

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + paireRatio.second + "</td>";

            // Membre opéré T2
            paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAdducteursO").toDouble(),
                                       getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxAbducteursO").toDouble(),
                                       "ratioAA");

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + paireRatio.second + "</td>";
        }

        //Membre sain TLast
        QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAdducteursNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAbducteursNO").toDouble(),
                                                           "ratioAA");

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

        // Membre opéré TLast
        paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAdducteursO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxAbducteursO").toDouble(),
                                   "ratioAA");

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

    }

    texteTableauCourant.append("</table>");
    return texteTableauCourant;
}


//****************************************
QString MainWindow::ecrireRatioREHanche(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxREA";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Rotateurs Externes de Hanche (REH)";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - FMax Adducteurs (N)
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax REH Assis (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxREAssisNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxREAssisO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxREAssisNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxREAssisO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxREAssisNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAssisNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAssisNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxREAssisO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAssisO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAssisO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAssisNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAssisO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax Abducteurs (N)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax REH Allongé (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxREAllongeNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxREAllongeO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxREAllongeNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxREAllongeO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxREAllongeNO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAllongeNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAllongeNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxREAllongeO").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAllongeO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAllongeO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAllongeNO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxREAllongeO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");
    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireRatioAABP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "Adducteurs" << "Abducteurs";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">Ratio Adducteurs / Abducteurs</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre G</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre D</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Asymétrie</th>";

    // 1ere row - FMax Adducteurs (N)
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Adducteurs (N)</th>"
                                                "<td>" + mapCourante.value("fmaxAdducteursG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxAdducteursD") + "</td>";

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxAdducteursG").toDouble(),
                                      mapCourante.value("fmaxAdducteursD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax Abducteurs (N)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Abducteurs (N)</th>"
                                                "<td>" + mapCourante.value("fmaxAbducteursG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxAbducteursD") + "</td>";

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxAbducteursG").toDouble(),
                                    mapCourante.value("fmaxAbducteursD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";


    // 3e row - Ratio
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th style=\"background-color:#e8e8e9; color:#002e40; border:1px solid rgb(160,160,160); padding:8px 10px;\" scope=\"row\">Ratio</th>";
;

    QPair<QString, QString> paireRatio = getPaireRatio(mapCourante.value("fmaxAdducteursG").toDouble(),
                                                   mapCourante.value("fmaxAbducteursG").toDouble(),
                                                   "ratioAA");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    paireRatio = getPaireRatio(mapCourante.value("fmaxAdducteursD").toDouble(),
                               mapCourante.value("fmaxAbducteursD").toDouble(),
                               "ratioAA");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    texteTableauCourant.append("</table>");
    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireAclRsi(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "testRSI";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.size();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits== 0){
        return "";
    }

    texteTableauCourant.append("<table><tr>");
    listeColonnesTab << "";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "T" + numeroTestFait;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\" style=\"background-color:#fdfefe; color:#002e40;\"></th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Test ACL-RSI</th>";

    couleurCourante = getCouleurACLRsi(getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("testRSI").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurCourante + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("testRSI") + "/100</td>";

    if(tailleListeFaits > 1){

        // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if (tailleListeFaits > 2) {
            couleurCourante = getCouleurACLRsi(getMapListeRapport(listePairesRapport, avantDernierTest).value("testRSI").toDouble());

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurCourante + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + getMapListeRapport(listePairesRapport, avantDernierTest).value("testRSI") + "/100</td>";
        }

        couleurCourante = getCouleurACLRsi(getMapListeRapport(listePairesRapport, dernierTest).value("testRSI").toDouble());

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurCourante + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + getMapListeRapport(listePairesRapport, dernierTest).value("testRSI") + "/100</td>";
    }
    texteTableauCourant.append("</tr></table>");

    return texteTableauCourant;
}


/****************************************
/*
 *
 */
QString MainWindow::ecrirePointsReceptionUnipodale(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString pointCourant;
    QString couleurPoint;

    QString texteRes;
    QStringList listeColonnesTab;
    int tailleListe = listePairesRapport.size();

    QStringList listeCaractereCles;

    QMap<QString, QString> mapDernierTest = getMapListeRapport(listePairesRapport, QString::number(listePairesRapport.count()));

    // On regarde si des valeurs pour les points de reception unipodal ont ete remplies sinon on ecrit pas
    if(doitEtreEcrit(listeCaractereCles, mapDernierTest) == false){
        return "";
    }

    // Titre du test
    texteRes = texteRes + "<table width=\"900\" style=\"text-align:left;\"><tr>";
    texteRes= texteRes + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Single leg landing</th>";
    texteRes= texteRes + " <th scope=\"col\">Observation</th>";

    // Controle du tronc bassin
    if(mapDernierTest.value("controleTroncOK").contains("1")){
        pointCourant = mapDernierTest.value("controleTroncOK").split(";").first();
        couleurPoint = "#169d53";
    }
    else{
        pointCourant = mapDernierTest.value("controleTroncNOK").split(";").first();
        couleurPoint = "#9f3f36";
    }
    texteRes = texteRes + "</tr>"
                          "<tr>"
                          "<th width=\"20%\" scope=\"col\" style=\"text-align:left;\">Controle du tronc/bassin :</th>";

    texteRes = texteRes + "<td width=\"42%\" style=\"background-color:" + couleurPoint + "; text-align:left;color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
               + pointCourant + "</td>";

    // Controle du genou controle
    if(mapDernierTest.value("controleGenouFrontal").contains("1")){
        pointCourant = mapDernierTest.value("controleGenouFrontal").split(";").first();
        couleurPoint = "#169d53";
    }
    else{
        pointCourant = mapDernierTest.value("controleGenouValgus").split(";").first();
        couleurPoint = "#9f3f36";
    }
    texteRes = texteRes + "</tr>"
                          "<tr>"
                          "<th scope=\"col\" style=\"text-align:left;\">1er controle du genou :</th>";

    texteRes = texteRes + "<td style=\"background-color:" + couleurPoint + "; text-align:left;color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
               + pointCourant + "</td>";

    // Controle genou reception
    if(mapDernierTest.value("angleFlexionOK").contains("1")){
        pointCourant = mapDernierTest.value("angleFlexionOK").split(";").first();
        couleurPoint = "#169d53";
    }
    else{
        pointCourant = mapDernierTest.value("angleFlexionNOK").split(";").first();
        couleurPoint = "#9f3f36";
    }
    texteRes = texteRes + "</tr>"
                          "<tr>"
                          "<th scope=\"col\" style=\"text-align:left;\">2e controle du genou :</th>";

    texteRes = texteRes + "<td style=\"background-color:" + couleurPoint + "; text-align:left;color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
               + pointCourant + "</td>";

    // Repartitions charge checkBox
    QString texteRepartitionCharges = "</tr>"
                                      "<tr>"
                                      "<th scope=\"col\" style=\"text-align:left;\">Repartition de la charge au niveau du pied</th>";

    bool estPremier = true;
    if(mapDernierTest.value("receptionMedioPied").contains("1")){
        estPremier = false;
        texteRes = texteRes + texteRepartitionCharges;
        texteRes = texteRes + "<td style=\"background-color:#169d53;text-align:left;border:1px solid #023448;\">"+ mapDernierTest.value("receptionMedioPied").split(";").first() + "</td></tr>";
    }

    if(mapDernierTest.value("receptionAvantPied").contains("1")){
        if(!estPremier){
            texteRes = texteRes + "<tr><td style=\"border:none;\"></td>";
        }
        else{
            texteRes = texteRes + texteRepartitionCharges;
        }
        estPremier = false;
        texteRes = texteRes + "<td style=\"background-color:#9f3f36;text-align:left;border:1px solid #023448;\">"+ mapDernierTest.value("receptionAvantPied").split(";").first() + "</td></tr>";
    }

    if(mapDernierTest.value("receptionBordInterne").contains("1")){
        if(!estPremier){
            texteRes = texteRes + "<tr><td style=\"border:none;\"></td>";
        }
        else{
            texteRes = texteRes + texteRepartitionCharges;
        }
        estPremier = false;
        texteRes = texteRes + "<td style=\"background-color:#9f3f36;text-align:left;border:1px solid #023448;\">"+ mapDernierTest.value("receptionBordInterne").split(";").first() + "</td></tr>";
    }

    if(mapDernierTest.value("receptionTalon").contains("1")){
        if(!estPremier){
            texteRes = texteRes + "<tr><td style=\"border:none;\"></td>";
        }
        else{
            texteRes = texteRes + texteRepartitionCharges;
        }
        texteRes = texteRes + "<td style=\"background-color:#9f3f36;text-align:left;border:1px solid #023448;\">"+ mapDernierTest.value("receptionTalon").split(";").first() + "</td></tr>";
    }

    texteRes = texteRes + "</table>";

    return texteRes;
}

//****************************************
QString MainWindow::ecrireSjBipodal(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "Sj";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test Squat Jump Bipodal" <<  "Hauteur de saut (cm)" << "RFDMax membre sain (N.s)" << "RFDMax membre " + labelBlessure + " (N.s)" << "Asymétrie RFDMax";
    for (int i = 0; i < listeColonnesTab.count(); ++i) {
        if(i==0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    //T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T"+listeTestFaits.first()+"</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("hauteurSautSj") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdmaxNOSj") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdmaxOSj") + "</td>";

    //ASymetrie
     QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdmaxNOSj").toDouble(),
                                    getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdmaxOSj").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td>";

    // T2
    if(tailleListeFaits > 1 ){

        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //T2
            texteTableauCourant = texteTableauCourant + "</tr>"
                                                        "<tr>"
                                                        "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T"
                                                        + avantDernierTest+"</th>";
            // hauteur saut
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautSj")+ "</td>" ;
            // rfdmax sain
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxNOSj") + "</td>" ;
            // rfdmax opere
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxOSj")+ "</td>";
            // Asymetrie
            paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxNOSj").toDouble(),
                                           getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxOSj").toDouble());

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                 + paireCourante.second+ "</td>";
        }

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T" + dernierTest + "</th>";

        // hauteur saut
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautSj").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautSj").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second + ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautSj")
                              + texteEvolution + "</td>" ;
        // rfdmax sain
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxNOSj").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxNOSj").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxNOSj")
                              + texteEvolution + "</td>" ;

        // rfdmax opere
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxOSj").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxOSj").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxOSj")
                              + texteEvolution + "</td>";

        // Asymetrie
        paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxNOSj").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxOSj").toDouble());

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                             + paireCourante.second+ "</td></tr>";
    }

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireSjBipodalBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "Sj";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test Squat Jump Bipodal" <<  "Hauteur de saut (cm)" << "RFDMax membre G (N.s)" << "RFDMax membre D (N.s)" << "Asymétrie RFDMax";
    for (int i = 0; i < listeColonnesTab.count(); ++i) {
        if(i==0){
            texteTableauCourant= texteTableauCourant + "<th style=\"border: 0px;\"></th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    //T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Test Squat Jump Bipodal</th>"
                                                "<td>" + mapCourante.value("hauteurSautSj") + "</td>"
                                                "<td>" + mapCourante.value("rfdmaxSjG") + "</td>"
                                                "<td>" + mapCourante.value("rfdmaxSjD") + "</td>";

    //ASymetrie
     QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("rfdmaxSjG").toDouble(),
                                    mapCourante.value("rfdmaxSjD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireCmjBipodal(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString sexe, QString labelBlessure){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "CmjB";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test CMJ Bipodal"
                     << "Hauteur de saut (cm)"
                     << "RSI Modifie"
                     << "RFD Deceleration membre sain (N.s-1)"
                     << "RFD Deceleration membre " + labelBlessure + " (N.s-1)"
                     << "Asymétrie RFD Deceleration";

    for (int i = 0; i < listeColonnesTab.count(); ++i) {
        if(i==0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    //Tfirst
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T"+listeTestFaits.first()+"</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("hauteurSautCmjB") + "</td>";
    // RSI Modifie
    QPair<QString, QString> paireRatio = getPaireRsiModifie(getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("hauteurSautCmjB").toDouble() / 100 ,
                                                            getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("tempsMvmtCmjB").toDouble() / 1000,
                                                            sexe);

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
            + paireRatio.second + "</td>";

    //  RFD deceleration
    texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdDecelerationNOCmjB") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdDecelerationOCmjB") + "</td>";

    // Asymetrie deceleration
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdDecelerationNOCmjB").toDouble(),
                                                              getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdDecelerationOCmjB").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
            + paireCourante.second+ "</td>";

    // TLast
    if(tailleListeFaits > 1){

        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){
            //T2
            texteTableauCourant = texteTableauCourant + "</tr>"
                                                        "<tr>"
                                                        "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T"+avantDernierTest+"</th>";
            // hauteur saut
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautCmjB")+"</td>" ;

            // RSI Modifie
            QPair<QString, QString> paireRatio = getPaireRsiModifie(getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautCmjB").toDouble() / 100 ,
                                                                    getMapListeRapport(listePairesRapport, avantDernierTest).value("tempsMvmtCmjB").toDouble() / 1000,
                                                                    sexe);

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + paireRatio.second + "</td>";

            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdDecelerationNOCmjB") + "</td>"
                                                        "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdDecelerationOCmjB") + "</td>";

            // Asymetrie deceleration
            QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdDecelerationNOCmjB").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdDecelerationOCmjB").toDouble());

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                    + paireCourante.second+ "</td>";
        }

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T"+dernierTest+"</th>";

        // hauteur saut
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautCmjB").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautCmjB").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second + ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautCmjB")
                              + texteEvolution + "</td>" ;

        // RSI Modifie
        QPair<QString, QString> paireRatio = getPaireRsiModifie(getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautCmjB").toDouble() / 100 ,
                                                                getMapListeRapport(listePairesRapport, dernierTest).value("tempsMvmtCmjB").toDouble() / 1000,
                                                                sexe);

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

        // RDF Deceleration sain
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdDecelerationNOCmjB").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("rfdDecelerationNOCmjB").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rfdDecelerationNOCmjB")
                              + texteEvolution + "</td>";

        // RDF Deceleration opere
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdDecelerationOCmjB").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("rfdDecelerationOCmjB").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rfdDecelerationOCmjB")
                              + texteEvolution + "</td>";

        // Asymetrie RDF Deceleration
        paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("rfdDecelerationNOCmjB").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("rfdDecelerationOCmjB").toDouble());

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                             + paireCourante.second+ "</td></tr>";
    }

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireCmjBipodalBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString sexe){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "CmjB";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test CMJ Bipodal"
                     << "Hauteur de saut (cm)"
                     << "RSI Modifie"
                     << "RFD Deceleration membre G (N.s-1)"
                     << "RFD Deceleration membre D (N.s-1)"
                     << "Asymétrie RFD Deceleration";

    for (int i = 0; i < listeColonnesTab.count(); ++i) {
        if(i==0){
            texteTableauCourant= texteTableauCourant + "<th style=\"border: 0px;\"></th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    //Tfirst
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Test CMJ Bipodal</th>"
                                                "<td>" + mapCourante.value("hauteurSautCmjB") + "</td>";
    // RSI Modifie
    QPair<QString, QString> paireRatio = getPaireRsiModifie(mapCourante.value("hauteurSautCmjB").toDouble() / 100 ,
                                                            mapCourante.value("tempsMvmtCmjB").toDouble() / 1000,
                                                            sexe);

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
            + paireRatio.second + "</td>";

    //  RFD deceleration
    texteTableauCourant = texteTableauCourant + "<td>" + mapCourante.value("rfdDecelerationCmjBG") + "</td>"
                                                "<td>" + mapCourante.value("rfdDecelerationCmjBD") + "</td>";

    // Asymetrie deceleration
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("rfdDecelerationCmjBG").toDouble(),
                                                              mapCourante.value("rfdDecelerationCmjBD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
            + paireCourante.second+ "</td>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireCmjUnipodal(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "CmjNO" << "CmjO";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test CMJ Unipodal ";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    QString dernierTest = listeTestFaits.last();

    // 1ere row - Hauteur de saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Hauteur de saut (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("hauteurSautCmjNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("hauteurSautCmjO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);
        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautCmjNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautCmjO")+ "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautCmjNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautCmjNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautCmjNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautCmjO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautCmjO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautCmjO")
                              + texteEvolution + "</td>" ;
    }

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautCmjNO").toDouble(),
                                                              getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautCmjO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireCmjUnipodalBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "CmjG" << "CmjD";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test CMJ Unipodal"
                    << "Membre G"
                    << "Membre D"
                    << "Asymétrie";

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row - Hauteur de saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Hauteur de saut (cm)</th>"
                                                "<td>" + mapCourante.value("hauteurSautCmjG") + "</td>"
                                                "<td>" + mapCourante.value("hauteurSautCmjD") + "</td>";

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("hauteurSautCmjG").toDouble(),
                                                              mapCourante.value("hauteurSautCmjD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireDjBipodal(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "DjB";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test DropJump Bipodal"
                        << "Hauteur de saut (cm)"
                        << "RSI "
                        << "RFDMax membre sain(N.s)"
                        <<"RFDMax membre " + labelBlessure + " (N.s)"
                        << "Asymétrie RFDMax";

    for (int i = 0; i < listeColonnesTab.count(); ++i) {
        if(i==0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    //
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T"+listeTestFaits.first()+"</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("hauteurSautDjB") + "</td>";

    QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("tempsVolDjB").toDouble(),
                                                       getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("tempsContactDjB").toDouble(),
                                                       "rsi");
    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdmaxNODjB") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdmaxODjB") + "</td>";

    // Asymetrie RFDMax
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdmaxNODjB").toDouble(),
                                                              getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("rfdmaxODjB").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
            + paireCourante.second+ "</td>";

    // T2 et/ou T3
    if(tailleListeFaits > 1){

        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //T2
            texteTableauCourant = texteTableauCourant + "</tr>"
                                                        "<tr>"
                                                        "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T"+ avantDernierTest+"</th>";
            // hauteur saut
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautDjB")+ "</td>" ;

            // RSI
            QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, avantDernierTest).value("tempsVolDjB").toDouble() ,
                                                               getMapListeRapport(listePairesRapport, avantDernierTest).value("tempsContactDjB").toDouble(),
                                                               "rsi");

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + paireRatio.second + "</td>";

            // rfdmax sain
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxNODjB")+ "</td>" ;
            // rfdmax opere
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxODjB")+ "</td>";

            // Asymetrie deceleration
            paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxNODjB").toDouble(),
                                                    getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxODjB").toDouble());

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                    + paireCourante.second+ "</td>";
        }

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T"+dernierTest+"</th>";

        // hauteur saut
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautDjB").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautDjB").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second + ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautDjB")
                              + texteEvolution + "</td>" ;

        // RSI
        QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("tempsVolDjB").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("tempsContactDjB").toDouble(),
                                                           "rsi" );

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

        // rfdmax sain
        prog = getProgressionPourcentage(false, getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxNODjB").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxNODjB").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxNODjB")
                              + texteEvolution + "</td>" ;

        // rfdmax opere
        prog = getProgressionPourcentage(false, getMapListeRapport(listePairesRapport, avantDernierTest).value("rfdmaxODjB").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxODjB").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxODjB")
                              + texteEvolution + "</td>";

        // Asymetrie rfdmax
        paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxNODjB").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("rfdmaxODjB").toDouble());

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                             + paireCourante.second+ "</td></tr>";
    }

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireDjBipodalBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "DjB";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test DropJump Bipodal"
                        << "Hauteur de saut (cm)"
                        << "RSI "
                        << "RFDMax membre G(N.s)"
                        << "RFDMax membre D (N.s)"
                        << "Asymétrie RFDMax";

    for (int i = 0; i < listeColonnesTab.count(); ++i) {
        if(i==0){
            texteTableauCourant= texteTableauCourant + "<th style=\"border: 0px;\"></th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    //
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Test DropJump Bipodal</th>"
                                                "<td>" + mapCourante.value("hauteurSautDjB") + "</td>";

    QPair<QString, QString> paireRatio = getPaireRatio(mapCourante.value("tempsVolDjB").toDouble(),
                                                       mapCourante.value("tempsContactDjB").toDouble(),
                                                       "rsi");
    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    texteTableauCourant = texteTableauCourant + "<td>" + mapCourante.value("rfdmaxDjBG") + "</td>"
                                                "<td>" + mapCourante.value("rfdmaxDjBD") + "</td>";

    // Asymetrie RFDMax
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("rfdmaxDjBG").toDouble(),
                                                              mapCourante.value("rfdmaxDjBD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
            + paireCourante.second+ "</td>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireDjUnipodal(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "DjNO" << "DjO";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test DropJump Unipodal";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    QString dernierTest = listeTestFaits.last();

    // 1ere row - Hauteur de saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Hauteur de saut (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("hauteurSautDjNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("hauteurSautDjO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautDjNO")+ "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautDjO")+ "</td>" ;
        }

        //Membre sain Tlast
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautDjNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautDjNO").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautDjNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré Tlast
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurSautDjO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautDjO").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautDjO")
                              + texteEvolution + "</td>" ;
    }

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautDjNO").toDouble(),
                                                              getMapListeRapport(listePairesRapport, dernierTest).value("hauteurSautDjO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireDjUnipodalBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "DjG" << "DjD";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab    << "Test DropJump Unipodal"
                        << "Membre G"
                        << "Membre D"
                        << "Asymétrie";

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row - Hauteur de saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Hauteur de saut (cm)</th>"
                                                "<td>" + mapCourante.value("hauteurSautDjG") + "</td>"
                                                "<td>" + mapCourante.value("hauteurSautDjD") + "</td>";

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("hauteurSautDjG").toDouble(),
                                                              mapCourante.value("hauteurSautDjD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireTestAcc(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QStringList listeColonnesTab;
    int tailleListe = listePairesRapport.size();

    texteTableauCourant.append("<table><tr>");
    listeColonnesTab << "" <<  "T1";

    if(tailleListe == 2){
        listeColonnesTab <<  "T2";
    }
    else if(tailleListe == 3){
        listeColonnesTab << "T2" << "T3" ;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\" style=\"background-color:#fdfefe; color:#002e40;\"></th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Test d'accroupissement</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, "1").value("testAccroupissement").replace("<", "&lt; ") + "</td>";

    if(tailleListe > 1){
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("testAccroupissement").replace("<", "&lt; ") + "</td>";

        if (tailleListe > 2) {
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "3").value("testAccroupissement").replace("<", "&lt; ") + "</td>";
        }
    }
    texteTableauCourant.append("</tr></table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrirekStart(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QStringList listeNumerosTest){

    bool tousKstartNuls = true;

    QString texteTableauCourant;

    texteTableauCourant.append("<table>");

    foreach (QString numeroTest, listeNumerosTest) {

        if(getMapListeRapport(listePairesRapport, numeroTest).value("kStart") != "0"){

            texteTableauCourant = texteTableauCourant + "<tr><th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">KStart T"+numeroTest+"</th>";

            QPair<QString, QString> pairekStart = getPaireKstart(getMapListeRapport(listePairesRapport, numeroTest).value("kStart").toDouble());

            texteTableauCourant = texteTableauCourant + "<td style=\"text-align:left;background-color:" + pairekStart.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + getMapListeRapport(listePairesRapport, numeroTest).value("kStart") + "/100</td>" +
                                  "<td>" + pairekStart.second + "</td></tr>";

            tousKstartNuls = false;
        }
    }

    texteTableauCourant.append("</tr></table>");

    if(tousKstartNuls == true)
        return "";
    else
        return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireAmplitudesEpaule(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;

    for (int i = 0; i < listePairesRapport.count(); ++i) {
        listeTestFaits.append(QString::number(i+1));
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Amplitudes articulaires";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
    }
    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "elevationAnterieure";
    // 1ere row - Elevation anterieure
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Elevation antérieure (°)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("elevationAnterieureNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("elevationAnterieureO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("elevationAnterieureNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("elevationAnterieureNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("elevationAnterieureNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("elevationAnterieureO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("elevationAnterieureO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("elevationAnterieureO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("elevationAnterieureO")
                                  + texteEvolution + "</td>" ;
        }
    }


    listeCaracteresCol.clear();
    listeCaracteresCol << "elevationLateral";
    // 2e row - Elavation Laterale
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Elevation latérale (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("elevationLateraleNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("elevationLateraleO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("elevationLateraleNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("elevationLateraleNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("elevationLateraleNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("elevationLateraleO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("elevationLateraleO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("elevationLateraleO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("elevationLateraleO")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "extensionE";
    // 3e row - Extension
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Extension (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("extensionENO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("extensionEO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("extensionENO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("extensionENO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("extensionENO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("extensionEO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("extensionEO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("extensionEO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("extensionEO")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "adductionHorizontale";
    // 4e row - Adduction Horizontale
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Adduction Horizontale (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("adductionHorizontaleNO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("adductionHorizontaleO") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("adductionHorizontaleNO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("adductionHorizontaleNO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("adductionHorizontaleNO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("adductionHorizontaleO") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("adductionHorizontaleO").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("adductionHorizontaleO").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("adductionHorizontaleO")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationExterneR1";
    // 5e row - Rotation Externe R1
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Externe R1 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationExterneR1NO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationExterneR1O") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("rotationExterneR1NO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneR1NO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneR1NO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationExterneR1O") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("rotationExterneR1O").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneR1O").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneR1O")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationInterneR1";
    // 6e row - RIR1
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation Interne R1</th>"
                                                    "<td>Niveau épineuse de " + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationInterneR1NO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>Niveau épineuse de " + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationInterneR1O") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            texteTableauCourant = texteTableauCourant + "<td>Niveau épineuse de " + getMapListeRapport(listePairesRapport, dernierTest).value("rotationInterneR1NO")+ "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>Niveau épineuse de " + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationInterneR1O") + "</td>";

            // Membre opéré Tlast
            texteTableauCourant = texteTableauCourant + "<td>Niveau épineuse de " + getMapListeRapport(listePairesRapport, dernierTest).value("rotationInterneR1O")+ "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationExterneR2";
    // 7e row - Rotation externe R2
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation externe R2 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationExterneR2NO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationExterneR2O") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("rotationExterneR2NO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneR2NO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneR2NO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationExterneR2O") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("rotationExterneR2O").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneR2O").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rotationExterneR2O")
                                  + texteEvolution + "</td>" ;
        }
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "rotationInterneR2";
    // 8e row - Rotation interne R2
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\">Rotation interne R2 (°)</th>"
                                                    "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationInterneR2NO") + "</td>";

        if(tailleListeFaits == 1){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationInterneR2O") + "</td>";
        }
        else if(tailleListeFaits == 2){

            // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
            QString dernierTest = listeTestFaits.last();
            QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

            //Membre sain TLast
            QPair<QString, QString> prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("rotationInterneR2NO").toDouble(),
                                                               getMapListeRapport(listePairesRapport, dernierTest).value("rotationInterneR2NO").toDouble());

            QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rotationInterneR2NO")
                                  + texteEvolution + "</td>" ;

            //Membre opéré Tfirst
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rotationInterneR2O") + "</td>";

            // Membre opéré Tlast
            prog = calculerProgression("°", getMapListeRapport(listePairesRapport, avantDernierTest).value("rotationInterneR2O").toDouble(),
                                       getMapListeRapport(listePairesRapport, dernierTest).value("rotationInterneR2O").toDouble());

            texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("rotationInterneR2O")
                                  + texteEvolution + "</td>" ;
        }
    }

    texteTableauCourant.append("</tr></table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireTestsInstabilite(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QStringList listeColonnesTab;
    int tailleListe = listePairesRapport.size();

    texteTableauCourant.append("<table><tr>");
    listeColonnesTab << "" <<  "T1";

    if(tailleListe == 2){
        listeColonnesTab <<  "T2";
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\" style=\"background-color:#fdfefe; color:#002e40;\"></th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Test d'instabilité antérieure</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, "1").value("testInstabiliteA").replace("<", "&lt; ") + "</td>";

    if(tailleListe > 1){
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("testInstabiliteA").replace("<", "&lt; ") + "</td>";
    }

    // 2eme row
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Test d'instabilité postérieure</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, "1").value("testInstabiliteP").replace("<", "&lt; ") + "</td>";

    if(tailleListe > 1){
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, "2").value("testInstabiliteP").replace("<", "&lt; ") + "</td>";
    }
    texteTableauCourant.append("</tr></table>");

    return texteTableauCourant;
}



//****************************************
QString MainWindow::ecrireSiRsi(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "testRSI";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.size();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits== 0){
        return "";
    }

    texteTableauCourant.append("<table><tr>");
    listeColonnesTab << "";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "T" + numeroTestFait;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\" style=\"background-color:#fdfefe; color:#002e40;\"></th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Test SI-RSI</th>";

    couleurCourante = getCouleurSiRsi(getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("testSIRSI").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurCourante + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("testSIRSI") + "/100</td>";

    if(tailleListeFaits > 1){

        // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
        QString dernierTest = listeTestFaits.last();

        couleurCourante = getCouleurSiRsi(getMapListeRapport(listePairesRapport, dernierTest).value("testSIRSI").toDouble());

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurCourante + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + getMapListeRapport(listePairesRapport, dernierTest).value("testSIRSI") + "/100</td>";
    }
    texteTableauCourant.append("</tr></table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireTestGrip(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxGrip";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table style=\"margin-bottom:100px;\"><tr>");

    listeColonnesTab << "Test Grip";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - FMax
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxGripNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxGripO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxGripNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxGripNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxGripNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxGripO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxGripO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxGripO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxGripNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxGripO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}


//****************************************
QString MainWindow::ecrireTestGripBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxGrip";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport,"1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test Grip";

    listeColonnesTab << "Membre G";
    listeColonnesTab << "Membre D";

    listeColonnesTab << "Asymétrie";

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row - FMax
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax (N)</th>"
                                                "<td>" + mapCourante.value("fmaxGripG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxGripD") + "</td>";

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxGripG").toDouble(),
                                      mapCourante.value("fmaxGripD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireReRiR1(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "RER1" << "RIR1";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table style=\"margin-bottom:100px;\"><tr>");

    listeColonnesTab << "Ratio RE/RI (R1)";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - FMax RE
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Rotateurs Externes (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRER1NO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRER1O") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxRER1NO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER1NO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER1NO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxRER1O").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER1O").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER1O")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER1NO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER1O").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax RI
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Rotateurs Internes (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRIR1NO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRIR1O") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxRIR1NO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR1NO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR1NO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxRIR1O").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR1O").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR1O")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR1NO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR1O").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";


    // 3e row - Ratio
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th style=\"background-color:#e8e8e9; color:#002e40; border:1px solid rgb(160,160,160); padding:8px 10px;\" scope=\"row\">Ratio</th>";
;

    QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRER1NO").toDouble(),
                                                       getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRIR1NO").toDouble(),
                                                       "RERIR1");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRER1O").toDouble(),
                               getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRIR1O").toDouble(),
                               "RERIR1");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    if(tailleListeFaits > 1){

        //Membre sain TLast
        QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER1NO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR1NO").toDouble(),
                                                           "RERIR1");

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

        // Membre opéré TLast
        paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER1O").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR1O").toDouble(),
                                   "RERIR1");

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";
    }

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireReRiR2(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "RER2" << "RIR2" ;

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Ratio RE/RI (R2)";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - FMax RE
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Rotateurs Externes (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRER2NO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRER2O") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxRER2NO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER2NO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER2NO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxRER2O").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER2O").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER2O")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER2NO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER2O").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax RI
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Rotateurs Internes (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRIR2NO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRIR2O") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxRIR2NO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR2NO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR2NO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxRIR2O").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR2O").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR2O")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR2NO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR2O").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";


    // 3e row - Ratio
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th style=\"background-color:#e8e8e9; color:#002e40; border:1px solid rgb(160,160,160); padding:8px 10px;\" scope=\"row\">Ratio</th>";
;

    QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRER2NO").toDouble(),
                                                       getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRIR2NO").toDouble(),
                                                       "RERIR2");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRER2O").toDouble(),
                               getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxRIR2O").toDouble(),
                               "RERIR2");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER2NO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR2NO").toDouble(),
                                                           "RERIR2");

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

        // Membre opéré TLast
        paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRER2O").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxRIR2O").toDouble(),
                                   "RERIR2");

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

    }

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireReRiR1BP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "RER1" << "RIR1";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport,"1");


    if(doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table style=\"margin-bottom:100px;\"><tr>");

    listeColonnesTab << "Ratio RE/RI (R1)";

    listeColonnesTab << "Membre G";
    listeColonnesTab << "Membre D";

    listeColonnesTab << "Asymétrie";

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // 1ere row - FMax RE
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Rotateurs Externes (N)</th>"
                                                "<td>" + mapCourante.value("fmaxRER1G") + "</td>"
                                                "<td>" + mapCourante.value("fmaxRER1D") + "</td>";

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxRER1G").toDouble(),
                                      mapCourante.value("fmaxRER1D").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax RI
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Rotateurs Internes (N)</th>"
                                                "<td>" + mapCourante.value("fmaxRIR1G") + "</td>"
                                                "<td>" + mapCourante.value("fmaxRIR1D") + "</td>";

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxRIR1G").toDouble(),
                                    mapCourante.value("fmaxRIR1D").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";


    // 3e row - Ratio
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th style=\"background-color:#e8e8e9; color:#002e40; border:1px solid rgb(160,160,160); padding:8px 10px;\" scope=\"row\">Ratio</th>";
;

    QPair<QString, QString> paireRatio = getPaireRatio(mapCourante.value("fmaxRER1G").toDouble(),
                                                       mapCourante.value("fmaxRIR1G").toDouble(),
                                                       "RERIR1");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    paireRatio = getPaireRatio(mapCourante.value("fmaxRER1D").toDouble(),
                               mapCourante.value("fmaxRIR1D").toDouble(),
                               "RERIR1");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

        texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireReRiR2BP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "RER2" << "RIR2";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport,"1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Ratio RE/RI (R2)";

    listeColonnesTab << "Membre G";
    listeColonnesTab << "Membre D";

    listeColonnesTab << "Asymétrie";

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // 1ere row - FMax RE
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Rotateurs Externes (N)</th>"
                                                "<td>" + mapCourante.value("fmaxRER2G", "-") + "</td>"
                                                "<td>" + mapCourante.value("fmaxRER2D", "-") + "</td>";

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxRER2G", "-").toDouble(),
                                      mapCourante.value("fmaxRER2D").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax RI
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Rotateurs Internes (N)</th>"
                                                "<td>" + mapCourante.value("fmaxRIR2G", "-") + "</td>"
                                                "<td>" + mapCourante.value("fmaxRIR2D", "-") + "</td>";

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxRIR2G").toDouble(),
                                    mapCourante.value("fmaxRIR2D").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";


    // 3e row - Ratio
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th style=\"background-color:#e8e8e9; color:#002e40; border:1px solid rgb(160,160,160); padding:8px 10px;\" scope=\"row\">Ratio</th>";
;

    QPair<QString, QString> paireRatio = getPaireRatio(mapCourante.value("fmaxRER2G", "-").toDouble(),
                                                       mapCourante.value("fmaxRIR2G", "-").toDouble(),
                                                       "RERIR2");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    paireRatio = getPaireRatio(mapCourante.value("fmaxRER2D").toDouble(),
                               mapCourante.value("fmaxRIR2D").toDouble(),
                               "RERIR2");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

        texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireTestIYT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxI" << "fmaxY" << "fmaxT";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test IYT (ASH Test)";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - FMax I
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax I (180°) (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxINO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxIO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxINO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxINO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxINO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxIO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxINO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxIO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax Y
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Y (135°) (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxYNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxYO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxYNO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("fmaxYNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxYNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxYO").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("fmaxYO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxYO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxYNO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxYO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 3e row - FMax T
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax T (90°) (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxTNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxTO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxTNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxTNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxTNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxTO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxTO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxTO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxTNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxTO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}


//****************************************
QString MainWindow::ecrireUQYBT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceS" << "distanceI" << "distanceM";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<p style=\"text-align: justify;\">* En appui avec la main du membre supérieur testé (coude en extension) au niveau "
                               "du croisement des branches du Y et les pieds au sol de manière à avoir une position de "
                               "planche, amener un gobelet (ou autre objet) le plus loin possible sur chaque branche du "
                               "Y avec la main libre, répéter l’opération avec l’autre bras.</p><br />");
    //Ecrire les branches du test
    QString suffixeBrasDroit;
    QString suffixeBrasGauche;
    QString labelBrasDroit;
    QString labelBrasGauche;

    // Si le bras droit est opere alors on prend les bonnes informations
    if(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("brasOpere") == "Droit"){
        suffixeBrasDroit = "O";
        suffixeBrasGauche = "NO";
        labelBrasDroit = labelBlessure;
        labelBrasGauche = "sain";
    }
    else{
        suffixeBrasDroit = "NO";
        suffixeBrasGauche = "O";
        labelBrasDroit = "sain";
        labelBrasGauche = labelBlessure;
    }

    // Ecrire le T1
    texteTableauCourant.append(dessinerTestUQ(listePairesRapport,suffixeBrasDroit, suffixeBrasGauche, labelBrasDroit,
                                              labelBrasGauche,listeTestFaits.first()));
    // Ecrire le T2
    if(tailleListeFaits > 1){
        texteTableauCourant.append(dessinerTestUQ(listePairesRapport,suffixeBrasDroit, suffixeBrasGauche, labelBrasDroit,
                                                  labelBrasGauche,listeTestFaits.last()));
    }

    // Ecrire le tableau du test
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test UQ-YBT* (Upper Quarter Y Balance Test)";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - Distance supero-laterale
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance supero-laterale (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceSLNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceSLO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceSLNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceSLO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLO").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - Distance infero-laterale
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance infero-laterale (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceINO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceIO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceINO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("distanceINO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceINO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceIO").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("distanceIO").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceIO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("distanceINO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("distanceIO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 3e row - Distance Mediale
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance Mediale (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceMNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceMO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceMNO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("distanceMNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceMNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceMO").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("distanceMO").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceMO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("distanceMNO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("distanceMO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 4e row - Limb Symmetry Index
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Limb Symmetry Index* (%)</th>";

    QPair<QString, QString> paireLSI = getPaireLSI(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceSLNO").toDouble(),
                                                getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceINO").toDouble(),
                                                getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceMNO").toDouble(),
                                                getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("longueurBras").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireLSI.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireLSI.second + "%</td>";

    paireLSI = getPaireLSI(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceSLO").toDouble(),
                                              getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceIO").toDouble(),
                                              getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceMO").toDouble(),
                                              getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("longueurBras").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireLSI.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireLSI.second + "%</td>";

    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        paireLSI = getPaireLSI(getMapListeRapport(listePairesRapport,listeTestFaits.last()).value("distanceSLNO").toDouble(),
                                                  getMapListeRapport(listePairesRapport,listeTestFaits.last()).value("distanceINO").toDouble(),
                                                  getMapListeRapport(listePairesRapport,listeTestFaits.last()).value("distanceMNO").toDouble(),
                                                  getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("longueurBras").toDouble());

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireLSI.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireLSI.second + "%</td>";

        // Membre opéré TLast
        paireLSI = getPaireLSI(getMapListeRapport(listePairesRapport,listeTestFaits.last()).value("distanceSLO").toDouble(),
                                                  getMapListeRapport(listePairesRapport,listeTestFaits.last()).value("distanceIO").toDouble(),
                                                  getMapListeRapport(listePairesRapport,listeTestFaits.last()).value("distanceMO").toDouble(),
                                                  getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("longueurBras").toDouble());

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireLSI.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireLSI.second + "%</td>";
    }

    texteTableauCourant.append("</table>");
    texteTableauCourant.append("<p style=\"margin-bottom:35px; text-align: justify;\">* LSI = [ sommes des trois distances / (3 x longueur de bras (distance épineuse de C7 - extremité du 3ème doigt) ) ]</p>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::dessinerTestUQ(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport,
                                   QString suffixeBrasDroit, QString suffixeBrasGauche,
                                   QString labelBrasDroit, QString labelBrasGauche, QString numeroTest){
    QString res;

    QString texteImageDroit = "<img src=\"" + QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "uqYbt_droit") + "\" width=\"250\" height=\"150\" style=\"display: block;border:1px solid #023448\">";
    QString texteImageGauche = "<img src=\"" + QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "uqYbt_gauche") +  "\" width=\"250\" height=\"150\">";

    //Ecriture du bras droit et bras gauche
    res.append("<table style=\"margin-top:10px;\">");
    res = res + "<tr>"
                    "<td style=\"border:none; padding-left:0px; padding-right:5px;;\"></td>"
                    "<td style=\"border:none; font-weight: bold; padding:0px;\">Membre gauche "+ labelBrasGauche +" T" + numeroTest + "</td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; font-weight: bold; padding-left:5px; padding-right:0px;\">Membre droit " + labelBrasDroit + " T" + numeroTest + "</td>"
                "</tr>"
                "<tr>"
                    "<td style=\"text-align:right;vertical-align:bottom;border:none; padding:0px;\">" + getMapListeRapport(listePairesRapport,numeroTest).value("distanceSL" + suffixeBrasGauche) + "</td>" +
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"text-align:left;vertical-align:bottom;border:none; padding:0px;\">" + getMapListeRapport(listePairesRapport,numeroTest).value("distanceSL" + suffixeBrasDroit) + "</td>" +
                "</tr>"
                "<tr>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\">" + texteImageGauche + "</td>"
                    "<td style=\"text-align:center;vertical-align:middle;border:none; padding:0px;\">" + getMapListeRapport(listePairesRapport,numeroTest).value("distanceM"+ suffixeBrasGauche) + "</td>"
                    "<td style=\"border:none;padding-left:15px; padding-right:15px;\"></td>"
                    "<td style=\"text-align:center;vertical-align:middle;border:none; padding:0px;\">" + getMapListeRapport(listePairesRapport,numeroTest).value("distanceM"+ suffixeBrasDroit) + "</td>"
                    "<td style=\"border:none; padding:0px;\">" + texteImageDroit + "</td>"
                "</tr>"
                "<tr>"
                    "<td style=\"text-align:right;vertical-align:top;border:none; padding:0px;\">" + getMapListeRapport(listePairesRapport,numeroTest).value("distanceI"+ suffixeBrasGauche) + "</td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"border:none; padding:0px;\"></td>"
                    "<td style=\"text-align:left;vertical-align:top;border:none; padding:0px;\">" + getMapListeRapport(listePairesRapport,numeroTest).value("distanceI"+ suffixeBrasDroit) + "</td>" +
                "</tr>";

    res.append("</table>");

    return res;
}

//******************************************************
QString MainWindow::dessinerTestYBalance(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport,
                                         QString suffixeDroit, QString suffixeGauche,
                                         QString labelDroit, QString labelGauche, QString numeroTest)
{
    QString res;

    QString imagePath = QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "yBalance");

    QString texteImageGauche = "<img src=\"" + QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "uqYbt_gauche") +  "\" width=\"250\" height=\"150\">";


    auto blocImage = [&](QString distTop, QString distLeft, QString distRight){
        return QString(
            "<table style='border:1px solid #a0a0a0; width:250px; height:250px; border-collapse:collapse; margin:auto;'>"
            // Ligne haute (distance antérieure)
            "<tr><td colspan='3' style='text-align:center; font-weight:bold; border:none;'>%1</td></tr>"
            // Ligne image avec espaces gauche/droite
            "<tr>"
            "<td style='width:33%; vertical-align:bottom; text-align:left; font-weight:bold; border:none;'>%2</td>"
            "<td style='width:34%; text-align:center; border:none;'><img src='%4' style='max-width:150; max-height:250;'></td>"
            "<td style='width:33%; vertical-align:bottom; text-align:right; font-weight:bold; border:none;'>%3</td>"
            "</tr>"
            "</table>"
        ).arg(distTop, distLeft, distRight, imagePath);
    };

    res.append("<table style='margin-top:10px; width:100%; text-align:center; border:none;'>");

    // Titres
    res += "<tr>"
           "<td style='border:none; font-weight:bold; text-align:center;'>Membre gauche " + labelGauche + " T" + numeroTest + "</td>"
           "<td style='border:none; width:50px;'></td>"
           "<td style='border:none; font-weight:bold; text-align:center;'>Membre droit " + labelDroit + " T" + numeroTest + "</td>"
           "</tr>";

    // Images avec valeurs correctement placées
    res += "<tr>"
           "<td style='border:none; text-align:center;'>" +
           blocImage(
                getMapListeRapport(listePairesRapport, numeroTest).value("distanceANO"),
                getMapListeRapport(listePairesRapport, numeroTest).value("distancePMNO"),
                getMapListeRapport(listePairesRapport, numeroTest).value("distancePLNO")
            ) +
           "</td>"
           "<td style='border:none;'></td>"
           "<td style='border:none; text-align:center;'>" +
           blocImage(
                getMapListeRapport(listePairesRapport, numeroTest).value("distanceAO"),
                getMapListeRapport(listePairesRapport, numeroTest).value("distancePMO"),
                getMapListeRapport(listePairesRapport, numeroTest).value("distancePLO")
            ) +
           "</td>"
           "</tr>";

    res.append("</table>");

    return res;
}
//******************************************************
QString MainWindow::ecrireCkCuest(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "nbTouches";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<p style=\"text-align: justify;\">*en position de pompe, les mains écartées "
                               "d’une distance D = épineuse de C7 - extrémité du 3ème doigt, on demande le "
                               "nombre maximal de touches de part et d’autre de chaque mains (en alternant) en 15 secondes.</p>");

    texteTableauCourant.append("<table style=\"margin-bottom:1px;\"><tr>");
    listeColonnesTab << "Test CK-CUEST modifie *";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "T" + numeroTestFait;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - Distance supero-laterale
    //T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Nombre de touchés (N)</th>";

    QString couleur = getCouleurCKCuest(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("nbTouches").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleur + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("nbTouches") + "</td>";

    //T2
    if(tailleListeFaits > 1){

        //Membre sain TLast
        QString couleur = getCouleurCKCuest(getMapListeRapport(listePairesRapport,dernierTest).value("nbTouches").toDouble());

        //Membre sain TLast
        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleur + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                + getMapListeRapport(listePairesRapport, dernierTest).value("nbTouches")+ "</td>" ;
    }

    texteTableauCourant.append("</tr></table>");

    texteTableauCourant.append("<p style=\"text-align: justify;\">N &lt; 18 insuffisant</p>");
    texteTableauCourant.append("<p style=\"text-align: justify;\">18 &lt; N &lt; 25 moyen</p>");
    texteTableauCourant.append("<p style=\"text-align: justify;margin-bottom:50px;\">N > 25 bon</p>< /br>< /br>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireSASSPT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceLance";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<p style=\"text-align: justify;\">*En position assise, dos au mur, les genoux fléchis, lancer un "
                               "medecine de ball de 3 kg le plus loin possible de manière horizontale avec un seul bras."
                               " En moyenne, on admet une distance supérieure de 6,6% du côté dominant en comparaison à l’autre côté.</p>");

    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test SASSPT (Seated Single-Arm Shot-Put Test) *";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - Distance lancer
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceLanceNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("distanceLanceO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceLanceNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("distanceLanceNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceLanceNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceLanceO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("distanceLanceO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceLanceO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("distanceLanceNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("distanceLanceO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireULRT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "nbRepetitions";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<p style=\"text-align: justify;\">* en position de planche sur les coudes (coude de l'épaule testée contre le mur) : "
                               "nombre maximum de rotation du tronc avec touche du coude du côté opposé contre le mur en 15 secondes. "
                               "(Attention les pieds ne doivent pas bouger, les épaules doivent rester à 90° d'abduction et de "
                               "rotation externe; le coude à 90° de flexion)</p>");

    texteTableauCourant.append("<table style=\"margin-bottom:1px;\"><tr>");

    listeColonnesTab << "Test ULRT (Upper Limb Rotation Test) *";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - Nb repetitions
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Nombre de répétitions </th>";

    QString couleurNO = getCouleurURLT(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("nbRepetitionsNO").toDouble());
    QString couleurO = getCouleurURLT(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("nbRepetitionsO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurNO + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("nbRepetitionsNO") + "</td>";

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurO + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("nbRepetitionsO") + "</td>";

    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("nbRepetitionsNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("nbRepetitionsNO").toDouble());

        QString couleurNO = getCouleurURLT(getMapListeRapport(listePairesRapport,dernierTest).value("nbRepetitionsNO").toDouble());
        QString couleurO = getCouleurURLT(getMapListeRapport(listePairesRapport,dernierTest).value("nbRepetitionsO").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant +
                "<td style=\"background-color:" + couleurNO + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                + getMapListeRapport(listePairesRapport, dernierTest).value("nbRepetitionsNO")
                + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("nbRepetitionsO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("nbRepetitionsO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant +
                "<td style=\"background-color:" + couleurO + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                + getMapListeRapport(listePairesRapport, dernierTest).value("nbRepetitionsO")
                + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("nbRepetitionsNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("nbRepetitionsO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    texteTableauCourant.append("<p style=\"text-align: justify;\">N &lt; 10 insuffisant</p>");
    texteTableauCourant.append("<p style=\"text-align: justify;\">10 &lt; N &lt; 15 moyen</p>");
    texteTableauCourant.append("<p style=\"text-align: justify;margin-bottom:50px;\">N > 15 bon</p>");

    return texteTableauCourant;
}

/*
 *
 *
 */
QString MainWindow::ecrirePSET(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "pset";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    texteTableauCourant.append("<pstyle=\"margin-bottom:10px;text-align: justify;\">* Patient à plat ventre sur une table ou un support surélevé avec le front posé sur la main du membre qui n’est pas testé</p></br>");
    texteTableauCourant.append("<p style=\"text-align: justify;\">&emsp; - Test en Y : le patient maintiens en l’air une charge (~2% du poids du corps) le plus longtemps possible "
                               " avec l’épaule en position Y (135° abduction, RE maximale, coude en extension complète)</p>");

    texteTableauCourant.append("<p style=\"margin-bottom:10px;text-align: justify;\">Fin du test :  à l’apparition de compensations ou lorsque l’haltère passe en dessous du plan de la table, on obtient le Score Y en second.</p>");

    texteTableauCourant.append("<p style=\"text-align: justify;\"> - Test en W : mêmes paramètres de charge et de calcul du score, seule la position change : épaule placée en position  R2 (90° abduction, "
                               "90° RE, 90° Flexion de coude)</p>");

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "PSET* modifié (Prone Shoulder Endurance Test)";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - PSET en Y
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Score Y (s)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("psetYNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("psetYO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("psetYNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("psetYNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("psetYNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("psetYO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("psetYO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("psetYO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("psetYNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("psetYO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - Score W (s)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Score W (s)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("psetWNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("psetWO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("psetWNO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("psetWNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("psetWNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("psetWO").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("psetWO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("psetWO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("psetWNO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("psetWO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireSStart(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QStringList listeNumerosTest, QString labelBlessure){

    bool tousSstartNuls = true;

    QString texteTableauCourant;

    texteTableauCourant.append("<table>");

    foreach (QString numeroTest, listeNumerosTest) {

        if(getMapListeRapport(listePairesRapport, numeroTest).value("kStart") != "0"){

            texteTableauCourant = texteTableauCourant + "<tr><th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">SStart T"+numeroTest+"</th>";

            QPair<QString, QString> pairekStart = getPaireSstart(getMapListeRapport(listePairesRapport, numeroTest).value("sStart").toDouble());

            texteTableauCourant = texteTableauCourant + "<td style=\"text-align:left;background-color:" + pairekStart.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + getMapListeRapport(listePairesRapport, numeroTest).value("sStart") + "/100</td>" +
                                  "<td>" + pairekStart.second + "</td></tr>";

            tousSstartNuls = false;
        }
    }

    texteTableauCourant.append("</tr></table>");

    if(tousSstartNuls == true)
        return "";
    else
        return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireBroadJump(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString contexte){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceBroadJump";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test Broad Jump ";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "T" + numeroTestFait;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    QString dernierTest = listeTestFaits.last();

    // 1ere row - Distance sautee
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance saut (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("distanceBroadJump") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceBroadJump") + "</td>" ;
        }

        QPair<QString, QString> prog = calculerProgression(" cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceBroadJump").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("distanceBroadJump").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceBroadJump")
                              + texteEvolution + "</td>" ;
    }


    //DiSPLAYZ
    QString cheminImageScore =  QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "scoresBroadJump");

    // On génère une version HD pour éviter la pixellisation
    cheminImageScore = redimensionnerImage(cheminImageScore, 1000);

    // Image à droite du tableau
    texteTableauCourant = encadrerTableauEtImageFlexible(texteTableauCourant, cheminImageScore, "right", 400, 300);

    return texteTableauCourant;
}




//****************************************
QString MainWindow::ecrireHop(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure, QString contexte){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceSLH";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }
    else if(contexte == "genou" && listePairesRapport.count() > 1){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Hop Test";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    QString dernierTest = listeTestFaits.last();

    // 1ere row - Distance saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance saut (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("distanceSLHNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("distanceSLHO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);
        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceSLHNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceSLHO")+ "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceSLHNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLHNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLHNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceSLHO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLHO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLHO")
                              + texteEvolution + "</td>" ;
    }

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLHNO").toDouble(),
                                                              getMapListeRapport(listePairesRapport, dernierTest).value("distanceSLHO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireHopBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceSLH";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Hop Test"
                     << "Membre G"
                     << "Membre D"
                     << "Asymétrie";

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row - Distance saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance saut (cm)</th>"
                                                "<td>" + mapCourante.value("distanceSLHG") + "</td>"
                                                "<td>" + mapCourante.value("distanceSLHD") + "</td>";

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("distanceSLHG").toDouble(),
                                                              mapCourante.value("distanceSLHD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireTripleHop(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceTH";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Triple Hop Test";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    QString dernierTest = listeTestFaits.last();

    // 1ere row - Distance saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance totale sauts (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("distanceTHNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("distanceTHO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);
        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceTHNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceTHO")+ "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceTHNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("distanceTHNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceTHNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceTHO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("distanceTHO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceTHO")
                              + texteEvolution + "</td>" ;
    }

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("distanceTHNO").toDouble(),
                                                              getMapListeRapport(listePairesRapport, dernierTest).value("distanceTHO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireCrossOverHop(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceCH";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table style=\"page-break-inside: avoid;\" ><tr>");

    listeColonnesTab << "Cross Over Hop Test";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    QString dernierTest = listeTestFaits.last();

    // 1ere row - Distance totale saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance totale sauts (cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("distanceCHNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("distanceCHO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);
        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceCHNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceCHO")+ "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceCHNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("distanceCHNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceCHNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("distanceCHO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("distanceCHO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("distanceCHO")
                              + texteEvolution + "</td>" ;
    }

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("distanceCHNO").toDouble(),
                                                              getMapListeRapport(listePairesRapport, dernierTest).value("distanceCHO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireTripleHopBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceTH";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Triple Hop Test"
                    << "Membre G"
                    << "Membre D"
                    << "Asymétrie";

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row - Distance saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance totale sauts (cm)</th>"
                                                "<td>" + mapCourante.value("distanceTHG") + "</td>"
                                                "<td>" + mapCourante.value("distanceTHD") + "</td>";

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("distanceTHG").toDouble(),
                                                              mapCourante.value("distanceTHD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireCrossOverHopBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceCH";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table style=\"page-break-inside: avoid;\" ><tr>");

    listeColonnesTab << "Cross Over Hop Test"
                     << "Membre G"
                     << "Membre D"
                     << "Asymétrie";

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row - Distance totale saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance totale sauts (cm)</th>"
                                                "<td>" + mapCourante.value("distanceCHG") + "</td>"
                                                "<td>" + mapCourante.value("distanceCHD") + "</td>";

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("distanceCHG").toDouble(),
                                                              mapCourante.value("distanceCHD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireFmaxReleveursCheville(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxReleveurs";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - Fmax releveurs
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                " <th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Fmax releveurs (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxReleveursNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxReleveursO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxReleveursNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxReleveursO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxReleveursNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxReleveursNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxReleveursNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxReleveursO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxReleveursO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxReleveursO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxReleveursNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxReleveursO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireFmaxReleveursSoleaireBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxReleveurs";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport,"1");

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    texteTableauCourant= texteTableauCourant + " <th style=\"border: 0px;\"></th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre G</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre D</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Asymétrie</th>";

    // 1ere row - Fmax releveurs
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Fmax releveurs (N)</th>"
                                                "<td>" + mapCourante.value("fmaxReleveursG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxReleveursD") + "</td>";

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxReleveursG").toDouble(),
                                      mapCourante.value("fmaxReleveursD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td>";

    // 2e row - Fmax Soleaire
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Fmax Soleaire (N)</th>"
                                                "<td>" + mapCourante.value("fmaxSoleaireG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxSoleaireD") + "</td>";

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxSoleaireG").toDouble(),
                                      mapCourante.value("fmaxSoleaireD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";


    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireFmaxSoleaireCheville(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxSoleaire";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - Fmax releveurs
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                " <th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Fmax soleaire (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxSoleaireNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxSoleaireO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxSoleaireNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxSoleaireO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxSoleaireNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxSoleaireNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxSoleaireNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxSoleaireO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxSoleaireO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxSoleaireO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxSoleaireNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxSoleaireO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireRatioVerseurs(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxEverseurs" << "fmaxInverseurs";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Ratio Everseurs / Inverseurs";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    // 1ere row - FMax Everseurs
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Everseurs (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxEverseursNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxEverseursO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxEverseursNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxEverseursO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxEverseursNO").toDouble(),
                                                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxEverseursNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxEverseursNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxEverseursO").toDouble(),
                                              getMapListeRapport(listePairesRapport, dernierTest).value("fmaxEverseursO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxEverseursO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxEverseursNO").toDouble(),
                                      getMapListeRapport(listePairesRapport, dernierTest).value("fmaxEverseursO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax Inverseurs
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Inverseurs (N)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxInverseursNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxInverseursO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxInverseursNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxInverseursO") + "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxInverseursNO").toDouble(),
                                                                 getMapListeRapport(listePairesRapport, dernierTest).value("fmaxInverseursNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxInverseursNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxInverseursO").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("fmaxInverseursO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("fmaxInverseursO")
                              + texteEvolution + "</td>" ;
    }

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("fmaxInverseursNO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxInverseursO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";


    // 3e row - Ratio
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th style=\"background-color:#e8e8e9; color:#002e40; border:1px solid rgb(160,160,160); padding:8px 10px;\" scope=\"row\">Ratio</th>";
;

    QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxEverseursNO").toDouble(),
                                                       getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxInverseursNO").toDouble(),
                                                       "ratioEI");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxEverseursO").toDouble(),
                               getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("fmaxInverseursO").toDouble(),
                               "ratioEI");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);
        if(tailleListeFaits == 3){

            //Membre sain T2
            QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxEverseursNO").toDouble()
                                                               ,getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxInverseursNO").toDouble(),
                                                               "ratioEI");

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + paireRatio.second + "</td>";

            // Membre opéré T2
            paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxEverseursO").toDouble(),
                                       getMapListeRapport(listePairesRapport, avantDernierTest).value("fmaxInverseursO").toDouble(),
                                       "ratioEI");

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + paireRatio.second + "</td>";
        }

        //Membre sain TLast
        QPair<QString, QString> paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("fmaxEverseursNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("fmaxInverseursNO").toDouble(),
                                                           "ratioEI");

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

        // Membre opéré TLast
        paireRatio = getPaireRatio(getMapListeRapport(listePairesRapport, dernierTest).value("fmaxEverseursO").toDouble(),
                                    getMapListeRapport(listePairesRapport, dernierTest).value("fmaxInverseursO").toDouble(),
                                   "ratioEI");

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + paireRatio.second + "</td>";

    }

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireRatioVerseursBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QString couleurCourante;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxEverseurs" << "fmaxInverseurs";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">Ratio Everseurs / Inverseurs</th>";

    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre G</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Membre D</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Asymétrie</th>";

    // 1ere row - FMax Everseurs
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Everseurs (N)</th>"
                                                "<td>" + mapCourante.value("fmaxEverseursG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxEverseursD") + "</td>";
    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxEverseursG").toDouble(),
                                                                    mapCourante.value("fmaxEverseursD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax Inverseurs
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Inverseurs (N)</th>"
                                                "<td>" + mapCourante.value("fmaxInverseursG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxInverseursD") + "</td>";


    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxInverseursG").toDouble(),
                                    mapCourante.value("fmaxInverseursD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";


    // 3e row - Ratio
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th style=\"background-color:#e8e8e9; color:#002e40; border:1px solid rgb(160,160,160); padding:8px 10px;\" scope=\"row\">Ratio</th>";
;

    QPair<QString, QString> paireRatio = getPaireRatio(mapCourante.value("fmaxEverseursG").toDouble(),
                                                       mapCourante.value("fmaxInverseursG").toDouble(),
                                                       "ratioEI");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    paireRatio = getPaireRatio(mapCourante.value("fmaxEverseursD").toDouble(),
                               mapCourante.value("fmaxInverseursD").toDouble(),
                               "ratioEI");

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireRatio.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireRatio.second + "</td>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireAlrRsi(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "alrRsi";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.size();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits== 0){
        return "";
    }

    texteTableauCourant.append("<table><tr>");
    listeColonnesTab << "";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "T" + numeroTestFait;
    }

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\" style=\"background-color:#fdfefe; color:#002e40;\"></th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Test ALR-RSI</th>";

    couleurCourante = getCouleurACLRsi(getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("alrRsi").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurCourante + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("alrRsi") + "/100</td>";

    if(tailleListeFaits > 1){

        // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if (tailleListeFaits > 2) {
            couleurCourante = getCouleurACLRsi(getMapListeRapport(listePairesRapport, avantDernierTest).value("alrRsi").toDouble());

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurCourante + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                  + getMapListeRapport(listePairesRapport, avantDernierTest).value("alrRsi") + "/100</td>";
        }

        couleurCourante = getCouleurACLRsi(getMapListeRapport(listePairesRapport, dernierTest).value("alrRsi").toDouble());

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurCourante + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + getMapListeRapport(listePairesRapport, dernierTest).value("alrRsi") + "/100</td>";
    }
    texteTableauCourant.append("</tr></table>");

    return texteTableauCourant;
}



//****************************************
QString MainWindow::ecrireSautsRepetes(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "forceMoyenneSR" << "hauteurMoyenneSR" << "pMoyenneSR" << "rsiMoyenSR";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test de Sauts Repetes 10-5" <<  "Hauteur moyenne (cm)" << "RSI moyen" << "% Repartition des forces";
    for (int i = 0; i < listeColonnesTab.count(); ++i) {
        if(i==0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    //T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T"+listeTestFaits.first()+"</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("hauteurMoyenneSR") + "</td>";

    QString couleurRsi = getCouleurSautsRepetesRsi(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rsiMoyenSR").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurRsi + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("rsiMoyenSR") + "</td>";

    //Ecrire tableau pourcentage force
    texteTableauCourant.append("<td>");

    texteTableauCourant.append("<table class=\"tableSansMargin\"><tr>");

    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">sain</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">"+ labelBlessure+ "</th>";

    QString couleurPourcentage = getCouleurPourcentageForce(getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("forceMoyenneSRNO").toDouble(),
                                                            getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("forceMoyenneSRO").toDouble());

    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>";

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurPourcentage + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("forceMoyenneSRNO") + "%</td>";

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurPourcentage + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("forceMoyenneSRO") + "%</td>";

    texteTableauCourant.append("</tr></table></td>");

    // T2
    if(tailleListeFaits > 1 ){

        QString dernierTest = listeTestFaits.last();
        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);

        if(tailleListeFaits == 3){

            //T2
            texteTableauCourant = texteTableauCourant + "</tr>"
                                                        "<tr>"
                                                        "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T" + avantDernierTest+"</th>"
                                                         "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurMoyenneSR") + "</td>"
                                                         "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("pMoyenneSR") + "</td>";

            QString couleurRsi = getCouleurSautsRepetesRsi(getMapListeRapport(listePairesRapport, avantDernierTest).value("rsiMoyenSR").toDouble());

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurRsi + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                        getMapListeRapport(listePairesRapport, avantDernierTest).value("rsiMoyenSR") + "</td>";

            //Ecrire tableau pourcentage force
            texteTableauCourant.append("<td>");
            texteTableauCourant.append("<table class=\"tableSansMargin\"><tr>");

            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">sain</th>";
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">"+ labelBlessure+ "</th>";

            QString couleurPourcentage = getCouleurPourcentageForce(getMapListeRapport(listePairesRapport, avantDernierTest).value("forceMoyenneSRNO").toDouble(),
                                                                    getMapListeRapport(listePairesRapport, avantDernierTest).value("forceMoyenneSRO").toDouble());

            texteTableauCourant = texteTableauCourant + "</tr>"
                                                        "<tr>";

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurPourcentage + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                        getMapListeRapport(listePairesRapport, avantDernierTest).value("forceMoyenneSRNO") + "%</td>";

            texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurPourcentage + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                        getMapListeRapport(listePairesRapport, avantDernierTest).value("forceMoyenneSRO") + "%</td>";

            texteTableauCourant.append("</tr></table></td>");
        }

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>"
                                                    "<th scope=\"row\" style=\"background-color:#d7dbdd;color:#002e40;border:1px solid #023448;\">T" + dernierTest + "</th>";

        // hauteur saut
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("hauteurMoyenneSR").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("hauteurMoyenneSR").toDouble());

        QString texteEvolution = "<span style=\"color:" + prog.second + ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("hauteurMoyenneSR")
                              + texteEvolution + "</td>" ;
        // pMoyenneSR sain
        prog = getProgressionPourcentage(false,getMapListeRapport(listePairesRapport, avantDernierTest).value("pMoyenneSR").toDouble(),
                                         getMapListeRapport(listePairesRapport, dernierTest).value("pMoyenneSR").toDouble());

        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("pMoyenneSR")
                              + texteEvolution + "</td>" ;

        // RSI
        QString couleurRsi = getCouleurSautsRepetesRsi(getMapListeRapport(listePairesRapport,dernierTest).value("rsiMoyenSR").toDouble());

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurRsi + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                    getMapListeRapport(listePairesRapport,dernierTest).value("rsiMoyenSR") + "</td>";

        //Ecrire tableau pourcentage force
        texteTableauCourant.append("<td>");
        texteTableauCourant.append("<table class=\"tableSansMargin\"><tr>");

        texteTableauCourant= texteTableauCourant + " <th scope=\"col\">sain</th>";
        texteTableauCourant= texteTableauCourant + " <th scope=\"col\">"+ labelBlessure+ "</th>";
        QString couleurPourcentage = getCouleurPourcentageForce(getMapListeRapport(listePairesRapport, dernierTest).value("forceMoyenneSRNO").toDouble(),
                                                                getMapListeRapport(listePairesRapport, dernierTest).value("forceMoyenneSRO").toDouble());

        texteTableauCourant = texteTableauCourant + "</tr>"
                                                    "<tr>";

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurPourcentage + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                    getMapListeRapport(listePairesRapport, dernierTest).value("forceMoyenneSRNO") + "%</td>";

        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurPourcentage + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                    getMapListeRapport(listePairesRapport, dernierTest).value("forceMoyenneSRO") + "%</td>";

        texteTableauCourant.append("</tr></table></td>");
    }

    texteTableauCourant.append("</table>");

    //DYSPLAYZ
    QString cheminImageScore =  QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "scoresSautesRepetes");
    // On génère une version HD pour éviter la pixellisation
    cheminImageScore = redimensionnerImage(cheminImageScore, 1000);

    // Image à droite du tableau
    texteTableauCourant = encadrerTableauEtImageFlexible(texteTableauCourant, cheminImageScore, "bottom", 400, 300);

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireSautsRepetesBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "forceMoyenneSR" << "hauteurMoyenneSR" << "rsiMoyenSR";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test de Sauts Repetes 10-5" <<  "Hauteur moyenne (cm)" << "RSI moyen" << "% Repartition des forces";
    for (int i = 0; i < listeColonnesTab.count(); ++i) {
        if(i==0){
            texteTableauCourant= texteTableauCourant + "<th style=\"border: 0px;\"></th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    //T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Test de Sauts Repetes 10-5</th>"
                                                "<td>" + mapCourante.value("hauteurMoyenneSR") + "</td>";

    QString couleurRsi = getCouleurSautsRepetesRsi(mapCourante.value("rsiMoyenSR").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurRsi + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                mapCourante.value("rsiMoyenSR") + "</td>";

    //Ecrire tableau pourcentage force
    texteTableauCourant.append("<td>");

    texteTableauCourant.append("<table class=\"tableSansMargin\"><tr>");

    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">G</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">D</th>";

    QString couleurPourcentage = getCouleurPourcentageForce(mapCourante.value("forceMoyenneSRG").toDouble(),
                                                            mapCourante.value("forceMoyenneSRD").toDouble());

    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>";

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurPourcentage + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                mapCourante.value("forceMoyenneSRG") + "%</td>";

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + couleurPourcentage + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                                mapCourante.value("forceMoyenneSRD") + "%</td>";

    texteTableauCourant.append("</tr></table></td>");

    texteTableauCourant.append("</table>");

    //DYSPLAYZ
    QString cheminImageScore =  QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "scoresSautesRepetes");
    // On génère une version HD pour éviter la pixellisation
    cheminImageScore = redimensionnerImage(cheminImageScore, 1000);

    // Image à droite du tableau
    texteTableauCourant = encadrerTableauEtImageFlexible(texteTableauCourant, cheminImageScore, "bottom", 400, 300);

    return texteTableauCourant;
}
//****************************************
QString MainWindow::ecrireSLIHRH(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceTH";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire texte explicatif du test
    texteTableauCourant.append("<p style=\"text-align: justify;\">*Hauteur maximale obtenue entre le sol et le talon"
                               " lors d’une montée en pointe des pieds à une jambe maintenue pendant 10 secondes.</p>");

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Single Leg Isometric Heel Raise Hold *";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    QString dernierTest = listeTestFaits.last();

    // 1ere row - Distance saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Distance sol-talon(cm)</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("flexionSLIHRHNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("flexionSLIHRHO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);
        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionSLIHRHNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionSLIHRHO")+ "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionSLIHRHNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("flexionSLIHRHNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionSLIHRHNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("cm",getMapListeRapport(listePairesRapport, avantDernierTest).value("flexionSLIHRHO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("flexionSLIHRHO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("flexionSLIHRHO")
                              + texteEvolution + "</td>" ;
    }

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("flexionSLIHRHNO").toDouble(),
                                                              getMapListeRapport(listePairesRapport, dernierTest).value("flexionSLIHRHO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireHeelRise(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceTH";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire texte explicatif du test
    texteTableauCourant.append("<p style=\"text-align: justify;\">*Nombre maximal de répétitions de montée en pointe à une seule jambe "
                               "obtenu sans compensations (flexion de genou, perte d’amplitude, pause au sol).</p>");

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Heel Rise Test *";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    QString dernierTest = listeTestFaits.last();

    // 1ere row - Distance saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Nombre de répétitions maximales</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("nombreRepHeelNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("nombreRepHeelO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);
        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("nombreRepHeelNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("nombreRepHeelO")+ "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("",getMapListeRapport(listePairesRapport, avantDernierTest).value("nombreRepHeelNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("nombreRepHeelNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("nombreRepHeelNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("",getMapListeRapport(listePairesRapport, avantDernierTest).value("nombreRepHeelO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("nombreRepHeelO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("nombreRepHeelO")
                              + texteEvolution + "</td>" ;
    }

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("nombreRepHeelNO").toDouble(),
                                                              getMapListeRapport(listePairesRapport, dernierTest).value("nombreRepHeelO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");


    //DYSPLAYZ
    QString cheminImageScore =  QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "scoresHeelRise");
    // On génère une version HD pour éviter la pixellisation
    cheminImageScore = redimensionnerImage(cheminImageScore, 1000);

    // Image à droite du tableau
    texteTableauCourant = encadrerTableauEtImageFlexible(texteTableauCourant, cheminImageScore, "bottom", 400, 300);

    return texteTableauCourant;
}


//****************************************
QString MainWindow::ecrireFootLift(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QString couleurCourante;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "nombreErreurFL";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    // Ecrire texte explicatif du test
    texteTableauCourant.append("<p style=\"text-align: justify;\">*Patient en équilibre unipodal, mains sur les hanches et les yeux fermés pendant 30 secondes,"
                               " on note le nombre d’ « erreurs » (pertes d’équilibre, décoller le gros orteil, enlever une main des hanches, toucher le deuxième"
                               " pied au sol, ouvrir les yeux) durant le temps du test.</p>");

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Foot Lift Test *";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    QString dernierTest = listeTestFaits.last();

    // 1ere row - Distance saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Nombre d'erreurs</th>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("nombreErreurFLNO") + "</td>"
                                                "<td>" + getMapListeRapport(listePairesRapport, listeTestFaits.first()).value("nombreErreurFLO") + "</td>";
    if(tailleListeFaits > 1){

        QString avantDernierTest = listeTestFaits.at(listeTestFaits.indexOf(listeTestFaits.last()) - 1);
        if(tailleListeFaits == 3){

            //Membre sain T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("nombreErreurFLNO") + "</td>" ;

            // Membre opéré T2
            texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, avantDernierTest).value("nombreErreurFLO")+ "</td>" ;
        }

        //Membre sain TLast
        QPair<QString, QString> prog = calculerProgression("",getMapListeRapport(listePairesRapport, avantDernierTest).value("nombreErreurFLNO").toDouble(),
                                                           getMapListeRapport(listePairesRapport, dernierTest).value("nombreErreurFLNO").toDouble());


        QString texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("nombreErreurFLNO")
                              + texteEvolution + "</td>" ;

        // Membre opéré TLast
        prog = calculerProgression("",getMapListeRapport(listePairesRapport, avantDernierTest).value("nombreErreurFLO").toDouble(),
                                   getMapListeRapport(listePairesRapport, dernierTest).value("nombreErreurFLO").toDouble());


        texteEvolution = "<span style=\"color:" + prog.second+ ";\"> " + prog.first + "</span>";
        texteTableauCourant = texteTableauCourant + "<td>" + getMapListeRapport(listePairesRapport, dernierTest).value("nombreErreurFLO")
                              + texteEvolution + "</td>" ;
    }

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, getMapListeRapport(listePairesRapport, dernierTest).value("nombreErreurFLNO").toDouble(),
                                                              getMapListeRapport(listePairesRapport, dernierTest).value("nombreErreurFLO").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireYBalance(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeTestFaits;
    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceA" << "distancePM" << "distancePM";

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        if(doitEtreEcrit(listeCaracteresCol, getMapListeRapport(listePairesRapport, QString::number(i+1)))){
            listeTestFaits.append(QString::number(i+1));
        }
    }

    int tailleListeFaits = listeTestFaits.count();

    //Si il n y a le bilan que d un seul test fait et que les amplitudes n ont pas ete ecrites, le tableau n existe pas
    if(tailleListeFaits == 0){
        return "";
    }

    texteTableauCourant.append(
        "<p style=\"text-align: justify;\">"
        "* Patient en appui sur le pied du membre inférieur testé avec les mains sur les hanches, "
        "le centre du pied au niveau du croisement des branches du Y. "
        "Amener un gobelet (ou autre objet léger) le plus loin possible sur chacune des branches du Y "
        "avec le pied libre, répéter l’opération avec l’autre jambe."
        "<br>"
        "L’essai est invalidé si :"
        "<ul>"
        "<li>mouvement du pied d’appui ou talon qui se décolle</li>"
        "<li>transfert de poids sur la deuxième jambe par déséquilibre</li>"
        "<li>lever une main des hanches</li>"
        "</ul>"
        "</p><br />"
    );

    //Ecrire les branches du test
    QString suffixeDroit;
    QString suffixeGauche;
    QString labelDroit;
    QString labelGauche;

    // Si le bras droit est opere alors on prend les bonnes informations
    if(getMapListeRapport(listePairesRapport,listeTestFaits.first()).value("chevilleOperee") == "Droite"){
        suffixeDroit = "O";
        suffixeGauche = "NO";
        labelDroit = labelBlessure;
        labelGauche = "sain";
    }
    else{
        suffixeDroit = "NO";
        suffixeGauche = "O";
        labelDroit = "sain";
        labelGauche = labelBlessure;
    }

    // Ecrire le T1
    texteTableauCourant.append(dessinerTestYBalance(listePairesRapport,suffixeDroit, suffixeGauche, labelDroit,
                                              labelGauche,listeTestFaits.last()));

    // Ecrire le tableau du test
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test Y-Balance*";

    foreach (QString numeroTestFait, listeTestFaits) {
        listeColonnesTab << "Membre sain T" + numeroTestFait;
        listeColonnesTab << "Membre " + labelBlessure + " T" + numeroTestFait;
    }

    listeColonnesTab << "Asymétrie T" + listeTestFaits.last();

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else if(listeColonnesTab.at(i).contains(labelBlessure)){
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\"style=\"background-color:#e2edf1; color:#002e40;border:1px solid #023448\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }
    // Recuperer dernier T et avant dernier T => Seront toujours dernier et avant dernier de la liste listeTestFaits
    QString dernierTest = listeTestFaits.last();

    auto getValeur = [&](const QString &test, const QString &key) -> QString {
        return getMapListeRapport(listePairesRapport, test).value(key);
    };

    // =====================
    // DISTANCE SUPÉRO-LATÉRALE
    // =====================
    texteTableauCourant += "<tr><th scope=\"row\">Distance antérieure (cm)</th>";
    for(int i = 0; i < listeTestFaits.size(); ++i){
        QString test = listeTestFaits.at(i);
        QString valeur = getValeur(test, "distanceANO");
        QString texteCellule = valeur;

        // Progression (si pas le premier test)
        if(i > 0){
            QPair<QString, QString> prog = calculerProgression("cm",
                getValeur(listeTestFaits.at(i-1), "distanceANO").toDouble(),
                valeur.toDouble()
            );
            texteCellule += "<span style=\"color:" + prog.second + ";\"> " + prog.first + "</span>";
        }
        texteTableauCourant += "<td>" + texteCellule + "</td>";
    }

    // Même chose pour membre opéré
    for(int i = 0; i < listeTestFaits.size(); ++i){
        QString test = listeTestFaits.at(i);
        QString valeur = getValeur(test, "distanceAO");
        QString texteCellule = valeur;

        if(i > 0){
            QPair<QString, QString> prog = calculerProgression("cm",
                getValeur(listeTestFaits.at(i-1), "distanceAO").toDouble(),
                valeur.toDouble()
            );
            texteCellule += "<span style=\"color:" + prog.second + ";\"> " + prog.first + "</span>";
        }
        texteTableauCourant += "<td>" + texteCellule + "</td>";
    }

    // Asymétrie finale (dernier test uniquement)
    {
        QString dernierTest = listeTestFaits.last();
        QPair<QString, QString> paire = getPaireAsymetrie(false,
            getValeur(dernierTest, "distanceANO").toDouble(),
            getValeur(dernierTest, "distanceAO").toDouble()
        );
        texteTableauCourant += "<td style=\"background-color:" + paire.first +
                               "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                               paire.second + "</td>";
    }
    texteTableauCourant += "</tr>";

    // =====================
    //  DISTANCE
    // =====================
    texteTableauCourant += "<tr><th scope=\"row\">Distance postéro-médiale (cm)</th>";
    for(int i = 0; i < listeTestFaits.size(); ++i){
        QString test = listeTestFaits.at(i);
        QString valeur = getValeur(test, "distancePMNO");
        QString texteCellule = valeur;

        if(i > 0){
            QPair<QString, QString> prog = calculerProgression("cm",
                getValeur(listeTestFaits.at(i-1), "distancePMNO").toDouble(),
                valeur.toDouble()
            );
            texteCellule += "<span style=\"color:" + prog.second + ";\"> " + prog.first + "</span>";
        }
        texteTableauCourant += "<td>" + texteCellule + "</td>";
    }

    for(int i = 0; i < listeTestFaits.size(); ++i){
        QString test = listeTestFaits.at(i);
        QString valeur = getValeur(test, "distancePMO");
        QString texteCellule = valeur;

        if(i > 0){
            QPair<QString, QString> prog = calculerProgression("cm",
                getValeur(listeTestFaits.at(i-1), "distancePMO").toDouble(),
                valeur.toDouble()
            );
            texteCellule += "<span style=\"color:" + prog.second + ";\"> " + prog.first + "</span>";
        }
        texteTableauCourant += "<td>" + texteCellule + "</td>";
    }

    // Asymétrie finale
    {
        QString dernierTest = listeTestFaits.last();
        QPair<QString, QString> paire = getPaireAsymetrie(false,
            getValeur(dernierTest, "distancePMNO").toDouble(),
            getValeur(dernierTest, "distancePMO").toDouble()
        );
        texteTableauCourant += "<td style=\"background-color:" + paire.first +
                               "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                               paire.second + "</td>";
    }
    texteTableauCourant += "</tr>";

    // =====================
    // DISTANCE
    // =====================
    texteTableauCourant += "<tr><th scope=\"row\">Distance Postéro-latérale (cm)</th>";
    for(int i = 0; i < listeTestFaits.size(); ++i){
        QString test = listeTestFaits.at(i);
        QString valeur = getValeur(test, "distancePLNO");
        QString texteCellule = valeur;

        if(i > 0){
            QPair<QString, QString> prog = calculerProgression("cm",
                getValeur(listeTestFaits.at(i-1), "distancePLNO").toDouble(),
                valeur.toDouble()
            );
            texteCellule += "<span style=\"color:" + prog.second + ";\"> " + prog.first + "</span>";
        }
        texteTableauCourant += "<td>" + texteCellule + "</td>";
    }

    for(int i = 0; i < listeTestFaits.size(); ++i){
        QString test = listeTestFaits.at(i);
        QString valeur = getValeur(test, "distancePLO");
        QString texteCellule = valeur;

        if(i > 0){
            QPair<QString, QString> prog = calculerProgression("cm",
                getValeur(listeTestFaits.at(i-1), "distancePLO").toDouble(),
                valeur.toDouble()
            );
            texteCellule += "<span style=\"color:" + prog.second + ";\"> " + prog.first + "</span>";
        }
        texteTableauCourant += "<td>" + texteCellule + "</td>";
    }

    // Asymétrie finale
    {
        QString dernierTest = listeTestFaits.last();
        QPair<QString, QString> paire = getPaireAsymetrie(false,
            getValeur(dernierTest, "distancePLNO").toDouble(),
            getValeur(dernierTest, "distancePLO").toDouble()
        );
        texteTableauCourant += "<td style=\"background-color:" + paire.first +
                               "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                               paire.second + "</td>";
    }
    texteTableauCourant += "</tr>";

    // =====================
    // LIMB SYMMETRY INDEX (LSI)
    // =====================
    texteTableauCourant += "<tr><th scope=\"row\">Limb Symmetry Index* (%)</th>";
    for(int i = 0; i < listeTestFaits.size(); ++i){
        QString test = listeTestFaits.at(i);
        QPair<QString, QString> paireLSI = getPaireLSI(
            getValeur(test, "distanceANO").toDouble(),
            getValeur(test, "distancePMNO").toDouble(),
            getValeur(test, "distancePLNO").toDouble(),
            getValeur(listeTestFaits.first(), "longueurMI").toDouble()
        );

        texteTableauCourant += "<td style=\"background-color:" + paireLSI.first +
                               "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                               paireLSI.second + "%</td>";
    }

    for(int i = 0; i < listeTestFaits.size(); ++i){
        QString test = listeTestFaits.at(i);
        QPair<QString, QString> paireLSI = getPaireLSI(
            getValeur(test, "distanceAO").toDouble(),
            getValeur(test, "distancePMO").toDouble(),
            getValeur(test, "distancePLO").toDouble(),
            getValeur(listeTestFaits.first(), "longueurMI").toDouble()
        );

        texteTableauCourant += "<td style=\"background-color:" + paireLSI.first +
                               "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">" +
                               paireLSI.second + "%</td>";
    }
    texteTableauCourant += "</tr>";

    texteTableauCourant.append("</table>");
    texteTableauCourant.append("<p style=\"margin-bottom:35px; text-align: justify;\">* LSI = [ sommes des trois distances / (3 x longueur du membre inférieur (distance EIAS - malléole interne)) ) ]</p>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireHeelRiseBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "nombreRepHeel";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire texte explicatif du test
    texteTableauCourant.append("<p style=\"text-align: justify;\">*Nombre maximal de répétitions de montée en pointe à une seule jambe "
                               "obtenu sans compensations (flexion de genou, perte d’amplitude, pause au sol).</p>");

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Heel Rise Test *"
                     << "Membre G"
                     << "Membre D"
                     << "Asymétrie";

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row - Distance saut (cm)
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">Nombre de répétitions maximales</th>"
                                                "<td>" + mapCourante.value("nombreRepHeelG") + "</td>"
                                                "<td>" + mapCourante.value("nombreRepHeelD") + "</td>";

    //Asymetrie
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("nombreRepHeelG").toDouble(),
                                                              mapCourante.value("nombreRepHeelD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");


    //DYSPLAYZ
    QString cheminImageScore =  QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "scoresHeelRise");
    // On génère une version HD pour éviter la pixellisation
    cheminImageScore = redimensionnerImage(cheminImageScore, 1000);

    // Image à droite du tableau
    texteTableauCourant = encadrerTableauEtImageFlexible(texteTableauCourant, cheminImageScore, "bottom", 400, 300);
    return texteTableauCourant;
}



//****************************************
QString MainWindow::ecrireFmaxBS(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString poids){

    QString texteTableauCourant;

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    QStringList listeCaracteresCol;

    bool estEcrit = false;

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">RM Back Squat</th>";
    texteTableauCourant= texteTableauCourant + " <th scope=\"col\">Poids (kg)</th>";

    // 1ere row - FMax Ischios
    //Membre sain T1 - Membre opere T1
    listeCaracteresCol.clear();
    listeCaracteresCol << "unRMBS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;

        texteTableauCourant = texteTableauCourant + "</tr>"
                            "<tr>"
                            "<th scope=\"row\">1 RM</th>"
                            "<td>" + mapCourante.value("unRMBS") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "troisRMBS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant = texteTableauCourant + "</tr>"
                            "<tr>"
                            "<th scope=\"row\">3 RM</th>"
                            "<td>" + mapCourante.value("troisRMBS") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "cinqRMBS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant = texteTableauCourant + "</tr>"
                            "<tr>"
                            "<th scope=\"row\">5 RM</th>"
                            "<td>" + mapCourante.value("cinqRMBS") + "</td>";
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "unRMBS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;

        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\"></th>"
                                    "<th scope=\"row\"></th>"
                                    "</tr>");

        texteTableauCourant = texteTableauCourant + "</tr>"
                            "<tr>"
                            "<th scope=\"row\">Ratio 1RM/Poids</th>";
        QString  valeurCourante = QString::number( mapCourante.value("unRMBS", "-").toFloat() / poids.toFloat(), 'f', 2);
        texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + getCouleurScoreBS(mapCourante.value("unRMBS", "-").toFloat() / poids.toFloat(), poids.toInt()) + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                              + valeurCourante + "</td></tr>";
    }

    texteTableauCourant.append("</table>");

    if(!estEcrit)
    {
        return "";
    }

    // //Display
    QString cheminImageScore =  QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "BS");
    cheminImageScore = redimensionnerImage(cheminImageScore, 400);

    // On génère une version HD pour éviter la pixellisation
    cheminImageScore = redimensionnerImage(cheminImageScore, 1000);

    // Image à droite du tableau
    texteTableauCourant += encadrerTableauEtImageFlexible(texteTableauCourant,
                                                         cheminImageScore,
                                                         "right", 400, 300);
    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireFmaxPL(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString poids){

    QString texteTableauCourant;

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    QStringList listeCaracteresCol;

    bool estEcrit = false;

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    // Ligne d’en-tête
    texteTableauCourant.append("<tr>"
                            "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Exercice</th>"
                            "<th scope=\"col\">1 RM (kg)</th>"
                            "<th scope=\"col\">3 RM (kg)</th>"
                            "<th scope=\"col\">5 RM (kg)</th>"
                            "<th scope=\"col\">Ratio 1RM/Poids</th>"
                            "</tr>");

    // Ligne Back Squat
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMBS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                "<th scope=\"row\">Back Squat (kg)</th>"
                                "<td>" + mapCourante.value("unRMBS") + "</td>"
                                "<td>" + mapCourante.value("troisRMBS") + "</td>"
                                "<td>" + mapCourante.value("cinqRMBS") + "</td>"
                                "<td>" + QString::number( mapCourante.value("unRMBS", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                "</tr>");
    }

    // Ligne Deadlift
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMDL";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Deadlift (kg)</th>"
                                   "<td>" + mapCourante.value("unRMDL") + "</td>"
                                    "<td>" + mapCourante.value("troisRMDL") + "</td>"
                                    "<td>" + mapCourante.value("cinqRMDL") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMDL", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    // Ligne Hip Thrust
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMHT";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Hip Thrust (kg)</th>"
                                    "<td>" + mapCourante.value("unRMHT") + "</td>"
                                    "<td>" + mapCourante.value("troisRMHT") + "</td>"
                                    "<td>" + mapCourante.value("cinqRMHT") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMHT", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }

    texteTableauCourant.append("</table>");

    if(!estEcrit)
    {
        return "";
    }

    //TODO
    // QString cheminImageScoreBS =  QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "BS");
    // cheminImageScoreBS = redimensionnerImage(cheminImageScoreBS, 300);

    // texteTableauCourant = texteTableauCourant + "<div style=\"text-align: center;\"><img src=" + cheminImageScoreBS  + "></div>";


    return texteTableauCourant;
}


//****************************************
QString MainWindow::ecrireTestFmaxBPF(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString poids){

    QString texteTableauCourant;

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    QStringList listeCaracteresCol;

    bool estEcrit = false;

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    texteTableauCourant.append("<tr>"
                            "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Exercice</th>"
                            "<th scope=\"col\">1 RM (kg)</th>"
                            "<th scope=\"col\">3 RM (kg)</th>"
                            "<th scope=\"col\">5 RM (kg)</th>"
                            "<th scope=\"col\">Ratio 1RM/Poids</th>"
                            "</tr>");

    listeCaracteresCol.clear();
    listeCaracteresCol << "RMBP";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Bench Press</th>"
                                    "<td>" + mapCourante.value("unRMBP") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMBP", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "RMTP";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Seal Row</th>"
                                    "<td>" + mapCourante.value("unRMTP") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMTP", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMBS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Back Squat</th>"
                                    "<td>" + mapCourante.value("unRMBS") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMBS", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMDL";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Deadlift</th>"
                                    "<td>" + mapCourante.value("unRMDL") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMDL", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMCJ";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Clean & Jerk</th>"
                                    "<td>" + mapCourante.value("unRMCJ") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMCJ", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Snatch</th>"
                                    "<td>" + mapCourante.value("unRMS") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMS", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    if(!estEcrit)
        {
            return "";
        }

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}


//****************************************
QString MainWindow::ecrireTestFmaxBPCF(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString poids){

    QString texteTableauCourant;

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    QStringList listeCaracteresCol;

    bool estEcrit = false;

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    texteTableauCourant.append("<tr>"
                            "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Exercice</th>"
                            "<th scope=\"col\">1 RM (kg)</th>"
                            "<th scope=\"col\">Ratio 1RM/Poids</th>"
                            "</tr>");

    listeCaracteresCol.clear();
    listeCaracteresCol << "RMBP";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Strict Press</th>"
                                    "<td>" + mapCourante.value("unRMSP") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMSP", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMBP";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Bench Press</th>"
                                    "<td>" + mapCourante.value("unRMBP") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMBP", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }

    listeCaracteresCol.clear();
    listeCaracteresCol << "RMTP";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                   "<th scope=\"row\">Seal Row</th>"
                                    "<td>" + mapCourante.value("unRMTP") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMTP", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMBS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Back Squat</th>"
                                    "<td>" + mapCourante.value("unRMBS") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMBS", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMFS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Front Squat</th>"
                                    "<td>" + mapCourante.value("unRMFS") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMFS", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMDL";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Deadlift</th>"
                                    "<td>" + mapCourante.value("unRMDL") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMDL", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMC";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Clean</th>"
                                    "<td>" + mapCourante.value("unRMC") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMC", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMJ";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Jerk</th>"
                                    "<td>" + mapCourante.value("unRMJ") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMJ", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Snatch</th>"
                                    "<td>" + mapCourante.value("unRMS") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMS", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMSB";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Snatch Balance</th>"
                                    "<td>" + mapCourante.value("unRMBS") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMSB", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }
    listeCaracteresCol.clear();
    listeCaracteresCol << "RMOS";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Overhead Squat</th>"
                                    "<td>" + mapCourante.value("unRMOS") + "</td>"
                                    "<td>" + QString::number( mapCourante.value("unRMOS", "-").toFloat() / poids.toFloat(), 'f', 2) + "</td>"
                                    "</tr>");
    }

    texteTableauCourant.append("<tr>"
                                "<th scope=\"row\"></th>"
                                "<th scope=\"row\"></th>"
                                "<th scope=\"row\"></th>"
                                "</tr>");

    listeCaracteresCol.clear();
    listeCaracteresCol << "maxPU";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant.append("<tr>"
                                    "<th scope=\"row\">Max rep Pull-up</th>"
                                   "<td colspan=\"2\">" + mapCourante.value("maxPU") + "</td>"
                                    "</tr>");
    }

    if(!estEcrit)
    {
        return "";
    }
    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireProfilFVV(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    QStringList listeCaracteresCol;
    listeCaracteresCol << "fZeroFV" << "vZeroFV" << "vZeroFV";

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    texteTableauCourant += "<h1 style=\"text-align: left; margin-bottom: 30px;\">Profil Force / Vitesse Vertical</h1>";

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    // En-têtes des lignes (deviennent la première colonne)
    texteTableauCourant.append("<tr>"
                                "<th scope=\"row\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Profil Force / Vitesse Vertical</th>"
                                "<th scope=\"row\">Valeurs mesurées</th>"
                                "</tr>");

    // F₀
    texteTableauCourant.append("<tr>"
                                "<th scope=\"col\">F₀ (N)</th>"
                                "<td>" + mapCourante.value("fZeroFV", "-") + "</td>"
                                "</tr>");

    // V₀
    texteTableauCourant.append("<tr>"
                                "<th scope=\"col\">V₀ (m/s)</th>"
                                "<td>" + mapCourante.value("vZeroFV", "-") + "</td>"
                                "</tr>");

    // Pmax
    texteTableauCourant.append("<tr>"
                                "<th scope=\"col\">Pmax (W)</th>"
                                "<td>" + mapCourante.value("pMaxFV", "-") + "</td>"
                                "</tr>");

    // Asymétrie
    texteTableauCourant.append("<tr>"
                                "<th scope=\"col\">Asymétrie (%)</th>"
                                "<td>" + mapCourante.value("asymetrieFV", "-") + "</td>"
                                "</tr>");

    texteTableauCourant.append("</table>");

    //DiSPLAYZ
    QString cheminImageScore =  QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "profilFVV");
    // On génère une version HD pour éviter la pixellisation
    cheminImageScore = redimensionnerImage(cheminImageScore, 1000);

    // Image à droite du tableau
    texteTableauCourant = encadrerTableauEtImageFlexible(texteTableauCourant, cheminImageScore, "right", 400, 300);

    //Courbe FVV
    if(mapCheminsImages.values().contains("PFVV")){

    QString cheminImageVV = redimensionnerImage(mapCheminsImages.key("PFVV"), 250);
    texteTableauCourant += "<table><tr>"
                           "<td colspan=\"2\" style=\"padding: 10px; border:0px; text-align: center; vertical-align: middle;\">"
                           "<p align=\"center\">"
                           "<img src=\"" + cheminImageVV + "\" />"
                           "</p>"
                           "</td>"
                           "</tr></table>";
    }
    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireProfilFVH(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString titreEtImage;
    QString texteTableauCourant;
    QString res;

    if(mapCheminsImages.values().contains("PFVH")){
        titreEtImage.append(ecrireAnalyseGenerique(mapCheminsImages, "", "Profil Force / Vitesse Horizontal sur 30m Sprint", "PFVH", 300, 300));
    }

    texteTableauCourant = texteTableauCourant + ecrireSprintTest(listePairesRapport);

    // Chemin et redimensionnement de l'image
    QString cheminImageScore = QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "FVH");

    // On génère une version HD pour éviter la pixellisation
    cheminImageScore = redimensionnerImage(cheminImageScore, 1000);

    // Image à droite du tableau
    texteTableauCourant = encadrerTableauEtImageFlexible(texteTableauCourant, cheminImageScore, "right", 400, 300);

    res += titreEtImage;
    res += texteTableauCourant;


    return res;
}

//****************************************
QString MainWindow::ecrireTestIYTBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;
    QStringList listeColonnesTab;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxI" << "fmaxY" << "fmaxT";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }


    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    listeColonnesTab << "Test IYT (ASH Test)"
                     << "Membre G"
                     << "Membre D"
                     << "Asymétrie";

    // Ecrire les colonnes associees
    for (int i = 0; i < listeColonnesTab.count(); ++i) {

        if(i == 0){
            texteTableauCourant = texteTableauCourant + " <th scope=\"col\" style=\"background-color: white; color:#002e40; border: 1px solid #023448;\">"
                                  + listeColonnesTab.at(i) +"</th>";
        }
        else{
            texteTableauCourant= texteTableauCourant + " <th scope=\"col\">" + listeColonnesTab.at(i) +"</th>";
        }
    }

    // 1ere row - FMax I
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax I (180°) (N)</th>"
                                                "<td>" + mapCourante.value("fmaxIG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxID") + "</td>";


    // Asymetrie TLast
    QPair<QString, QString> paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxIG").toDouble(),
                                      mapCourante.value("fmaxID").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 2e row - FMax Y
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax Y (135°) (N)</th>"
                                                "<td>" + mapCourante.value("fmaxYG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxYD") + "</td>";

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxYG").toDouble(),
                                    mapCourante.value("fmaxYD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    // 3e row - FMax T
    //Membre sain T1 - Membre opere T1
    texteTableauCourant = texteTableauCourant + "</tr>"
                                                "<tr>"
                                                "<th scope=\"row\">FMax T (90°) (N)</th>"
                                                "<td>" + mapCourante.value("fmaxTG") + "</td>"
                                                "<td>" + mapCourante.value("fmaxTD") + "</td>";

    // Asymetrie TLast
    paireCourante = getPaireAsymetrie(false, mapCourante.value("fmaxTG").toDouble(),
                                      mapCourante.value("fmaxTD").toDouble());

    texteTableauCourant = texteTableauCourant + "<td style=\"background-color:" + paireCourante.first + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                          + paireCourante.second+ "</td></tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireDSI(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    QString texteTableauCourant;

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    QStringList listeCaracteresCol;
    listeCaracteresCol << "fmaxCMJ" << "fmaxTI" << "DSI *";

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire liste des colonnes du tableau
    texteTableauCourant.append("<table><tr>");

    // En-têtes des lignes (deviennent la première colonne)
    texteTableauCourant.append("<tr>"
                                "<th scope=\"row\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Dynamic Strength Index (DSI)</th>"
                                "<th scope=\"row\">Valeurs mesurées</th>"
                                "</tr>");

    // F₀
    texteTableauCourant.append("<tr>"
                                "<th scope=\"col\">Fmax CMJ (N)</th>"
                                "<td>" + mapCourante.value("fmaxCMJ", "-") + "</td>"
                                "</tr>");

    // V₀
    texteTableauCourant.append("<tr>"
                                "<th scope=\"col\">Fmax Triage Isométrique (N)</th>"
                                "<td>" + mapCourante.value("fmaxTI", "-") + "</td>"
                                "</tr>");

    // Pmax
    texteTableauCourant.append("<tr>"
                                "<th scope=\"col\">DSI</th>"
                                "<td>" + mapCourante.value("DSI", "-") + "</td>"
                                "</tr>");

    texteTableauCourant.append("</table>");

    //DiSPLAYZ
    QString cheminImageScore =  QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "DSI");
    // On génère une version HD pour éviter la pixellisation
    cheminImageScore = redimensionnerImage(cheminImageScore, 1000);

    // Image à droite du tableau
    texteTableauCourant = encadrerTableauEtImageFlexible(texteTableauCourant, cheminImageScore, "right", 400, 300);

    return texteTableauCourant;
}
//****************************************
QString MainWindow::ecrireProfilVM(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString sexe){
    QString texteTableauCourant;

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    bool estEcrit = false ;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "proAgility" << "illinoisAgility";

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }
    texteTableauCourant.append("<table>");

    // Ligne Pro Agility
    listeCaracteresCol.clear();
    listeCaracteresCol << "proAgility";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){

        estEcrit = true;
        texteTableauCourant += "<tr>"
                                "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Pro agility 5-10-5 (s)</th>"
                                "<td style=\"background-color:" + getCouleurAgility(mapCourante.value("proAgility", "-").toDouble(), sexe)
                                + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                                + mapCourante.value("proAgility", "-")
                                + "</td>"
                                "</tr>";
    }

    // Ligne Illinois Agility
    listeCaracteresCol.clear();
    listeCaracteresCol << "illinoisAgility";
    if(doitEtreEcritAllTest(listeCaracteresCol, listePairesRapport)){
        estEcrit = true;
        texteTableauCourant += "<tr>"
                               "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Illinois agility Test (s)</th>"
                               "<td style=\"background-color:" + getCouleurIllinois(mapCourante.value("illinoisAgility", "-").toDouble(), sexe)
                               + "; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">"
                               + mapCourante.value("illinoisAgility", "-")
                               + "</td>"
                               "</tr>";
    }

    if(!estEcrit)
    {
        return "";
    }

    texteTableauCourant.append("</table>");

    this->mapCheminsImages.insert(QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "agility"), "VM");
    this->mapCheminsImages.insert(QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "illinois"), "VM");
    texteTableauCourant.append(ecrireAnalyseGenerique(mapCheminsImages, "", "", "VM", 300, 300));

    return texteTableauCourant;
}

//****************************************
QString MainWindow::ecrireSprintTest(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport) {

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");
    QString texteTableau;

    // Start table
    texteTableau.append("<table>");

    // Header row
    texteTableau += "<tr>"
                    "<th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Distance de Sprint (m)</th>"
                    "<th scope=\"col\">Temps (s)</th>"
                    "</tr>";

    // Row for 10 meters
    texteTableau += "<tr>"
                    "<th scope=\"col\">10 mètres</th>"
                    "<td>" + mapCourante.value("distanceTenMeters", "-") + "</td>"
                    "</tr>";

    // Row for 30 meters
    texteTableau += "<tr>"
                    "<th scope=\"col\">30 mètres</th>"
                    "<td>" + mapCourante.value("distanceThirtyMeters", "-") + "</td>"
                    "</tr>";

    texteTableau.append("</table>");

    return texteTableau;
}

//****************************************
QString MainWindow::ecrireMTT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    QStringList listeCaracteresCol;
    listeCaracteresCol << "MTT";

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Ecrire texte explicatif du test
    texteTableauCourant.append("<p style=\"text-align: justify;\">*Athlète assis par terre, dos au mur, lancer un médecine ball de 3kg le plus "
                               "loin possible, on mesure la distance au point de chute.</p>");

    texteTableauCourant.append("<table>");

    // Ligne Illinois Agility
    texteTableauCourant.append("<tr>"
        "<th scope=\"row\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Medball Throw Test (cm) *</th>"
        "<td>" + mapCourante.value("distanceMTT", "-") + "</td>"
        "</tr>");
    texteTableauCourant.append("</table>");

    //TODO
    QString cheminImageScore =  QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "MTT");
    cheminImageScore = redimensionnerImage(cheminImageScore, 400);

    texteTableauCourant = texteTableauCourant + "<div style=\"text-align: center;\"><img src=" + cheminImageScore  + "></div>";

    return texteTableauCourant;
}


//****************************************
QString MainWindow::ecrireNordicCurl(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){
    QString texteTableauCourant;
    QString commentaire;
    QString couleur;

    QStringList listeCaracteresCol;
    listeCaracteresCol << "distanceFreinage";

    QMap<QString, QString> mapCourante = getMapListeRapport(listePairesRapport, "1");

    if(!doitEtreEcrit(listeCaracteresCol, mapCourante)){
        return "";
    }

    // Récupérer et convertir la distance
    double distance = mapCourante.value("distanceFreinage").toDouble();

    // Déterminer la couleur et le commentaire
    if(distance > 50){
        couleur = "#169d53"; // Vert
        commentaire = "Très bon contrôle excentrique des ischios, risque de blessure lors d’un sprint amoindrit.";
    }
    else if(distance >= 40 && distance <= 49){
        couleur = "#ff9929"; // Orange
        commentaire = "Contrôle excentrique moyen, risque modéré de blessure lors d’un sprint.";
    }
    else{
        couleur = "#9f3f36"; // Rouge
        commentaire = "Contrôle excentrique insuffisant, risque accru de blessure lors d’un sprint.";
    }

    // Début du tableau
    texteTableauCourant.append("<table>");

    // Ligne 1 : Titre
    texteTableauCourant += "<tr>"
                           "<th colspan=\"1\" style=\"background-color:white; color:#002e40; padding:6px; font-weight:bold;\">Nordic Curl Test</th>"
                           "<th scope=\"col\"style=\"background-color: white; border: 0px\"></th>"
                           "</tr>";

    // Ligne 2 : Distance
    texteTableauCourant += "<tr>"
                           "<th scope=\"row\">Distance de freinage (cm)</th>"
                           "<td>" + mapCourante.value("distanceFreinage") + "</td>"
                           "</tr>";

    // Ligne 3 : Commentaire
    texteTableauCourant += "<tr>"
                           "<td colspan=\"2\" style=\"background-color:" + couleur + "; color:#002e40; padding:6px; font-weight:bold;\">" + commentaire + "</td>"
                           "</tr>";

    texteTableauCourant.append("</table>");

    return texteTableauCourant;
}


//****************************************
/*
 *
 */
QString MainWindow::ecrirePhotos(){

    QString res;

    // TEST
    QString htmlPhotos = "<h2>Photos ajoutées</h2>";
    htmlPhotos += "<table style=\"width: 100%; text-align: center; border-collapse: collapse;\">";

    int count = 0;
    htmlPhotos += "<tr>";  // Start first row

    for (const QString &chemin : this->cheminsImages) {
        htmlPhotos += "<td style=\"padding: 10px;\">";
        htmlPhotos += "<img src=\"file:///" + chemin + "\" style=\"border: 1px solid #ccc;\"><br>";
        htmlPhotos += "<span style=\"font-size: 10pt;\">" + QFileInfo(chemin).fileName() + "</span>";
        htmlPhotos += "</td>";

        count++;

        // Wrap to new row every 3 images
        if (count % 3 == 0 && count != this->cheminsImages.size()) {
            htmlPhotos += "</tr><tr>";
        }
    }

    htmlPhotos += "</tr></table>";
    res.append(htmlPhotos);
    qDebug() << res;

    return res;
}

//****************************************
QMap<QString, QString> MainWindow::getMapListeRapport(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString numeroTest){

    QMap<QString, QString> res;

    bool trouve = false;

    for (int i = 0; i < listePairesRapport.count() && !trouve; ++i) {

        QPair<QString, QMap<QString, QString>> paireCourante = listePairesRapport.at(i);

        if (paireCourante.first == numeroTest) {

            res = paireCourante.second;
            trouve = true;
        }
    }

    return res;
}


//---------------------------------------------------------
// SLOTS
//---------------------------------------------------------



void MainWindow::actionGestionPatient_clicked(){

    if(!gest->isActiveWindow()){
        gest->show();
    }
}



//****************************************
void MainWindow::on_pushButton_rechercher_clicked(){

    QString baseInfosCourante;

    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);

    // SETTINGS
    if(ui->comboBox_type_Bilan->currentText() == "Genou"){

        baseInfosCourante = "infosBilanGenou";
        ui->scrollArea->setWidget(ui->widget_genou);
        ui->widget_genou->setEnabled(false);
    }
    if(ui->comboBox_type_Bilan->currentText() == "Epaule"){
        baseInfosCourante = "infosBilanEpaule";
        ui->scrollArea->setWidget(ui->widget_epaule);
        ui->widget_epaule->setEnabled(false);
    }
    if(ui->comboBox_type_Bilan->currentText() == "Hanche"){
        baseInfosCourante = "infosBilanHanche";
        ui->scrollArea->setWidget(ui->widget_hanche);
        ui->widget_hanche->setEnabled(false);
    }
    if(ui->comboBox_type_Bilan->currentText() == "Cheville"){
        baseInfosCourante = "infosBilanCheville";
        ui->scrollArea->setWidget(ui->widget_cheville);
        ui->widget_cheville->setEnabled(false);
    }
    if(ui->comboBox_type_Bilan->currentText().contains( "Course")){
        baseInfosCourante = "infosBilanCourse";
        ui->scrollArea->setWidget(ui->widget_bpc);
        ui->widget_bpc->setEnabled(false);
    }
    if(ui->comboBox_type_Bilan->currentText().contains( "collectif")){
        baseInfosCourante = "infosBilanSportCollectif";
        ui->scrollArea->setWidget(ui->widget_bpsc);
        ui->widget_bpsc->setEnabled(false);
    }
    if(ui->comboBox_type_Bilan->currentText().contains( "Combat")){
        baseInfosCourante = "infosBilanSportCombat";
        ui->scrollArea->setWidget(ui->widget_bpf);
        ui->widget_bpf->setEnabled(false);
    }
    if(ui->comboBox_type_Bilan->currentText().contains( "Crossfit")){
        baseInfosCourante = "infosBilanCrossfit";
        ui->scrollArea->setWidget(ui->widget_bpcf);
        ui->widget_bpcf->setEnabled(false);
    }

    ui->scrollArea->setVisible(true);

    ui->comboBox_dateBilan->setEnabled(false);
    ui->comboBox_dateBilan->clear();
    ui->pushButton_generer_rapport->setVisible(false);
    viderInfosBilan();

    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();

    QString textRequete = "SELECT numeroTest FROM " + baseInfosCourante + " WHERE "
                          "idPatient = (SELECT idPatient FROM Patient WHERE  nomFamille LIKE '%" + nomFamilleCourant +
                          "%' and prenom LIKE '%" + prenomCourant + "%') "
                          "AND idTypeBilan = (SELECT idTypeBilan FROM TypeBilan WHERE libelle='"
                          + ui->comboBox_type_Bilan->currentText() + "') ORDER BY numeroTest;";

    QSqlQuery requete;
    if(!requete.exec(textRequete)){
        ecrireLog("Requete impossible : " + textRequete);
    }

    listeTestsCourant.clear();
    while (requete.next()) {
        listeTestsCourant << requete.value(0).toString();
    }

    // Si deja trois test ont ete fait alors on ne peut plus en ajouter
    if((listeTestsCourant.size() == 3)
            || ((listeTestsCourant.size() == 2) && ui->comboBox_type_Bilan->currentText() == "Epaule")
            || ((listeTestsCourant.size() == 1) && ui->comboBox_type_Bilan->currentText().contains("Performance"))){
        ui->pushButton_editer_bilan->setEnabled(false);
    }
    else{
        ui->pushButton_editer_bilan->setEnabled(true);
    }

    // Si un test na jamais ete fait
    if(listeTestsCourant.size() == 0){
        ui->textEdit->setText("Aucun bilan de fait");
        ui->textEdit->setStyleSheet("background-color:rgb(255,186,24);");
        ui->pushButton_modifier_bilan->setEnabled(false);
    }
    else{
        ui->pushButton_generer_rapport->setVisible(true);
        ui->textEdit->setStyleSheet("background-color:rgb(82,247,159);");
        ui->textEdit->setText("Il y a deja " + QString::number(listeTestsCourant.count()) + " de fait");

        ui->comboBox_dateBilan->setEnabled(true);
        ui->comboBox_dateBilan->clear();
        ui->comboBox_dateBilan->addItems(listeTestsCourant);

        ui->pushButton_modifier_bilan->setEnabled(true);
    }
}


//****************************************
void MainWindow::on_pushButton_valider_bilan_clicked(){

    QString nomPatientCourant = ui->comboBox_patient_courant->currentText();

    // Si on est dans un cas d INSERTION
    if(ui->pushButton_editer_bilan->isEnabled()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanGenou("insert");

        //INSERT INTO
        QString insertColonnes = "(";
        QString insertValues = "(";

        QMapIterator<QString, QString> iterateur(mapRequete);
        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                insertColonnes = insertColonnes + iterateur.key() + ",";
                insertValues = insertValues + iterateur.value() + ",";
            }
            else{
                insertColonnes = insertColonnes + iterateur.key() + ")";
                insertValues = insertValues + iterateur.value() + ")";
            }
        }

        QString texteRequete = "INSERT INTO infosBilanGenou " + insertColonnes + " VALUES " + insertValues;

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a ete enregistre !");

        ui->comboBox_dateBilan->addItem(mapRequete.value("numeroTest"));
    }

    //Si on est dans un cas de MODIFICATION
    if(ui->pushButton_annulerModificationBilan->isVisible()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanGenou("update");

        //INSERT INTO
        QString parametresUpdate;

        QMapIterator<QString, QString> iterateur(mapRequete);

        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value() + ",";
            }
            else{
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value();
            }
        }

        QString texteRequete = "UPDATE infosBilanGenou SET " + parametresUpdate +
                " WHERE idPatient=" + mapRequete.value("idPatient") + " AND numeroTest=" + ui->comboBox_dateBilan->currentText();

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a bien ete modifie !");
    }

    ui->widget_genou->setEnabled(false);

    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);

    ui->pushButton_editer_bilan->setText("Ajouter un nouveau bilan");
    ui->pushButton_annulerEditionBilan->setVisible(false);
    ui->pushButton_annulerModificationBilan->setVisible(false);

    emit on_pushButton_rechercher_clicked();
}

//****************************************
void MainWindow::on_pushButton_valider_bilan_epaule_clicked(){

    QString nomPatientCourant = ui->comboBox_patient_courant->currentText();

    // Si on est dans un cas d INSERTION
    if(ui->pushButton_editer_bilan->isEnabled()){
        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanEpaule("insert");

        //INSERT INTO
        QString insertColonnes = "(";
        QString insertValues = "(";

        QMapIterator<QString, QString> iterateur(mapRequete);
        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                insertColonnes = insertColonnes + iterateur.key() + ",";
                insertValues = insertValues + iterateur.value() + ",";
            }
            else{
                insertColonnes = insertColonnes + iterateur.key() + ")";
                insertValues = insertValues + iterateur.value() + ")";
            }
        }

        QString texteRequete = "INSERT INTO infosBilanEpaule " + insertColonnes + " VALUES " + insertValues;

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a ete enregistre !");

        ui->comboBox_dateBilan->addItem(mapRequete.value("numeroTest"));
    }

    //Si on est dans un cas de MODIFICATION
    if(ui->pushButton_annulerModificationBilan->isVisible()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanEpaule("update");

        //INSERT INTO
        QString parametresUpdate;

        QMapIterator<QString, QString> iterateur(mapRequete);

        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value() + ",";
            }
            else{
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value();
            }
        }

        QString texteRequete = "UPDATE infosBilanEpaule SET " + parametresUpdate +
                " WHERE idPatient=" + mapRequete.value("idPatient") + " AND numeroTest=" + ui->comboBox_dateBilan->currentText();

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a bien ete modifie !");
    }

    ui->widget_epaule->setEnabled(false);

    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);

    ui->pushButton_editer_bilan->setText("Ajouter un nouveau bilan");
    ui->pushButton_annulerEditionBilan->setVisible(false);
    ui->pushButton_annulerModificationBilan->setVisible(false);

    emit on_pushButton_rechercher_clicked();
}

//****************************************
void MainWindow::on_pushButton_valider_bilan_hanche_clicked()
{
    QString nomPatientCourant = ui->comboBox_patient_courant->currentText();

    // Si on est dans un cas d INSERTION
    if(ui->pushButton_editer_bilan->isEnabled()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanHanche("insert");

        //INSERT INTO
        QString insertColonnes = "(";
        QString insertValues = "(";

        QMapIterator<QString, QString> iterateur(mapRequete);
        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                insertColonnes = insertColonnes + iterateur.key() + ",";
                insertValues = insertValues + iterateur.value() + ",";
            }
            else{
                insertColonnes = insertColonnes + iterateur.key() + ")";
                insertValues = insertValues + iterateur.value() + ")";
            }
        }

        QString texteRequete = "INSERT INTO infosBilanHanche " + insertColonnes + " VALUES " + insertValues;

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant+ " a ete enregistre !");

        ui->comboBox_dateBilan->addItem(mapRequete.value("numeroTest"));
    }

    //Si on est dans un cas de MODIFICATION
    if(ui->pushButton_annulerModificationBilan->isVisible()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanHanche("update");

        //INSERT INTO
        QString parametresUpdate;

        QMapIterator<QString, QString> iterateur(mapRequete);

        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value() + ",";
            }
            else{
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value();
            }
        }

        QString texteRequete = "UPDATE infosBilanHanche SET " + parametresUpdate +
                " WHERE idPatient=" + mapRequete.value("idPatient") + " AND numeroTest=" + ui->comboBox_dateBilan->currentText();

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a bien ete modifie !");
    }

    ui->widget_hanche->setEnabled(false);

    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);

    ui->pushButton_editer_bilan->setText("Ajouter un nouveau bilan");
    ui->pushButton_annulerEditionBilan->setVisible(false);
    ui->pushButton_annulerModificationBilan->setVisible(false);

    emit on_pushButton_rechercher_clicked();
}

void MainWindow::on_pushButton_valider_bilan_cheville_clicked()
{

    QString nomPatientCourant = ui->comboBox_patient_courant->currentText();

    // Si on est dans un cas d INSERTION
    if(ui->pushButton_editer_bilan->isEnabled()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanCheville("insert");

        //INSERT INTO
        QString insertColonnes = "(";
        QString insertValues = "(";

        QMapIterator<QString, QString> iterateur(mapRequete);
        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                insertColonnes = insertColonnes + iterateur.key() + ",";
                insertValues = insertValues + iterateur.value() + ",";
            }
            else{
                insertColonnes = insertColonnes + iterateur.key() + ")";
                insertValues = insertValues + iterateur.value() + ")";
            }
        }

        QString texteRequete = "INSERT INTO infosBilanCheville " + insertColonnes + " VALUES " + insertValues;

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a ete enregistre !");

        ui->comboBox_dateBilan->addItem(mapRequete.value("numeroTest"));
    }

    //Si on est dans un cas de MODIFICATION
    if(ui->pushButton_annulerModificationBilan->isVisible()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanCheville("update");

        //INSERT INTO
        QString parametresUpdate;

        QMapIterator<QString, QString> iterateur(mapRequete);

        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value() + ",";
            }
            else{
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value();
            }
        }

        QString texteRequete = "UPDATE infosBilanCheville SET " + parametresUpdate +
                " WHERE idPatient=" + mapRequete.value("idPatient") + " AND numeroTest=" + ui->comboBox_dateBilan->currentText();

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a bien ete modifie !");
    }

    ui->widget_cheville->setEnabled(false);

    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);

    ui->pushButton_editer_bilan->setText("Ajouter un nouveau bilan");
    ui->pushButton_annulerEditionBilan->setVisible(false);
    ui->pushButton_annulerModificationBilan->setVisible(false);

    emit on_pushButton_rechercher_clicked();

}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_valider_bilan_bpc_clicked()
{
    QString nomPatientCourant = ui->comboBox_patient_courant->currentText();

    // Si on est dans un cas d INSERTION
    if(ui->pushButton_editer_bilan->isEnabled()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanBpc("insert");

        //INSERT INTO
        QString insertColonnes = "(";
        QString insertValues = "(";

        QMapIterator<QString, QString> iterateur(mapRequete);
        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                insertColonnes = insertColonnes + iterateur.key() + ",";
                insertValues = insertValues + iterateur.value() + ",";
            }
            else{
                insertColonnes = insertColonnes + iterateur.key() + ")";
                insertValues = insertValues + iterateur.value() + ")";
            }
        }

        QString texteRequete = "INSERT INTO infosBilanCourse " + insertColonnes + " VALUES " + insertValues;

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a ete enregistre !");

        ui->comboBox_dateBilan->addItem(mapRequete.value("numeroTest"));
    }

    //Si on est dans un cas de MODIFICATION
    if(ui->pushButton_annulerModificationBilan->isVisible()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanBpc("update");

        //INSERT INTO
        QString parametresUpdate;

        QMapIterator<QString, QString> iterateur(mapRequete);

        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value() + ",";
            }
            else{
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value();
            }
        }

        QString texteRequete = "UPDATE infosBilanCourse SET " + parametresUpdate +
                " WHERE idPatient=" + mapRequete.value("idPatient") + " AND numeroTest=" + ui->comboBox_dateBilan->currentText();

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a bien ete modifie !");
    }

    ui->widget_bpc->setEnabled(false);

    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);

    ui->pushButton_editer_bilan->setText("Ajouter un nouveau bilan");
    ui->pushButton_annulerEditionBilan->setVisible(false);
    ui->pushButton_annulerModificationBilan->setVisible(false);

    emit on_pushButton_rechercher_clicked();
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_valider_bilan_bpsc_clicked()
{
    QString nomPatientCourant = ui->comboBox_patient_courant->currentText();

    // Si on est dans un cas d INSERTION
    if(ui->pushButton_editer_bilan->isEnabled()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanBpsc("insert");

        //INSERT INTO
        QString insertColonnes = "(";
        QString insertValues = "(";

        QMapIterator<QString, QString> iterateur(mapRequete);
        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                insertColonnes = insertColonnes + iterateur.key() + ",";
                insertValues = insertValues + iterateur.value() + ",";
            }
            else{
                insertColonnes = insertColonnes + iterateur.key() + ")";
                insertValues = insertValues + iterateur.value() + ")";
            }
        }

        QString texteRequete = "INSERT INTO infosBilanSportCollectif " + insertColonnes + " VALUES " + insertValues;

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a ete enregistre !");

        ui->comboBox_dateBilan->addItem(mapRequete.value("numeroTest"));
    }

    //Si on est dans un cas de MODIFICATION
    if(ui->pushButton_annulerModificationBilan->isVisible()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanBpsc("update");

        //INSERT INTO
        QString parametresUpdate;

        QMapIterator<QString, QString> iterateur(mapRequete);

        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value() + ",";
            }
            else{
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value();
            }
        }

        QString texteRequete = "UPDATE infosBilanSportCollectif SET " + parametresUpdate +
                " WHERE idPatient=" + mapRequete.value("idPatient") + " AND numeroTest=" + ui->comboBox_dateBilan->currentText();

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a bien ete modifie !");
    }

    ui->widget_bpsc->setEnabled(false);

    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);

    ui->pushButton_editer_bilan->setText("Ajouter un nouveau bilan");
    ui->pushButton_annulerEditionBilan->setVisible(false);
    ui->pushButton_annulerModificationBilan->setVisible(false);

    emit on_pushButton_rechercher_clicked();
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_valider_bilan_bpf_clicked()
{

    QString nomPatientCourant = ui->comboBox_patient_courant->currentText();

    // Si on est dans un cas d INSERTION
    if(ui->pushButton_editer_bilan->isEnabled()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanBpf("insert");

        //INSERT INTO
        QString insertColonnes = "(";
        QString insertValues = "(";

        QMapIterator<QString, QString> iterateur(mapRequete);
        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                insertColonnes = insertColonnes + iterateur.key() + ",";
                insertValues = insertValues + iterateur.value() + ",";
            }
            else{
                insertColonnes = insertColonnes + iterateur.key() + ")";
                insertValues = insertValues + iterateur.value() + ")";
            }
        }

        QString texteRequete = "INSERT INTO infosBilanSportCombat " + insertColonnes + " VALUES " + insertValues;

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a ete enregistre !");

        ui->comboBox_dateBilan->addItem(mapRequete.value("numeroTest"));
    }

    //Si on est dans un cas de MODIFICATION
    if(ui->pushButton_annulerModificationBilan->isVisible()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanBpf("update");

        //INSERT INTO
        QString parametresUpdate;

        QMapIterator<QString, QString> iterateur(mapRequete);

        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value() + ",";
            }
            else{
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value();
            }
        }

        QString texteRequete = "UPDATE infosBilanSportCombat SET " + parametresUpdate +
                " WHERE idPatient=" + mapRequete.value("idPatient") + " AND numeroTest=" + ui->comboBox_dateBilan->currentText();

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a bien ete modifie !");
    }

    ui->widget_bpf->setEnabled(false);

    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);

    ui->pushButton_editer_bilan->setText("Ajouter un nouveau bilan");
    ui->pushButton_annulerEditionBilan->setVisible(false);
    ui->pushButton_annulerModificationBilan->setVisible(false);

    emit on_pushButton_rechercher_clicked();
}


void MainWindow::on_pushButton_valider_bilan_bpcf_clicked()
{

    QString nomPatientCourant = ui->comboBox_patient_courant->currentText();

    // Si on est dans un cas d INSERTION
    if(ui->pushButton_editer_bilan->isEnabled()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanBpcf("insert");

        //INSERT INTO
        QString insertColonnes = "(";
        QString insertValues = "(";

        QMapIterator<QString, QString> iterateur(mapRequete);
        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                insertColonnes = insertColonnes + iterateur.key() + ",";
                insertValues = insertValues + iterateur.value() + ",";
            }
            else{
                insertColonnes = insertColonnes + iterateur.key() + ")";
                insertValues = insertValues + iterateur.value() + ")";
            }
        }

        QString texteRequete = "INSERT INTO infosBilanCrossfit " + insertColonnes + " VALUES " + insertValues;

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a ete enregistre !");

        ui->comboBox_dateBilan->addItem(mapRequete.value("numeroTest"));
    }

    //Si on est dans un cas de MODIFICATION
    if(ui->pushButton_annulerModificationBilan->isVisible()){

        QSqlQuery requete;
        QString texteColonnes;

        //Creation de la QMap pour la requete
        QMap<QString, QString> mapRequete = remplirQMapInfoBilanBpcf("update");

        //INSERT INTO
        QString parametresUpdate;

        QMapIterator<QString, QString> iterateur(mapRequete);

        while(iterateur.hasNext()){
            iterateur.next();
            if(iterateur.hasNext()){
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value() + ",";
            }
            else{
                parametresUpdate = parametresUpdate + iterateur.key() + "=" + iterateur.value();
            }
        }

        QString texteRequete = "UPDATE infosBilanCrossfit SET " + parametresUpdate +
                " WHERE idPatient=" + mapRequete.value("idPatient") + " AND numeroTest=" + ui->comboBox_dateBilan->currentText();

        if(!requete.exec(texteRequete)){
            ecrireLog("Requete impossible : " + texteRequete);
        }
        while (requete.next()) {
            texteColonnes = requete.value(0).toString();
        }

        QMessageBox::information(this, tr("Bilan Ajoute"),
                                 "Le bilan de " + mapRequete.value("numeroTest") + " pour " + nomPatientCourant + " a bien ete modifie !");
    }

    ui->widget_bpcf->setEnabled(false);

    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);

    ui->pushButton_editer_bilan->setText("Ajouter un nouveau bilan");
    ui->pushButton_annulerEditionBilan->setVisible(false);
    ui->pushButton_annulerModificationBilan->setVisible(false);

    emit on_pushButton_rechercher_clicked();
}


//****************************************
void MainWindow::on_pushButton_generer_rapport_clicked(){

    viderInfosRapport();

    // Demander confirmation au user
    bool reponseAcceptee;
    QMessageBox::StandardButton reponseUser;
    reponseUser = QMessageBox::question(this, "Validation", "Voulez vous generer le rapport de "
                                                                +  ui->comboBox_dateBilan->currentText() +" pour "
                                                                + ui->comboBox_patient_courant->currentText() + " ?",
                                        QMessageBox::Yes|QMessageBox::No);
    if (reponseUser == QMessageBox::No) {
        return;
    } else {

        reponseAcceptee = true;
    }

    if(reponseAcceptee){

        ui->scrollArea->takeWidget();
        //set this property
        ui->scrollArea->setWidgetResizable(false);

        // SETTINGS
        if(ui->comboBox_type_Bilan->currentText() == "Genou"){
            //reset widget
            ui->scrollArea->setWidget(ui->widget_generation_rapport_genou);
        }
        else if(ui->comboBox_type_Bilan->currentText() == "Epaule"){
            ui->scrollArea->setWidget(ui->widget_generation_rapport_epaule);
        }
        else if(ui->comboBox_type_Bilan->currentText() == "Hanche"){
            ui->scrollArea->setWidget(ui->widget_generation_rapport_hanche);
        }
        else if(ui->comboBox_type_Bilan->currentText() == "Cheville"){
            ui->scrollArea->setWidget(ui->widget_generation_rapport_cheville);
        }
        else if(ui->comboBox_type_Bilan->currentText().contains( "Course")){
            ui->scrollArea->setWidget(ui->widget_generation_rapport_bpc);
        }
        else if(ui->comboBox_type_Bilan->currentText().contains( "collectif")){
            ui->scrollArea->setWidget(ui->widget_generation_rapport_bpsc);
        }
        else if(ui->comboBox_type_Bilan->currentText().contains( "Combat")){
            ui->scrollArea->setWidget(ui->widget_generation_rapport_bpf);
        }
        else if(ui->comboBox_type_Bilan->currentText().contains( "Crossfit")){
            ui->scrollArea->setWidget(ui->widget_generation_rapport_bpcf);
        }

        ui->pushButton_generer_rapport->setText("Reinitialiser le rapport");
        ui->comboBox_dateBilan->setEnabled(false);
        ui->comboBox_type_Bilan->setEnabled(false);
        ui->comboBox_patient_courant->setEnabled(false);
        ui->pushButton_rechercher->setEnabled(false);
        ui->pushButton_editer_bilan->setEnabled(false);

        ui->pushButton_annulerEditionRapport->setVisible(true);

        this->mapCheminsImages.clear();
    }
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_modifier_bilan_clicked(){

    if(ui->comboBox_dateBilan->count() < 1)
        return;

    ui->comboBox_dateBilan->setEnabled(false);
    ui->comboBox_type_Bilan->setEnabled(false);
    ui->comboBox_patient_courant->setEnabled(false);
    ui->pushButton_generer_rapport->setVisible(false);
    ui->pushButton_rechercher->setEnabled(false);

    ui->pushButton_editer_bilan->setEnabled(false);
    ui->pushButton_modifier_bilan->setEnabled(false);

    ui->pushButton_annulerModificationBilan->setVisible(true);

    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);

    // SETTINGS
    if(ui->comboBox_type_Bilan->currentText() == "Genou"){

        ui->scrollArea->setWidget(ui->widget_genou);
        ui->widget_genou->setEnabled(true);
        ui->pushButton_valider_bilan->setVisible(true);

        if(ui->comboBox_dateBilan->currentText() != "1"){

            // Test Hop
            ui->doubleSpinBox_g_distanceSLHNO->setEnabled(false);
            ui->doubleSpinBox_g_distanceSLHO->setEnabled(false);
        }
        else{
            // Test Hop
            ui->doubleSpinBox_g_distanceSLHNO->setEnabled(true);
            ui->doubleSpinBox_g_distanceSLHO->setEnabled(true);
        }
    }
    else if(ui->comboBox_type_Bilan->currentText() == "Epaule"){

        ui->scrollArea->setWidget(ui->widget_epaule);
        ui->widget_epaule->setEnabled(true);
        ui->pushButton_valider_bilan_epaule->setVisible(true);

        // Si le test n est ni pas un test 1 alors la main dominante et le bras sont desactive
        if(ui->comboBox_dateBilan->currentText() != "1"){
            ui->comboBox_e_brasOpere->setEnabled(false);
            ui->comboBox_e_mainDominante->setEnabled(false);
            ui->doubleSpinBox_e_longueurBras->setEnabled(false);
        }
        else{
            ui->comboBox_e_brasOpere->setEnabled(true);
            ui->comboBox_e_mainDominante->setEnabled(true);
            ui->doubleSpinBox_e_longueurBras->setEnabled(true);
        }
    }
    else if(ui->comboBox_type_Bilan->currentText() == "Hanche"){
        ui->scrollArea->setWidget(ui->widget_hanche);
        ui->widget_hanche->setEnabled(true);
        ui->pushButton_valider_bilan_hanche->setVisible(true);
    }
    else if(ui->comboBox_type_Bilan->currentText() == "Cheville"){
        ui->scrollArea->setWidget(ui->widget_cheville);
        ui->widget_cheville->setEnabled(true);
        ui->pushButton_valider_bilan_cheville->setVisible(true);

        // Si le test n est ni pas un test 1 alors le reception unipodal est desactive
        if(ui->comboBox_dateBilan->count() > 0){
            ui->groupBox_repartitionCharge_c->setEnabled(false);
            ui->groupBox_controleGenou_c->setEnabled(false);
            ui->groupBox_troncBassin_c->setEnabled(false);
        }
        else{
            ui->groupBox_repartitionCharge_c->setEnabled(true);
            ui->groupBox_controleGenou_c->setEnabled(true);
            ui->groupBox_troncBassin_c->setEnabled(true);
        }

        if(ui->comboBox_dateBilan->currentText() != "1"){
            ui->doubleSpinBox_c_longueurMI->setEnabled(false);
            ui->comboBox_c_chevilleOperee->setEnabled(false);
        }
        else{
            ui->comboBox_e_brasOpere->setEnabled(true);
            ui->doubleSpinBox_c_longueurMI->setEnabled(true);
            ui->comboBox_c_chevilleOperee->setEnabled(true);
        }
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "Course")){
        ui->scrollArea->setWidget(ui->widget_bpc);
        ui->widget_bpc->setEnabled(true);
        ui->pushButton_valider_bilan_bpc->setVisible(true);
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "collectif")){
        ui->scrollArea->setWidget(ui->widget_bpsc);
        ui->widget_bpsc->setEnabled(true);
        ui->pushButton_valider_bilan_bpsc->setVisible(true);
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "Combat")){
        ui->scrollArea->setWidget(ui->widget_bpf);
        ui->widget_bpf->setEnabled(true);
        ui->pushButton_valider_bilan_bpf->setVisible(true);
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "Crossfit")){
        ui->scrollArea->setWidget(ui->widget_bpcf);
        ui->widget_bpcf->setEnabled(true);
        ui->pushButton_valider_bilan_bpcf->setVisible(true);
    }
}

//****************************************
void MainWindow::on_pushButton_editer_bilan_clicked(){

    ui->comboBox_dateBilan->setEnabled(false);
    ui->comboBox_type_Bilan->setEnabled(false);
    ui->comboBox_patient_courant->setEnabled(false);
    ui->pushButton_modifier_bilan->setEnabled(false);
    ui->pushButton_generer_rapport->setVisible(false);
    ui->pushButton_rechercher->setEnabled(false);

    ui->pushButton_editer_bilan->setText("Reinitialiser le bilan");

    ui->pushButton_annulerEditionBilan->setVisible(true);

    viderInfosBilan();

    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);

    // SETTINGS
    if(ui->comboBox_type_Bilan->currentText() == "Genou"){

        ui->scrollArea->setWidget(ui->widget_genou);
        ui->widget_genou->setEnabled(true);
        ui->pushButton_valider_bilan->setVisible(true);

        // Si le test n est ni pas un test 1 alors le reception unipodal est desactive
        if(ui->comboBox_dateBilan->count() > 0){

            // Test reception unipodale
            ui->groupBox_repartitionCharge_g->setEnabled(false);
            ui->groupBox_controleGenou_g->setEnabled(false);
            ui->groupBox_troncBassin_g->setEnabled(false);

            // Test Hop
            ui->doubleSpinBox_g_distanceSLHNO->setEnabled(false);
            ui->doubleSpinBox_g_distanceSLHO->setEnabled(false);
        }
        else{
            // Test reception unipodale
            ui->groupBox_repartitionCharge_g->setEnabled(true);
            ui->groupBox_controleGenou_g->setEnabled(true);
            ui->groupBox_troncBassin_g->setEnabled(true);

            // Test Hop
            ui->doubleSpinBox_g_distanceSLHNO->setEnabled(true);
            ui->doubleSpinBox_g_distanceSLHO->setEnabled(true);
        }
    }
    else if(ui->comboBox_type_Bilan->currentText() == "Epaule"){
        ui->scrollArea->setWidget(ui->widget_epaule);
        ui->widget_epaule->setEnabled(true);
        ui->pushButton_valider_bilan_epaule->setVisible(true);

        // Si le test n est ni pas un test 1 alors la main dominante et le bras sont desactive
        if(ui->comboBox_dateBilan->count() > 0){
            ui->comboBox_e_brasOpere->setEnabled(false);
            ui->comboBox_e_mainDominante->setEnabled(false);
            ui->doubleSpinBox_e_longueurBras->setEnabled(false);
        }
        else{
            ui->comboBox_e_brasOpere->setEnabled(true);
            ui->comboBox_e_mainDominante->setEnabled(true);
            ui->doubleSpinBox_e_longueurBras->setEnabled(true);
        }
    }
    else if(ui->comboBox_type_Bilan->currentText() == "Hanche"){
        ui->scrollArea->setWidget(ui->widget_hanche);
        ui->widget_hanche->setEnabled(true);
        ui->pushButton_valider_bilan_hanche->setVisible(true);

        // Si le test n est ni pas un test 1 alors le reception unipodal est desactive
        if(ui->comboBox_dateBilan->count() > 0){
            ui->groupBox_repartitionCharge_h->setEnabled(false);
            ui->groupBox_controleGenou_h->setEnabled(false);
            ui->groupBox_troncBassin_h->setEnabled(false);
        }
        else{
            ui->groupBox_repartitionCharge_h->setEnabled(true);
            ui->groupBox_controleGenou_h->setEnabled(true);
            ui->groupBox_troncBassin_h->setEnabled(true);
        }
    }
    else if(ui->comboBox_type_Bilan->currentText() == "Cheville"){
        ui->scrollArea->setWidget(ui->widget_cheville);
        ui->widget_cheville->setEnabled(true);
        ui->pushButton_valider_bilan_cheville->setVisible(true);

        // Si le test n est ni pas un test 1 alors le reception unipodal est desactive
        if(ui->comboBox_dateBilan->count() > 0){
            ui->groupBox_repartitionCharge_c->setEnabled(false);
            ui->groupBox_controleGenou_c->setEnabled(false);
            ui->groupBox_troncBassin_c->setEnabled(false);
        }
        else{
            ui->groupBox_repartitionCharge_c->setEnabled(true);
            ui->groupBox_controleGenou_c->setEnabled(true);
            ui->groupBox_troncBassin_c->setEnabled(true);
        }

        if(ui->comboBox_dateBilan->currentText() != "1"){
            ui->doubleSpinBox_c_longueurMI->setEnabled(false);
            ui->comboBox_c_chevilleOperee->setEnabled(false);
        }
        else{
            ui->comboBox_e_brasOpere->setEnabled(true);
            ui->doubleSpinBox_c_longueurMI->setEnabled(true);
            ui->comboBox_c_chevilleOperee->setEnabled(true);
        }
    }
    else if(ui->comboBox_type_Bilan->currentText().contains("Course")){
        ui->scrollArea->setWidget(ui->widget_bpc);
        ui->widget_bpc->setEnabled(true);
        ui->pushButton_valider_bilan_bpc->setVisible(true);
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "collectif")){
        ui->scrollArea->setWidget(ui->widget_bpsc);
        ui->widget_bpsc->setEnabled(true);
        ui->pushButton_valider_bilan_bpsc->setVisible(true);
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "Combat")){
        ui->scrollArea->setWidget(ui->widget_bpf);
        ui->widget_bpf->setEnabled(true);
        ui->pushButton_valider_bilan_bpf->setVisible(true);
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "Crossfit")){
        ui->scrollArea->setWidget(ui->widget_bpcf);
        ui->widget_bpcf->setEnabled(true);
        ui->pushButton_valider_bilan_bpcf->setVisible(true);
    }
}

//****************************************
void MainWindow::on_pushButton_annulerEditionBilan_clicked(){

    ui->comboBox_dateBilan->setEnabled(true);
    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);

    if(ui->comboBox_dateBilan->count() > 0)
        ui->pushButton_generer_rapport->setVisible(true);

    ui->pushButton_editer_bilan->setText("Ajouter un nouveau bilan");

    //SETTINGS
    ui->widget_genou->setEnabled(false);
    ui->widget_epaule->setEnabled(false);
    ui->widget_hanche->setEnabled(false);
    ui->widget_cheville->setEnabled(false);
    ui->widget_bpc->setEnabled(false);
    ui->widget_bpsc->setEnabled(false);
    ui->widget_bpf->setEnabled(false);
    ui->widget_bpcf->setEnabled(false);

    //SETTINGS
    ui->pushButton_valider_bilan->setVisible(false);
    ui->pushButton_valider_bilan_epaule->setVisible(false);
    ui->pushButton_valider_bilan_hanche->setVisible(false);
    ui->pushButton_valider_bilan_cheville->setVisible(false);
    ui->pushButton_valider_bilan_bpc->setVisible(false);
    ui->pushButton_valider_bilan_bpsc->setVisible(false);
    ui->pushButton_valider_bilan_bpf->setVisible(false);
    ui->pushButton_valider_bilan_bpcf->setVisible(false);

    ui->pushButton_annulerEditionBilan->setVisible(false);
    ui->pushButton_annulerModificationBilan->setVisible(false);
    viderInfosBilan();
}

//****************************************
/*
 *
 */
void MainWindow::on_pushButton_annulerEditionRapport_clicked(){
    ui->pushButton_annulerEditionRapport->setVisible(false);

    viderInfosRapport();

    // On revient la ou on en etait
    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);
    //reset widget

    // SETTINGS
    if(ui->comboBox_type_Bilan->currentText() == "Genou")
        ui->scrollArea->setWidget(ui->widget_genou);
    else if(ui->comboBox_type_Bilan->currentText() == "Epaule")
        ui->scrollArea->setWidget(ui->widget_epaule);
    else if(ui->comboBox_type_Bilan->currentText() == "Hanche")
        ui->scrollArea->setWidget(ui->widget_hanche);
    else if(ui->comboBox_type_Bilan->currentText() == "Cheville")
        ui->scrollArea->setWidget(ui->widget_cheville);
    else if(ui->comboBox_type_Bilan->currentText().contains( "Course"))
        ui->scrollArea->setWidget(ui->widget_bpc);
    else if(ui->comboBox_type_Bilan->currentText().contains( "collectif"))
        ui->scrollArea->setWidget(ui->widget_bpsc);
    else if(ui->comboBox_type_Bilan->currentText().contains( "Combat"))
        ui->scrollArea->setWidget(ui->widget_bpf);
    else if(ui->comboBox_type_Bilan->currentText().contains( "Crossfit"))
        ui->scrollArea->setWidget(ui->widget_bpcf);

    ui->pushButton_generer_rapport->setText("Generer le rapport");
    ui->comboBox_dateBilan->setEnabled(true);
    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);
    ui->pushButton_editer_bilan->setEnabled(true);

    this->mapCheminsImages.clear();

    emit on_pushButton_rechercher_clicked();
}


void MainWindow::on_pushButton_validerRapport_clicked() {

    // Récupérer le chemin du fichier annexes
    QString pathFichierAnnexes = ui->lineEdit_g_pathAnnexes->text();
    QFileInfo fichierInfoAnnexes(pathFichierAnnexes);

    // Récupérer les numéros de test
    QStringList listeNumerosTest;
    for (int i = 0; i < ui->comboBox_dateBilan->currentText().toInt(); ++i) {
        listeNumerosTest.append(ui->comboBox_dateBilan->itemText(i));
    }

    // Générer le contenu HTML
    QString contenuHtml = remplirChaineHtmlGenou(listeNumerosTest);
    genererRapportPdf(contenuHtml);

    // Vérifier que le fichier rapport existe
    QString pathFichierPdf = getValue(PATH_CONFIG, "paths", "pdfRes");
    QFileInfo fichierInfoRapport(pathFichierPdf);

    if (!fichierInfoRapport.isFile()) {
        QMessageBox::information(this, tr("Erreur fichiers inexistants"), "Le fichier rapport n'existe pas ! : " + pathFichierPdf);
        return;
    }

    // Construire le chemin vers la page de garde
    QString pathPageGarde = QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "PageGardeGenou");

    // Construire le nom final du fichier concaténé
    QString pathFichierRes = getValue(PATH_CONFIG, "paths", "dossierRapports")
                             + "/rapport_genou_"
                             + QString::number(listeNumerosTest.count())
                             + "_"
                             + ui->comboBox_patient_courant->currentText().replace(" ", "_")
                             + "_"
                             + QDate::currentDate().toString("dd_MM_yyyy")
                             + ".pdf";

    // Liste des fichiers à concaténer
    QStringList fichiersAConcatener;
    fichiersAConcatener << pathPageGarde << pathFichierPdf;
    if (fichierInfoAnnexes.isFile()) {
        fichiersAConcatener << pathFichierAnnexes;
    }

    // Fusion des PDF
    bool reussi = lancerCmdPdftk(fichiersAConcatener, pathFichierRes);
    if (!reussi) {
        QMessageBox::information(this, tr("Erreur PDFTK"), "La commande PDFTK a échoué lors de la fusion finale.");
        ecrireLog("La commande PDFTK a échoué : fichiers = " + fichiersAConcatener.join(" + ") + " => " + pathFichierRes);
        return;
    }

    // Créer une copie horodatée du fichier final
    QFileInfo fichierInfoRes(pathFichierRes);
    QString pathFichierCopie = getValue(PATH_CONFIG, "paths", "dossierBackupRapports") + "/" + fichierInfoRes.baseName()
                               + "_" + QDateTime::currentDateTime().toString("ddMMyyyy_hhmmsszzz") + ".pdf";
    copyFile(pathFichierRes, pathFichierCopie);

    // Message succès
    QMessageBox::information(this, tr("Rapport généré"),
                             "Le rapport genou numéro " + QString::number(listeNumerosTest.count()) +
                             " pour le patient " + ui->comboBox_patient_courant->currentText() + " a été enregistré !");

    // Ouvrir le PDF
    QUrl pdfUrl = QUrl::fromLocalFile(pathFichierRes);
    if (!QDesktopServices::openUrl(pdfUrl)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier PDF automatiquement."));
    }

    // Remettre l'interface à l'état initial
    viderInfosRapport();

    ui->scrollArea->takeWidget();
    ui->scrollArea->setWidgetResizable(false);
    ui->scrollArea->setWidget(ui->widget_genou);

    ui->pushButton_generer_rapport->setText("Generer le rapport");
    ui->comboBox_dateBilan->setEnabled(true);
    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);
    ui->pushButton_editer_bilan->setEnabled(true);
    ui->pushButton_annulerEditionRapport->setVisible(false);

    this->mapCheminsImages.clear();

    // Rafraîchir la liste
    emit on_pushButton_rechercher_clicked();
}


//****************************************
/*
 *
 */
void MainWindow::on_pushButton_validerRapport_epaule_clicked(){

    // Recuperer le chemin des fichiers pdf a recuperer pour le merge
    QString pathFichierAnnexes = ui->lineEdit_e_pathAnnexes->text();

    QStringList listeNumerosTest;

    for(int i = 0; i < ui->comboBox_dateBilan->currentText().toInt(); i++){
        listeNumerosTest.append(ui->comboBox_dateBilan->itemText(i));
    }

    // ecrire le QString html
    QString contenuHtml = remplirChaineHtmlEpaule(listeNumerosTest);

    // generer le PDF resultat et en garder une copie
    genererRapportPdf(contenuHtml);

    QFileInfo fichierInfoAnnexes(pathFichierAnnexes);

    // Vérifier que le fichier rapport existe
    QString pathFichierPdf = getValue(PATH_CONFIG, "paths", "pdfRes");
    QFileInfo fichierInfoRapport(pathFichierPdf);

    if (!fichierInfoRapport.isFile()) {
        QMessageBox::information(this, tr("Erreur fichiers inexistants"), "Le fichier rapport n'existe pas ! : " + pathFichierPdf);
        return;
    }

    // Construire le chemin vers la page de garde
    QString pathPageGarde = QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "PageGardeEpaule");

    // Construire le nom final du fichier concaténé
    QString pathFichierRes = getValue(PATH_CONFIG, "paths", "dossierRapports")
                             + "/rapport_epaule_"
                             + QString::number(listeNumerosTest.count())
                             + "_"
                             + ui->comboBox_patient_courant->currentText().replace(" ", "_")
                             + "_"
                             + QDate::currentDate().toString("dd_MM_yyyy")
                             + ".pdf";

    // Liste des fichiers à concaténer
    QStringList fichiersAConcatener;
    fichiersAConcatener << pathPageGarde << pathFichierPdf;
    if (fichierInfoAnnexes.isFile()) {
        fichiersAConcatener << pathFichierAnnexes;
    }

    // Fusion des PDF
    bool reussi = lancerCmdPdftk(fichiersAConcatener, pathFichierRes);
    if (!reussi) {
        QMessageBox::information(this, tr("Erreur PDFTK"), "La commande PDFTK a échoué lors de la fusion finale.");
        ecrireLog("La commande PDFTK a échoué : fichiers = " + fichiersAConcatener.join(" + ") + " => " + pathFichierRes);
        return;
    }

    // Créer une copie horodatée du fichier final
    QFileInfo fichierInfoRes(pathFichierRes);
    QString pathFichierCopie = getValue(PATH_CONFIG, "paths", "dossierBackupRapports") + "/" + fichierInfoRes.baseName()
                               + "_" + QDateTime::currentDateTime().toString("ddMMyyyy_hhmmsszzz") + ".pdf";
    copyFile(pathFichierRes, pathFichierCopie);

    // Message succès
    QMessageBox::information(this, tr("Rapport généré"),
                             "Le rapport genou numéro " + QString::number(listeNumerosTest.count()) +
                             " pour le patient " + ui->comboBox_patient_courant->currentText() + " a été enregistré !");

    // Ouvrir le PDF
    QUrl pdfUrl = QUrl::fromLocalFile(pathFichierRes);
    if (!QDesktopServices::openUrl(pdfUrl)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier PDF automatiquement."));
    }

    // Gerer interface
    viderInfosRapport();

    // On revient la ou on en etait
    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);
    //reset widget
    ui->scrollArea->setWidget(ui->widget_epaule);

    ui->pushButton_generer_rapport->setText("Generer le rapport");
    ui->comboBox_dateBilan->setEnabled(true);
    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);
    ui->pushButton_editer_bilan->setEnabled(true);

    ui->pushButton_annulerEditionRapport->setVisible(false);

    this->mapCheminsImages.clear();

    emit on_pushButton_rechercher_clicked();
}

//****************************************
/*
 *
 */
void MainWindow::on_pushButton_validerRapport_hanche_clicked()
{

    // Recuperer le chemin des fichiers pdf a recuperer pour le merge
    QString pathFichierAnnexes = ui->lineEdit_h_pathAnnexes->text();

    QStringList listeNumerosTest;

    for(int i = 0; i < ui->comboBox_dateBilan->currentText().toInt(); i++){
        listeNumerosTest.append(ui->comboBox_dateBilan->itemText(i));
    }

    // ecrire le QString html
    QString contenuHtml = remplirChaineHtmlHanche(listeNumerosTest);

    // generer le PDF resultat et en garder une copie
    genererRapportPdf(contenuHtml);

    QFileInfo fichierInfoAnnexes(pathFichierAnnexes);

    // Vérifier que le fichier rapport existe
    QString pathFichierPdf = getValue(PATH_CONFIG, "paths", "pdfRes");
    QFileInfo fichierInfoRapport(pathFichierPdf);

    if (!fichierInfoRapport.isFile()) {
        QMessageBox::information(this, tr("Erreur fichiers inexistants"), "Le fichier rapport n'existe pas ! : " + pathFichierPdf);
        return;
    }

    // Construire le chemin vers la page de garde
    QString pathPageGarde = QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "PageGardeHanche");

    // Construire le nom final du fichier concaténé
    QString pathFichierRes = getValue(PATH_CONFIG, "paths", "dossierRapports")
                             + "/rapport_hanche_"
                             + QString::number(listeNumerosTest.count())
                             + "_"
                             + ui->comboBox_patient_courant->currentText().replace(" ", "_")
                             + "_"
                             + QDate::currentDate().toString("dd_MM_yyyy")
                             + ".pdf";

    // Liste des fichiers à concaténer
    QStringList fichiersAConcatener;
    fichiersAConcatener << pathPageGarde << pathFichierPdf;
    if (fichierInfoAnnexes.isFile()) {
        fichiersAConcatener << pathFichierAnnexes;
    }

    // Fusion des PDF
    bool reussi = lancerCmdPdftk(fichiersAConcatener, pathFichierRes);
    if (!reussi) {
        QMessageBox::information(this, tr("Erreur PDFTK"), "La commande PDFTK a échoué lors de la fusion finale.");
        ecrireLog("La commande PDFTK a échoué : fichiers = " + fichiersAConcatener.join(" + ") + " => " + pathFichierRes);
        return;
    }

    // Créer une copie horodatée du fichier final
    QFileInfo fichierInfoRes(pathFichierRes);
    QString pathFichierCopie = getValue(PATH_CONFIG, "paths", "dossierBackupRapports") + "/" + fichierInfoRes.baseName()
                               + "_" + QDateTime::currentDateTime().toString("ddMMyyyy_hhmmsszzz") + ".pdf";
    copyFile(pathFichierRes, pathFichierCopie);

    // Message succès
    QMessageBox::information(this, tr("Rapport généré"),
                             "Le rapport genou numéro " + QString::number(listeNumerosTest.count()) +
                             " pour le patient " + ui->comboBox_patient_courant->currentText() + " a été enregistré !");

    // Ouvrir le PDF
    QUrl pdfUrl = QUrl::fromLocalFile(pathFichierRes);
    if (!QDesktopServices::openUrl(pdfUrl)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier PDF automatiquement."));
    }

    // Gerer interface
    viderInfosRapport();

    // On revient la ou on en etait
    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);
    //reset widget
    ui->scrollArea->setWidget(ui->widget_hanche);

    ui->pushButton_generer_rapport->setText("Generer le rapport");
    ui->comboBox_dateBilan->setEnabled(true);
    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);
    ui->pushButton_editer_bilan->setEnabled(true);

    ui->pushButton_annulerEditionRapport->setVisible(false);

    this->mapCheminsImages.clear();

    emit on_pushButton_rechercher_clicked();
}

//****************************************
/*
 *
 */
void MainWindow::on_pushButton_validerRapport_cheville_clicked()
{

    // Recuperer le chemin des fichiers pdf a recuperer pour le merge
    QString pathFichierAnnexes = ui->lineEdit_c_pathAnnexes->text();

    QStringList listeNumerosTest;

    for(int i = 0; i < ui->comboBox_dateBilan->currentText().toInt(); i++){
        listeNumerosTest.append(ui->comboBox_dateBilan->itemText(i));
    }

    // ecrire le QString html
    QString contenuHtml = remplirChaineHtmlCheville(listeNumerosTest);

    // generer le PDF resultat et en garder une copie
    genererRapportPdf(contenuHtml);

    QFileInfo fichierInfoAnnexes(pathFichierAnnexes);

    // Vérifier que le fichier rapport existe
    QString pathFichierPdf = getValue(PATH_CONFIG, "paths", "pdfRes");
    QFileInfo fichierInfoRapport(pathFichierPdf);

    if (!fichierInfoRapport.isFile()) {
        QMessageBox::information(this, tr("Erreur fichiers inexistants"), "Le fichier rapport n'existe pas ! : " + pathFichierPdf);
        return;
    }

    // Construire le chemin vers la page de garde
    QString pathPageGarde = QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "PageGardeCheville");

    // Construire le nom final du fichier concaténé
    QString pathFichierRes = getValue(PATH_CONFIG, "paths", "dossierRapports")
                             + "/rapport_cheville_"
                             + QString::number(listeNumerosTest.count())
                             + "_"
                             + ui->comboBox_patient_courant->currentText().replace(" ", "_")
                             + "_"
                             + QDate::currentDate().toString("dd_MM_yyyy")
                             + ".pdf";

    // Liste des fichiers à concaténer
    QStringList fichiersAConcatener;
    fichiersAConcatener << pathPageGarde << pathFichierPdf;
    if (fichierInfoAnnexes.isFile()) {
        fichiersAConcatener << pathFichierAnnexes;
    }

    // Fusion des PDF
    bool reussi = lancerCmdPdftk(fichiersAConcatener, pathFichierRes);
    if (!reussi) {
        QMessageBox::information(this, tr("Erreur PDFTK"), "La commande PDFTK a échoué lors de la fusion finale.");
        ecrireLog("La commande PDFTK a échoué : fichiers = " + fichiersAConcatener.join(" + ") + " => " + pathFichierRes);
        return;
    }

    // Créer une copie horodatée du fichier final
    QFileInfo fichierInfoRes(pathFichierRes);
    QString pathFichierCopie = getValue(PATH_CONFIG, "paths", "dossierBackupRapports") + "/" + fichierInfoRes.baseName()
                               + "_" + QDateTime::currentDateTime().toString("ddMMyyyy_hhmmsszzz") + ".pdf";
    copyFile(pathFichierRes, pathFichierCopie);

    // Message succès
    QMessageBox::information(this, tr("Rapport généré"),
                             "Le rapport genou numéro " + QString::number(listeNumerosTest.count()) +
                             " pour le patient " + ui->comboBox_patient_courant->currentText() + " a été enregistré !");

    // Ouvrir le PDF
    QUrl pdfUrl = QUrl::fromLocalFile(pathFichierRes);
    if (!QDesktopServices::openUrl(pdfUrl)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier PDF automatiquement."));
    }

    // Gerer interface
    viderInfosRapport();

    // On revient la ou on en etait
    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);
    //reset widget
    ui->scrollArea->setWidget(ui->widget_cheville);

    ui->pushButton_generer_rapport->setText("Generer le rapport");
    ui->comboBox_dateBilan->setEnabled(true);
    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);
    ui->pushButton_editer_bilan->setEnabled(true);

    ui->pushButton_annulerEditionRapport->setVisible(false);

    this->mapCheminsImages.clear();

    emit on_pushButton_rechercher_clicked();
}


/****************************************
/*
 *
 */
void MainWindow::on_pushButton_validerRapport_bpc_clicked()
{

    // Recuperer le chemin des fichiers pdf a recuperer pour le merge
    QString pathFichierAnnexes = ui->lineEdit_bpc_pathAnnexes->text();

    QStringList listeNumerosTest;

    for(int i = 0; i < ui->comboBox_dateBilan->currentText().toInt(); i++){
        listeNumerosTest.append(ui->comboBox_dateBilan->itemText(i));
    }

    // ecrire le QString html
    QString contenuHtml = remplirChaineHtmlCourse(listeNumerosTest);

    // generer le PDF resultat et en garder une copie
    genererRapportPdf(contenuHtml);

    QFileInfo fichierInfoAnnexes(pathFichierAnnexes);

    // Vérifier que le fichier rapport existe
    QString pathFichierPdf = getValue(PATH_CONFIG, "paths", "pdfRes");
    QFileInfo fichierInfoRapport(pathFichierPdf);

    if (!fichierInfoRapport.isFile()) {
        QMessageBox::information(this, tr("Erreur fichiers inexistants"), "Le fichier rapport n'existe pas ! : " + pathFichierPdf);
        return;
    }

    // Construire le chemin vers la page de garde
    QString pathPageGarde = QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "PageGardeCourse");

    // Construire le nom final du fichier concaténé
    QString pathFichierRes = getValue(PATH_CONFIG, "paths", "dossierRapports")
                             + "/rapport_course_"
                             + QString::number(listeNumerosTest.count())
                             + "_"
                             + ui->comboBox_patient_courant->currentText().replace(" ", "_")
                             + "_"
                             + QDate::currentDate().toString("dd_MM_yyyy")
                             + ".pdf";

    // Liste des fichiers à concaténer
    QStringList fichiersAConcatener;
    fichiersAConcatener << pathPageGarde << pathFichierPdf;
    if (fichierInfoAnnexes.isFile()) {
        fichiersAConcatener << pathFichierAnnexes;
    }

    // Fusion des PDF
    bool reussi = lancerCmdPdftk(fichiersAConcatener, pathFichierRes);
    if (!reussi) {
        QMessageBox::information(this, tr("Erreur PDFTK"), "La commande PDFTK a échoué lors de la fusion finale.");
        ecrireLog("La commande PDFTK a échoué : fichiers = " + fichiersAConcatener.join(" + ") + " => " + pathFichierRes);
        return;
    }

    // Créer une copie horodatée du fichier final
    QFileInfo fichierInfoRes(pathFichierRes);
    QString pathFichierCopie = getValue(PATH_CONFIG, "paths", "dossierBackupRapports") + "/" + fichierInfoRes.baseName()
                               + "_" + QDateTime::currentDateTime().toString("ddMMyyyy_hhmmsszzz") + ".pdf";
    copyFile(pathFichierRes, pathFichierCopie);

    // Message succès
    QMessageBox::information(this, tr("Rapport généré"),
                             "Le rapport genou numéro " + QString::number(listeNumerosTest.count()) +
                             " pour le patient " + ui->comboBox_patient_courant->currentText() + " a été enregistré !");

    // Ouvrir le PDF
    QUrl pdfUrl = QUrl::fromLocalFile(pathFichierRes);
    if (!QDesktopServices::openUrl(pdfUrl)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier PDF automatiquement."));
    }

    // Gerer interface
    viderInfosRapport();

    // On revient la ou on en etait
    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);
    //reset widget
    ui->scrollArea->setWidget(ui->widget_bpc);

    ui->pushButton_generer_rapport->setText("Generer le rapport");
    ui->comboBox_dateBilan->setEnabled(true);
    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);
    ui->pushButton_editer_bilan->setEnabled(true);

    ui->pushButton_annulerEditionRapport->setVisible(false);

    this->mapCheminsImages.clear();

    emit on_pushButton_rechercher_clicked();
}


/****************************************
/*
 *
 */
void MainWindow::on_pushButton_validerRapport_bpsc_clicked()
{
    // Recuperer le chemin des fichiers pdf a recuperer pour le merge
    QString pathFichierAnnexes = ui->lineEdit_bpsc_pathAnnexes->text();

    QStringList listeNumerosTest;

    for(int i = 0; i < ui->comboBox_dateBilan->currentText().toInt(); i++){
        listeNumerosTest.append(ui->comboBox_dateBilan->itemText(i));
    }

    // ecrire le QString html
    QString contenuHtml = remplirChaineHtmlSportCollectif(listeNumerosTest);

    // generer le PDF resultat et en garder une copie
    genererRapportPdf(contenuHtml);

    QFileInfo fichierInfoAnnexes(pathFichierAnnexes);

    // Vérifier que le fichier rapport existe
    QString pathFichierPdf = getValue(PATH_CONFIG, "paths", "pdfRes");
    QFileInfo fichierInfoRapport(pathFichierPdf);

    if (!fichierInfoRapport.isFile()) {
        QMessageBox::information(this, tr("Erreur fichiers inexistants"), "Le fichier rapport n'existe pas ! : " + pathFichierPdf);
        return;
    }

    // Construire le chemin vers la page de garde
    QString pathPageGarde = QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "PageGardeCollectif");

    // Construire le nom final du fichier concaténé
    QString pathFichierRes = getValue(PATH_CONFIG, "paths", "dossierRapports")
                             + "/rapport_collectif_"
                             + QString::number(listeNumerosTest.count())
                             + "_"
                             + ui->comboBox_patient_courant->currentText().replace(" ", "_")
                             + "_"
                             + QDate::currentDate().toString("dd_MM_yyyy")
                             + ".pdf";

    // Liste des fichiers à concaténer
    QStringList fichiersAConcatener;
    fichiersAConcatener << pathPageGarde << pathFichierPdf;
    if (fichierInfoAnnexes.isFile()) {
        fichiersAConcatener << pathFichierAnnexes;
    }

    // Fusion des PDF
    bool reussi = lancerCmdPdftk(fichiersAConcatener, pathFichierRes);
    if (!reussi) {
        QMessageBox::information(this, tr("Erreur PDFTK"), "La commande PDFTK a échoué lors de la fusion finale.");
        ecrireLog("La commande PDFTK a échoué : fichiers = " + fichiersAConcatener.join(" + ") + " => " + pathFichierRes);
        return;
    }

    // Créer une copie horodatée du fichier final
    QFileInfo fichierInfoRes(pathFichierRes);
    QString pathFichierCopie = getValue(PATH_CONFIG, "paths", "dossierBackupRapports") + "/" + fichierInfoRes.baseName()
                               + "_" + QDateTime::currentDateTime().toString("ddMMyyyy_hhmmsszzz") + ".pdf";
    copyFile(pathFichierRes, pathFichierCopie);

    // Message succès
    QMessageBox::information(this, tr("Rapport généré"),
                             "Le rapport genou numéro " + QString::number(listeNumerosTest.count()) +
                             " pour le patient " + ui->comboBox_patient_courant->currentText() + " a été enregistré !");

    // Ouvrir le PDF
    QUrl pdfUrl = QUrl::fromLocalFile(pathFichierRes);
    if (!QDesktopServices::openUrl(pdfUrl)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier PDF automatiquement."));
    }

    // Gerer interface
    viderInfosRapport();

    // On revient la ou on en etait
    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);
    //reset widget
    ui->scrollArea->setWidget(ui->widget_bpsc);

    ui->pushButton_generer_rapport->setText("Generer le rapport");
    ui->comboBox_dateBilan->setEnabled(true);
    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);
    ui->pushButton_editer_bilan->setEnabled(true);

    ui->pushButton_annulerEditionRapport->setVisible(false);

    this->mapCheminsImages.clear();

    emit on_pushButton_rechercher_clicked();
}

//****************************************
/*
 *
 */
void MainWindow::on_pushButton_validerRapport_bpf_clicked()
{

    // Recuperer le chemin des fichiers pdf a recuperer pour le merge
    QString pathFichierAnnexes = ui->lineEdit_bpf_pathAnnexes->text();

    QStringList listeNumerosTest;

    for(int i = 0; i < ui->comboBox_dateBilan->currentText().toInt(); i++){
        listeNumerosTest.append(ui->comboBox_dateBilan->itemText(i));
    }

    // ecrire le QString html
    QString contenuHtml = remplirChaineHtmlSportCombat(listeNumerosTest);

    // generer le PDF resultat et en garder une copie
    genererRapportPdf(contenuHtml);

    QFileInfo fichierInfoAnnexes(pathFichierAnnexes);

    // Vérifier que le fichier rapport existe
    QString pathFichierPdf = getValue(PATH_CONFIG, "paths", "pdfRes");
    QFileInfo fichierInfoRapport(pathFichierPdf);

    if (!fichierInfoRapport.isFile()) {
        QMessageBox::information(this, tr("Erreur fichiers inexistants"), "Le fichier rapport n'existe pas ! : " + pathFichierPdf);
        return;
    }

    // Construire le chemin vers la page de garde
    QString pathPageGarde = QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "PageGardeCombat");

    // Construire le nom final du fichier concaténé
    QString pathFichierRes = getValue(PATH_CONFIG, "paths", "dossierRapports")
                             + "/rapport_combat_"
                             + QString::number(listeNumerosTest.count())
                             + "_"
                             + ui->comboBox_patient_courant->currentText().replace(" ", "_")
                             + "_"
                             + QDate::currentDate().toString("dd_MM_yyyy")
                             + ".pdf";

    // Liste des fichiers à concaténer
    QStringList fichiersAConcatener;
    fichiersAConcatener << pathPageGarde << pathFichierPdf;
    if (fichierInfoAnnexes.isFile()) {
        fichiersAConcatener << pathFichierAnnexes;
    }

    // Fusion des PDF
    bool reussi = lancerCmdPdftk(fichiersAConcatener, pathFichierRes);
    if (!reussi) {
        QMessageBox::information(this, tr("Erreur PDFTK"), "La commande PDFTK a échoué lors de la fusion finale.");
        ecrireLog("La commande PDFTK a échoué : fichiers = " + fichiersAConcatener.join(" + ") + " => " + pathFichierRes);
        return;
    }

    // Créer une copie horodatée du fichier final
    QFileInfo fichierInfoRes(pathFichierRes);
    QString pathFichierCopie = getValue(PATH_CONFIG, "paths", "dossierBackupRapports") + "/" + fichierInfoRes.baseName()
                               + "_" + QDateTime::currentDateTime().toString("ddMMyyyy_hhmmsszzz") + ".pdf";
    copyFile(pathFichierRes, pathFichierCopie);

    // Message succès
    QMessageBox::information(this, tr("Rapport généré"),
                             "Le rapport genou numéro " + QString::number(listeNumerosTest.count()) +
                             " pour le patient " + ui->comboBox_patient_courant->currentText() + " a été enregistré !");

    // Ouvrir le PDF
    QUrl pdfUrl = QUrl::fromLocalFile(pathFichierRes);
    if (!QDesktopServices::openUrl(pdfUrl)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier PDF automatiquement."));
    }

    // Gerer interface
    viderInfosRapport();

    // On revient la ou on en etait
    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);
    //reset widget
    ui->scrollArea->setWidget(ui->widget_bpf);

    ui->pushButton_generer_rapport->setText("Generer le rapport");
    ui->comboBox_dateBilan->setEnabled(true);
    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);
    ui->pushButton_editer_bilan->setEnabled(true);

    ui->pushButton_annulerEditionRapport->setVisible(false);

    this->mapCheminsImages.clear();

    emit on_pushButton_rechercher_clicked();
}

void MainWindow::on_pushButton_validerRapport_bpcf_clicked()
{
    // Recuperer le chemin des fichiers pdf a recuperer pour le merge
    QString pathFichierAnnexes = ui->lineEdit_bpcf_pathAnnexes->text();

    QStringList listeNumerosTest;

    for(int i = 0; i < ui->comboBox_dateBilan->currentText().toInt(); i++){
        listeNumerosTest.append(ui->comboBox_dateBilan->itemText(i));
    }

    // ecrire le QString html
    QString contenuHtml = remplirChaineHtmlCrossfit(listeNumerosTest);

    // generer le PDF resultat et en garder une copie
    genererRapportPdf(contenuHtml);

    QFileInfo fichierInfoAnnexes(pathFichierAnnexes);

    // Vérifier que le fichier rapport existe
    QString pathFichierPdf = getValue(PATH_CONFIG, "paths", "pdfRes");
    QFileInfo fichierInfoRapport(pathFichierPdf);

    if (!fichierInfoRapport.isFile()) {
        QMessageBox::information(this, tr("Erreur fichiers inexistants"), "Le fichier rapport n'existe pas ! : " + pathFichierPdf);
        return;
    }

    // Construire le chemin vers la page de garde
    QString pathPageGarde = QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "PageGardeCrossfit");

    // Construire le nom final du fichier concaténé
    QString pathFichierRes = getValue(PATH_CONFIG, "paths", "dossierRapports")
                             + "/rapport_crossfit_"
                             + QString::number(listeNumerosTest.count())
                             + "_"
                             + ui->comboBox_patient_courant->currentText().replace(" ", "_")
                             + "_"
                             + QDate::currentDate().toString("dd_MM_yyyy")
                             + ".pdf";

    // Liste des fichiers à concaténer
    QStringList fichiersAConcatener;
    fichiersAConcatener << pathPageGarde << pathFichierPdf;
    if (fichierInfoAnnexes.isFile()) {
        fichiersAConcatener << pathFichierAnnexes;
    }

    // Fusion des PDF
    bool reussi = lancerCmdPdftk(fichiersAConcatener, pathFichierRes);
    if (!reussi) {
        QMessageBox::information(this, tr("Erreur PDFTK"), "La commande PDFTK a échoué lors de la fusion finale.");
        ecrireLog("La commande PDFTK a échoué : fichiers = " + fichiersAConcatener.join(" + ") + " => " + pathFichierRes);
        return;
    }

    // Créer une copie horodatée du fichier final
    QFileInfo fichierInfoRes(pathFichierRes);
    QString pathFichierCopie = getValue(PATH_CONFIG, "paths", "dossierBackupRapports") + "/" + fichierInfoRes.baseName()
                               + "_" + QDateTime::currentDateTime().toString("ddMMyyyy_hhmmsszzz") + ".pdf";
    copyFile(pathFichierRes, pathFichierCopie);

    // Message succès
    QMessageBox::information(this, tr("Rapport généré"),
                             "Le rapport genou numéro " + QString::number(listeNumerosTest.count()) +
                             " pour le patient " + ui->comboBox_patient_courant->currentText() + " a été enregistré !");

    // Ouvrir le PDF
    QUrl pdfUrl = QUrl::fromLocalFile(pathFichierRes);
    if (!QDesktopServices::openUrl(pdfUrl)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier PDF automatiquement."));
    }

    // Gerer interface
    viderInfosRapport();

    // On revient la ou on en etait
    ui->scrollArea->takeWidget();
    //set this property
    ui->scrollArea->setWidgetResizable(false);
    //reset widget
    ui->scrollArea->setWidget(ui->widget_bpcf);

    ui->pushButton_generer_rapport->setText("Generer le rapport");
    ui->comboBox_dateBilan->setEnabled(true);
    ui->comboBox_type_Bilan->setEnabled(true);
    ui->comboBox_patient_courant->setEnabled(true);
    ui->pushButton_rechercher->setEnabled(true);
    ui->pushButton_editer_bilan->setEnabled(true);

    ui->pushButton_annulerEditionRapport->setVisible(false);

    this->mapCheminsImages.clear();

    emit on_pushButton_rechercher_clicked();
}



//****************************************
/*
 *
 */
void MainWindow::on_toolButton_g_clicked(){

    QFileDialog dialog(this);
    dialog.setNameFilter(tr("*.jpg"));
    dialog.setViewMode(QFileDialog::Detail);

    QString fileName  = QFileDialog::getOpenFileName(this,tr("Selectionnez les annexes"), "/home", tr("*.pdf"));

    QRegularExpression regex("[!@#$%^&*(),?\"¨+^{¤}|<>]");

    if(fileName.contains(regex))
        QMessageBox::warning(this, tr("Nom du fichier non pris en charge"), "Veuillez renommer le fichier sans "
                                                                            "caracteres speciaux, le plus simple possible !");
    else
        ui->lineEdit_g_pathAnnexes->setText(fileName);
}

//****************************************
/*
 *
 */
void MainWindow::on_toolButton_e_clicked(){
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("*.jpg"));
    dialog.setViewMode(QFileDialog::Detail);

    QString fileName  = QFileDialog::getOpenFileName(this,tr("Selectionnez les annexes"), "/home", tr("*.pdf"));

    QRegularExpression regex("[!@#$%^&*(),?\"¨+^{¤}|<>]");

    if(fileName.contains(regex))
        QMessageBox::warning(this, tr("Nom du fichier non pris en charge"), "Veuillez renommer le fichier sans "
                                                                            "caracteres speciaux, le plus simple possible !");
    else
        ui->lineEdit_e_pathAnnexes->setText(fileName);
}

//****************************************
/*
 *
 */
void MainWindow::on_toolButton_h_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("*.jpg"));
    dialog.setViewMode(QFileDialog::Detail);

    QString fileName  = QFileDialog::getOpenFileName(this,tr("Selectionnez les annexes"), "/home", tr("*.pdf"));

    QRegularExpression regex("[!@#$%^&*(),?\"¨+^{¤}|<>]");

    if(fileName.contains(regex))
        QMessageBox::warning(this, tr("Nom du fichier non pris en charge"), "Veuillez renommer le fichier sans "
                                                                            "caracteres speciaux, le plus simple possible !");
    else
        ui->lineEdit_h_pathAnnexes->setText(fileName);
}

//****************************************
/*
 *
 */
void MainWindow::on_toolButton_c_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("*.jpg"));
    dialog.setViewMode(QFileDialog::Detail);

    QString fileName  = QFileDialog::getOpenFileName(this,tr("Selectionnez les annexes"), "/home", tr("*.pdf"));

    QRegularExpression regex("[!@#$%^&*(),?\"¨+^{¤}|<>]");

    if(fileName.contains(regex))
        QMessageBox::warning(this, tr("Nom du fichier non pris en charge"), "Veuillez renommer le fichier sans "
                                                                            "caracteres speciaux, le plus simple possible !");
    else
        ui->lineEdit_c_pathAnnexes->setText(fileName);
}

/****************************************
/*
 *
 */
void MainWindow::on_toolButton_bpc_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("*.jpg"));
    dialog.setViewMode(QFileDialog::Detail);

    QString fileName  = QFileDialog::getOpenFileName(this,tr("Selectionnez les annexes"), "/home", tr("*.pdf"));

    QRegularExpression regex("[!@#$%^&*(),?\"¨+^{¤}|<>]");

    if(fileName.contains(regex))
        QMessageBox::warning(this, tr("Nom du fichier non pris en charge"), "Veuillez renommer le fichier sans "
                                                                            "caracteres speciaux, le plus simple possible !");
    else
        ui->lineEdit_bpc_pathAnnexes->setText(fileName);
}

/****************************************
/*
 *
 */
void MainWindow::on_toolButton_bpsc_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("*.jpg"));
    dialog.setViewMode(QFileDialog::Detail);

    QString fileName  = QFileDialog::getOpenFileName(this,tr("Selectionnez les annexes"), "/home", tr("*.pdf"));

    QRegularExpression regex("[!@#$%^&*(),?\"¨+^{¤}|<>]");

    if(fileName.contains(regex))
        QMessageBox::warning(this, tr("Nom du fichier non pris en charge"), "Veuillez renommer le fichier sans "
                                                                            "caracteres speciaux, le plus simple possible !");
    else
        ui->lineEdit_bpsc_pathAnnexes->setText(fileName);
}

void MainWindow::on_toolButton_bpf_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("*.jpg"));
    dialog.setViewMode(QFileDialog::Detail);

    QString fileName  = QFileDialog::getOpenFileName(this,tr("Selectionnez les annexes"), "/home", tr("*.pdf"));

    QRegularExpression regex("[!@#$%^&*(),?\"¨+^{¤}|<>]");

    if(fileName.contains(regex))
        QMessageBox::warning(this, tr("Nom du fichier non pris en charge"), "Veuillez renommer le fichier sans "
                                                                            "caracteres speciaux, le plus simple possible !");
    else
        ui->lineEdit_bpf_pathAnnexes->setText(fileName);
}


//****************************************
/*
 *
 */
void MainWindow::on_comboBox_dateBilan_currentTextChanged(const QString &numeroTest){

    QMap<QString, QString> mapInfos;

    // SETTINGS
    if(ui->comboBox_type_Bilan->currentText() == "Genou"){
        mapInfos = recupererInfosBilanGenouBdd(numeroTest);
    }
    else if(ui->comboBox_type_Bilan->currentText() == "Epaule"){
        mapInfos = recupererInfosBilanEpauleBdd(numeroTest);
    }
    else if(ui->comboBox_type_Bilan->currentText() == "Hanche"){
        mapInfos = recupererInfosBilanHancheBdd(numeroTest);
    }
    else if(ui->comboBox_type_Bilan->currentText() == "Cheville"){
        mapInfos = recupererInfosBilanChevilleBdd(numeroTest);
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "Course")){
        mapInfos = recupererInfosBilanBpcBdd(numeroTest);
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "collectif")){
        mapInfos = recupererInfosBilanBpscBdd(numeroTest);
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "Combat")){
        mapInfos = recupererInfosBilanBpfBdd(numeroTest);
    }
    else if(ui->comboBox_type_Bilan->currentText().contains( "Crossfit")){
        mapInfos = recupererInfosBilanBpcfBdd(numeroTest);
    }

    if(mapInfos.size() == 0){
        viderInfosBilan();

        // SETTINGS
        ui->widget_genou->setEnabled(false);
        ui->widget_epaule->setEnabled(false);
        ui->widget_hanche->setEnabled(false);
        ui->widget_cheville->setEnabled(false);
        ui->widget_bpc->setEnabled(false);
        ui->widget_bpsc->setEnabled(false);
        ui->widget_bpf->setEnabled(false);
        ui->widget_bpcf->setEnabled(false);
    }
    else{
        // SETTINGS
        // Mettre a jour les boutons
        ui->pushButton_valider_bilan->setVisible(false);
        ui->pushButton_valider_bilan_epaule->setVisible(false);
        ui->pushButton_valider_bilan_hanche->setVisible(false);
        ui->pushButton_valider_bilan_cheville->setVisible(false);
        ui->pushButton_valider_bilan_bpc->setVisible(false);
        ui->pushButton_valider_bilan_bpsc->setVisible(false);
        ui->pushButton_valider_bilan_bpf->setVisible(false);
        ui->pushButton_valider_bilan_bpcf->setVisible(false);

        if(ui->comboBox_type_Bilan->currentText() == "Genou"){

            QStringList listeColonnesValeursInt;
            listeColonnesValeursInt << "testRSI" << "kStart";

            QStringList listeColonnesCheckBox;
            listeColonnesCheckBox << "receptionMedioPied" << "receptionAvantPied" << "receptionBordInterne" << "receptionTalon";

            QStringList listeRadio;
            listeRadio << "controleGenouFrontal" << "controleGenouValgus" << "controleTroncOK" << "controleTroncNOK" << "angleFlexionNOK" << "angleFlexionOK";

            QMapIterator<QString, QString> iterateur(mapInfos);
            while(iterateur.hasNext()){

                iterateur.next();

                // TODO ATTENTION MODIFICATION infosBilanBenou
                //Remplissage des donnees depuis la bdd
                if(iterateur.key() != "idTypeBilan" && iterateur.key() != "dateBilan" && iterateur.key() != "idPatient"
                    && iterateur.key() != "numeroTest"){

                    ecrireLog("Remplissage du GUI genou avec la colonne bdd " + iterateur.key() + " et de valeur --> " + iterateur.value());

                    if(iterateur.key() == "testAccroupissement"){
                        QComboBox *object1 = this->findChild<QComboBox *>("comboBox_g_" + iterateur.key());
                        object1->setCurrentText(iterateur.value());
                    }
                    else if(listeColonnesCheckBox.contains(iterateur.key())){
                        QCheckBox *object = this->findChild<QCheckBox *>("checkBox_g_" + iterateur.key());

                        if(iterateur.value().contains("0"))
                            object->setChecked(false);
                        else if(iterateur.value().contains("1"))
                            object->setChecked(true);

                    }
                    else if(listeRadio.contains(iterateur.key())){
                        QRadioButton *object = this->findChild<QRadioButton *>("radioButton_g_" + iterateur.key());

                        if(iterateur.value().contains("0"))
                            object->setChecked(false);
                        else if(iterateur.value().contains("1"))
                            object->setChecked(true);
                    }
                    else if(listeColonnesValeursInt.contains(iterateur.key())){
                        QSpinBox *object = this->findChild<QSpinBox *>("spinBox_g_" + iterateur.key());
                        object->setValue(iterateur.value().toInt());
                    }
                    else{
                        QDoubleSpinBox *object = this->findChild<QDoubleSpinBox *>("doubleSpinBox_g_" + iterateur.key());
                        object->setValue(iterateur.value().toDouble());
                    }
                }
            }
        }
        else if(ui->comboBox_type_Bilan->currentText() == "Epaule"){

            QStringList listeColonnesValeursInt;
            listeColonnesValeursInt << "testSIRSI" << "sStart" << "nbRepetitionsNO" << "nbRepetitionsO";

            QStringList listeComboBox;
            listeComboBox << "brasOpere" << "mainDominante" << "testInstabiliteA" << "testInstabiliteP" << "rotationInterneR1NO" << "rotationInterneR1O";

            QMapIterator<QString, QString> iterateur(mapInfos);
            while(iterateur.hasNext()){

                iterateur.next();

                // TODO ATTENTION MODIFICATION infosBilanEpaule
                if(iterateur.key() != "idTypeBilan" && iterateur.key() != "dateBilan" && iterateur.key() != "idPatient"
                    && iterateur.key() != "numeroTest"){

                    ecrireLog("Remplissage du GUI epaule avec la colonne bdd " + iterateur.key() + " et de valeur --> " + iterateur.value());

                    if(listeComboBox.contains(iterateur.key())){
                        QComboBox *object1 = this->findChild<QComboBox *>("comboBox_e_" + iterateur.key());
                        object1->setCurrentText(iterateur.value());
                    }
                    else if(listeColonnesValeursInt.contains(iterateur.key())){
                        QSpinBox *object = this->findChild<QSpinBox *>("spinBox_e_" + iterateur.key());
                        object->setValue(iterateur.value().toInt());
                    }
                    else{
                        QDoubleSpinBox *object = this->findChild<QDoubleSpinBox *>("doubleSpinBox_e_" + iterateur.key());
                        object->setValue(iterateur.value().toDouble());
                    }
                }
            }
        }
        else if(ui->comboBox_type_Bilan->currentText() == "Hanche"){

            QStringList listeColonnesCheckBox;
            listeColonnesCheckBox << "receptionMedioPied" << "receptionAvantPied" << "receptionBordInterne" << "receptionTalon";

            QStringList listeRadio;
            listeRadio << "controleGenouFrontal" << "controleGenouValgus" << "controleTroncOK" << "controleTroncNOK" << "angleFlexionNOK" << "angleFlexionOK";

            QMapIterator<QString, QString> iterateur(mapInfos);
            while(iterateur.hasNext()){

                iterateur.next();

                // TODO ATTENTION MODIFICATION infosBilanHanche
                //Remplissage des donnees depuis la bdd
                if(iterateur.key() != "idTypeBilan" && iterateur.key() != "dateBilan" && iterateur.key() != "idPatient"
                    && iterateur.key() != "numeroTest"){

                    ecrireLog("Remplissage du GUI Hanche avec la colonne bdd " + iterateur.key() + " et de valeur --> " + iterateur.value());

                    if(iterateur.key() == "testAccroupissement"){
                        QComboBox *object1 = this->findChild<QComboBox *>("comboBox_h_" + iterateur.key());
                        object1->setCurrentText(iterateur.value());
                    }
                    else if(listeColonnesCheckBox.contains(iterateur.key())){
                        QCheckBox *object = this->findChild<QCheckBox *>("checkBox_h_" + iterateur.key());

                        if(iterateur.value().contains("0"))
                            object->setChecked(false);
                        else if(iterateur.value().contains("1"))
                            object->setChecked(true);

                    }
                    else if(listeRadio.contains(iterateur.key())){
                        QRadioButton *object = this->findChild<QRadioButton *>("radioButton_h_" + iterateur.key());

                        if(iterateur.value().contains("0"))
                            object->setChecked(false);
                        else if(iterateur.value().contains("1"))
                            object->setChecked(true);
                    }
                    else{
                        QDoubleSpinBox *object = this->findChild<QDoubleSpinBox *>("doubleSpinBox_h_" + iterateur.key());
                        object->setValue(iterateur.value().toDouble());
                    }
                }
            }
        }
        else if(ui->comboBox_type_Bilan->currentText() == "Cheville"){

            QStringList listeColonnesCheckBox;
            listeColonnesCheckBox << "receptionMedioPied" << "receptionAvantPied" << "receptionBordInterne" << "receptionTalon";

            QStringList listeRadio;
            listeRadio << "controleGenouFrontal" << "controleGenouValgus" << "controleTroncOK" << "controleTroncNOK" << "angleFlexionNOK" << "angleFlexionOK";

            QStringList listeComboBox;
            listeComboBox << "chevilleOperee";

            QStringList listeColonnesValeursInt;
            listeColonnesValeursInt << "alrRsi";

            QMapIterator<QString, QString> iterateur(mapInfos);
            while(iterateur.hasNext()){

                iterateur.next();

                // TODO ATTENTION MODIFICATION infosBilanHanche
                //Remplissage des donnees depuis la bdd
                if(iterateur.key() != "idTypeBilan" && iterateur.key() != "dateBilan" && iterateur.key() != "idPatient"
                    && iterateur.key() != "numeroTest"){

                    ecrireLog("Remplissage du GUI Cheville avec la colonne bdd " + iterateur.key() + " et de valeur --> " + iterateur.value());

                    if(iterateur.key() == "testAccroupissement"){
                        QComboBox *object1 = this->findChild<QComboBox *>("comboBox_c_" + iterateur.key());
                        object1->setCurrentText(iterateur.value());
                    }
                    else if(listeComboBox.contains(iterateur.key())){
                        QComboBox *object1 = this->findChild<QComboBox *>("comboBox_c_" + iterateur.key());
                        object1->setCurrentText(iterateur.value());
                    }
                    else if(listeColonnesCheckBox.contains(iterateur.key())){
                        QCheckBox *object = this->findChild<QCheckBox *>("checkBox_c_" + iterateur.key());

                        if(iterateur.value().contains("0"))
                            object->setChecked(false);
                        else if(iterateur.value().contains("1"))
                            object->setChecked(true);

                    }
                    else if(listeRadio.contains(iterateur.key())){
                        QRadioButton *object = this->findChild<QRadioButton *>("radioButton_c_" + iterateur.key());

                        if(iterateur.value().contains("0"))
                            object->setChecked(false);
                        else if(iterateur.value().contains("1"))
                            object->setChecked(true);
                    }
                    else if(listeColonnesValeursInt.contains(iterateur.key())){
                        QSpinBox *object = this->findChild<QSpinBox *>("spinBox_c_" + iterateur.key());
                        object->setValue(iterateur.value().toInt());
                    }
                    else{
                        QDoubleSpinBox *object = this->findChild<QDoubleSpinBox *>("doubleSpinBox_c_" + iterateur.key());
                        object->setValue(iterateur.value().toDouble());
                    }
                }
            }
        }
        else if(ui->comboBox_type_Bilan->currentText().contains("Course")){
            QStringList listeColonnesCheckBox;
            QStringList listeRadio;
            QStringList listeColonnesValeursInt;

            QMapIterator<QString, QString> iterateur(mapInfos);
            while(iterateur.hasNext()){

                iterateur.next();

                // TODO ATTENTION MODIFICATION infosBilanHanche
                //Remplissage des donnees depuis la bdd
                if(iterateur.key() != "idTypeBilan" && iterateur.key() != "dateBilan" && iterateur.key() != "idPatient"
                    && iterateur.key() != "numeroTest"){

                    ecrireLog("Remplissage du GUI Course avec la colonne bdd " + iterateur.key() + " et de valeur --> " + iterateur.value());

                    if(iterateur.key() == "texteRachis"){
                        ui->lineEdit_bpc_textRachis->setText(iterateur.value());
                    }
                    else{
                        QDoubleSpinBox *object = this->findChild<QDoubleSpinBox *>("doubleSpinBox_bpc_" + iterateur.key());
                        object->setValue(iterateur.value().toDouble());
                    }
                }
            }
        }
        else if(ui->comboBox_type_Bilan->currentText().contains("collectif")){
            QStringList listeRadio;
            listeRadio << "controleGenouFrontal" << "controleGenouValgus" << "controleTroncOK" << "controleTroncNOK" << "angleFlexionNOK" << "angleFlexionOK";

            QMapIterator<QString, QString> iterateur(mapInfos);
            while(iterateur.hasNext()){

                iterateur.next();

                // TODO ATTENTION MODIFICATION infosBilanBenou
                //Remplissage des donnees depuis la bdd
                if(iterateur.key() != "idTypeBilan" && iterateur.key() != "dateBilan" && iterateur.key() != "idPatient"
                    && iterateur.key() != "numeroTest"){

                    ecrireLog("Remplissage du GUI genou avec la colonne bdd " + iterateur.key() + " et de valeur --> " + iterateur.value());

                    if(listeRadio.contains(iterateur.key())){
                        QRadioButton *object = this->findChild<QRadioButton *>("radioButton_bpsc_" + iterateur.key());

                        if(iterateur.value().contains("0"))
                            object->setChecked(false);
                        else if(iterateur.value().contains("1"))
                            object->setChecked(true);
                    }
                    else if(iterateur.key() == "texteRachis"){
                        ui->lineEdit_bpsc_textRachis->setText(iterateur.value());
                    }
                    else{
                        QDoubleSpinBox *object = this->findChild<QDoubleSpinBox *>("doubleSpinBox_bpsc_" + iterateur.key());
                        object->setValue(iterateur.value().toDouble());
                    }
                }
            }
        }
        else if(ui->comboBox_type_Bilan->currentText().contains("Combat")){

                QStringList listeComboBox;
                listeComboBox << "rotationInterneR1G" << "rotationInterneR1D";

                QMapIterator<QString, QString> iterateur(mapInfos);
                while(iterateur.hasNext()){

                    iterateur.next();

                    // TODO ATTENTION MODIFICATION infosBilanEpaule
                    if(iterateur.key() != "idTypeBilan" && iterateur.key() != "dateBilan" && iterateur.key() != "idPatient"
                       && iterateur.key() != "numeroTest"){

                    ecrireLog("Remplissage du GUI epaule avec la colonne bdd " + iterateur.key() + " et de valeur --> " + iterateur.value());

                    if(listeComboBox.contains(iterateur.key())){
                        QComboBox *object1 = this->findChild<QComboBox *>("comboBox_bpf_" + iterateur.key());
                        object1->setCurrentText(iterateur.value());
                    }
                    else if(iterateur.key() == "texteRachis"){
                        ui->lineEdit_bpf_textRachis->setText(iterateur.value());
                    }
                    else{
                        QDoubleSpinBox *object = this->findChild<QDoubleSpinBox *>("doubleSpinBox_bpf_" + iterateur.key());
                        object->setValue(iterateur.value().toDouble());
                    }
                }
            }
        }
        else if(ui->comboBox_type_Bilan->currentText().contains("Crossfit")){

                QStringList listeComboBox;
                listeComboBox << "rotationInterneR1G" << "rotationInterneR1D";

                QMapIterator<QString, QString> iterateur(mapInfos);
                while(iterateur.hasNext()){

                    iterateur.next();

                    // TODO ATTENTION MODIFICATION infosBilanEpaule
                    if(iterateur.key() != "idTypeBilan" && iterateur.key() != "dateBilan" && iterateur.key() != "idPatient"
                       && iterateur.key() != "numeroTest"){

                    ecrireLog("Remplissage du GUI epaule avec la colonne bdd " + iterateur.key() + " et de valeur --> " + iterateur.value());

                    if(listeComboBox.contains(iterateur.key())){
                        QComboBox *object1 = this->findChild<QComboBox *>("comboBox_bpcf_" + iterateur.key());
                        object1->setCurrentText(iterateur.value());
                    }
                    else if(iterateur.key() == "texteRachis"){
                        ui->lineEdit_bpcf_textRachis->setText(iterateur.value());
                    }
                    else{
                        QDoubleSpinBox *object = this->findChild<QDoubleSpinBox *>("doubleSpinBox_bpcf_" + iterateur.key());
                        object->setValue(iterateur.value().toDouble());
                    }
                }
            }
        }
    }
}

//****************************************
/*
 *
 */
void MainWindow::on_comboBox_patient_courant_currentTextChanged(const QString &arg1){

    ui->comboBox_dateBilan->setEnabled(false);
    ui->comboBox_dateBilan->clear();
    ui->pushButton_generer_rapport->setVisible(false);
}

//****************************************
/*
 *
 */
void MainWindow::on_comboBox_type_Bilan_currentTextChanged(const QString &arg1){
    emit on_comboBox_patient_courant_currentTextChanged(ui->comboBox_patient_courant->currentText());
}


//****************************************
/*
 *
 */
QString MainWindow::remplirChaineHtmlGenou(QStringList listeNumerosTest){

    QString res;

    // Recuperation de la base HTML
    QFile file(QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "nomFichierHtml"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream flux(&file);
    res = flux.readAll();

    file.close();

    // On commence a ecrire
    QSqlQuery requete;
    QString texteRequete;

    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();

    QStringList colonnesPatient = recupererListeColonnesTable("Patient");
    colonnesPatient.removeLast();

    QList<QPair<QString, QMap<QString, QString>>> listePairesRapport;

    foreach (QString numeroTestCourant, listeNumerosTest) {

        QPair<QString, QMap<QString, QString>> paireCourante;
        paireCourante.first = numeroTestCourant;
        paireCourante.second = recupererInfosBilanGenouBdd(numeroTestCourant);

        listePairesRapport.append(paireCourante);
    }


    //-----------------
    // Recuperer les donnees du patient et les inserer dans la liste
    QMap<QString, QString> mapInfosPatient;

    texteRequete = "SELECT * FROM Patient WHERE prenom LIKE '%" + prenomCourant +"%' AND nomFamille LIKE '%" + nomFamilleCourant + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }

    while (requete.next()) {

        for (int i = 0; i < colonnesPatient.count(); ++i) {
            mapInfosPatient.insert(colonnesPatient.at(i),requete.value(i).toString());
        }
    }

    res.append("<body>");

    // //-----------------
    // // ecrire le tableau des donnees du patient
    // //-----------------

    // // Si le patient a eu une intervention chirurgicale
    // QString texteInfosOperation;
    QString texteInfosCoteLese;
    // QString marginBottom;
    QString labelBlessure;
    QString typeBlessure;

    if(mapInfosPatient.value("estOpere") == "Non"){
        texteInfosCoteLese = "Côté lésé";
        labelBlessure = "lésé";
        typeBlessure = "Type de lésion";
    }
    else{
        texteInfosCoteLese = "Côté opéré";
        labelBlessure = "opéré";
        typeBlessure = "Type d'intervention chirurgicale";
    }

    // // Texte operation
    // if(mapInfosPatient.value("estOpere") == "Non"){
    //     marginBottom = "115px";
    // }
    // else{
    //     texteInfosOperation = texteInfosOperation +
    //             "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de l'operation : </td>"
    //             "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateOperation") +  "</td></tr>";

    //     marginBottom = "50px";
    // }
    // texteInfosOperation = texteInfosOperation +
    //         "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\">" + typeBlessure + " : </td>"
    //         "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("typeOperation") +  "</td></tr>";

    // // Informations
    // res = res + "<table style=\"border: none; margin-top:75px;margin-bottom:" + marginBottom + ";text-align:left;padding:10px 10px;\">"
    //                 "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding: 10px 10px;\">Nom et prénom : </td>"
    //                 "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("nomFamille") + " " + mapInfosPatient.value("prenom") + "</td></tr>"
    //                 "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de naissance : </td>"
    //                 "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateNaissance") +  "</td></tr>"
    //                 "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Sexe : </td>"
    //                 "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("sexe") +  "</td></tr>"
    //                 "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Taille : </td>"
    //                 "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("taille") +  "cm</td></tr>"
    //                 "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Poids : </td>"
    //                 "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("poids") +  "kg</td></tr>"
    //                 "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\">" + texteInfosCoteLese + " : </td>"
    //                 "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("coteBlesse") + "</td></tr>"
    //                 + texteInfosOperation +
    //             "</table>";

    // res = res +  "<p>Date du rapport : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>< /br>< /br>";

    // foreach (QString numeroTest, listeNumerosTest) {

    //     QString dateCourante = "Date du test numero T" + numeroTest + " : ";
    //     dateCourante = dateCourante + getMapListeRapport(listePairesRapport, numeroTest).value("dateBilan");
    //     res = res +  "<p>" + dateCourante + "</p>";
    // }

    // // Ecrire les infos du cabinet de Jordan
    // res = res + "<table style=\"margin-top:45px; width: 300px;text-align:center;\">"
    //             "<tr>"
    //             "<th scope=\"col\" style=\"background-color:transparent;font-weight:normal;color:#002e40;\">"
    //             "<p>Cabinet Kinesithérapie SCP 9 bis   -   9 bis Route de Launaguet, 31200 Toulouse</p>"
    //             "<p>scp9bis@gmail.com - 05 61 57 13 13</p></th>"
    //             "</tr>"
    //             "</table>";

    // // Ecrire les infos du cabinet d antho
    // res = res + "<table style=\"margin-top:45px; width: 300px;text-align:center;\">"
    //             "<tr>"
    //             "<th scope=\"col\" style=\"background-color:transparent;font-weight:normal;color:#002e40;\">"
    //             "<p>Cabinet Kiné Sport Rochois  - 21a chemin du Lycée, 74800 La Roche sur Foron</p>"
    //             "<p>kinesportrochois@gmail.com - 04 50 25 65 49</p></th>"
    //             "</tr>"
    //             "</table>";

    res = res +  "<DIV STYLE=\"page-break-before:always\"></DIV>";

    //Ecrire la legende
    QString legende = "<table><tr><th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Legende tableau</th>"
                      "<td style=\"background-color:#169d53; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Bon</td>"
                      "<td style=\"background-color:#ff9929; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Moyen</td>"
                      "<td style=\"background-color:#9f3f36; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Insuffisant</td></tr></table>";

    res.append(legende);

    // ecrire le tableau des amplitudes articulaires
    res.append(ecrireAmplitudesGenou(listePairesRapport, labelBlessure));

    // ecrire le tableau des testAccroupissement
    res.append(ecrireTestAcc(listePairesRapport));

    // ecrire le tableau des permietres
    res.append(ecrirePerimetres(listePairesRapport, labelBlessure));

    // ecrire le ACL RSI
    res.append(ecrireAclRsi(listePairesRapport));

    res.append("<h1 style=\"text-align:center;\">Tests et ratios de force isométrique</h1>");

    // ecrire le tableau du ration ischio jambiers quadri
    res.append(ecrireRatioIJ(listePairesRapport, labelBlessure));

    // ecrire le test de Mc Call
    res.append(ecrireMcCall(listePairesRapport, labelBlessure));

    //Nouvelle page si T3 ou T2
    if(listeNumerosTest.count() == 3 || listeNumerosTest.count() == 2)
        res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    // ecrire le tableau des abdd add
    res.append(ecrireRatioA(listePairesRapport, labelBlessure));

    res.append(ecrireRatioREHanche(listePairesRapport, labelBlessure));

    res.append("<h1 style=\"text-align:center;\">Tests de sauts verticaux</h1>");

    // ecrire le tableau du squatJump bipodal
    res.append(ecrireSjBipodal(listePairesRapport, labelBlessure));

    // ecrire le tableau du CMJ bipodal
    res.append(ecrireCmjBipodal(listePairesRapport, mapInfosPatient.value("sexe"), labelBlessure));

    //Nouvelle page si T3
    // if(listeNumerosTest.count() == 3)
    //     res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    // ecrire le tableau du drop jump bipodal
    res.append(ecrireDjBipodal(listePairesRapport, labelBlessure));

    //Nouvelle page si T1
    if(listeNumerosTest.count() == 1 || listeNumerosTest.count() == 2)
        res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    // ecrire le tableau du test CMJ unipodal
    res.append(ecrireCmjUnipodal(listePairesRapport, labelBlessure));

    // ecrire le tableau du drop jump unipodal
    res.append(ecrireDjUnipodal(listePairesRapport, labelBlessure));

    res.append("<h1 style=\"text-align:center;\">Tests fonctionnels</h1>");

    // ecrire les points de reception unipodale
    res.append(ecrirePointsReceptionUnipodale(listePairesRapport));

    //Ecrire tests Hop
    res.append(ecrireBroadJump(listePairesRapport, "genou"));
    res.append(ecrireHop(listePairesRapport, labelBlessure, "genou"));

    // ecrire le KSTart
    res.append(ecrirekStart(listePairesRapport, listeNumerosTest));

    //Nouvelle page si T2
    if(listeNumerosTest.count() == 2)
        res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    // Ecrire l interpretation du professionnel
    // Recuperer le texte interpretation
    bool presenceInfos = false;

    QString texteInfos;

    QString texteInterpretation = ui->textEdit_interpretationKine->toPlainText();

    if(texteInterpretation != ""){
        presenceInfos = true;
        texteInterpretation.replace("\n","<br/>");
        texteInterpretation.replace("[", "<span style=\"font-weight: bold;\">");
        texteInterpretation.replace("]", "</span>");

        texteInfos = texteInfos
                     + "<table style=\"margin-bottom:20px; width: 300px;\">"
                       "<tr>"
                       "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                       "<p style=\" font-size: 200px;font-weight: bold; text-align:left;\"> Interprétation du kinésithérapeute :<p>< br¨/>"
                       "<p style=\"text-align:left;\"><br>" + texteInterpretation +"</p></br>"
                                             "</th>"
                                             "</tr>"
                                             "</table>";
    }

    // Recuperer les libelles des checkBox coches
    QString texteAxes;
    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("checkBox_g")){

            QCheckBox *checkBox = dynamic_cast<QCheckBox*>(w);
            if (checkBox->isChecked()) {
                texteAxes = texteAxes + "<p style=\"text-align:left;\"><br> - " + checkBox->text() + "</br></p>< /br>";
            }
        }
    }

    if (texteAxes != "") {
        presenceInfos = true;
        texteInfos = texteInfos + "<table style=\"margin-bottom:20px; width: 300px;\">"
                                  "<tr>"
                                  "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                                  "<p style=\"font-size: 200px;font-weight: bold; text-align:left;\">Axes à améliorer :<p></br>";

        texteInfos.append(texteAxes);
    }

    if(presenceInfos){
        res.append(texteInfos);
    }

    res.append("</body></html>");

    return res;
}


//****************************************
/*
 *
 */
QString MainWindow::remplirChaineHtmlEpaule(QStringList listeNumerosTest){

    QString res;

    // Recuperation de la base HTML
    QFile file(QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "nomFichierHtml"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream flux(&file);
    res = flux.readAll();

    file.close();


    // On commence a ecrire
    QSqlQuery requete;
    QString texteRequete;

    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();

    QStringList colonnesPatient = recupererListeColonnesTable("Patient");
    colonnesPatient.removeLast();

    QList<QPair<QString, QMap<QString, QString>>> listePairesRapport;

    foreach (QString numeroTestCourant, listeNumerosTest) {

        QPair<QString, QMap<QString, QString>> paireCourante;
        paireCourante.first = numeroTestCourant;
        paireCourante.second = recupererInfosBilanEpauleBdd(numeroTestCourant);

        listePairesRapport.append(paireCourante);
    }


    //-----------------
    // Recuperer les donnees du patient et les inserer dans la liste
    QMap<QString, QString> mapInfosPatient;

    texteRequete = "SELECT * FROM Patient WHERE prenom LIKE '%" + prenomCourant +"%' AND nomFamille LIKE '%" + nomFamilleCourant + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }

    while (requete.next()) {

        for (int i = 0; i < colonnesPatient.count(); ++i) {
            mapInfosPatient.insert(colonnesPatient.at(i),requete.value(i).toString());
        }
    }

    res.append("<body>");

    //-----------------
    // ecrire le tableau des donnees du patient
    //-----------------

    // Si le patient a eu une intervention chirurgicale
    QString texteInfosOperation;
    QString texteInfosCoteLese;
    QString marginBottom;
    QString labelBlessure;
    QString typeBlessure;

    if(mapInfosPatient.value("estOpere") == "Non"){
        texteInfosCoteLese = "Côté lésé";
        labelBlessure = "lésé";
        typeBlessure = "Type de lésion";
    }
    else{
        texteInfosCoteLese = "Côté opéré";
        labelBlessure = "opéré";
        typeBlessure = "Type d'intervention chirurgicale";
    }

    // Texte operation
    if(mapInfosPatient.value("estOpere") == "Non"){
        marginBottom = "90px";
    }
    else{
        texteInfosOperation = texteInfosOperation +
                "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de l'operation : </td>"
                "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateOperation") +  "</td></tr>";

        marginBottom = "50px";
    }
    texteInfosOperation = texteInfosOperation +
            "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\">" + typeBlessure + " : </td>"
            "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("typeOperation") +  "</td></tr>";

    // Informations
    res = res + "<table style=\"border: none; margin-top:75px;margin-bottom:" + marginBottom + ";text-align:left;padding:10px 10px;\">"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding: 10px 10px;\">Nom et prénom : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("nomFamille") + " " + mapInfosPatient.value("prenom") + "</td></tr>"

                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de naissance : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateNaissance") +  "</td></tr>"

                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Sexe : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("sexe") +  "</td></tr>"

                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Taille : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("taille") +  "cm</td></tr>"

                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Poids : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("poids") +  "kg</td></tr>"

                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Main dominante : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + getMapListeRapport(listePairesRapport,"1").value("mainDominante") + " </td></tr>"

                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\">" + texteInfosCoteLese + " : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("coteBlesse") + "</td></tr>"

                    + texteInfosOperation +
                "</table>";

    res = res +  "<p>Date du rapport : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>< /br>< /br>";

    foreach (QString numeroTest, listeNumerosTest) {

        QString dateCourante = "Date du test numero T" + numeroTest + " : ";
        dateCourante = dateCourante + getMapListeRapport(listePairesRapport, numeroTest).value("dateBilan");
        res = res +  "<p>" + dateCourante + "</p>";
    }

    // Ecrire les infos du cabinet
    res = res + "<table style=\"margin-top:35px; width: 300px;text-align:center;\">"
                "<tr>"
                "<th scope=\"col\" style=\"background-color:transparent;font-weight:normal;color:#002e40;\">"
                "<p>Cabinet Kinesithérapie SCP 9 bis   -   9 bis Route de Launaguet, 31200 Toulouse</p>"
                "<p>scp9bis@gmail.com - 05 61 57 13 13</p></th>"
                "</tr>"
                "</table>";

    res = res +  "<DIV STYLE=\"page-break-before:always\"></DIV>";

    //Ecrire la legende
    QString legende = "<table><tr><th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Legende tableau</th>"
                      "<td style=\"background-color:#169d53; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Bon</td>"
                      "<td style=\"background-color:#ff9929; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Moyen</td>"
                      "<td style=\"background-color:#9f3f36; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Insuffisant</td></tr></table>";

    res.append(legende);

    //************************************************************************************
    // ecrire le tableau des amplitudes articulaires
    res.append(ecrireAmplitudesEpaule(listePairesRapport, labelBlessure));

    // ecrire le tableau des testAccroupissement
    res.append(ecrireTestsInstabilite(listePairesRapport));

    // ecrire le ACL RSI
    res.append(ecrireSiRsi(listePairesRapport));

    //Nouvelle page
    res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    res.append("<h1 style=\"text-align:center;\">Tests et ratios de force isométrique</h1>");

    // ecrire le tableau du test de grip
    res.append(ecrireTestGrip(listePairesRapport, labelBlessure));

    // ecrire le tableau du RERI R1
    res.append(ecrireReRiR1(listePairesRapport, labelBlessure));

    // ecrire le tableau du RERI R2
    res.append(ecrireReRiR2(listePairesRapport, labelBlessure));

    // ecrire le tableau du test IYT
    res.append(ecrireTestIYT(listePairesRapport, labelBlessure));

    //Nouvelle page
    res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    res.append("<h1 style=\"text-align:center;\">Tests fonctionnels</h1>");

    // ecrire le tableau du test UQ YBT
    res.append(ecrireUQYBT(listePairesRapport, labelBlessure));

    //Nouvelle page
    res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    // ecrire le tableau du test CK CUEST
    res.append(ecrireCkCuest(listePairesRapport));

    // ecrire le tableau du test SASSPT
    res.append(ecrireSASSPT(listePairesRapport, labelBlessure));

    // ecrire le tableau du test ULRT
    res.append(ecrireULRT(listePairesRapport, labelBlessure));

    // ecrire le tableau du test PSET
    res.append(ecrirePSET(listePairesRapport, labelBlessure));

    //Nouvelle page
    res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    //************************************************************************************

    // Ecrire l interpretation du professionnel
    // Recuperer le texte interpretation
    bool presenceInfos = false;

    QString texteInfos;

    QString texteInterpretation = ui->textEdit_interpretationKine_2->toPlainText();

    if(texteInterpretation != ""){
        presenceInfos = true;
        texteInterpretation.replace("\n","<br/>");
        texteInterpretation.replace("[", "<span style=\"font-weight: bold;\">");
        texteInterpretation.replace("]", "</span>");

        texteInfos = texteInfos
                     + "<table style=\"margin-bottom:20px; width: 300px;\">"
                       "<tr>"
                       "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                       "<p style=\" font-size: 200px;font-weight: bold; text-align:left;\"> Interprétation du kinésithérapeute :<p>< br¨/>"
                       "<p style=\"text-align:left;\"><br>" + texteInterpretation +"</p></br>"
                         "</th>"
                         "</tr>"
                        "</table>";
    }

    // Recuperer les libelles des checkBox coches
    QString texteAxes;
    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("checkBox_e")){

            QCheckBox *checkBox = dynamic_cast<QCheckBox*>(w);
            if (checkBox->isChecked()) {
                texteAxes = texteAxes + "<p style=\"text-align:left;\"><br> - " + checkBox->text() + "</br></p>< /br>";
            }
        }
    }

    if (texteAxes != "") {

        presenceInfos = true;
        texteInfos = texteInfos + "<table style=\"margin-bottom:20px; width: 300px;\">"
                                  "<tr>"
                                  "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                                  "<p style=\"font-size: 200px;font-weight: bold; text-align:left;\">Axes à améliorer :<p></br>";

        texteInfos.append(texteAxes);
    }

    if(presenceInfos){
        res.append(texteInfos);
    }

    res.append("</body></html>");

    return res;
}

//****************************************
/*
 *
 */
QString MainWindow::remplirChaineHtmlHanche(QStringList listeNumerosTest){

    QString res;

    // Recuperation de la base HTML
    QFile file(QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "nomFichierHtml"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream flux(&file);
    res = flux.readAll();

    file.close();

    // On commence a ecrire
    QSqlQuery requete;
    QString texteRequete;

    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();

    QStringList colonnesPatient = recupererListeColonnesTable("Patient");
    colonnesPatient.removeLast();

    QList<QPair<QString, QMap<QString, QString>>> listePairesRapport;

    foreach (QString numeroTestCourant, listeNumerosTest) {

        QPair<QString, QMap<QString, QString>> paireCourante;
        paireCourante.first = numeroTestCourant;
        paireCourante.second = recupererInfosBilanHancheBdd(numeroTestCourant);

        listePairesRapport.append(paireCourante);
    }


    //-----------------
    // Recuperer les donnees du patient et les inserer dans la liste
    QMap<QString, QString> mapInfosPatient;

    texteRequete = "SELECT * FROM Patient WHERE prenom LIKE '%" + prenomCourant +"%' AND nomFamille LIKE '%" + nomFamilleCourant + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }

    while (requete.next()) {

        for (int i = 0; i < colonnesPatient.count(); ++i) {
            mapInfosPatient.insert(colonnesPatient.at(i),requete.value(i).toString());
        }
    }

    res.append("<body>");


    //-----------------
    // ecrire le tableau des donnees du patient
    //-----------------

    // Si le patient a eu une intervention chirurgicale
    QString texteInfosOperation;
    QString texteInfosCoteLese;
    QString marginBottom;
    QString labelBlessure;
    QString typeBlessure;

    if(mapInfosPatient.value("estOpere") == "Non"){
        texteInfosCoteLese = "Côté lésé";
        labelBlessure = "lésé";
        typeBlessure = "Type de lésion";
    }
    else{
        texteInfosCoteLese = "Côté opéré";
        labelBlessure = "opéré";
        typeBlessure = "Type d'intervention chirurgicale";
    }

    // Texte operation
    if(mapInfosPatient.value("estOpere") == "Non"){
        marginBottom = "115px";
    }
    else{
        texteInfosOperation = texteInfosOperation +
                "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de l'operation : </td>"
                "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateOperation") +  "</td></tr>";

        marginBottom = "50px";
    }
    texteInfosOperation = texteInfosOperation +
            "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\">" + typeBlessure + " : </td>"
            "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("typeOperation") +  "</td></tr>";

    // Informations
    res = res + "<table style=\"border: none; margin-top:75px;margin-bottom:" + marginBottom + ";text-align:left;padding:10px 10px;\">"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding: 10px 10px;\">Nom et prénom : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("nomFamille") + " " + mapInfosPatient.value("prenom") + "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de naissance : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateNaissance") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Sexe : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("sexe") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Taille : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("taille") +  "cm</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Poids : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("poids") +  "kg</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\">" + texteInfosCoteLese + " : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("coteBlesse") + "</td></tr>"
                    + texteInfosOperation +
                "</table>";

    res = res +  "<p>Date du rapport : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>< /br>< /br>";

    foreach (QString numeroTest, listeNumerosTest) {

        QString dateCourante = "Date du test numero T" + numeroTest + " : ";
        dateCourante = dateCourante + getMapListeRapport(listePairesRapport, numeroTest).value("dateBilan");
        res = res +  "<p>" + dateCourante + "</p>";
    }

    // Ecrire les infos du cabinet de Jordan
    res = res + "<table style=\"margin-top:45px; width: 300px;text-align:center;\">"
                "<tr>"
                "<th scope=\"col\" style=\"background-color:transparent;font-weight:normal;color:#002e40;\">"
                "<p>Cabinet Kinesithérapie SCP 9 bis   -   9 bis Route de Launaguet, 31200 Toulouse</p>"
                "<p>scp9bis@gmail.com - 05 61 57 13 13</p></th>"
                "</tr>"
                "</table>";

    res = res +  "<DIV STYLE=\"page-break-before:always\"></DIV>";

    //Ecrire la legende
    QString legende = "<table><tr><th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Legende tableau</th>"
                      "<td style=\"background-color:#169d53; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Bon</td>"
                      "<td style=\"background-color:#ff9929; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Moyen</td>"
                      "<td style=\"background-color:#9f3f36; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Insuffisant</td></tr></table>";

    res.append(legende);

    // ecrire le tableau des amplitudes articulaires
    res.append(ecrireAmplitudesHanche(listePairesRapport, labelBlessure));

    // ecrire le tableau des permietres
    res.append(ecrirePerimetres(listePairesRapport, labelBlessure));

    res.append("<h1 style=\"text-align:center;\">Tests et ratios de force isométrique</h1>");

    // ecrire le tableau du ration ischio jambiers quadri
    res.append(ecrireRatioIJ(listePairesRapport, labelBlessure));

    res.append(ecrireIP(listePairesRapport, labelBlessure));

    // ecrire le tableau des abdd add
    res.append(ecrireRatioA(listePairesRapport, labelBlessure));

    res.append(ecrireRatioREHanche(listePairesRapport, labelBlessure));

    //Nouvelle page si T3 ou T2
    if(listeNumerosTest.count() == 3 || listeNumerosTest.count() == 2)
        res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    res.append("<h1 style=\"text-align:center;\">Tests de sauts verticaux</h1>");

    // ecrire le tableau du squatJump bipodal
    res.append(ecrireSjBipodal(listePairesRapport, labelBlessure));

    // ecrire le tableau du CMJ bipodal
    res.append(ecrireCmjBipodal(listePairesRapport, mapInfosPatient.value("sexe"), labelBlessure));

    //Nouvelle page si T3
    if(listeNumerosTest.count() == 3)
        res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    // ecrire le tableau du drop jump bipodal
    res.append(ecrireDjBipodal(listePairesRapport, labelBlessure));

    //Nouvelle page si T1
    if(listeNumerosTest.count() == 1 || listeNumerosTest.count() == 2)
        res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    // ecrire le tableau du test CMJ unipodal
    res.append(ecrireCmjUnipodal(listePairesRapport, labelBlessure));

    // ecrire le tableau du drop jump unipodal
    res.append(ecrireDjUnipodal(listePairesRapport, labelBlessure));

    res.append("<h1 style=\"text-align:center;\">Tests fonctionnels</h1>");

    // ecrire les points de reception unipodale
    res.append(ecrirePointsReceptionUnipodale(listePairesRapport));

    //Ecrire test Hop
    res.append(ecrireBroadJump(listePairesRapport, "hanche"));
    res.append(ecrireHop(listePairesRapport, labelBlessure, "hanche"));
    res.append(ecrireTripleHop(listePairesRapport, labelBlessure));
    res.append(ecrireCrossOverHop(listePairesRapport, labelBlessure));

    //Nouvelle page si T2
    if(listeNumerosTest.count() == 2)
        res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");


    // Ecrire l interpretation du professionnel
    // Recuperer le texte interpretation
    bool presenceInfos = false;

    QString texteInfos;

    QString texteInterpretation = ui->textEdit_interpretationKine_hanche->toPlainText();

    if(texteInterpretation != ""){
        presenceInfos = true;
        texteInterpretation.replace("\n","<br/>");
        texteInterpretation.replace("[", "<span style=\"font-weight: bold;\">");
        texteInterpretation.replace("]", "</span>");

        texteInfos = texteInfos
                     + "<table style=\"margin-bottom:20px; width: 300px;\">"
                       "<tr>"
                       "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                       "<p style=\" font-size: 200px;font-weight: bold; text-align:left;\"> Interprétation du kinésithérapeute :<p>< br¨/>"
                       "<p style=\"text-align:left;\"><br>" + texteInterpretation +"</p></br>"
                                             "</th>"
                                             "</tr>"
                                             "</table>";
    }

    // Recuperer les libelles des checkBox coches
    QString texteAxes;
    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("checkBox_h")){

            QCheckBox *checkBox = dynamic_cast<QCheckBox*>(w);
            if (checkBox->isChecked()) {
                texteAxes = texteAxes + "<p style=\"text-align:left;\"><br> - " + checkBox->text() + "</br></p>< /br>";
            }
        }
    }

    if (texteAxes != "") {
        presenceInfos = true;
        texteInfos = texteInfos + "<table style=\"margin-bottom:20px; width: 300px;\">"
                                  "<tr>"
                                  "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                                  "<p style=\"font-size: 200px;font-weight: bold; text-align:left;\">Axes à améliorer :<p></br>";

        texteInfos.append(texteAxes);
    }

    if(presenceInfos){
        res.append(texteInfos);
    }

    res.append("</body></html>");

    return res;
}

//****************************************
/*
 *
 */
QString MainWindow::remplirChaineHtmlCheville(QStringList listeNumerosTest){

    QString res;

    // Recuperation de la base HTML
    QFile file(QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "nomFichierHtml"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream flux(&file);
    res = flux.readAll();

    file.close();

    // On commence a ecrire
    QSqlQuery requete;
    QString texteRequete;

    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();

    QStringList colonnesPatient = recupererListeColonnesTable("Patient");
    colonnesPatient.removeLast();

    QList<QPair<QString, QMap<QString, QString>>> listePairesRapport;

    foreach (QString numeroTestCourant, listeNumerosTest) {

        QPair<QString, QMap<QString, QString>> paireCourante;
        paireCourante.first = numeroTestCourant;
        QMap<QString, QString> mapCourante = recupererInfosBilanChevilleBdd(numeroTestCourant);

        QMapIterator<QString, QString> iterateur(mapCourante);

        while(iterateur.hasNext()){
            iterateur.next();

            if(iterateur.key().contains("WBL")){
                mapCourante.insert(iterateur.key() + "Degre", QString::number(iterateur.value().toDouble() * 3.6));
            }
        }
        paireCourante.second = mapCourante;
        listePairesRapport.append(paireCourante);
    }

    //-----------------
    // Recuperer les donnees du patient et les inserer dans la liste
    QMap<QString, QString> mapInfosPatient;

    texteRequete = "SELECT * FROM Patient WHERE prenom LIKE '%" + prenomCourant +"%' AND nomFamille LIKE '%" + nomFamilleCourant + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }

    while (requete.next()) {

        for (int i = 0; i < colonnesPatient.count(); ++i) {
            mapInfosPatient.insert(colonnesPatient.at(i),requete.value(i).toString());
        }
    }

    res.append("<body>");

    //-----------------
    // ecrire le tableau des donnees du patient
    //-----------------

    // Si le patient a eu une intervention chirurgicale
    QString texteInfosOperation;
    QString texteInfosCoteLese;
    QString marginBottom;
    QString labelBlessure;
    QString typeBlessure;

    if(mapInfosPatient.value("estOpere") == "Non"){
        texteInfosCoteLese = "Côté lésé";
        labelBlessure = "lésé";
        typeBlessure = "Type de lésion";
    }
    else{
        texteInfosCoteLese = "Côté opéré";
        labelBlessure = "opéré";
        typeBlessure = "Type d'intervention chirurgicale";
    }

    // Texte operation
    if(mapInfosPatient.value("estOpere") == "Non"){
        marginBottom = "115px";
    }
    else{
        texteInfosOperation = texteInfosOperation +
                "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de l'operation : </td>"
                "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateOperation") +  "</td></tr>";

        marginBottom = "50px";
    }
    texteInfosOperation = texteInfosOperation +
            "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\">" + typeBlessure + " : </td>"
            "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("typeOperation") +  "</td></tr>";

    // Informations
    res = res + "<table style=\"border: none; margin-top:75px;margin-bottom:" + marginBottom + ";text-align:left;padding:10px 10px;\">"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding: 10px 10px;\">Nom et prénom : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("nomFamille") + " " + mapInfosPatient.value("prenom") + "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de naissance : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateNaissance") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Sexe : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("sexe") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Taille : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("taille") +  "cm</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Poids : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("poids") +  "kg</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\">" + texteInfosCoteLese + " : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("coteBlesse") + "</td></tr>"
                    + texteInfosOperation +
                "</table>";

    res = res +  "<p>Date du rapport : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>< /br>< /br>";

    foreach (QString numeroTest, listeNumerosTest) {

        QString dateCourante = "Date du test numero T" + numeroTest + " : ";
        dateCourante = dateCourante + getMapListeRapport(listePairesRapport, numeroTest).value("dateBilan");
        res = res +  "<p>" + dateCourante + "</p>";
    }

    // Ecrire les infos du cabinet de Jordan
    res = res + "<table style=\"margin-top:45px; width: 300px;text-align:center;\">"
                "<tr>"
                "<th scope=\"col\" style=\"background-color:transparent;font-weight:normal;color:#002e40;\">"
                "<p>Cabinet Kinesithérapie SCP 9 bis   -   9 bis Route de Launaguet, 31200 Toulouse</p>"
                "<p>scp9bis@gmail.com - 05 61 57 13 13</p></th>"
                "</tr>"
                "</table>";

    res = res +  "<DIV STYLE=\"page-break-before:always\"></DIV>";

    //Ecrire la legende
    QString legende = "<table><tr><th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Legende tableau</th>"
                      "<td style=\"background-color:#169d53; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Bon</td>"
                      "<td style=\"background-color:#ff9929; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Moyen</td>"
                      "<td style=\"background-color:#9f3f36; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Insuffisant</td></tr></table>";

    res.append(legende);

    // ecrire le tableau des amplitudes articulaires
    res.append(ecrireAmplitudesCheville(listePairesRapport, labelBlessure));

    // ecrire le tableau des permietres
    res.append(ecrirePerimetres(listePairesRapport, labelBlessure));

    // ecrire le ALR RSI
    res.append(ecrireAlrRsi(listePairesRapport));

    res.append("<h1 style=\"text-align:center;\">Tests et ratios de force isométrique</h1>");

    // ecrire le releveurs
    res.append(ecrireFmaxReleveursCheville(listePairesRapport, labelBlessure));

    // ecrire soleaire
    res.append(ecrireFmaxSoleaireCheville(listePairesRapport, labelBlessure));

    // ecrire le test de Verseurs
    res.append(ecrireRatioVerseurs(listePairesRapport, labelBlessure));

    // //Nouvelle page si T3 ou T2
    // if(listeNumerosTest.count() == 3 || listeNumerosTest.count() == 2)
    //     res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    res.append("<h1 style=\"text-align:center;\">Tests de sauts verticaux</h1>");

    // ecrire le tableau du squatJump bipodal
    res.append(ecrireSjBipodal(listePairesRapport, labelBlessure));

    // ecrire le tableau du CMJ bipodal
    res.append(ecrireCmjBipodal(listePairesRapport, mapInfosPatient.value("sexe"), labelBlessure));

    // //Nouvelle page si T3
    // if(listeNumerosTest.count() == 3)
    //     res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    // ecrire le tableau du drop jump bipodal
    res.append(ecrireDjBipodal(listePairesRapport, labelBlessure));

    // //Nouvelle page si T1
    // if(listeNumerosTest.count() == 1 || listeNumerosTest.count() == 2)
    //     res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    // ecrire le tableau du test CMJ unipodal
    res.append(ecrireCmjUnipodal(listePairesRapport, labelBlessure));

    // ecrire le tableau du drop jump unipodal
    res.append(ecrireDjUnipodal(listePairesRapport, labelBlessure));

    // ecrire le test de ecrireSautsRepetes
    res.append(ecrireSautsRepetes(listePairesRapport, labelBlessure));

    res.append("<h1 style=\"text-align:center;\">Tests fonctionnels</h1>");

    // ecrire les points de reception unipodale
    res.append(ecrirePointsReceptionUnipodale(listePairesRapport));

    //Ecrire test Hop
    res.append(ecrireBroadJump(listePairesRapport, "cheville"));
    res.append(ecrireHop(listePairesRapport, labelBlessure, "cheville"));
    res.append(ecrireTripleHop(listePairesRapport, labelBlessure));
    res.append(ecrireCrossOverHop(listePairesRapport, labelBlessure));
    res.append(ecrireSLIHRH(listePairesRapport, labelBlessure));
    res.append(ecrireHeelRise(listePairesRapport, labelBlessure));
    res.append(ecrireFootLift(listePairesRapport, labelBlessure));
    res.append(ecrireYBalance(listePairesRapport, labelBlessure));

    // //Nouvelle page si T2
    // if(listeNumerosTest.count() == 2)
    //     res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");


    // Ecrire l interpretation du professionnel
    // Recuperer le texte interpretation
    bool presenceInfos = false;

    QString texteInfos;

    QString texteInterpretation = ui->textEdit_interpretationKine_cheville->toPlainText();

    if(texteInterpretation != ""){
        presenceInfos = true;
        texteInterpretation.replace("\n","<br/>");
        texteInterpretation.replace("[", "<span style=\"font-weight: bold;\">");
        texteInterpretation.replace("]", "</span>");

        texteInfos = texteInfos
                     + "<table style=\"margin-bottom:20px; width: 300px;\">"
                       "<tr>"
                       "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                       "<p style=\" font-size: 200px;font-weight: bold; text-align:left;\"> Interprétation du kinésithérapeute :<p>< br¨/>"
                       "<p style=\"text-align:left;\"><br>" + texteInterpretation +"</p></br>"
                        "</th>"
                        "</tr>"
                        "</table>";
    }

    // Recuperer les libelles des checkBox coches
    QString texteAxes;
    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("checkBox_c")){

            QCheckBox *checkBox = dynamic_cast<QCheckBox*>(w);
            if (checkBox->isChecked()) {
                texteAxes = texteAxes + "<p style=\"text-align:left;\"><br> - " + checkBox->text() + "</br></p>< /br>";
            }
        }
    }

    if (texteAxes != "") {
        presenceInfos = true;
        texteInfos = texteInfos + "<table style=\"margin-bottom:20px; width: 300px;\">"
                                  "<tr>"
                                  "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                                  "<p style=\"font-size: 200px;font-weight: bold; text-align:left;\">Axes à améliorer :<p></br>";

        texteInfos.append(texteAxes);
    }

    if(presenceInfos){
        res.append(texteInfos);
    }

    res.append("</body></html>");

    return res;
}

//****************************************
/*
 *
 */
QString MainWindow::remplirChaineHtmlCourse(QStringList listeNumerosTest){

    QString res;

    // Recuperation de la base HTML
    QFile file(QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "nomFichierHtml"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream flux(&file);
    res = flux.readAll();

    file.close();

    // On commence a ecrire
    QSqlQuery requete;
    QString texteRequete;

    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();

    QStringList colonnesPatient = recupererListeColonnesTable("Patient");
    colonnesPatient.removeLast();

    QList<QPair<QString, QMap<QString, QString>>> listePairesRapport;

    foreach (QString numeroTestCourant, listeNumerosTest) {

        QPair<QString, QMap<QString, QString>> paireCourante;
        paireCourante.first = numeroTestCourant;
        QMap<QString, QString> mapCourante = recupererInfosBilanBpcBdd(numeroTestCourant);

        QMapIterator<QString, QString> iterateur(mapCourante);

        while(iterateur.hasNext()){
            iterateur.next();

            if(iterateur.key().contains("WBL")){
                mapCourante.insert(iterateur.key() + "Degre", QString::number(iterateur.value().toDouble() * 3.6));
            }
        }
        paireCourante.second = mapCourante;
        listePairesRapport.append(paireCourante);
    }

    //-----------------
    // Recuperer les donnees du patient et les inserer dans la liste
    QMap<QString, QString> mapInfosPatient;

    texteRequete = "SELECT * FROM Patient WHERE prenom LIKE '%" + prenomCourant +"%' AND nomFamille LIKE '%" + nomFamilleCourant + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }

    while (requete.next()) {

        for (int i = 0; i < colonnesPatient.count(); ++i) {
            mapInfosPatient.insert(colonnesPatient.at(i),requete.value(i).toString());
        }
    }

    res.append("<body>");

    //-----------------
    // ecrire le tableau des donnees du patient
    //-----------------

    // Si le patient a eu une intervention chirurgicale
    QString texteInfosOperation;
    QString texteInfosCoteLese;
    QString marginBottom;
    QString labelBlessure;
    QString typeBlessure;

    // Texte operation
    marginBottom = "115px";

    // Informations
    res = res + "<table style=\"border: none; margin-top:75px;margin-bottom:" + marginBottom + ";text-align:left;padding:10px 10px;\">"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding: 10px 10px;\">Nom et prénom : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("nomFamille") + " " + mapInfosPatient.value("prenom") + "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de naissance : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateNaissance") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Sexe : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("sexe") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Taille : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("taille") +  "cm</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Poids : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("poids") +  "kg</td></tr>"
                    + texteInfosOperation +
                "</table>";

    res = res +  "<p>Date du rapport : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>< /br>< /br>";

    foreach (QString numeroTest, listeNumerosTest) {

        QString dateCourante = "Date du test numero T" + numeroTest + " : ";
        dateCourante = dateCourante + getMapListeRapport(listePairesRapport, numeroTest).value("dateBilan");
        res = res +  "<p>" + dateCourante + "</p>";
    }

    // Ecrire les infos du cabinet de Jordan
    res = res + "<table style=\"margin-top:45px; width: 300px;text-align:center;\">"
                "<tr>"
                "<th scope=\"col\" style=\"background-color:transparent;font-weight:normal;color:#002e40;\">"
                "<p>Cabinet Kinesithérapie SCP 9 bis   -   9 bis Route de Launaguet, 31200 Toulouse</p>"
                "<p>scp9bis@gmail.com - 05 61 57 13 13</p></th>"
                "</tr>"
                "</table>";

    res = res +  "<DIV STYLE=\"page-break-before:always\"></DIV>";

    //Ecrire la legende
    QString legende = "<table><tr><th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Legende tableau</th>"
                      "<td style=\"background-color:#169d53; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Bon</td>"
                      "<td style=\"background-color:#ff9929; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Moyen</td>"
                      "<td style=\"background-color:#9f3f36; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Insuffisant</td></tr></table>";

    res.append(legende);

    //ZYZY
    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Analyse mobilité articulaire</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    // ecrire le tableau des amplitudes articulaires
    res.append(ecrireAmplitudesBp(listePairesRapport));

    if(mapCheminsImages.values().contains("APS")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpc_analysePosturaleStatique->toPlainText(),
               "Analyse Posturale Statique", "", 350, 250));
    }

    if(mapCheminsImages.values().contains("APD")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpc_analysePosturaleDynamique->toPlainText(),
                   "Analyse Posturale Dynamique", "APD", 350, 250));
    }

    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Tests de force isométrique et ratios agonistes / antagonistes / Dynamomètre</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    res.append(ecrireRatioVerseursBP(listePairesRapport));

    // ecrire le test de solair
    res.append(ecrireFmaxReleveursSoleaireBP(listePairesRapport));

    // ecrire le ratio IJ
    res.append(ecrireRatioIJBP(listePairesRapport));

    // ecrire MCcall
    res.append(ecrireMcCallBP(listePairesRapport));

    // ecrire le ratio IJ
    res.append(ecrireRatioAABP(listePairesRapport));

    // ecrireIPBP
    res.append(ecrireIPBP(listePairesRapport));

    // //Nouvelle page si T3 ou T2
    // if(listeNumerosTest.count() == 3 || listeNumerosTest.count() == 2)
    //     res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Tests de puissance (PLATEFORME DE FORCE)</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    // ecrire le tableau du squatJump bipodal
    res.append(ecrireSjBipodalBP(listePairesRapport));

    // ecrire le tableau du CMJ bipodal
    res.append(ecrireCmjBipodalBP(listePairesRapport, mapInfosPatient.value("sexe")));

    // ecrire le tableau du drop jump bipodal
    res.append(ecrireDjBipodalBP(listePairesRapport));

    // ecrire le tableau du test CMJ unipodal
    res.append(ecrireCmjUnipodalBP(listePairesRapport));

    // ecrire le tableau du drop jump unipodal
    res.append(ecrireDjUnipodalBP(listePairesRapport));

    // ecrire le test de ecrireSautsRepetes
    res.append(ecrireSautsRepetesBP(listePairesRapport));

    res.append(ecrireBroadJump(listePairesRapport, ""));
    res.append(ecrireHopBP(listePairesRapport));

    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Test de Force Maximale</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    //DISPLAY Image Back Squat
    if(mapCheminsImages.values().contains("AGBS"))
    {
        QString cheminImageBS=  mapCheminsImages.key("AGBS");
        cheminImageBS = redimensionnerImage(cheminImageBS, 250);
        res.append( "<div style=\"text-align: center;\"><img src=" + cheminImageBS  + "></div>");
    }

    res.append(ecrireFmaxBS(listePairesRapport, mapInfosPatient.value("poids")));

    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Tests fonctionnels</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    //Ecrire test Hop

    res.append(ecrireTripleHopBP(listePairesRapport));
    res.append(ecrireCrossOverHopBP(listePairesRapport));
    res.append(ecrireHeelRiseBP(listePairesRapport));

    if(mapCheminsImages.values().contains("AG")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpc_analyseGestuelle->toPlainText(),"Analyse Gestuelle Course a Pied", "AG", 350, 250));
    }

    // Ecrire l interpretation du professionnel
    // Recuperer le texte interpretation
    bool presenceInfos = false;

    QString texteInfos;

    QString texteInterpretation = ui->textEdit_interpretation_kine_bpc->toPlainText();

    if(texteInterpretation != ""){
        presenceInfos = true;
        texteInfos = ecrireInterpretation(texteInterpretation, "Interprétation du kinésithérapeute :");
    }

    texteInterpretation = ui->textEdit_bpc_conseilsChaussures->toPlainText();

    if(texteInterpretation != ""){
        texteInfos = ecrireInterpretation(texteInterpretation, "Conseils Chaussures:");
    }

    // Recuperer les libelles des checkBox coches
    QString texteAxes;
    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("checkBox_bpc")){

            QCheckBox *checkBox = dynamic_cast<QCheckBox*>(w);
            if (checkBox->isChecked()) {
                texteAxes = texteAxes + "<p style=\"text-align:left;\"><br> - " + checkBox->text() + "</br></p>< /br>";
            }
        }
    }

    if (texteAxes != "") {
        presenceInfos = true;
        texteInfos = texteInfos + "<table style=\"margin-bottom:20px; width: 300px;\">"
                                  "<tr>"
                                  "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                                  "<p style=\"font-size: 200px;font-weight: bold; text-align:left;\">Axes à améliorer :<p></br>";

        texteInfos.append(texteAxes);
    }

    if(presenceInfos){
        res.append(texteInfos);
    }

    res.append("</body></html>");

    return res;
}

//****************************************
/*
 *
 */
QString MainWindow::remplirChaineHtmlSportCollectif(QStringList listeNumerosTest){

    QString res;

    // Recuperation de la base HTML
    QFile file(QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "nomFichierHtml"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream flux(&file);
    res = flux.readAll();

    file.close();

    // On commence a ecrire
    QSqlQuery requete;
    QString texteRequete;

    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();

    QStringList colonnesPatient = recupererListeColonnesTable("Patient");
    colonnesPatient.removeLast();

    QList<QPair<QString, QMap<QString, QString>>> listePairesRapport;

    foreach (QString numeroTestCourant, listeNumerosTest) {

        QPair<QString, QMap<QString, QString>> paireCourante;
        paireCourante.first = numeroTestCourant;
        QMap<QString, QString> mapCourante = recupererInfosBilanBpscBdd(numeroTestCourant);

        QMapIterator<QString, QString> iterateur(mapCourante);

        while(iterateur.hasNext()){
            iterateur.next();

            if(iterateur.key().contains("WBL")){
                mapCourante.insert(iterateur.key() + "Degre", QString::number(iterateur.value().toDouble() * 3.6));
            }
        }
        paireCourante.second = mapCourante;
        listePairesRapport.append(paireCourante);
    }

    //-----------------
    // Recuperer les donnees du patient et les inserer dans la liste
    QMap<QString, QString> mapInfosPatient;

    texteRequete = "SELECT * FROM Patient WHERE prenom LIKE '%" + prenomCourant +"%' AND nomFamille LIKE '%" + nomFamilleCourant + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }

    while (requete.next()) {

        for (int i = 0; i < colonnesPatient.count(); ++i) {
            mapInfosPatient.insert(colonnesPatient.at(i),requete.value(i).toString());
        }
    }

    res.append("<body>");

    //-----------------
    // ecrire le tableau des donnees du patient
    //-----------------

    // Si le patient a eu une intervention chirurgicale
    QString texteInfosOperation;
    QString texteInfosCoteLese;
    QString marginBottom;
    QString labelBlessure;
    QString typeBlessure;

    // Texte operation
    marginBottom = "115px";

    // Informations
    res = res + "<table style=\"border: none; margin-top:75px;margin-bottom:" + marginBottom + ";text-align:left;padding:10px 10px;\">"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding: 10px 10px;\">Nom et prénom : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("nomFamille") + " " + mapInfosPatient.value("prenom") + "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de naissance : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateNaissance") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Sexe : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("sexe") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Taille : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("taille") +  "cm</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Poids : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("poids") +  "kg</td></tr>"
                    + texteInfosOperation +
                "</table>";

    res = res +  "<p>Date du rapport : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>< /br>< /br>";

    foreach (QString numeroTest, listeNumerosTest) {

        QString dateCourante = "Date du test numero T" + numeroTest + " : ";
        dateCourante = dateCourante + getMapListeRapport(listePairesRapport, numeroTest).value("dateBilan");
        res = res +  "<p>" + dateCourante + "</p>";
    }

    // Ecrire les infos du cabinet de Jordan
    res = res + "<table style=\"margin-top:45px; width: 300px;text-align:center;\">"
                "<tr>"
                "<th scope=\"col\" style=\"background-color:transparent;font-weight:normal;color:#002e40;\">"
                "<p>Cabinet Kinesithérapie SCP 9 bis   -   9 bis Route de Launaguet, 31200 Toulouse</p>"
                "<p>scp9bis@gmail.com - 05 61 57 13 13</p></th>"
                "</tr>"
                "</table>";

    res = res +  "<DIV STYLE=\"page-break-before:always\"></DIV>";

    //Ecrire la legende
    QString legende = "<table><tr><th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Legende tableau</th>"
                      "<td style=\"background-color:#169d53; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Bon</td>"
                      "<td style=\"background-color:#ff9929; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Moyen</td>"
                      "<td style=\"background-color:#9f3f36; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Insuffisant</td></tr></table>";

    res.append(legende);

    //ZYZY
    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Analyse mobilité articulaire</h1>");
    res.append("<div style=\"height: 30px;\"></div>");
    // ecrire le tableau des amplitudes articulaires
    res.append(ecrireAmplitudesBp(listePairesRapport));

    if(mapCheminsImages.values().contains("APS")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpsc_analysePosturaleStatique->toPlainText(),
               "Analyse Posturale Statique", "APS", 350, 250));
    }

    if(mapCheminsImages.values().contains("APD")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpsc_analysePosturaleDynamique->toPlainText(),
                   "Analyse Posturale Dynamique", "APD", 350, 250));
    }

    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Tests de force isométrique et ratios agonistes / antagonistes / Dynamomètre</h1>");
    res.append("<div style=\"height: 30px;\"></div>");
    res.append(ecrireRatioVerseursBP(listePairesRapport));

    // ecrire le test de solair
    res.append(ecrireFmaxReleveursSoleaireBP(listePairesRapport));

    // ecrire le ratio IJ
    res.append(ecrireRatioIJBP(listePairesRapport));

    // ecrire MCcall
    res.append(ecrireMcCallBP(listePairesRapport));

    // ecrire le ratio IJ
    res.append(ecrireRatioAABP(listePairesRapport));

    // ecrireIPBP
    res.append(ecrireIPBP(listePairesRapport));

    res.append("<h1 style=\"text-align:left;\">Tests de puissance (PLATEFORME DE FORCE)</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    // ecrire le tableau du squatJump bipodal
    res.append(ecrireSjBipodalBP(listePairesRapport));

    // ecrire le tableau du CMJ bipodal
    res.append(ecrireCmjBipodalBP(listePairesRapport, mapInfosPatient.value("sexe")));

    // ecrire le tableau du drop jump bipodal
    res.append(ecrireDjBipodalBP(listePairesRapport));

    // ecrire le tableau du test CMJ unipodal
    res.append(ecrireCmjUnipodalBP(listePairesRapport));

    // ecrire le tableau du drop jump unipodal
    res.append(ecrireDjUnipodalBP(listePairesRapport));

    // ecrire le test de ecrireSautsRepetes
    res.append(ecrireSautsRepetesBP(listePairesRapport));

    res.append(ecrireBroadJump(listePairesRapport, ""));
    res.append(ecrireHopBP(listePairesRapport));
    res.append(ecrireHeelRiseBP(listePairesRapport));

    res.append("<h1 style=\"text-align:left;\">Tests de Force Maximale </h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    //DISPLAY Image Back Squat
    if(mapCheminsImages.values().contains("AGBS"))
    {
         res.append(ecrireAnalyseGenerique(mapCheminsImages, "", "", "AGBS", 350, 250));
    }

    res.append(ecrireFmaxPL(listePairesRapport, mapInfosPatient.value("poids")));

    res.append("<h1 style=\"text-align:left;\">Tests fonctionnels</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    //Ecrire test Hop
    res.append(ecrireNordicCurl(listePairesRapport));
    res.append(ecrireTripleHopBP(listePairesRapport));
    res.append(ecrireCrossOverHopBP(listePairesRapport));

    res.append("<h1 style=\"text-align:left;\">Profilage Force /Vitesse</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    res.append(ecrireDSI(listePairesRapport));
    res.append(ecrireProfilFVV(listePairesRapport));

    res.append(ecrireProfilFVH(listePairesRapport));

    if(mapCheminsImages.values().contains("AGSprint"))
    {
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpsc_analyseGestuelleSprint->toPlainText(),
                       "Analyse Gestuelle Sprint", "AGSprint", 350, 250));
    }

    res.append("<h1 style=\"text-align:left;\">Tests de vitesse multidirectionnelle</h1>");
    res.append("<div style=\"height: 30px;\"></div>");
    res.append(ecrireProfilVM(listePairesRapport, mapInfosPatient.value("sexe")));

    if(mapCheminsImages.values().contains("AGVM"))
    {
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpsc_analyseGestuelleVM->toPlainText(),
                   "Analyse Gestuelle", "AGVM", 350, 250));
    }

    // Ecrire l interpretation du professionnel
    // Recuperer le texte interpretation
    bool presenceInfos = false;

    QString texteInfos;

    QString texteInterpretation = ui->textEdit_interpretation_kine_bpsc->toPlainText();

    if(texteInterpretation != ""){
        presenceInfos = true;
        texteInfos = ecrireInterpretation(texteInterpretation, "Interprétation du kinésithérapeute :");
    }

    // Recuperer les libelles des checkBox coches
    QString texteAxes;
    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("checkBox_bpsc")){

            QCheckBox *checkBox = dynamic_cast<QCheckBox*>(w);
            if (checkBox->isChecked()) {
                texteAxes = texteAxes + "<p style=\"text-align:left;\"><br> - " + checkBox->text() + "</br></p>< /br>";
            }
        }
    }

    if (texteAxes != "") {
        presenceInfos = true;
        texteInfos = texteInfos + "<table style=\"margin-bottom:20px; width: 300px;\">"
                                  "<tr>"
                                  "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                                  "<p style=\"font-size: 200px;font-weight: bold; text-align:left;\">Axes à améliorer :<p></br>";

        texteInfos.append(texteAxes);
    }

    if(presenceInfos){
        res.append(texteInfos);
    }

    res.append("</body></html>");

    return res;
}

//****************************************
/*
 *
 */
QString MainWindow::remplirChaineHtmlSportCombat(QStringList listeNumerosTest){

    QString res;

    // Recuperation de la base HTML
    QFile file(QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "nomFichierHtml"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream flux(&file);
    res = flux.readAll();

    file.close();

    // On commence a ecrire
    QSqlQuery requete;
    QString texteRequete;

    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();

    QStringList colonnesPatient = recupererListeColonnesTable("Patient");
    colonnesPatient.removeLast();

    QList<QPair<QString, QMap<QString, QString>>> listePairesRapport;

    foreach (QString numeroTestCourant, listeNumerosTest) {

        QPair<QString, QMap<QString, QString>> paireCourante;
        paireCourante.first = numeroTestCourant;
        QMap<QString, QString> mapCourante = recupererInfosBilanBpfBdd(numeroTestCourant);

        QMapIterator<QString, QString> iterateur(mapCourante);

        while(iterateur.hasNext()){
            iterateur.next();

            if(iterateur.key().contains("WBL")){
                mapCourante.insert(iterateur.key() + "Degre", QString::number(iterateur.value().toDouble() * 3.6));
            }
        }
        paireCourante.second = mapCourante;
        listePairesRapport.append(paireCourante);
    }

    //-----------------
    // Recuperer les donnees du patient et les inserer dans la liste
    QMap<QString, QString> mapInfosPatient;

    texteRequete = "SELECT * FROM Patient WHERE prenom LIKE '%" + prenomCourant +"%' AND nomFamille LIKE '%" + nomFamilleCourant + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }

    while (requete.next()) {

        for (int i = 0; i < colonnesPatient.count(); ++i) {
            mapInfosPatient.insert(colonnesPatient.at(i),requete.value(i).toString());
        }
    }

    res.append("<body>");

    //-----------------
    // ecrire le tableau des donnees du patient
    //-----------------

    // Si le patient a eu une intervention chirurgicale
    QString texteInfosOperation;
    QString texteInfosCoteLese;
    QString marginBottom;
    QString labelBlessure;
    QString typeBlessure;

    // Texte operation
    marginBottom = "115px";

    // Informations
    res = res + "<table style=\"border: none; margin-top:75px;margin-bottom:" + marginBottom + ";text-align:left;padding:10px 10px;\">"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding: 10px 10px;\">Nom et prénom : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("nomFamille") + " " + mapInfosPatient.value("prenom") + "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de naissance : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateNaissance") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Sexe : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("sexe") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Taille : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("taille") +  "cm</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Poids : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("poids") +  "kg</td></tr>"
                    + texteInfosOperation +
                "</table>";

    res = res +  "<p>Date du rapport : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>< /br>< /br>";

    foreach (QString numeroTest, listeNumerosTest) {

        QString dateCourante = "Date du test numero T" + numeroTest + " : ";
        dateCourante = dateCourante + getMapListeRapport(listePairesRapport, numeroTest).value("dateBilan");
        res = res +  "<p>" + dateCourante + "</p>";
    }

    // Ecrire les infos du cabinet de Jordan
    res = res + "<table style=\"margin-top:45px; width: 300px;text-align:center;\">"
                "<tr>"
                "<th scope=\"col\" style=\"background-color:transparent;font-weight:normal;color:#002e40;\">"
                "<p>Cabinet Kinesithérapie SCP 9 bis   -   9 bis Route de Launaguet, 31200 Toulouse</p>"
                "<p>scp9bis@gmail.com - 05 61 57 13 13</p></th>"
                "</tr>"
                "</table>";

    res = res +  "<DIV STYLE=\"page-break-before:always\"></DIV>";

    //Ecrire la legende
    QString legende = "<table><tr><th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Legende tableau</th>"
                      "<td style=\"background-color:#169d53; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Bon</td>"
                      "<td style=\"background-color:#ff9929; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Moyen</td>"
                      "<td style=\"background-color:#9f3f36; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Insuffisant</td></tr></table>";

    res.append(legende);

    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Analyse mobilité articulaire</h1>");
    res.append("<div style=\"height: 30px;\"></div>");
    // ecrire le tableau des amplitudes articulaires
    res.append(ecrireAmplitudesBpf(listePairesRapport));

    if(mapCheminsImages.values().contains("APS")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpf_analysePosturaleStatique->toPlainText(),
                   "Analyse Posturale Statique", "APS", 350, 250));
    }

    if(mapCheminsImages.values().contains("APDMI")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpf_analysePosturaleDynamiqueMI->toPlainText(),
                       "Analyse Posturale Dynamique Membre Inferieur", "APDMI", 350, 250));
    }

    if(mapCheminsImages.values().contains("APDMS")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpf_analysePosturaleDynamiqueMS->toPlainText(),
                       "Analyse Posturale Dynamique Membre Superieur", "APDMS", 350, 250));
    }

    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Tests de force isométrique et ratios agonistes / antagonistes / Dynamomètre</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    // ecrire le tableau du test de grip
    res.append(ecrireTestGripBP(listePairesRapport));

    res.append(ecrireReRiR2BP(listePairesRapport));

    res.append(ecrireTestIYTBP(listePairesRapport));

    // ecrire le ratio IJ
    res.append(ecrireRatioIJBP(listePairesRapport));

    // ecrire le ratio IJ
    res.append(ecrireRatioAABP(listePairesRapport));

    // //Nouvelle page si T3 ou T2
    // if(listeNumerosTest.count() == 3 || listeNumerosTest.count() == 2)
    //     res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    res.append("<h1 style=\"text-align:left;\">Tests de puissance (PLATEFORME DE FORCE)</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    // ecrire le tableau du squatJump bipodal
    res.append(ecrireSjBipodalBP(listePairesRapport));

    // ecrire le tableau du CMJ bipodal
    res.append(ecrireCmjBipodalBP(listePairesRapport, mapInfosPatient.value("sexe")));

    // ecrire le tableau du test CMJ unipodal
    res.append(ecrireCmjUnipodalBP(listePairesRapport));

    res.append(ecrireBroadJump(listePairesRapport, ""));
    res.append(ecrireHopBP(listePairesRapport));
    res.append(ecrireMTT(listePairesRapport));

    res.append("<h1 style=\"text-align:left;\">Profilage Force /Vitesse</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    res.append(ecrireDSI(listePairesRapport));
    res.append(ecrireProfilFVV(listePairesRapport));

    res.append("<h1 style=\"text-align:left;\">Tests de Force Maximale </h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    res.append(ecrireTestFmaxBPF(listePairesRapport, mapInfosPatient.value("poids")));

    if(ui->textEdit_bpf_analyseForceMaximale->toPlainText() != ""){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpf_analyseForceMaximale->toPlainText(),
               "Analyse Ratio 1RM / Poids du corps", "ATFM",350, 250));
    }

    if(mapCheminsImages.values().contains("AG")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpf_analyseGestuelle->toPlainText(),
                   "Analyse Gestuelle", "AG",350, 250));
    }

    // Ecrire l interpretation du professionnel
    // Recuperer le texte interpretation
    bool presenceInfos = false;

    QString texteInfos;

    QString texteInterpretation = ui->textEdit_interpretation_kine_bpf->toPlainText();

    if(texteInterpretation != ""){
        presenceInfos = true;
        texteInfos = ecrireInterpretation(texteInterpretation, "Interprétation du kinésithérapeute :");
    }

    // Recuperer les libelles des checkBox coches
    QString texteAxes;
    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("checkBox_bpf")){

            QCheckBox *checkBox = dynamic_cast<QCheckBox*>(w);
            if (checkBox->isChecked()) {
                texteAxes = texteAxes + "<p style=\"text-align:left;\"><br> - " + checkBox->text() + "</br></p>< /br>";
            }
        }
    }

    if (texteAxes != "") {
        presenceInfos = true;
        texteInfos = texteInfos + "<table style=\"margin-bottom:20px; width: 300px;\">"
                                  "<tr>"
                                  "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                                  "<p style=\"font-size: 200px;font-weight: bold; text-align:left;\">Axes à améliorer :<p></br>";

        texteInfos.append(texteAxes);
    }

    if(presenceInfos){
        res.append(texteInfos);
    }

    res.append("</body></html>");

    return res;
}

//****************************************
/*
 *
 */
QString MainWindow::remplirChaineHtmlCrossfit(QStringList listeNumerosTest){

    QString res;

    // Recuperation de la base HTML
    QFile file(QApplication::applicationDirPath() + "/src/" + getValue(PATH_CONFIG, "nomsFichier", "nomFichierHtml"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream flux(&file);
    res = flux.readAll();

    file.close();

    // On commence a ecrire
    QSqlQuery requete;
    QString texteRequete;

    QString nomFamilleCourant = ui->comboBox_patient_courant->currentText().split(" ").first();
    QString prenomCourant = ui->comboBox_patient_courant->currentText().split(" ").last();

    QStringList colonnesPatient = recupererListeColonnesTable("Patient");
    colonnesPatient.removeLast();

    QList<QPair<QString, QMap<QString, QString>>> listePairesRapport;

    foreach (QString numeroTestCourant, listeNumerosTest) {

        QPair<QString, QMap<QString, QString>> paireCourante;
        paireCourante.first = numeroTestCourant;
        QMap<QString, QString> mapCourante = recupererInfosBilanBpcfBdd(numeroTestCourant);

        QMapIterator<QString, QString> iterateur(mapCourante);

        while(iterateur.hasNext()){
            iterateur.next();

            if(iterateur.key().contains("WBL")){
                mapCourante.insert(iterateur.key() + "Degre", QString::number(iterateur.value().toDouble() * 3.6));
            }
        }
        paireCourante.second = mapCourante;
        listePairesRapport.append(paireCourante);
    }

    //-----------------
    // Recuperer les donnees du patient et les inserer dans la liste
    QMap<QString, QString> mapInfosPatient;

    texteRequete = "SELECT * FROM Patient WHERE prenom LIKE '%" + prenomCourant +"%' AND nomFamille LIKE '%" + nomFamilleCourant + "%'";

    if(!requete.exec(texteRequete)){
        ecrireLog("Requete impossible : " + texteRequete);
    }

    while (requete.next()) {

        for (int i = 0; i < colonnesPatient.count(); ++i) {
            mapInfosPatient.insert(colonnesPatient.at(i),requete.value(i).toString());
        }
    }

    res.append("<body>");

    //-----------------
    // ecrire le tableau des donnees du patient
    //-----------------

    // Si le patient a eu une intervention chirurgicale
    QString texteInfosOperation;
    QString texteInfosCoteLese;
    QString marginBottom;
    QString labelBlessure;
    QString typeBlessure;

    // Texte operation
    marginBottom = "115px";

    // Informations
    res = res + "<table style=\"border: none; margin-top:75px;margin-bottom:" + marginBottom + ";text-align:left;padding:10px 10px;\">"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding: 10px 10px;\">Nom et prénom : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("nomFamille") + " " + mapInfosPatient.value("prenom") + "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Date de naissance : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("dateNaissance") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Sexe : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("sexe") +  "</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Taille : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("taille") +  "cm</td></tr>"
                    "<tr><td style=\"font-size: 200px;font-weight:bold;border: none; text-align:left;padding:10px 10px;\"> Poids : </td>"
                    "<td style=\"font-size: 200px;border: none; text-align:left;padding:10px 10px;\">" + mapInfosPatient.value("poids") +  "kg</td></tr>"
                    + texteInfosOperation +
                "</table>";

    res = res +  "<p>Date du rapport : " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>< /br>< /br>";

    foreach (QString numeroTest, listeNumerosTest) {

        QString dateCourante = "Date du test numero T" + numeroTest + " : ";
        dateCourante = dateCourante + getMapListeRapport(listePairesRapport, numeroTest).value("dateBilan");
        res = res +  "<p>" + dateCourante + "</p>";
    }

    // Ecrire les infos du cabinet de Jordan
    res = res + "<table style=\"margin-top:45px; width: 300px;text-align:center;\">"
                "<tr>"
                "<th scope=\"col\" style=\"background-color:transparent;font-weight:normal;color:#002e40;\">"
                "<p>Cabinet Kinesithérapie SCP 9 bis   -   9 bis Route de Launaguet, 31200 Toulouse</p>"
                "<p>scp9bis@gmail.com - 05 61 57 13 13</p></th>"
                "</tr>"
                "</table>";

    res = res +  "<DIV STYLE=\"page-break-before:always\"></DIV>";

    //Ecrire la legende
    QString legende = "<table><tr><th scope=\"col\" style=\"background-color: white; color:#002e40; border:1px solid #023448;\">Legende tableau</th>"
                      "<td style=\"background-color:#169d53; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Bon</td>"
                      "<td style=\"background-color:#ff9929; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Moyen</td>"
                      "<td style=\"background-color:#9f3f36; color:#002e40;border:1px solid #023448; padding: 8px 10px;\">Insuffisant</td></tr></table>";

    res.append(legende);

    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Analyse mobilité articulaire</h1>");
    res.append("<div style=\"height: 30px;\"></div>");// ecrire le tableau des amplitudes articulaires
    res.append(ecrireAmplitudesBpcf(listePairesRapport));

    if(mapCheminsImages.values().contains("APS")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpcf_analysePosturaleStatique->toPlainText(),
               "Analyse Posturale Statique", "APS", 350, 250));
    }

    if(mapCheminsImages.values().contains("APDMI")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpcf_analysePosturaleDynamiqueMI->toPlainText(),
                   "Analyse Posturale Dynamique Membre Inferieur", "APDMI", 350, 250));
    }

    if(mapCheminsImages.values().contains("APDMS")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpcf_analysePosturaleDynamiqueMS->toPlainText(),
                   "Analyse Posturale Dynamique Membre Superieur", "APDMS", 350, 250));
    }
    res.append("<h1 style=\"text-align: left; margin-bottom: 30px;\">Tests de force isométrique et ratios agonistes / antagonistes / Dynamomètre</h1>");
    res.append("<div style=\"height: 30px;\"></div>");
    // ecrire le tableau du test de grip
    res.append(ecrireTestGripBP(listePairesRapport));

    res.append(ecrireReRiR2BP(listePairesRapport));

    res.append(ecrireTestIYTBP(listePairesRapport));

    // ecrire le ratio IJ
    res.append(ecrireRatioIJBP(listePairesRapport));

    // ecrire le ratio IJ
    res.append(ecrireRatioAABP(listePairesRapport));

    // //Nouvelle page si T3 ou T2
    // if(listeNumerosTest.count() == 3 || listeNumerosTest.count() == 2)
    //     res.append("<DIV STYLE=\"page-break-before:always\"></DIV>");

    res.append("<h1 style=\"text-align:left;\">Tests de puissance (PLATEFORME DE FORCE)</h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    // ecrire le tableau du squatJump bipodal
    res.append(ecrireSjBipodalBP(listePairesRapport));

    // ecrire le tableau du CMJ bipodal
    res.append(ecrireCmjBipodalBP(listePairesRapport, mapInfosPatient.value("sexe")));

    // ecrire le tableau du drop jump bipodal
    res.append(ecrireDjBipodalBP(listePairesRapport));

    // ecrire le tableau du test CMJ unipodal
    res.append(ecrireCmjUnipodalBP(listePairesRapport));

    // ecrire le tableau du drop jump unipodal
    res.append(ecrireDjUnipodalBP(listePairesRapport));

    // ecrire le test de ecrireSautsRepetes
    res.append(ecrireSautsRepetesBP(listePairesRapport));

    res.append(ecrireBroadJump(listePairesRapport, ""));
    res.append(ecrireHopBP(listePairesRapport));
    res.append(ecrireMTT(listePairesRapport));

    res.append("<h1 style=\"text-align:left;\">Profilage Force /Vitesse</h1>");
    res.append("<div style=\"height: 30px;\"></div>");
    res.append(ecrireDSI(listePairesRapport));
    res.append(ecrireProfilFVV(listePairesRapport));

    res.append("<h1 style=\"text-align:left;\">Tests de Force Maximale </h1>");
    res.append("<div style=\"height: 30px;\"></div>");

    res.append(ecrireTestFmaxBPCF(listePairesRapport, mapInfosPatient.value("poids")));

    if(ui->textEdit_bpcf_analyseForceMaximale->toPlainText() != ""){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpcf_analyseForceMaximale->toPlainText(),
               "Analyse Ratio 1RM / Poids du corps", "ATFM", 350, 250));
    }

    if(mapCheminsImages.values().contains("AG")){
        res.append(ecrireAnalyseGenerique(mapCheminsImages, ui->textEdit_bpcf_analyseGestuelle->toPlainText(),
                   "Analyse Gestuelle", "AG", 350, 250));
    }
    // Ecrire l interpretation du professionnel
    // Recuperer le texte interpretation
    bool presenceInfos = false;

    QString texteInfos;

    QString texteInterpretation = ui->textEdit_interpretation_kine_bpcf->toPlainText();

    if(texteInterpretation != ""){
        presenceInfos = true;
        texteInfos = ecrireInterpretation(texteInterpretation, "Interprétation du kinésithérapeute :");
    }

    // Recuperer les libelles des checkBox coches
    QString texteAxes;
    QList<QWidget *> allWidgets = this->findChildren<QWidget *>();
    for( QWidget * w : allWidgets ) {

        if(w->objectName().contains("checkBox_bpcf")){

            QCheckBox *checkBox = dynamic_cast<QCheckBox*>(w);
            if (checkBox->isChecked()) {
                texteAxes = texteAxes + "<p style=\"text-align:left;\"><br> - " + checkBox->text() + "</br></p>< /br>";
            }
        }
    }

    if (texteAxes != "") {
        presenceInfos = true;
        texteInfos = texteInfos + "<table style=\"margin-bottom:20px; width: 300px;\">"
                                  "<tr>"
                                  "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">"
                                  "<p style=\"font-size: 200px;font-weight: bold; text-align:left;\">Axes à améliorer :<p></br>";

        texteInfos.append(texteAxes);
    }

    if(presenceInfos){
        res.append(texteInfos);
    }

    res.append("</body></html>");

    return res;
}

/****************************************
/*
 *
 */
QString MainWindow::genererPageCouvertureBF(const QString& patientName,
                                            const QString& patientDate,
                                            const QString& pathAthleteImage,
                                            const QString& pathLogo,
                                            const QString& titreBilan)
{
    QString html;

    // Conteneur principal
    html += "<div style='padding:40px; font-family:\"Barlow Semi Condensed\", Arial, sans-serif;'>";

    // Image athlète en haut à droite
    html += "<div align='right'><img src='" + pathAthleteImage + "' width='150' height='350' "
            "style='background:#efefef; padding:2px; border:1px solid #ccc;'></div>";


    // Nom du patient
    html += "<br><center><font color='#002e40' size='4'><b>" + patientName + "</b></font></center><br><br>";

    // Titre principal (bilan)
    html += "<center>"
            "<hr style='height:10px; background:black; border:none; width:85%;'>"
            "<font color='#0056b3' size='35'><b>BILAN FONCTIONNEL<br>" + titreBilan.toUpper() + "</b></font>"
            "<hr style='height:10px; background:black; border:none; width:85%;'>"
            "</center><br><br>";

    // Date
    html += "<center><font color='#002e40' size='4'><b>DATE : " + patientDate + "</b></font></center><br><br><br>";

    // Logo en bas centré
    html += "<div align='center' style='margin-top:150px;'><img src='" + pathLogo + "' width='175' height='125'></div>";

    html += "</div>";

    return html;
}


/****************************************
/*
 *
 *//****************************************
/*
 *
 */
bool MainWindow::doitEtreEcrit(QStringList listecaractereCles, QMap<QString, QString> map){

    bool res = true;

    QMapIterator<QString, QString> iterateur(map);

    while(iterateur.hasNext()){
        iterateur.next();

        foreach (QString caractereCle, listecaractereCles) {

            if(iterateur.key().contains(caractereCle) && iterateur.value() == "0"){
                return false;
            }
        }
    }

    return res;
}

/****************************************
/*
 *
 */
bool MainWindow::doitEtreEcritAllTest(QStringList listecaractereCles, QList<QPair<QString, QMap<QString, QString>>> listePairesRapport){

    bool res = true;

    for (int i = 0; i < listePairesRapport.count(); ++i) {

        QPair<QString, QMap<QString, QString>> paireCourante = listePairesRapport.at(i);

        if(!doitEtreEcrit(listecaractereCles, paireCourante.second)){
            return false;
        }
    }

    return res;
}

//
QString MainWindow::ecrireAnalyseGenerique(QMap<QString, QString> mapChemins,
                                          QString texteEncadre,
                                          QString titreEncadre,
                                          QString typeEncadre,
                                          int maxWidth,
                                          int maxHeight)
{
    QString texteInfos;

    texteInfos += "<h1 style='text-align: left; margin-bottom: 30px;'>" + titreEncadre + "</h1>";
    texteInfos += "<table style='margin-top:50px; margin-bottom:20px; border:0; border-collapse:collapse; "
                  "margin-left:auto; margin-right:auto; text-align:center;'>";

    int compteur = 0;
    QStringList imagesAInserer;
    bool trouve = false;

    // Charger les images correspondantes
    for (auto it = mapCheminsImages.begin(); it != mapCheminsImages.end(); ++it) {
        if (it.value() == typeEncadre) {
            QString pathFichier = redimensionnerImage(it.key(), 1000); // garder qualité
            if (!pathFichier.isEmpty()) {
                imagesAInserer.append(pathFichier);
                trouve = true;
            }
        }
    }

    while (compteur < imagesAInserer.size() && trouve) {
        texteInfos += "<tr>";

        int imagesRestantes = imagesAInserer.size() - compteur;
        int nbImages = (imagesRestantes >= 3) ? 3 : imagesRestantes;

        if (nbImages == 1) {
            // Centrage unique image
            texteInfos += "<td colspan='3' style='text-align:center; padding:0;'>";
            QString path = imagesAInserer[compteur];
            QImage img(path);
            double ratio = qMin((double)maxWidth / img.width(), (double)maxHeight / img.height());
            int newW = (int)(img.width() * ratio);
            int newH = (int)(img.height() * ratio);

            texteInfos += "<img src='" + path +
                          "' width='" + QString::number(newW) +
                          "' height='" + QString::number(newH) +
                          "' style='display:block; margin:auto; border:0;' />";
            compteur++;
            texteInfos += "</td>";
        }
        else {
            // Deux ou trois images, centrées
            for (int i = 0; i < nbImages; ++i) {
                QString path = imagesAInserer[compteur];
                QImage img(path);
                double ratio = qMin((double)maxWidth / img.width(), (double)maxHeight / img.height());
                int newW = (int)(img.width() * ratio);
                int newH = (int)(img.height() * ratio);

                texteInfos += "<td style='padding:10px; text-align:center;'>"
                              "<img src='" + path +
                              "' width='" + QString::number(newW) +
                              "' height='" + QString::number(newH) +
                              "' style='display:block; margin:auto; border:0;' />"
                              "</td>";
                compteur++;
            }
        }

        texteInfos += "</tr>";
    }

    texteInfos += "</table>";
    texteInfos += ecrireInterpretation(texteEncadre, "Analyse");

    return texteInfos;
}

/****************************************
/*
 *
 */
QString MainWindow::ecrireInterpretation(QString texteInterpretation, QString titreInterpretation){

    QString texteInfos;

    if(texteInterpretation == ""){
        return "";
    }

    texteInterpretation.replace("\n","<br/>");
    texteInterpretation.replace("[", "<span style=\"font-weight: bold;\">");
    texteInterpretation.replace("]", "</span>");

    texteInfos = texteInfos
                 + "<table style=\"margin-bottom:20px; width: 300px;\">"
                   "<tr>"
                   "<th scope=\"col\" style=\"background-color:#f0f3f4; font-weight:normal;color:#002e40; border:0.5px solid #023448;\">";

    if(titreInterpretation != ""){
        texteInfos += "<h3 style=\"text-align: left; margin-bottom: 20px;\">" + titreInterpretation + "</h3>";
    }

    texteInfos = texteInfos + "<p style=\"text-align:left;\"><br>" + texteInterpretation +"</p></br>"
                            "</th>"
                            "</tr>"
                            "</table>";

    return texteInfos;
}

/****************************************
/*
 *
 */
void MainWindow::ecrireLog(QString text) {

    text.prepend(QDateTime::currentDateTime().toString("hhmmsszzz:  "));

    QString filePath = QApplication::applicationDirPath() + "/Logs/" + QDate::currentDate().toString("yyyy_MM_dd") + ".log";

    QDir destinationDir;
    if (!destinationDir.mkpath(QFileInfo(filePath).absoluteDir().path())) {
        qDebug() << "Failed to create destination directory!";
    }

    // Open the file in Append mode if it exists, otherwise create it
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open file for appending!";
        return;
    }

    // Create a QTextStream to write to the file
    QTextStream out(&file);

    // Write the text to the file
    out << text << Qt::endl;

    // Close the file
    file.close();
}

/****************************************
/*
 *
 */
void MainWindow::copyFile(const QString& sourceFilePath, const QString& destinationFilePath) {

    QFile sourceFile(sourceFilePath);
    QFile destinationFile(destinationFilePath);

    if (!sourceFile.open(QIODevice::ReadOnly)) {
        ecrireLog("Failed to open source file for reading: " + sourceFilePath);
        return;
    }

    if (!destinationFile.open(QIODevice::WriteOnly)) {
        ecrireLog("Failed to open destination file for writing: " + destinationFilePath);
        sourceFile.close();
        return;
    }

    QByteArray buffer;
    while (!sourceFile.atEnd()) {
        buffer = sourceFile.read(8192); // Read in chunks of 8192 bytes
        destinationFile.write(buffer);
    }

    sourceFile.close();
    destinationFile.close();
}


/****************************************
/*
 *
 */
void MainWindow::on_pushButton_annulerModificationBilan_clicked()
{
    emit on_pushButton_annulerEditionBilan_clicked();
}


/****************************************
/*
 *
 */
QString MainWindow::redimensionnerImage(QString pathFichierImage, int tailleMax)
{
    QImageReader reader(pathFichierImage);
    reader.setAutoTransform(true); // Orientation EXIF
    QImage imageOriginale = reader.read();

    if (imageOriginale.isNull()) {
        ecrireLog("Erreur lecture image: " + pathFichierImage);
        return QString();
    }

    // Si image plus grande que tailleMax -> on réduit
    if (imageOriginale.width() > tailleMax || imageOriginale.height() > tailleMax) {
        imageOriginale = imageOriginale.scaled(
            tailleMax,
            tailleMax,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        );
    }

    // Sauvegarde image temporaire
    QString nomFichier = QFileInfo(pathFichierImage).fileName();
    QString cheminTemp = QDir::tempPath() + "/thumb_" + nomFichier;
    imageOriginale.save(cheminTemp, "PNG", 100);

    return cheminTemp;
}
/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpc_photos_analyseGestuelle_clicked()
{
    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant,"AG");
    }

    this->ui->lineEdit_bpc_photos_analyseGestuelle->setText(nomFichiers.join(" | "));
}


/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpc_photos_analysePosturaleDynamique_clicked()
{
    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant, "APD");
    }

    this->ui->lineEdit_bpc_photos_analysePosturaleDynamique->setText(nomFichiers.join(" | "));
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpsc_photos_analysePosturaleDynamique_clicked()
{

    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant, "APD");
    }

    this->ui->lineEdit_bpsc_photos_analysePosturaleDynamique->setText(nomFichiers.join(" | "));
}




/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpf_photos_analysePosturaleDynamiqueMI_clicked()
{
    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant, "APDMI");
    }

    this->ui->lineEdit_bpf_photos_analysePosturaleDynamiqueMI->setText(nomFichiers.join(" | "));
}


/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpf_photos_analysePosturaleDynamiqueMS_clicked()
{

    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant, "APDMS");
    }

    this->ui->lineEdit_bpf_photos_analysePosturaleDynamiqueMS->setText(nomFichiers.join(" | "));
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpcf_photos_analysePosturaleDynamiqueMI_clicked()
{

    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant, "APDMI");
    }

    this->ui->lineEdit_bpcf_photos_analysePosturaleDynamiqueMI->setText(nomFichiers.join(" | "));
}


/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpcf_photos_analysePosturaleDynamiqueMS_clicked()
{

    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant, "APDMS");
    }

    this->ui->lineEdit_bpcf_photos_analysePosturaleDynamiqueMS->setText(nomFichiers.join(" | "));
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpc_photos_analysePosturaleStatique_clicked()
{
    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant,"APS");
    }

    this->ui->lineEdit_bpc_photos_analysePosturaleStatique->setText(nomFichiers.join(" | "));
}


/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpf_photos_analysePosturaleStatique_clicked()
{

    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant,"APS");
    }

    this->ui->lineEdit_bpf_photos_analysePosturaleStatique->setText(nomFichiers.join(" | "));
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpsc_photos_analysePosturaleStatique_clicked()
{

    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant,"APS");
    }

    this->ui->lineEdit_bpsc_photos_analysePosturaleStatique->setText(nomFichiers.join(" | "));
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpcf_photos_analysePosturaleStatique_clicked()
{

    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant,"APS");
    }

    this->ui->lineEdit_bpcf_photos_analysePosturaleStatique->setText(nomFichiers.join(" | "));
}


/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpc_photos_analyseGestuelleBS_clicked()
{
    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant,"AGBS");
    }

    this->ui->lineEdit_bpc_photos_analyseGestuelleBS->setText(nomFichiers.join(" | "));

}




/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpsc_photos_analyseGestuelleFVV_clicked()
{
    QString pathFichierCourant = QFileDialog::getOpenFileName(
                this,
                "Choisir une image",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );


    QFileInfo fichierInfo(pathFichierCourant);
    mapCheminsImages.insert(pathFichierCourant,"PFVV");

    this->ui->lineEdit_bpsc_photos_analyseGestuelleFVV->setText(fichierInfo.fileName());
}

void MainWindow::on_pushButton_bpcf_photos_analyseGestuelleFVV_clicked()
{
    QString pathFichierCourant = QFileDialog::getOpenFileName(
                this,
                "Choisir une image",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    QFileInfo fichierInfo(pathFichierCourant);
    mapCheminsImages.insert(pathFichierCourant,"PFVV");

    this->ui->lineEdit_bpcf_photos_analyseGestuelleFVV->setText(fichierInfo.fileName());
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpsc_photos_analyseGestuelleFVH_clicked()
{

    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant,"PFVH");
    }

    this->ui->lineEdit_bpsc_photos_analyseGestuelleFVH->setText(nomFichiers.join(" | "));
}




/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpsc_photos_analyseGestuelleSprint_clicked()
{
    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant,"AGSprint");
    }

    this->ui->lineEdit_bpsc_photos_analyseGestuelleSprint->setText(nomFichiers.join(" | "));
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpsc_photos_analyseGestuelleVM_clicked()
{
    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
               this,
               "Choisir des images",
               QString(),
               "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
               );

    for (QString pathFichierCourant : pathsFichiers) {

       QFileInfo fichierInfo(pathFichierCourant);
       nomFichiers << fichierInfo.fileName();
       mapCheminsImages.insert(pathFichierCourant,"AGVM");
    }

    this->ui->lineEdit_bpsc_photos_analyseGestuelleVM->setText(nomFichiers.join(" | "));
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpsc_photos_analyseGestuelleBS_clicked()
{

    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
                this,
                "Choisir des images",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );

    for (QString pathFichierCourant : pathsFichiers) {

        QFileInfo fichierInfo(pathFichierCourant);
        nomFichiers << fichierInfo.fileName();
        mapCheminsImages.insert(pathFichierCourant,"AGBS");
    }

    this->ui->lineEdit_bpc_photos_analyseGestuelleBS->setText(nomFichiers.join(" | "));
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpf_photos_analyseGestuelleFVV_clicked()
{
    QString pathFichierCourant = QFileDialog::getOpenFileName(
                this,
                "Choisir une image",
                QString(),
                "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
                );


    QFileInfo fichierInfo(pathFichierCourant);
    mapCheminsImages.insert(pathFichierCourant,"PFVV");

    this->ui->lineEdit_bpf_photos_analyseGestuelleFVV->setText(fichierInfo.fileName());
}


/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpf_photos_analyseGestuelle_clicked()
{

    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
               this,
               "Choisir des images",
               QString(),
               "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
               );

    for (QString pathFichierCourant : pathsFichiers) {

       QFileInfo fichierInfo(pathFichierCourant);
       nomFichiers << fichierInfo.fileName();
       mapCheminsImages.insert(pathFichierCourant,"AGVM");
    }

    this->ui->lineEdit_bpf_photos_analyseGestuelle->setText(nomFichiers.join(" | "));
}


/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpcf_photos_analyseGestuelle_clicked()
{
    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
               this,
               "Choisir des images",
               QString(),
               "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
               );

    for (QString pathFichierCourant : pathsFichiers) {

       QFileInfo fichierInfo(pathFichierCourant);
       nomFichiers << fichierInfo.fileName();
       mapCheminsImages.insert(pathFichierCourant,"AGVM");
    }

    this->ui->lineEdit_bpcf_photos_analyseGestuelle->setText(nomFichiers.join(" | "));
}

/****************************************
/*
 *
 */
QString MainWindow::encadrerTableauEtImage(const QString& texteTableau,
                                            const QString& cheminImage,
                                            int maxWidth,
                                            int maxHeight)
 {
     QString html;

     // Charger l'image pour récupérer ses dimensions originales
     QImage img(cheminImage);
     if (img.isNull()) {
         // Image introuvable ou corrompue
         html = "<table style='border-collapse: collapse; width: 100%;'><tr>"
                "<td style='vertical-align: bottom; text-align: left;'>" + texteTableau + "</td>"
                "<td style='vertical-align: top; text-align: center; padding-left: 30px;'>"
                "<span style='color:red;'>Image introuvable</span>"
                "</td></tr></table>";
         return html;
     }

     // Calcul du ratio pour redimensionner sans perte
     double ratio = qMin((double)maxWidth / img.width(), (double)maxHeight / img.height());
     int newW = (int)(img.width() * ratio);
     int newH = (int)(img.height() * ratio);

     // Génération du HTML avec image redimensionnée
     html += "<table style='border-collapse: collapse; width: 100%;'>"
             "<tr>"
             "<td style='vertical-align: bottom; text-align: left;'>" +
             texteTableau +
             "</td>"
             "<td style='vertical-align: top; text-align: center; padding-left: 30px;'>"
             "<img src='" + cheminImage +
             "' width='" + QString::number(newW) +
             "' height='" + QString::number(newH) +
             "' style='display:block; margin:auto; border:0;'/>"
             "</td>"
             "</tr>"
             "</table>";

     return html;
 }

/****************************************
/*
 * Affiche un tableau et une image côte à côte ou l'un au-dessus de l'autre.
 * position = "left", "right", "top", "bottom"
 */
// QString MainWindow::encadrerTableauEtImageFlexible(const QString& texteTableau,
//                                                    const QString& cheminImage,
//                                                    const QString& position,
//                                                    int maxWidth,
//                                                    int maxHeight)
// {
//     QString html;

//     // Charger l'image pour obtenir ses dimensions
//     QImage img(cheminImage);
//     if (img.isNull()) {
//         html = "<div style='color:red;'>Image introuvable</div>" + texteTableau;
//         return html;
//     }

//     // Calcul du ratio
//     double ratio = qMin((double)maxWidth / img.width(), (double)maxHeight / img.height());
//     int newW = (int)(img.width() * ratio);
//     int newH = (int)(img.height() * ratio);

//     // Construction HTML en fonction de la position
//     if (position == "left" || position == "right") {
//         // Image à gauche ou à droite du tableau
//         html += "<table style='border-collapse: collapse; width: 100%;'><tr>";

//         if (position == "left") {
//             html += "<td style='vertical-align: middle; text-align: center; padding-right: 20px;'>"
//                     "<img src='" + cheminImage +
//                     "' width='" + QString::number(newW) +
//                     "' height='" + QString::number(newH) +
//                     "' style='display:block; margin:auto; border:0;'/>"
//                     "</td>"
//                     "<td style='vertical-align: middle; text-align: left; width:100%;'>" +
//                     texteTableau +
//                     "</td>";
//         } else { // right
//             html += "<td style='vertical-align: middle; text-align: left; width:100%;'>" +
//                     texteTableau +
//                     "</td>"
//                     "<td style='vertical-align: middle; text-align: center; padding-left: 20px;'>"
//                     "<img src='" + cheminImage +
//                     "' width='" + QString::number(newW) +
//                     "' height='" + QString::number(newH) +
//                     "' style='display:block; margin:auto; border:0;'/>"
//                     "</td>";
//         }

//         html += "</tr></table>";

//     } else {
//         // Image au-dessus ou en dessous du tableau
//         html += "<div style='width:100%; text-align:center; margin-bottom:10px;'>";

//         if (position == "top") {
//             html += "<img src='" + cheminImage +
//                     "' width='" + QString::number(newW) +
//                     "' height='" + QString::number(newH) +
//                     "' style='display:block; margin:auto; border:0;'/><br/>" +
//                     texteTableau;
//         } else { // bottom
//             html += texteTableau +
//                     "<br/><img src='" + cheminImage +
//                     "' width='" + QString::number(newW) +
//                     "' height='" + QString::number(newH) +
//                     "' style='display:block; margin:auto; border:0;'/>";
//         }

//         html += "</div>";
//     }

//     return html;
// }


// QString MainWindow::encadrerTableauEtImageFlexible(const QString& texteTableau,
//                                                    const QString& cheminImage,
//                                                    const QString& position,
//                                                    int maxWidth,
//                                                    int maxHeight)
// {
//     QString html;

//     // Charger l'image pour obtenir ses dimensions
//     QImage img(cheminImage);
//     if (img.isNull()) {
//         html = "<div style='color:red;'>Image introuvable</div>" + texteTableau;
//         return html;
//     }

//     // Calcul du ratio
//     double ratio = qMin((double)maxWidth / img.width(), (double)maxHeight / img.height());
//     int newW = (int)(img.width() * ratio);
//     int newH = (int)(img.height() * ratio);

//     // Construction HTML en fonction de la position
//     if (position == "left" || position == "right") {
//         // Image à gauche ou à droite du tableau
//         html += "<table style='border-collapse: collapse; width: 100%;'><tr>";

//         if (position == "left") {
//             html += "<td style='vertical-align: middle; text-align: center;'>"
//                     "<img src='" + cheminImage +
//                     "' width='" + QString::number(newW) +
//                     "' height='" + QString::number(newH) +
//                     "' style='display:block; margin:auto; border:0;'/>"
//                     "</td>"
//                     "<td style='vertical-align: middle; text-align: left; width:100%; padding: 0;'>"
//                     + texteTableau +
//                     "</td>";
//         } else { // right
//             html += "<td style='vertical-align: middle; text-align: left; width:100%; padding: 0;'>"
//                     + texteTableau +
//                     "</td>"
//                     "<td style='vertical-align: middle; text-align: center;'>"
//                     "<img src='" + cheminImage +
//                     "' width='" + QString::number(newW) +
//                     "' height='" + QString::number(newH) +
//                     "' style='display:block; margin:auto; border:0;'/>"
//                     "</td>";
//         }

//         html += "</tr></table>";

//     } else {
//         // Image au-dessus ou en dessous du tableau
//         html += "<div style='width:100%; margin-bottom:10px;'>";

//         if (position == "top") {
//             html += "<div style='text-align:center;'>"
//                     "<img src='" + cheminImage +
//                     "' width='" + QString::number(newW) +
//                     "' height='" + QString::number(newH) +
//                     "' style='display:block; margin:auto; border:0;'/>"
//                     "</div>"
//                     "<div style='text-align:left; padding:0;'>" +
//                     texteTableau +
//                     "</div>";
//         } else { // bottom
//             html += "<div style='text-align:left; padding:0;'>" +
//                     texteTableau +
//                     "</div>"
//                     "<div style='text-align:center;'>"
//                     "<img src='" + cheminImage +
//                     "' width='" + QString::number(newW) +
//                     "' height='" + QString::number(newH) +
//                     "' style='display:block; margin:auto; border:0;'/>"
//                     "</div>";
//         }

//         html += "</div>";
//     }

//     return html;
// }

QString MainWindow::encadrerTableauEtImageFlexible(const QString& texteTableau,
                                                   const QString& cheminImage,
                                                   const QString& position,
                                                   int maxWidth,
                                                   int maxHeight)
{
    QString html;

    // Charger l'image pour obtenir ses dimensions
    QImage img(cheminImage);
    if (img.isNull()) {
        html = "<div style='color:red;'>Image introuvable</div>" + texteTableau;
        return html;
    }

    // Calcul du ratio
    double ratio = qMin((double)maxWidth / img.width(), (double)maxHeight / img.height());
    int newW = static_cast<int>(img.width() * ratio);
    int newH = static_cast<int>(img.height() * ratio);

    if (position == "left" || position == "right") {
        html += "<table style='border-collapse: collapse; width: 100%;'><tr>";

        if (position == "left") {
            html += "<td style='vertical-align: middle; text-align: center;'>"
                    "<img src='" + cheminImage + "' width='" + QString::number(newW) +
                    "' height='" + QString::number(newH) +
                    "' style='display:block; margin:auto; border:0;'/>"
                    "</td>"
                    "<td style='vertical-align: middle; text-align: left; width:100%; padding: 0;'>"
                    + texteTableau +
                    "</td>";
        } else {
            html += "<td style='vertical-align: middle; text-align: left; width:100%; padding: 0;'>"
                    + texteTableau +
                    "</td>"
                    "<td style='vertical-align: middle; text-align: center;'>"
                    "<img src='" + cheminImage + "' width='" + QString::number(newW) +
                    "' height='" + QString::number(newH) +
                    "' style='display:block; margin:auto; border:0;'/>"
                    "</td>";
        }
        html += "</tr></table>";

    } else {
        // Image en haut ou en bas
        html += "<div style='width:100%; margin-bottom:10px;'>";

        if (position == "top") {
            html += "<div style='text-align:center; margin-bottom:10px;'>"
                    "<img src='" + cheminImage + "' width='" + QString::number(newW) +
                    "' height='" + QString::number(newH) +
                    "' style='display:block; margin:auto; border:0;'/>"
                    "</div>"
                    "<div style='text-align:left; padding:0; margin-top:5px;'>"
                    + texteTableau +
                    "</div>";
        } else { // bottom
            html += "<div style='text-align:left; padding:0; margin-bottom:5px;'>"
                    + texteTableau +
                    "</div>"
                    "<div style='text-align:center; margin-top:5px;margin-bottom:50px'>"
                    "<img src='" + cheminImage + "' width='" + QString::number(newW) +
                    "' height='" + QString::number(newH) +
                    "' style='display:block; margin:auto; border:0;'/>"
                    "</div>";
        }
        html += "</div>";
    }

    return html;
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpcf_photos_forceMaximale_clicked()
{
    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
               this,
               "Choisir des images",
               QString(),
               "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
               );

    for (QString pathFichierCourant : pathsFichiers) {

       QFileInfo fichierInfo(pathFichierCourant);
       nomFichiers << fichierInfo.fileName();
       mapCheminsImages.insert(pathFichierCourant,"ATFM");
    }

    this->ui->lineEdit_bpcf_photos_analyseForceMaximale->setText(nomFichiers.join(" | "));
}

/****************************************
/*
 *
 */
void MainWindow::on_pushButton_bpf_photos_forceMaximale_clicked()
{
    QStringList nomFichiers;
    QStringList pathsFichiers = QFileDialog::getOpenFileNames(
               this,
               "Choisir des images",
               QString(),
               "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
               );

    for (QString pathFichierCourant : pathsFichiers) {

       QFileInfo fichierInfo(pathFichierCourant);
       nomFichiers << fichierInfo.fileName();
       mapCheminsImages.insert(pathFichierCourant,"ATFM");
    }

    this->ui->lineEdit_bpf_photos_analyseForceMaximale->setText(nomFichiers.join(" | "));
}

