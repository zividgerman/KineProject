#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QProcess>
#include <QTextDocument>
#include <QMenu>
#include <QtPrintSupport/QPrinter>
#include <QCompleter>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QWidget>
#include <QScrollArea>
#include <QFileDialog>
#include <QPainter>


#include "gestionpatients.h"

#define PATH_CONFIG QApplication::applicationDirPath() + "/config.ini"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void initialiserFenetre();

    void actionGestionPatient_clicked();

    void on_pushButton_rechercher_clicked();

    void on_pushButton_valider_bilan_clicked();

    void on_pushButton_generer_rapport_clicked();

    void on_comboBox_patient_courant_currentTextChanged(const QString &arg1);

    void on_pushButton_editer_bilan_clicked();

    void on_comboBox_dateBilan_currentTextChanged(const QString &dateBilan);

    void on_comboBox_type_Bilan_currentTextChanged(const QString &arg1);

    void on_pushButton_validerRapport_clicked();

    void on_pushButton_annulerEditionBilan_clicked();

    void on_pushButton_annulerEditionRapport_clicked();

    void on_pushButton_valider_bilan_epaule_clicked();

    void on_toolButton_g_clicked();

    void on_pushButton_validerRapport_epaule_clicked();

    void on_toolButton_e_clicked();

    void on_pushButton_modifier_bilan_clicked();

    void on_pushButton_valider_bilan_hanche_clicked();

    void on_pushButton_validerRapport_hanche_clicked();

    void on_toolButton_h_clicked();

    void on_pushButton_annulerModificationBilan_clicked();


    void on_toolButton_c_clicked();

    void on_pushButton_validerRapport_cheville_clicked();

    void on_pushButton_valider_bilan_cheville_clicked();

private:
    Ui::MainWindow *ui;

    enum Choice
    {
        troisMois = 3,
        sixMois = 6,
        neufMois = 9
    };

    GestionPatients *gest;
    QSqlDatabase database;
    QMap<QString, QString> mapPatient;

    QStringList listeTestsCourant;

    QString getValue(QString pathFichierConfig, QString groupe, QString cle);
    QStringList recupererListeColonnesTable(QString nomTable);
    QString ecrireLigneTableau(QStringList listeValeursLigne);

    QMap<QString, QString> remplirQMapInfoBilanEpaule(QString typeRequete);
    QMap<QString, QString> remplirQMapInfoBilanGenou(QString typeRequete);
    QMap<QString, QString> remplirQMapInfoBilanHanche(QString typeRequete);
    QMap<QString, QString> remplirQMapInfoBilanCheville(QString typeRequete);

    QMap<QString, QString> recupererInfosBilanGenouBdd(QString numeroTest);
    QMap<QString, QString> recupererInfosBilanEpauleBdd(QString numeroTest);
    QMap<QString, QString> recupererInfosBilanChevilleBdd(QString numeroTest);
    QMap<QString, QString> recupererInfosBilanHancheBdd(QString numeroTest);


    QString getCouleurRatioIschio(double ratio);
    QString getCouleurRatioAbd(double ratio);
    QString getCouleurACLRsi(double aclRsi);
    QString getCouleurRsiModifie(double rsi, QString sexe);
    QString getCouleurRsi(double rsi);
    QString getCouleurBkfo(double bkfo);

    QPair<QString, QString> getPaireRsiModifie(double numerateur, double denominateur, QString sexe);
    QPair<QString, QString> getPaireRatio(double numerateur, double denominateur, QString typeRatio);
    QPair<QString, QString> getPaireAsymetrie(bool inversion,double nonOpere, double opere);
    QPair<QString, QString> getPaireKstart(double kStart);
    QPair<QString, QString> calculerProgression(QString unite, double valeurAvant, double valeurApres);
    QPair<QString, QString> getProgressionPourcentage(bool inversion, double valeurAvant, double valeurApres);


    QString getCouleurReRiR1(double ratio);
    QString getCouleurReRiR2(double ratio);
    QString getCouleurSiRsi(double aclRsi);
    QPair<QString, QString> getPaireLSI(double dsl, double dil, double dm, double longueurBras);
    QString getCouleurPourcentageLSI(double pourcentage);
    QString getCouleurCKCuest(double nbTouches);
    QString getCouleurURLT(double nbRepetitions);
    QPair<QString, QString> getPaireSstart(double sStart);

    QMap<QString, QString> getMapListeRapport(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString numeroTest);

    QString ecrireAmplitudesGenou(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireAmplitudesHanche(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrirePerimetres(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireRatioIJ(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireMcCall(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireRatioA(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrirePointsReceptionUnipodale(QList<QPair<QString, QMap<QString, QString> > > listePairesRapport);
    QString ecrireCmjBipodal(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString sexe, QString labelBlessure);
    QString ecrireCmjUnipodal(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireDjBipodal(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireDjUnipodal(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireSjBipodal(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireTestAcc(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireAclRsi(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrirekStart(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QStringList listeNumerosTest);

    QString ecrireAmplitudesEpaule(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireTestsInstabilite(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireTestGrip(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireReRiR1(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireReRiR2(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString testIYT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireSiRsi(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireUQYBT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString dessinerTestUQ(QList<QPair<QString, QMap<QString, QString> > > listePairesRapport, QString suffixeBrasDroit, QString suffixeBrasGauche, QString labelBrasDroit,
                           QString labelBrasGauche, QString numeroTest);
    QString ecrireCkCuest(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireSASSPT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireULRT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrirePSET(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireSStart(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QStringList listeNumerosTest, QString labelBlessure);

    QString ecrireDoubleLegHop(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString contexte);
    QString ecireSingleLegHop(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure, QString contexte);
    QString ecireTripleHop(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecireCrossOverHop(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);

    bool doitEtreEcrit(QStringList listeCaractereCles, QMap<QString, QString> map);
    bool doitEtreEcritAllTest(QStringList listecaractereCles, QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);

    QStringList determinerTestsRemplis(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QStringList listeTestFaitsTableau, QString caractereCle);
    bool lancerCmdPdftk(QString pathFichierRapport, QString pathFichierAnnexes, QString pathFichierRes);
    void copyFile(const QString& sourceFilePath, const QString& destinationFilePath);

    QString remplirChaineHtmlGenou(QStringList listeNumerosTest);
    QString remplirChaineHtmlEpaule(QStringList listeNumerosTest);
    QString remplirChaineHtmlHanche(QStringList listeNumerosTest);
    QString remplirChaineHtmlCheville(QStringList listeNumerosTest);

    void initialiserDatabase();
    void testDb();
    void genererRapportPdf(QString contenuHtml);
    void viderInfosBilan();
    void viderInfosRapport();

    void ecrireLog(QString text);

};
#endif // MAINWINDOW_H
