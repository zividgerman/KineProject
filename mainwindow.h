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

    void on_pushButton_validerRapport_bpc_clicked();

    void on_toolButton_bpc_clicked();

    void on_pushButton_bpc_photos_analyseGestuelle_clicked();

    void on_pushButton_bpc_photos_analysePosturaleDynamique_clicked();

    void on_pushButton_bpc_photos_analysePosturaleStatique_clicked();

    void on_pushButton_valider_bilan_bpc_clicked();

    void on_pushButton_bpc_photos_analyseGestuelleBS_clicked();

    void on_pushButton_valider_bilan_bpsc_clicked();

    void on_pushButton_bpsc_photos_analyseGestuelleFVV_clicked();

    void on_pushButton_bpsc_photos_analyseGestuelleFVH_clicked();

    void on_pushButton_bpsc_photos_analyseGestuelleBS_clicked();

    void on_pushButton_bpsc_photos_analyseGestuelleSprint_clicked();

    void on_pushButton_bpsc_photos_analyseGestuelleVM_clicked();

    void on_pushButton_validerRapport_bpsc_clicked();

    void on_toolButton_bpsc_clicked();

    void on_pushButton_valider_bilan_bpf_clicked();

    void on_pushButton_bpsc_photos_analysePosturaleStatique_clicked();

    void on_pushButton_bpsc_photos_analysePosturaleDynamique_clicked();

    void on_pushButton_bpf_photos_analysePosturaleStatique_clicked();

    void on_pushButton_bpf_photos_analysePosturaleDynamiqueMI_clicked();

    void on_pushButton_validerRapport_bpf_clicked();

    void on_toolButton_bpf_clicked();

    void on_pushButton_bpf_photos_analyseGestuelleFVV_clicked();

    void on_pushButton_bpf_photos_analyseGestuelle_clicked();

    void on_pushButton_validerRapport_bpcf_clicked();

    void on_pushButton_valider_bilan_bpcf_clicked();

    void on_pushButton_bpcf_photos_analysePosturaleStatique_clicked();

    void on_pushButton_bpcf_photos_analysePosturaleDynamiqueMI_clicked();

    void on_pushButton_bpcf_photos_analysePosturaleDynamiqueMS_clicked();

    void on_pushButton_bpcf_photos_analyseGestuelle_clicked();

    void on_pushButton_bpf_photos_analysePosturaleDynamiqueMS_clicked();

    void on_pushButton_bpcf_photos_analyseGestuelleFVV_clicked();

    void on_pushButton_bpcf_photos_forceMaximale_clicked();

    void on_pushButton_bpf_photos_forceMaximale_clicked();

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

    QMap<QString, QString> mapCheminsImages;


    QStringList listeTestsCourant;
    QStringList cheminsImages;

    QString getValue(QString pathFichierConfig, QString groupe, QString cle);
    QStringList recupererListeColonnesTable(QString nomTable);
    QString ecrireLigneTableau(QStringList listeValeursLigne);

    QMap<QString, QString> remplirQMapInfoBilanEpaule(QString typeRequete);
    QMap<QString, QString> remplirQMapInfoBilanGenou(QString typeRequete);
    QMap<QString, QString> remplirQMapInfoBilanHanche(QString typeRequete);
    QMap<QString, QString> remplirQMapInfoBilanCheville(QString typeRequete);
    QMap<QString, QString> remplirQMapInfoBilanBpc(QString typeRequete);
    QMap<QString, QString> remplirQMapInfoBilanBpsc(QString typeRequete);
    QMap<QString, QString> remplirQMapInfoBilanBpf(QString typeRequete);
    QMap<QString, QString> remplirQMapInfoBilanBpcf(QString typeRequete);

    QMap<QString, QString> recupererInfosBilanGenouBdd(QString numeroTest);
    QMap<QString, QString> recupererInfosBilanEpauleBdd(QString numeroTest);
    QMap<QString, QString> recupererInfosBilanChevilleBdd(QString numeroTest);
    QMap<QString, QString> recupererInfosBilanHancheBdd(QString numeroTest);
    QMap<QString, QString> recupererInfosBilanBpcBdd(QString numeroTest);
    QMap<QString, QString> recupererInfosBilanBpscBdd(QString numeroTest);
    QMap<QString, QString> recupererInfosBilanBpfBdd(QString numeroTest);
    QMap<QString, QString> recupererInfosBilanBpcfBdd(QString numeroTest);

    QString getCouleurRatioIschio(double ratio);
    QString getCouleurRatioAbd(double ratio);
    QString getCouleurACLRsi(double aclRsi);
    QString getCouleurRsiModifie(double rsi, QString sexe);
    QString getCouleurRsi(double rsi);
    QString getCouleurBkfo(double bkfo);
    QString getCouleurScoreBS(double bkfo, int poids);
    QString getCouleurEI(double ratio);
    QString getCouleurSautsRepetesRsi(double rsi);

    QPair<QString, QString> getPaireRsiModifie(double numerateur, double denominateur, QString sexe);
    QPair<QString, QString> getPaireRatio(double numerateur, double denominateur, QString typeRatio);
    QPair<QString, QString> getPaireAsymetrie(bool inversion,double nonOpere, double opere);
    QPair<QString, QString> getPaireKstart(double kStart);
    QPair<QString, QString> calculerProgression(QString unite, double valeurAvant, double valeurApres);
    QPair<QString, QString> getProgressionPourcentage(bool inversion, double valeurAvant, double valeurApres);
    QString getCouleurPourcentageForce(double forceSain, double forceNO);

    QString getCouleurReRiR1(double ratio);
    QString getCouleurReRiR2(double ratio);
    QString getCouleurSiRsi(double aclRsi);
    QPair<QString, QString> getPaireLSI(double dsl, double dil, double dm, double longueurBras);
    QString getCouleurPourcentageLSI(double pourcentage);
    QString getCouleurCKCuest(double nbTouches);
    QString getCouleurURLT(double nbRepetitions);
    QString getCouleurAgility(double value, QString sexe);
    QString getCouleurIllinois(double value, QString sexe);

    QPair<QString, QString> getPaireSstart(double sStart);

    QMap<QString, QString> getMapListeRapport(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString numeroTest);

    QString ecrireAmplitudesGenou(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireAmplitudesHanche(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireAmplitudesCheville(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireAmplitudesBp(QList<QPair<QString, QMap<QString, QString> > > listePairesRapport);
    QString ecrireAmplitudesBpf(QList<QPair<QString, QMap<QString, QString> > > listePairesRapport);
    QString ecrireAmplitudesBpcf(QList<QPair<QString, QMap<QString, QString> > > listePairesRapport);

    QString ecrirePerimetres(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);

    QString ecrireRatioIJ(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireMcCall(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireRatioA(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireRatioREHanche(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireIP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
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
    QString ecrireTestIYT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireSiRsi(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireUQYBT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString dessinerTestUQ(QList<QPair<QString, QMap<QString, QString> > > listePairesRapport, QString suffixeBrasDroit, QString suffixeBrasGauche, QString labelBrasDroit,
                           QString labelBrasGauche, QString numeroTest);
    QString ecrireCkCuest(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireSASSPT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireULRT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrirePSET(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireSStart(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QStringList listeNumerosTest, QString labelBlessure);

    QString ecrireBroadJump(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString contexte);
    QString ecrireHop(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure, QString contexte);
    QString ecrireTripleHop(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireCrossOverHop(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireFootLift(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);

    QString ecrireFmaxReleveursCheville(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireFmaxSoleaireCheville(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireRatioVerseurs(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireSautsRepetes(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireAlrRsi(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);

    QString ecrireHeelRise(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString ecrireSLIHRH(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);

    QString ecrireYBalance(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString labelBlessure);
    QString dessinerTestYBalance(QList<QPair<QString, QMap<QString, QString> > > listePairesRapport, QString suffixeDroit, QString suffixeGauche, QString labelDroit,
                                 QString labelGauche, QString numeroTest);

    QString ecrireRatioVerseursBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireFmaxReleveursSoleaireBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireRatioIJBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireRatioAABP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireMcCallBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireIPBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);

    QString ecrireSjBipodalBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireCmjBipodalBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString sexe);
    QString ecrireDjBipodalBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireCmjUnipodalBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireDjUnipodalBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireSautsRepetesBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);

    QString ecrireFmaxBS(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString poids);
    QString ecrireHopBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireTripleHopBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireCrossOverHopBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireHeelRiseBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireTestIYTBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireTestGripBP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);

    QString ecrireMTT(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireNordicCurl(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireSprintTest(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);

    QString ecrireFmaxPL(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString poids);
    QString ecrireTestFmaxBPF(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString poids);
    QString ecrireTestFmaxBPCF(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString poids);

    QString ecrireProfilFVV(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireProfilFVH(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);

    QString ecrireProfilVM(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QString sexe);
    QString ecrireDSI(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);

    QString ecrireReRiR1BP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);
    QString ecrireReRiR2BP(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);


    QString ecrirePhotos();
    QString redimensionnerImage(QString pathFichierImage, int taille);


    bool doitEtreEcrit(QStringList listeCaractereCles, QMap<QString, QString> map);
    bool doitEtreEcritAllTest(QStringList listecaractereCles, QList<QPair<QString, QMap<QString, QString>>> listePairesRapport);

    QStringList determinerTestsRemplis(QList<QPair<QString, QMap<QString, QString>>> listePairesRapport, QStringList listeTestFaitsTableau, QString caractereCle);
    bool lancerCmdPdftk(QString pathFichierRapport, QString pathFichierAnnexes, QString pathFichierRes);
    void copyFile(const QString& sourceFilePath, const QString& destinationFilePath);

    QString remplirChaineHtmlGenou(QStringList listeNumerosTest);
    QString remplirChaineHtmlEpaule(QStringList listeNumerosTest);
    QString remplirChaineHtmlHanche(QStringList listeNumerosTest);
    QString remplirChaineHtmlCheville(QStringList listeNumerosTest);
    QString remplirChaineHtmlCourse(QStringList listeNumerosTest);
    QString remplirChaineHtmlSportCollectif(QStringList listeNumerosTest);
    QString remplirChaineHtmlSportCombat(QStringList listeNumerosTest);
    QString remplirChaineHtmlCrossfit(QStringList listeNumerosTest);

    QString genererPageCouvertureBF(const QString& patientName,
                                    const QString& patientDate,
                                    const QString& pathAthleteImage,
                                    const QString& pathLogo, const QString &titreBilan);

        //Course
    QString ecrireAnalyseGenerique(QMap<QString, QString> mapChemins, QString texteEncadre, QString titreEncadre, QString typeEncadre, int maxWidth, int maxHeight);
    QString ecrireInterpretation(QString texteInterpretation, QString titreInterpretation);
    QString encadrerTableauEtImage(const QString& texteTableau, const QString& cheminImage, int maxWidth, int maxHeight);
    QString encadrerTableauEtImageFlexible(const QString& texteTableau, const QString& cheminImage, const QString& position,int maxWidth,int maxHeight);


    void redimensionnerImages();
    void initialiserDatabase();
    void testDb();
    void genererRapportPdf(QString contenuHtml);
    void viderInfosBilan();
    void viderInfosRapport();

    void ecrireLog(QString text);

};
#endif // MAINWINDOW_H
