/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGestionPatient;
    QWidget *centralwidget;
    QComboBox *comboBox_dateBilan;
    QLabel *label_date_bilan;
    QComboBox *comboBox_patient_courant;
    QLabel *label_patient_courant;
    QFrame *line_5;
    QPushButton *pushButton_rechercher;
    QComboBox *comboBox_type_Bilan;
    QLabel *label_type_bilan;
    QPushButton *pushButton_generer_rapport;
    QPushButton *pushButton_editer_bilan;
    QTextEdit *textEdit;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *widget_genou;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_perimetres;
    QLabel *label_perimetre;
    QLabel *label_opere_3;
    QLabel *label_non_opere_3;
    QLabel *label_mollet;
    QLabel *label_sommet_rotule_dix;
    QLabel *label_sommet_rotule_vingt;
    QDoubleSpinBox *doubleSpinBox_g_perimetreMolletNO;
    QDoubleSpinBox *doubleSpinBox_g_perimetreMolletO;
    QDoubleSpinBox *doubleSpinBox_g_perimetreRotuleDixO;
    QDoubleSpinBox *doubleSpinBox_g_perimetreRotuleDixNO;
    QDoubleSpinBox *doubleSpinBox_g_perimetreRotuleVingtO;
    QDoubleSpinBox *doubleSpinBox_g_perimetreRotuleVingtNO;
    QWidget *layoutWidget_5;
    QGridLayout *gridLayout_aclRsi;
    QLabel *label_kStart;
    QLabel *label_rsi;
    QSpinBox *spinBox_g_kStart;
    QLabel *label_sur_cent;
    QSpinBox *spinBox_g_testRSI;
    QLabel *label_sur_cent_2;
    QWidget *layoutWidget_6;
    QGridLayout *gridLayout_amplitudes;
    QLabel *label_amplitude_articulaire;
    QLabel *label_opere;
    QLabel *label_non_opere;
    QLabel *label_flexion;
    QLabel *label_extension;
    QDoubleSpinBox *doubleSpinBox_g_flexionO;
    QDoubleSpinBox *doubleSpinBox_g_flexionNO;
    QDoubleSpinBox *doubleSpinBox_g_extensionO;
    QDoubleSpinBox *doubleSpinBox_g_extensionNO;
    QWidget *layoutWidget_7;
    QHBoxLayout *horizontalLayout;
    QLabel *label_test_accroupissement;
    QComboBox *comboBox_g_testAccroupissement;
    QWidget *layoutWidget_10;
    QGridLayout *gridLayout_rationAA;
    QLabel *label_fmax_abducteurs;
    QLabel *label_opere_5;
    QLabel *label_ration_add_abb;
    QLabel *label_non_opere_5;
    QLabel *label_fmax_adducteurs;
    QDoubleSpinBox *doubleSpinBox_g_fmaxAdducteursO;
    QDoubleSpinBox *doubleSpinBox_g_fmaxAdducteursNO;
    QDoubleSpinBox *doubleSpinBox_g_fmaxAbducteursO;
    QDoubleSpinBox *doubleSpinBox_g_fmaxAbducteursNO;
    QPushButton *pushButton_valider_bilan;
    QWidget *layoutWidget_11;
    QGridLayout *gridLayout_sjB;
    QDoubleSpinBox *doubleSpinBox_g_rfdmaxNOSj;
    QLabel *label_hauteur_saut_sj;
    QLabel *label_test_sjB;
    QLabel *label_fmax_sj;
    QLabel *label_pmax_Sj;
    QDoubleSpinBox *doubleSpinBox_g_rfdmaxOSj;
    QDoubleSpinBox *doubleSpinBox_g_hauteurSautSj;
    QWidget *layoutWidget_12;
    QGridLayout *gridLayout_ratioIJ;
    QDoubleSpinBox *doubleSpinBox_g_fmaxQuadriNO;
    QLabel *label_non_opere_4;
    QDoubleSpinBox *doubleSpinBox_g_fmaxIschioO;
    QLabel *label_opere_4;
    QLabel *label_ration_ij_quadri;
    QLabel *label_fmax_ij;
    QDoubleSpinBox *doubleSpinBox_g_fmaxIschioNO;
    QLabel *label_fmax_quadri;
    QDoubleSpinBox *doubleSpinBox_g_fmaxQuadriO;
    QFrame *line;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_6;
    QGroupBox *groupBox_controleGenou_g;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_g_controleGenouValgus;
    QRadioButton *radioButton_g_controleGenouFrontal;
    QGroupBox *groupBox;
    QRadioButton *radioButton_g_angleFlexionNOK;
    QRadioButton *radioButton_g_angleFlexionOK;
    QGroupBox *groupBox_repartitionCharge_g;
    QCheckBox *checkBox_g_receptionMedioPied;
    QCheckBox *checkBox_g_receptionAvantPied;
    QCheckBox *checkBox_g_receptionBordInterne;
    QCheckBox *checkBox_g_receptionTalon;
    QFrame *line_11;
    QGroupBox *groupBox_troncBassin_g;
    QRadioButton *radioButton_g_controleTroncOK;
    QRadioButton *radioButton_g_controleTroncNOK;
    QFrame *line_18;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_3;
    QLabel *label_test_dj;
    QLabel *label_opere_7;
    QLabel *label_non_opere_7;
    QLabel *label_hauteur_saut_dj;
    QDoubleSpinBox *doubleSpinBox_g_hauteurSautDjO;
    QDoubleSpinBox *doubleSpinBox_g_hauteurSautDjNO;
    QLabel *label_rfdmax_dj;
    QDoubleSpinBox *doubleSpinBox_g_rfdmaxDjO;
    QDoubleSpinBox *doubleSpinBox_g_rfdmaxDjNO;
    QLabel *label_tps_contact_dj;
    QDoubleSpinBox *doubleSpinBox_g_tempsContactDjO;
    QDoubleSpinBox *doubleSpinBox_g_tempsContactDjNO;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_2;
    QLabel *label_test_cmj;
    QLabel *label_opere_6;
    QLabel *label_non_opere_6;
    QLabel *label_hauteur_saut_cmj;
    QDoubleSpinBox *doubleSpinBox_g_hauteurSautCmjO;
    QDoubleSpinBox *doubleSpinBox_g_hauteurSautCmjNO;
    QWidget *layoutWidget_22;
    QGridLayout *gridLayout_ratioIJ_2;
    QDoubleSpinBox *doubleSpinBox_g_force90McCallNO;
    QLabel *label_non_opere_16;
    QDoubleSpinBox *doubleSpinBox_g_force30McCallO;
    QLabel *label_opere_17;
    QLabel *label_ration_ij_quadri_2;
    QLabel *label_f30_mccall;
    QDoubleSpinBox *doubleSpinBox_g_force30McCallNO;
    QLabel *label_f90_mccall;
    QDoubleSpinBox *doubleSpinBox_g_force90McCallO;
    QFrame *line_19;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout;
    QLabel *label_test_cmjB;
    QLabel *label_hauteur_saut_cmjB;
    QDoubleSpinBox *doubleSpinBox_g_hauteurSautCmjB;
    QLabel *label_tps_stabilisation_cmj_2;
    QDoubleSpinBox *doubleSpinBox_g_tempsMvmtCmjB;
    QLabel *label_fmax_cmjB;
    QDoubleSpinBox *doubleSpinBox_g_rfdDecelerationOCmjB;
    QLabel *label_RFDdeceleration;
    QDoubleSpinBox *doubleSpinBox_g_rfdDecelerationNOCmjB;
    QWidget *layoutWidget4;
    QGridLayout *gridLayout_4;
    QLabel *label_test_djB;
    QLabel *label_hauteur_saut_djB;
    QDoubleSpinBox *doubleSpinBox_g_hauteurSautDjB;
    QLabel *label_tps_vol_djB;
    QDoubleSpinBox *doubleSpinBox_g_tempsVolDjB;
    QLabel *label_tps_contact_djB;
    QDoubleSpinBox *doubleSpinBox_g_tempsContactDjB;
    QLabel *label_fmax_djB;
    QDoubleSpinBox *doubleSpinBox_g_rfdmaxODjB;
    QLabel *label_rfdmax_djB;
    QDoubleSpinBox *doubleSpinBox_g_rfdmaxNODjB;
    QWidget *widget_generation_rapport_genou;
    QTextEdit *textEdit_interpretationKine;
    QLabel *label_axes;
    QFrame *line_7;
    QLabel *label_axes_2;
    QPushButton *pushButton_validerRapport;
    QFrame *line_8;
    QToolButton *toolButton_g;
    QLabel *label_axes_3;
    QLineEdit *lineEdit_g_pathAnnexes;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_axesAmeliorer;
    QCheckBox *checkBox_g_tricepsSural;
    QCheckBox *checkBox_g_excentriqueQuadri;
    QCheckBox *checkBox_g_concentriqueQuadri;
    QCheckBox *checkBox_g_ij;
    QCheckBox *checkBox_g_renfoStabilisateurs;
    QCheckBox *checkBox_g_intrinseque;
    QCheckBox *checkBox_g_renforcementAdducteurs;
    QCheckBox *checkBox_g_changementDirection;
    QCheckBox *checkBox_g_plioHorizontaleAxe;
    QCheckBox *checkBox_g_plioVerticaleAxe;
    QCheckBox *checkBox_g_plioMulti;
    QCheckBox *checkBox_g_controleGenou;
    QCheckBox *checkBox_g_controleComplexe;
    QCheckBox *checkBox_g_force;
    QCheckBox *checkBox_g_explosivite;
    QCheckBox *checkBox_g_deceleration;
    QLabel *label;
    QPushButton *pushButton_annulerEditionBilan;
    QPushButton *pushButton_annulerEditionRapport;
    QLabel *label_nombreBilan;
    QWidget *widget_epaule;
    QWidget *layoutWidget_13;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_testApprehension;
    QComboBox *comboBox_e_testInstabiliteA;
    QWidget *layoutWidget_9;
    QGridLayout *gridLayout_RERI1;
    QDoubleSpinBox *doubleSpinBox_e_fmaxRIR1O;
    QLabel *label_testRotationR1;
    QLabel *label_fmaxRIR1;
    QLabel *label_opere_10;
    QDoubleSpinBox *doubleSpinBox_e_fmaxRIR1NO;
    QDoubleSpinBox *doubleSpinBox_e_fmaxRER1O;
    QLabel *label_fmaxRER1;
    QLabel *label_non_opere_10;
    QDoubleSpinBox *doubleSpinBox_e_fmaxRER1NO;
    QWidget *layoutWidget_14;
    QGridLayout *gridLayout_RERI2;
    QDoubleSpinBox *doubleSpinBox_e_fmaxRIR2O;
    QLabel *label_testRotationR2;
    QLabel *label_fmaxRIR2;
    QLabel *label_opere_11;
    QDoubleSpinBox *doubleSpinBox_e_fmaxRIR2NO;
    QDoubleSpinBox *doubleSpinBox_e_fmaxRER2O;
    QLabel *label_fmaxRER2;
    QLabel *label_non_opere_11;
    QDoubleSpinBox *doubleSpinBox_e_fmaxRER2NO;
    QWidget *layoutWidget_15;
    QGridLayout *gridLayout_UqYbt;
    QLabel *label_distanceSL;
    QDoubleSpinBox *doubleSpinBox_e_distanceSLNO;
    QLabel *label_opere_12;
    QLabel *label_distanceM;
    QLabel *label_distanceIL;
    QLabel *label_non_opere_12;
    QLabel *label_test_uqYbt;
    QDoubleSpinBox *doubleSpinBox_e_distanceSLO;
    QDoubleSpinBox *doubleSpinBox_e_distanceIO;
    QDoubleSpinBox *doubleSpinBox_e_distanceINO;
    QDoubleSpinBox *doubleSpinBox_e_distanceMO;
    QDoubleSpinBox *doubleSpinBox_e_distanceMNO;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_testCkCuest;
    QLabel *label_testCkCuest;
    QLabel *label_opere_13;
    QLabel *label_nbTouches;
    QDoubleSpinBox *doubleSpinBox_e_nbTouches;
    QWidget *layoutWidget_16;
    QGridLayout *gridLayout_testSasspt;
    QLabel *label_testSasspt;
    QLabel *label_opere_14;
    QLabel *label_non_opere_14;
    QLabel *label_distanceLancer;
    QDoubleSpinBox *doubleSpinBox_e_distanceLanceO;
    QDoubleSpinBox *doubleSpinBox_e_distanceLanceNO;
    QWidget *layoutWidget_17;
    QGridLayout *gridLayout_testUlrt;
    QLabel *label_testUlrt;
    QLabel *label_opere_15;
    QLabel *label_non_opere_15;
    QLabel *label_nbRepetitions;
    QSpinBox *spinBox_e_nbRepetitionsO;
    QSpinBox *spinBox_e_nbRepetitionsNO;
    QFrame *line_9;
    QFrame *line_12;
    QFrame *line_13;
    QWidget *layoutWidget_19;
    QGridLayout *gridLayout_siRsi;
    QLabel *label_kStart_3;
    QLabel *label_siRsi;
    QSpinBox *spinBox_e_sStart;
    QLabel *label_sur_cent_3;
    QSpinBox *spinBox_e_testSIRSI;
    QLabel *label_sur_cent_5;
    QFrame *line_14;
    QPushButton *pushButton_valider_bilan_epaule;
    QWidget *layoutWidget6;
    QGridLayout *gridLayout_amplitudes_epaule;
    QLabel *label_amplitude_articulaire_2;
    QLabel *label_opere_8;
    QLabel *label_non_opere_8;
    QLabel *label_elevationAnterieure;
    QDoubleSpinBox *doubleSpinBox_e_elevationAnterieureO;
    QDoubleSpinBox *doubleSpinBox_e_elevationAnterieureNO;
    QLabel *label_elevationLaterale;
    QDoubleSpinBox *doubleSpinBox_e_elevationLateraleO;
    QDoubleSpinBox *doubleSpinBox_e_elevationLateraleNO;
    QLabel *label_extensionE;
    QDoubleSpinBox *doubleSpinBox_e_extensionEO;
    QDoubleSpinBox *doubleSpinBox_e_extensionENO;
    QLabel *label_adductionHorizontale;
    QDoubleSpinBox *doubleSpinBox_e_adductionHorizontaleO;
    QDoubleSpinBox *doubleSpinBox_e_adductionHorizontaleNO;
    QLabel *label_rotationInterneR1;
    QLabel *label_rotationExterneR1;
    QDoubleSpinBox *doubleSpinBox_e_rotationExterneR1O;
    QDoubleSpinBox *doubleSpinBox_e_rotationExterneR1NO;
    QLabel *label_rotationInterneR2;
    QDoubleSpinBox *doubleSpinBox_e_rotationInterneR2O;
    QDoubleSpinBox *doubleSpinBox_e_rotationInterneR2NO;
    QLabel *label_rotationExterneR2;
    QDoubleSpinBox *doubleSpinBox_e_rotationExterneR2O;
    QDoubleSpinBox *doubleSpinBox_e_rotationExterneR2NO;
    QComboBox *comboBox_e_rotationInterneR1O;
    QComboBox *comboBox_e_rotationInterneR1NO;
    QWidget *layoutWidget7;
    QGridLayout *gridLayout_testGrip;
    QLabel *label_testGrip;
    QLabel *label_opere_9;
    QLabel *label_non_opere_9;
    QLabel *label_elevationAnterieure_2;
    QDoubleSpinBox *doubleSpinBox_e_fmaxGripO;
    QDoubleSpinBox *doubleSpinBox_e_fmaxGripNO;
    QLabel *label_3;
    QComboBox *comboBox_e_brasOpere;
    QWidget *layoutWidget_20;
    QGridLayout *gridLayout_RERI1_2;
    QDoubleSpinBox *doubleSpinBox_e_psetWO;
    QLabel *label_testRotationR1_2;
    QLabel *label_fmaxRIR1_2;
    QLabel *label_opere_16;
    QDoubleSpinBox *doubleSpinBox_e_psetWNO;
    QDoubleSpinBox *doubleSpinBox_e_psetYO;
    QLabel *label_fmaxRER1_2;
    QLabel *label_non_opere_13;
    QDoubleSpinBox *doubleSpinBox_e_psetYNO;
    QFrame *line_17;
    QWidget *layoutWidget_21;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_testApprehension_2;
    QComboBox *comboBox_e_testInstabiliteP;
    QTextEdit *textEdit_schemaYBT;
    QLabel *label_4;
    QComboBox *comboBox_e_mainDominante;
    QWidget *layoutWidget8;
    QFormLayout *formLayout;
    QLabel *label_distanceM_2;
    QDoubleSpinBox *doubleSpinBox_e_longueurBras;
    QFrame *line_20;
    QWidget *layoutWidget9;
    QGridLayout *gridLayout_5;
    QLabel *label_testRotationR1_3;
    QLabel *label_opere_18;
    QLabel *label_non_opere_17;
    QLabel *label_fmaxRER1_3;
    QDoubleSpinBox *doubleSpinBox_e_fmaxIO;
    QDoubleSpinBox *doubleSpinBox_e_fmaxINO;
    QLabel *label_fmaxRIR1_3;
    QDoubleSpinBox *doubleSpinBox_e_fmaxYO;
    QDoubleSpinBox *doubleSpinBox_e_fmaxYNO;
    QLabel *label_fmaxRIR1_4;
    QDoubleSpinBox *doubleSpinBox_e_fmaxTO;
    QDoubleSpinBox *doubleSpinBox_e_fmaxTNO;
    QWidget *widget_generation_rapport_epaule;
    QTextEdit *textEdit_interpretationKine_2;
    QLabel *label_axes_4;
    QFrame *line_15;
    QLabel *label_axes_5;
    QPushButton *pushButton_validerRapport_epaule;
    QFrame *line_16;
    QToolButton *toolButton_e;
    QLabel *label_axes_6;
    QLineEdit *lineEdit_e_pathAnnexes;
    QWidget *layoutWidget_18;
    QVBoxLayout *verticalLayout_axesAmeliorer_2;
    QCheckBox *checkBox_e_AugmenterAmplitudes;
    QCheckBox *checkBox_e_renfoExternes;
    QCheckBox *checkBox_e_renfoInternes;
    QCheckBox *checkBox_e_renfoTrapeze;
    QCheckBox *checkBox_e_renfoDentele;
    QCheckBox *checkBox_e_forceGrip;
    QCheckBox *checkBox_e_pousseeHorizontale;
    QCheckBox *checkBox_e_coiffeFixateur;
    QCheckBox *checkBox_e_controleArme;
    QCheckBox *checkBox_e_controleOverhead;
    QCheckBox *checkBox_e_explosivite;
    QLabel *label_2;
    QPushButton *pushButton_modifier_bilan;
    QWidget *widget_hanche;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_perimetres_2;
    QLabel *label_perimetre_2;
    QLabel *label_opere_19;
    QLabel *label_non_opere_18;
    QLabel *label_mollet_2;
    QLabel *label_sommet_rotule_dix_2;
    QLabel *label_sommet_rotule_vingt_2;
    QDoubleSpinBox *doubleSpinBox_h_perimetreMolletNO;
    QDoubleSpinBox *doubleSpinBox_h_perimetreMolletO;
    QDoubleSpinBox *doubleSpinBox_h_perimetreRotuleDixO;
    QDoubleSpinBox *doubleSpinBox_h_perimetreRotuleDixNO;
    QDoubleSpinBox *doubleSpinBox_h_perimetreRotuleVingtO;
    QDoubleSpinBox *doubleSpinBox_h_perimetreRotuleVingtNO;
    QWidget *layoutWidget_24;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_test_accroupissement_2;
    QComboBox *comboBox_h_testAccroupissement;
    QWidget *layoutWidget_25;
    QGridLayout *gridLayout_rationAA_2;
    QLabel *label_fmax_abducteurs_2;
    QLabel *label_opere_20;
    QLabel *label_ration_add_abb_2;
    QLabel *label_non_opere_19;
    QLabel *label_fmax_adducteurs_2;
    QDoubleSpinBox *doubleSpinBox_h_fmaxAdducteursO;
    QDoubleSpinBox *doubleSpinBox_h_fmaxAdducteursNO;
    QDoubleSpinBox *doubleSpinBox_h_fmaxAbducteursO;
    QDoubleSpinBox *doubleSpinBox_h_fmaxAbducteursNO;
    QPushButton *pushButton_valider_bilan_hanche;
    QWidget *layoutWidget_26;
    QGridLayout *gridLayout_sjB_2;
    QDoubleSpinBox *doubleSpinBox_h_rfdmaxNOSj;
    QLabel *label_hauteur_saut_sj_2;
    QLabel *label_test_sjB_2;
    QLabel *label_fmax_sj_2;
    QLabel *label_pmax_Sj_2;
    QDoubleSpinBox *doubleSpinBox_h_rfdmaxOSj;
    QDoubleSpinBox *doubleSpinBox_h_hauteurSautSj;
    QWidget *layoutWidget_27;
    QGridLayout *gridLayout_ratioIJ_3;
    QDoubleSpinBox *doubleSpinBox_h_fmaxQuadriNO;
    QLabel *label_non_opere_20;
    QDoubleSpinBox *doubleSpinBox_h_fmaxIschioO;
    QLabel *label_opere_21;
    QLabel *label_ration_ij_quadri_3;
    QLabel *label_fmax_ij_2;
    QDoubleSpinBox *doubleSpinBox_h_fmaxIschioNO;
    QLabel *label_fmax_quadri_2;
    QDoubleSpinBox *doubleSpinBox_h_fmaxQuadriO;
    QFrame *line_2;
    QFrame *line_10;
    QFrame *line_21;
    QGroupBox *groupBox_controleGenou_h;
    QGroupBox *groupBox_3;
    QRadioButton *radioButton_h_controleGenouValgus;
    QRadioButton *radioButton_h_controleGenouFrontal;
    QGroupBox *groupBox_4;
    QRadioButton *radioButton_h_angleFlexionNOK;
    QRadioButton *radioButton_h_angleFlexionOK;
    QGroupBox *groupBox_repartitionCharge_h;
    QCheckBox *checkBox_h_receptionMedioPied;
    QCheckBox *checkBox_h_receptionAvantPied;
    QCheckBox *checkBox_h_receptionBordInterne;
    QCheckBox *checkBox_h_receptionTalon;
    QFrame *line_23;
    QGroupBox *groupBox_troncBassin_h;
    QRadioButton *radioButton_h_controleTroncOK;
    QRadioButton *radioButton_h_controleTroncNOK;
    QFrame *line_24;
    QWidget *layoutWidget_4;
    QGridLayout *gridLayout_6;
    QLabel *label_test_dj_2;
    QLabel *label_opere_22;
    QLabel *label_non_opere_21;
    QLabel *label_hauteur_saut_dj_2;
    QDoubleSpinBox *doubleSpinBox_h_hauteurSautDjO;
    QDoubleSpinBox *doubleSpinBox_h_hauteurSautDjNO;
    QLabel *label_rfdmax_dj_2;
    QDoubleSpinBox *doubleSpinBox_h_rfdmaxDjO;
    QDoubleSpinBox *doubleSpinBox_h_rfdmaxDjNO;
    QLabel *label_tps_contact_dj_2;
    QDoubleSpinBox *doubleSpinBox_h_tempsContactDjO;
    QDoubleSpinBox *doubleSpinBox_h_tempsContactDjNO;
    QWidget *layoutWidget_28;
    QGridLayout *gridLayout_7;
    QLabel *label_test_cmj_2;
    QLabel *label_opere_23;
    QLabel *label_non_opere_22;
    QLabel *label_hauteur_saut_cmj_2;
    QDoubleSpinBox *doubleSpinBox_h_hauteurSautCmjO;
    QDoubleSpinBox *doubleSpinBox_h_hauteurSautCmjNO;
    QWidget *layoutWidget_29;
    QGridLayout *gridLayout_ratioIJ_4;
    QDoubleSpinBox *doubleSpinBox_h_force90McCallNO;
    QLabel *label_non_opere_23;
    QDoubleSpinBox *doubleSpinBox_h_force30McCallO;
    QLabel *label_opere_24;
    QLabel *label_ration_ij_quadri_4;
    QLabel *label_f30_mccall_2;
    QDoubleSpinBox *doubleSpinBox_h_force30McCallNO;
    QLabel *label_f90_mccall_2;
    QDoubleSpinBox *doubleSpinBox_h_force90McCallO;
    QFrame *line_25;
    QWidget *layoutWidget_30;
    QGridLayout *gridLayout_8;
    QLabel *label_test_cmjB_2;
    QLabel *label_hauteur_saut_cmjB_2;
    QDoubleSpinBox *doubleSpinBox_h_hauteurSautCmjB;
    QLabel *label_tps_stabilisation_cmj_3;
    QDoubleSpinBox *doubleSpinBox_h_tempsMvmtCmjB;
    QLabel *label_fmax_cmjB_2;
    QDoubleSpinBox *doubleSpinBox_h_rfdDecelerationOCmjB;
    QLabel *label_RFDdeceleration_2;
    QDoubleSpinBox *doubleSpinBox_h_rfdDecelerationNOCmjB;
    QWidget *layoutWidget_31;
    QGridLayout *gridLayout_9;
    QLabel *label_test_djB_2;
    QLabel *label_hauteur_saut_djB_2;
    QDoubleSpinBox *doubleSpinBox_h_hauteurSautDjB;
    QLabel *label_tps_vol_djB_2;
    QDoubleSpinBox *doubleSpinBox_h_tempsVolDjB;
    QLabel *label_tps_contact_djB_2;
    QDoubleSpinBox *doubleSpinBox_h_tempsContactDjB;
    QLabel *label_fmax_djB_2;
    QDoubleSpinBox *doubleSpinBox_h_rfdmaxODjB;
    QLabel *label_rfdmax_djB_2;
    QDoubleSpinBox *doubleSpinBox_h_rfdmaxNODjB;
    QWidget *layoutWidget10;
    QGridLayout *gridLayout_10;
    QLabel *label_amplitude_articulaire_3;
    QLabel *label_opere_2;
    QLabel *label_non_opere_2;
    QLabel *label_flexion_2;
    QDoubleSpinBox *doubleSpinBox_h_flexionO;
    QDoubleSpinBox *doubleSpinBox_h_flexionNO;
    QLabel *label_extension_2;
    QDoubleSpinBox *doubleSpinBox_h_extensionO;
    QDoubleSpinBox *doubleSpinBox_h_extensionNO;
    QLabel *label_flexion_3;
    QDoubleSpinBox *doubleSpinBox_h_abductionO;
    QDoubleSpinBox *doubleSpinBox_h_abductionNO;
    QLabel *label_flexion_7;
    QDoubleSpinBox *doubleSpinBox_h_adductionO;
    QDoubleSpinBox *doubleSpinBox_h_adductionNO;
    QLabel *label_flexion_4;
    QDoubleSpinBox *doubleSpinBox_h_rotationInterneO;
    QDoubleSpinBox *doubleSpinBox_h_rotationInterneNO;
    QLabel *label_flexion_5;
    QDoubleSpinBox *doubleSpinBox_h_rotationExterneO;
    QDoubleSpinBox *doubleSpinBox_h_rotationExterneNO;
    QLabel *label_flexion_6;
    QDoubleSpinBox *doubleSpinBox_h_bkfoO;
    QDoubleSpinBox *doubleSpinBox_h_bkfoNO;
    QWidget *widget_generation_rapport_hanche;
    QTextEdit *textEdit_interpretationKine_hanche;
    QLabel *label_axes_7;
    QFrame *line_22;
    QLabel *label_axes_8;
    QPushButton *pushButton_validerRapport_hanche;
    QFrame *line_26;
    QToolButton *toolButton_h;
    QLabel *label_axes_9;
    QLineEdit *lineEdit_h_pathAnnexes;
    QWidget *layoutWidget_8;
    QVBoxLayout *verticalLayout_axesAmeliorer_3;
    QCheckBox *checkBox_h_tricepsSural;
    QCheckBox *checkBox_h_excentriqueQuadri;
    QCheckBox *checkBox_h_concentriqueQuadri;
    QCheckBox *checkBox_h_ij;
    QCheckBox *checkBox_h_renfoStabilisateurs;
    QCheckBox *checkBox_h_intrinseque;
    QCheckBox *checkBox_h_renforcementAdducteurs;
    QCheckBox *checkBox_h_changementDirection;
    QCheckBox *checkBox_h_plioHorizontaleAxe;
    QCheckBox *checkBox_h_plioVerticaleAxe;
    QCheckBox *checkBox_h_plioMulti;
    QCheckBox *checkBox_h_controleGenou;
    QCheckBox *checkBox_h_controleComplexe;
    QCheckBox *checkBox_h_force;
    QCheckBox *checkBox_h_explosivite;
    QCheckBox *checkBox_h_deceleration;
    QLabel *label_5;
    QPushButton *pushButton_annulerModificationBilan;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 11759);
        MainWindow->setLocale(QLocale(QLocale::French, QLocale::France));
        actionGestionPatient = new QAction(MainWindow);
        actionGestionPatient->setObjectName("actionGestionPatient");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        comboBox_dateBilan = new QComboBox(centralwidget);
        comboBox_dateBilan->setObjectName("comboBox_dateBilan");
        comboBox_dateBilan->setGeometry(QRect(160, 100, 101, 21));
        label_date_bilan = new QLabel(centralwidget);
        label_date_bilan->setObjectName("label_date_bilan");
        label_date_bilan->setGeometry(QRect(50, 100, 111, 21));
        comboBox_patient_courant = new QComboBox(centralwidget);
        comboBox_patient_courant->setObjectName("comboBox_patient_courant");
        comboBox_patient_courant->setGeometry(QRect(160, 60, 161, 21));
        comboBox_patient_courant->setEditable(false);
        label_patient_courant = new QLabel(centralwidget);
        label_patient_courant->setObjectName("label_patient_courant");
        label_patient_courant->setGeometry(QRect(50, 60, 111, 21));
        line_5 = new QFrame(centralwidget);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(0, 190, 1001, 20));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        pushButton_rechercher = new QPushButton(centralwidget);
        pushButton_rechercher->setObjectName("pushButton_rechercher");
        pushButton_rechercher->setGeometry(QRect(160, 140, 91, 31));
        comboBox_type_Bilan = new QComboBox(centralwidget);
        comboBox_type_Bilan->setObjectName("comboBox_type_Bilan");
        comboBox_type_Bilan->setGeometry(QRect(160, 20, 181, 21));
        label_type_bilan = new QLabel(centralwidget);
        label_type_bilan->setObjectName("label_type_bilan");
        label_type_bilan->setGeometry(QRect(50, 20, 101, 21));
        pushButton_generer_rapport = new QPushButton(centralwidget);
        pushButton_generer_rapport->setObjectName("pushButton_generer_rapport");
        pushButton_generer_rapport->setGeometry(QRect(800, 100, 181, 31));
        pushButton_editer_bilan = new QPushButton(centralwidget);
        pushButton_editer_bilan->setObjectName("pushButton_editer_bilan");
        pushButton_editer_bilan->setGeometry(QRect(350, 140, 191, 31));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(540, 20, 121, 31));
        textEdit->setReadOnly(true);
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(20, 220, 981, 431));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1388, 429));
        scrollArea->setWidget(scrollAreaWidgetContents);
        widget_genou = new QWidget(centralwidget);
        widget_genou->setObjectName("widget_genou");
        widget_genou->setGeometry(QRect(10, 660, 921, 2001));
        layoutWidget = new QWidget(widget_genou);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(540, 10, 350, 154));
        gridLayout_perimetres = new QGridLayout(layoutWidget);
        gridLayout_perimetres->setSpacing(15);
        gridLayout_perimetres->setObjectName("gridLayout_perimetres");
        gridLayout_perimetres->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_perimetres->setContentsMargins(0, 0, 0, 0);
        label_perimetre = new QLabel(layoutWidget);
        label_perimetre->setObjectName("label_perimetre");
        label_perimetre->setTextFormat(Qt::RichText);

        gridLayout_perimetres->addWidget(label_perimetre, 0, 0, 1, 1);

        label_opere_3 = new QLabel(layoutWidget);
        label_opere_3->setObjectName("label_opere_3");

        gridLayout_perimetres->addWidget(label_opere_3, 0, 1, 1, 1);

        label_non_opere_3 = new QLabel(layoutWidget);
        label_non_opere_3->setObjectName("label_non_opere_3");

        gridLayout_perimetres->addWidget(label_non_opere_3, 0, 2, 1, 1);

        label_mollet = new QLabel(layoutWidget);
        label_mollet->setObjectName("label_mollet");

        gridLayout_perimetres->addWidget(label_mollet, 1, 0, 1, 1);

        label_sommet_rotule_dix = new QLabel(layoutWidget);
        label_sommet_rotule_dix->setObjectName("label_sommet_rotule_dix");

        gridLayout_perimetres->addWidget(label_sommet_rotule_dix, 2, 0, 1, 1);

        label_sommet_rotule_vingt = new QLabel(layoutWidget);
        label_sommet_rotule_vingt->setObjectName("label_sommet_rotule_vingt");

        gridLayout_perimetres->addWidget(label_sommet_rotule_vingt, 3, 0, 1, 1);

        doubleSpinBox_g_perimetreMolletNO = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_g_perimetreMolletNO->setObjectName("doubleSpinBox_g_perimetreMolletNO");
        doubleSpinBox_g_perimetreMolletNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_perimetreMolletNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_perimetreMolletNO->setAccelerated(true);
        doubleSpinBox_g_perimetreMolletNO->setDecimals(1);
        doubleSpinBox_g_perimetreMolletNO->setMaximum(100000.000000000000000);

        gridLayout_perimetres->addWidget(doubleSpinBox_g_perimetreMolletNO, 1, 2, 1, 1);

        doubleSpinBox_g_perimetreMolletO = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_g_perimetreMolletO->setObjectName("doubleSpinBox_g_perimetreMolletO");
        doubleSpinBox_g_perimetreMolletO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_perimetreMolletO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_perimetreMolletO->setAccelerated(true);
        doubleSpinBox_g_perimetreMolletO->setDecimals(1);
        doubleSpinBox_g_perimetreMolletO->setMaximum(100000.000000000000000);

        gridLayout_perimetres->addWidget(doubleSpinBox_g_perimetreMolletO, 1, 1, 1, 1);

        doubleSpinBox_g_perimetreRotuleDixO = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_g_perimetreRotuleDixO->setObjectName("doubleSpinBox_g_perimetreRotuleDixO");
        doubleSpinBox_g_perimetreRotuleDixO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_perimetreRotuleDixO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_perimetreRotuleDixO->setAccelerated(true);
        doubleSpinBox_g_perimetreRotuleDixO->setDecimals(1);
        doubleSpinBox_g_perimetreRotuleDixO->setMaximum(100000.000000000000000);

        gridLayout_perimetres->addWidget(doubleSpinBox_g_perimetreRotuleDixO, 2, 1, 1, 1);

        doubleSpinBox_g_perimetreRotuleDixNO = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_g_perimetreRotuleDixNO->setObjectName("doubleSpinBox_g_perimetreRotuleDixNO");
        doubleSpinBox_g_perimetreRotuleDixNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_perimetreRotuleDixNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_perimetreRotuleDixNO->setAccelerated(true);
        doubleSpinBox_g_perimetreRotuleDixNO->setDecimals(1);
        doubleSpinBox_g_perimetreRotuleDixNO->setMaximum(100000.000000000000000);

        gridLayout_perimetres->addWidget(doubleSpinBox_g_perimetreRotuleDixNO, 2, 2, 1, 1);

        doubleSpinBox_g_perimetreRotuleVingtO = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_g_perimetreRotuleVingtO->setObjectName("doubleSpinBox_g_perimetreRotuleVingtO");
        doubleSpinBox_g_perimetreRotuleVingtO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_perimetreRotuleVingtO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_perimetreRotuleVingtO->setAccelerated(true);
        doubleSpinBox_g_perimetreRotuleVingtO->setDecimals(1);
        doubleSpinBox_g_perimetreRotuleVingtO->setMaximum(100000.000000000000000);

        gridLayout_perimetres->addWidget(doubleSpinBox_g_perimetreRotuleVingtO, 3, 1, 1, 1);

        doubleSpinBox_g_perimetreRotuleVingtNO = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox_g_perimetreRotuleVingtNO->setObjectName("doubleSpinBox_g_perimetreRotuleVingtNO");
        doubleSpinBox_g_perimetreRotuleVingtNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_perimetreRotuleVingtNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_perimetreRotuleVingtNO->setAccelerated(true);
        doubleSpinBox_g_perimetreRotuleVingtNO->setDecimals(1);
        doubleSpinBox_g_perimetreRotuleVingtNO->setMaximum(100000.000000000000000);

        gridLayout_perimetres->addWidget(doubleSpinBox_g_perimetreRotuleVingtNO, 3, 2, 1, 1);

        layoutWidget_5 = new QWidget(widget_genou);
        layoutWidget_5->setObjectName("layoutWidget_5");
        layoutWidget_5->setGeometry(QRect(60, 1770, 239, 75));
        gridLayout_aclRsi = new QGridLayout(layoutWidget_5);
        gridLayout_aclRsi->setSpacing(15);
        gridLayout_aclRsi->setObjectName("gridLayout_aclRsi");
        gridLayout_aclRsi->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_aclRsi->setContentsMargins(0, 0, 0, 0);
        label_kStart = new QLabel(layoutWidget_5);
        label_kStart->setObjectName("label_kStart");

        gridLayout_aclRsi->addWidget(label_kStart, 1, 0, 1, 1);

        label_rsi = new QLabel(layoutWidget_5);
        label_rsi->setObjectName("label_rsi");

        gridLayout_aclRsi->addWidget(label_rsi, 0, 0, 1, 1);

        spinBox_g_kStart = new QSpinBox(layoutWidget_5);
        spinBox_g_kStart->setObjectName("spinBox_g_kStart");
        spinBox_g_kStart->setCursor(QCursor(Qt::ArrowCursor));
        spinBox_g_kStart->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinBox_g_kStart->setAccelerated(true);
        spinBox_g_kStart->setMaximum(100000);

        gridLayout_aclRsi->addWidget(spinBox_g_kStart, 1, 1, 1, 1);

        label_sur_cent = new QLabel(layoutWidget_5);
        label_sur_cent->setObjectName("label_sur_cent");

        gridLayout_aclRsi->addWidget(label_sur_cent, 0, 2, 1, 1);

        spinBox_g_testRSI = new QSpinBox(layoutWidget_5);
        spinBox_g_testRSI->setObjectName("spinBox_g_testRSI");
        spinBox_g_testRSI->setCursor(QCursor(Qt::ArrowCursor));
        spinBox_g_testRSI->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinBox_g_testRSI->setAccelerated(true);
        spinBox_g_testRSI->setMaximum(100000);

        gridLayout_aclRsi->addWidget(spinBox_g_testRSI, 0, 1, 1, 1);

        label_sur_cent_2 = new QLabel(layoutWidget_5);
        label_sur_cent_2->setObjectName("label_sur_cent_2");

        gridLayout_aclRsi->addWidget(label_sur_cent_2, 1, 2, 1, 1);

        layoutWidget_6 = new QWidget(widget_genou);
        layoutWidget_6->setObjectName("layoutWidget_6");
        layoutWidget_6->setGeometry(QRect(40, 10, 333, 110));
        gridLayout_amplitudes = new QGridLayout(layoutWidget_6);
        gridLayout_amplitudes->setSpacing(15);
        gridLayout_amplitudes->setObjectName("gridLayout_amplitudes");
        gridLayout_amplitudes->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_amplitudes->setContentsMargins(0, 0, 0, 0);
        label_amplitude_articulaire = new QLabel(layoutWidget_6);
        label_amplitude_articulaire->setObjectName("label_amplitude_articulaire");
        label_amplitude_articulaire->setTextFormat(Qt::RichText);

        gridLayout_amplitudes->addWidget(label_amplitude_articulaire, 0, 0, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

        label_opere = new QLabel(layoutWidget_6);
        label_opere->setObjectName("label_opere");

        gridLayout_amplitudes->addWidget(label_opere, 0, 1, 1, 1);

        label_non_opere = new QLabel(layoutWidget_6);
        label_non_opere->setObjectName("label_non_opere");

        gridLayout_amplitudes->addWidget(label_non_opere, 0, 2, 1, 1);

        label_flexion = new QLabel(layoutWidget_6);
        label_flexion->setObjectName("label_flexion");

        gridLayout_amplitudes->addWidget(label_flexion, 1, 0, 1, 1);

        label_extension = new QLabel(layoutWidget_6);
        label_extension->setObjectName("label_extension");

        gridLayout_amplitudes->addWidget(label_extension, 2, 0, 1, 1);

        doubleSpinBox_g_flexionO = new QDoubleSpinBox(layoutWidget_6);
        doubleSpinBox_g_flexionO->setObjectName("doubleSpinBox_g_flexionO");
        doubleSpinBox_g_flexionO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_flexionO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_flexionO->setAccelerated(true);
        doubleSpinBox_g_flexionO->setDecimals(1);
        doubleSpinBox_g_flexionO->setMaximum(360.000000000000000);

        gridLayout_amplitudes->addWidget(doubleSpinBox_g_flexionO, 1, 1, 1, 1);

        doubleSpinBox_g_flexionNO = new QDoubleSpinBox(layoutWidget_6);
        doubleSpinBox_g_flexionNO->setObjectName("doubleSpinBox_g_flexionNO");
        doubleSpinBox_g_flexionNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_flexionNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_flexionNO->setAccelerated(true);
        doubleSpinBox_g_flexionNO->setDecimals(1);
        doubleSpinBox_g_flexionNO->setMaximum(360.000000000000000);

        gridLayout_amplitudes->addWidget(doubleSpinBox_g_flexionNO, 1, 2, 1, 1);

        doubleSpinBox_g_extensionO = new QDoubleSpinBox(layoutWidget_6);
        doubleSpinBox_g_extensionO->setObjectName("doubleSpinBox_g_extensionO");
        doubleSpinBox_g_extensionO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_extensionO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_extensionO->setAccelerated(true);
        doubleSpinBox_g_extensionO->setDecimals(1);
        doubleSpinBox_g_extensionO->setMaximum(360.000000000000000);

        gridLayout_amplitudes->addWidget(doubleSpinBox_g_extensionO, 2, 1, 1, 1);

        doubleSpinBox_g_extensionNO = new QDoubleSpinBox(layoutWidget_6);
        doubleSpinBox_g_extensionNO->setObjectName("doubleSpinBox_g_extensionNO");
        doubleSpinBox_g_extensionNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_extensionNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_extensionNO->setAccelerated(true);
        doubleSpinBox_g_extensionNO->setDecimals(1);
        doubleSpinBox_g_extensionNO->setMaximum(360.000000000000000);

        gridLayout_amplitudes->addWidget(doubleSpinBox_g_extensionNO, 2, 2, 1, 1);

        layoutWidget_7 = new QWidget(widget_genou);
        layoutWidget_7->setObjectName("layoutWidget_7");
        layoutWidget_7->setGeometry(QRect(40, 150, 391, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget_7);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_test_accroupissement = new QLabel(layoutWidget_7);
        label_test_accroupissement->setObjectName("label_test_accroupissement");

        horizontalLayout->addWidget(label_test_accroupissement);

        comboBox_g_testAccroupissement = new QComboBox(layoutWidget_7);
        comboBox_g_testAccroupissement->addItem(QString());
        comboBox_g_testAccroupissement->addItem(QString());
        comboBox_g_testAccroupissement->addItem(QString());
        comboBox_g_testAccroupissement->addItem(QString());
        comboBox_g_testAccroupissement->setObjectName("comboBox_g_testAccroupissement");

        horizontalLayout->addWidget(comboBox_g_testAccroupissement);

        layoutWidget_10 = new QWidget(widget_genou);
        layoutWidget_10->setObjectName("layoutWidget_10");
        layoutWidget_10->setGeometry(QRect(500, 220, 420, 110));
        gridLayout_rationAA = new QGridLayout(layoutWidget_10);
        gridLayout_rationAA->setSpacing(15);
        gridLayout_rationAA->setObjectName("gridLayout_rationAA");
        gridLayout_rationAA->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_rationAA->setContentsMargins(0, 0, 0, 0);
        label_fmax_abducteurs = new QLabel(layoutWidget_10);
        label_fmax_abducteurs->setObjectName("label_fmax_abducteurs");

        gridLayout_rationAA->addWidget(label_fmax_abducteurs, 2, 0, 1, 1);

        label_opere_5 = new QLabel(layoutWidget_10);
        label_opere_5->setObjectName("label_opere_5");

        gridLayout_rationAA->addWidget(label_opere_5, 0, 1, 1, 1);

        label_ration_add_abb = new QLabel(layoutWidget_10);
        label_ration_add_abb->setObjectName("label_ration_add_abb");
        label_ration_add_abb->setTextFormat(Qt::RichText);

        gridLayout_rationAA->addWidget(label_ration_add_abb, 0, 0, 1, 1);

        label_non_opere_5 = new QLabel(layoutWidget_10);
        label_non_opere_5->setObjectName("label_non_opere_5");

        gridLayout_rationAA->addWidget(label_non_opere_5, 0, 2, 1, 1);

        label_fmax_adducteurs = new QLabel(layoutWidget_10);
        label_fmax_adducteurs->setObjectName("label_fmax_adducteurs");

        gridLayout_rationAA->addWidget(label_fmax_adducteurs, 1, 0, 1, 1);

        doubleSpinBox_g_fmaxAdducteursO = new QDoubleSpinBox(layoutWidget_10);
        doubleSpinBox_g_fmaxAdducteursO->setObjectName("doubleSpinBox_g_fmaxAdducteursO");
        doubleSpinBox_g_fmaxAdducteursO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_fmaxAdducteursO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_fmaxAdducteursO->setAccelerated(true);
        doubleSpinBox_g_fmaxAdducteursO->setDecimals(1);
        doubleSpinBox_g_fmaxAdducteursO->setMaximum(100000.000000000000000);

        gridLayout_rationAA->addWidget(doubleSpinBox_g_fmaxAdducteursO, 1, 1, 1, 1);

        doubleSpinBox_g_fmaxAdducteursNO = new QDoubleSpinBox(layoutWidget_10);
        doubleSpinBox_g_fmaxAdducteursNO->setObjectName("doubleSpinBox_g_fmaxAdducteursNO");
        doubleSpinBox_g_fmaxAdducteursNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_fmaxAdducteursNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_fmaxAdducteursNO->setAccelerated(true);
        doubleSpinBox_g_fmaxAdducteursNO->setDecimals(1);
        doubleSpinBox_g_fmaxAdducteursNO->setMaximum(100000.000000000000000);

        gridLayout_rationAA->addWidget(doubleSpinBox_g_fmaxAdducteursNO, 1, 2, 1, 1);

        doubleSpinBox_g_fmaxAbducteursO = new QDoubleSpinBox(layoutWidget_10);
        doubleSpinBox_g_fmaxAbducteursO->setObjectName("doubleSpinBox_g_fmaxAbducteursO");
        doubleSpinBox_g_fmaxAbducteursO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_fmaxAbducteursO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_fmaxAbducteursO->setAccelerated(true);
        doubleSpinBox_g_fmaxAbducteursO->setDecimals(1);
        doubleSpinBox_g_fmaxAbducteursO->setMaximum(100000.000000000000000);

        gridLayout_rationAA->addWidget(doubleSpinBox_g_fmaxAbducteursO, 2, 1, 1, 1);

        doubleSpinBox_g_fmaxAbducteursNO = new QDoubleSpinBox(layoutWidget_10);
        doubleSpinBox_g_fmaxAbducteursNO->setObjectName("doubleSpinBox_g_fmaxAbducteursNO");
        doubleSpinBox_g_fmaxAbducteursNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_fmaxAbducteursNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_fmaxAbducteursNO->setAccelerated(true);
        doubleSpinBox_g_fmaxAbducteursNO->setDecimals(1);
        doubleSpinBox_g_fmaxAbducteursNO->setMaximum(100000.000000000000000);

        gridLayout_rationAA->addWidget(doubleSpinBox_g_fmaxAbducteursNO, 2, 2, 1, 1);

        pushButton_valider_bilan = new QPushButton(widget_genou);
        pushButton_valider_bilan->setObjectName("pushButton_valider_bilan");
        pushButton_valider_bilan->setGeometry(QRect(310, 1870, 311, 51));
        layoutWidget_11 = new QWidget(widget_genou);
        layoutWidget_11->setObjectName("layoutWidget_11");
        layoutWidget_11->setGeometry(QRect(50, 930, 317, 198));
        gridLayout_sjB = new QGridLayout(layoutWidget_11);
        gridLayout_sjB->setSpacing(15);
        gridLayout_sjB->setObjectName("gridLayout_sjB");
        gridLayout_sjB->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_sjB->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox_g_rfdmaxNOSj = new QDoubleSpinBox(layoutWidget_11);
        doubleSpinBox_g_rfdmaxNOSj->setObjectName("doubleSpinBox_g_rfdmaxNOSj");
        doubleSpinBox_g_rfdmaxNOSj->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_rfdmaxNOSj->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_rfdmaxNOSj->setAccelerated(true);
        doubleSpinBox_g_rfdmaxNOSj->setDecimals(1);
        doubleSpinBox_g_rfdmaxNOSj->setMaximum(100000.000000000000000);

        gridLayout_sjB->addWidget(doubleSpinBox_g_rfdmaxNOSj, 3, 1, 1, 1);

        label_hauteur_saut_sj = new QLabel(layoutWidget_11);
        label_hauteur_saut_sj->setObjectName("label_hauteur_saut_sj");

        gridLayout_sjB->addWidget(label_hauteur_saut_sj, 1, 0, 1, 1);

        label_test_sjB = new QLabel(layoutWidget_11);
        label_test_sjB->setObjectName("label_test_sjB");
        label_test_sjB->setTextFormat(Qt::RichText);

        gridLayout_sjB->addWidget(label_test_sjB, 0, 0, 1, 1);

        label_fmax_sj = new QLabel(layoutWidget_11);
        label_fmax_sj->setObjectName("label_fmax_sj");

        gridLayout_sjB->addWidget(label_fmax_sj, 2, 0, 1, 1);

        label_pmax_Sj = new QLabel(layoutWidget_11);
        label_pmax_Sj->setObjectName("label_pmax_Sj");

        gridLayout_sjB->addWidget(label_pmax_Sj, 3, 0, 1, 1);

        doubleSpinBox_g_rfdmaxOSj = new QDoubleSpinBox(layoutWidget_11);
        doubleSpinBox_g_rfdmaxOSj->setObjectName("doubleSpinBox_g_rfdmaxOSj");
        doubleSpinBox_g_rfdmaxOSj->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_rfdmaxOSj->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_rfdmaxOSj->setAccelerated(true);
        doubleSpinBox_g_rfdmaxOSj->setDecimals(1);
        doubleSpinBox_g_rfdmaxOSj->setMaximum(100000.000000000000000);

        gridLayout_sjB->addWidget(doubleSpinBox_g_rfdmaxOSj, 2, 1, 1, 1);

        doubleSpinBox_g_hauteurSautSj = new QDoubleSpinBox(layoutWidget_11);
        doubleSpinBox_g_hauteurSautSj->setObjectName("doubleSpinBox_g_hauteurSautSj");
        doubleSpinBox_g_hauteurSautSj->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_hauteurSautSj->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_hauteurSautSj->setAccelerated(true);
        doubleSpinBox_g_hauteurSautSj->setDecimals(1);
        doubleSpinBox_g_hauteurSautSj->setMaximum(100000.000000000000000);

        gridLayout_sjB->addWidget(doubleSpinBox_g_hauteurSautSj, 1, 1, 1, 1);

        layoutWidget_12 = new QWidget(widget_genou);
        layoutWidget_12->setObjectName("layoutWidget_12");
        layoutWidget_12->setGeometry(QRect(40, 220, 457, 110));
        gridLayout_ratioIJ = new QGridLayout(layoutWidget_12);
        gridLayout_ratioIJ->setSpacing(15);
        gridLayout_ratioIJ->setObjectName("gridLayout_ratioIJ");
        gridLayout_ratioIJ->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox_g_fmaxQuadriNO = new QDoubleSpinBox(layoutWidget_12);
        doubleSpinBox_g_fmaxQuadriNO->setObjectName("doubleSpinBox_g_fmaxQuadriNO");
        doubleSpinBox_g_fmaxQuadriNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_fmaxQuadriNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_fmaxQuadriNO->setAccelerated(true);
        doubleSpinBox_g_fmaxQuadriNO->setDecimals(1);
        doubleSpinBox_g_fmaxQuadriNO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ->addWidget(doubleSpinBox_g_fmaxQuadriNO, 2, 2, 1, 1);

        label_non_opere_4 = new QLabel(layoutWidget_12);
        label_non_opere_4->setObjectName("label_non_opere_4");

        gridLayout_ratioIJ->addWidget(label_non_opere_4, 0, 2, 1, 1);

        doubleSpinBox_g_fmaxIschioO = new QDoubleSpinBox(layoutWidget_12);
        doubleSpinBox_g_fmaxIschioO->setObjectName("doubleSpinBox_g_fmaxIschioO");
        doubleSpinBox_g_fmaxIschioO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_fmaxIschioO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_fmaxIschioO->setAccelerated(true);
        doubleSpinBox_g_fmaxIschioO->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_g_fmaxIschioO->setDecimals(1);
        doubleSpinBox_g_fmaxIschioO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ->addWidget(doubleSpinBox_g_fmaxIschioO, 1, 1, 1, 1);

        label_opere_4 = new QLabel(layoutWidget_12);
        label_opere_4->setObjectName("label_opere_4");

        gridLayout_ratioIJ->addWidget(label_opere_4, 0, 1, 1, 1);

        label_ration_ij_quadri = new QLabel(layoutWidget_12);
        label_ration_ij_quadri->setObjectName("label_ration_ij_quadri");
        label_ration_ij_quadri->setTextFormat(Qt::RichText);

        gridLayout_ratioIJ->addWidget(label_ration_ij_quadri, 0, 0, 1, 1);

        label_fmax_ij = new QLabel(layoutWidget_12);
        label_fmax_ij->setObjectName("label_fmax_ij");

        gridLayout_ratioIJ->addWidget(label_fmax_ij, 1, 0, 1, 1);

        doubleSpinBox_g_fmaxIschioNO = new QDoubleSpinBox(layoutWidget_12);
        doubleSpinBox_g_fmaxIschioNO->setObjectName("doubleSpinBox_g_fmaxIschioNO");
        doubleSpinBox_g_fmaxIschioNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_fmaxIschioNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_fmaxIschioNO->setAccelerated(true);
        doubleSpinBox_g_fmaxIschioNO->setDecimals(1);
        doubleSpinBox_g_fmaxIschioNO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ->addWidget(doubleSpinBox_g_fmaxIschioNO, 1, 2, 1, 1);

        label_fmax_quadri = new QLabel(layoutWidget_12);
        label_fmax_quadri->setObjectName("label_fmax_quadri");

        gridLayout_ratioIJ->addWidget(label_fmax_quadri, 2, 0, 1, 1);

        doubleSpinBox_g_fmaxQuadriO = new QDoubleSpinBox(layoutWidget_12);
        doubleSpinBox_g_fmaxQuadriO->setObjectName("doubleSpinBox_g_fmaxQuadriO");
        doubleSpinBox_g_fmaxQuadriO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_fmaxQuadriO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_fmaxQuadriO->setAccelerated(true);
        doubleSpinBox_g_fmaxQuadriO->setDecimals(1);
        doubleSpinBox_g_fmaxQuadriO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ->addWidget(doubleSpinBox_g_fmaxQuadriO, 2, 1, 1, 1);

        line = new QFrame(widget_genou);
        line->setObjectName("line");
        line->setGeometry(QRect(270, 190, 381, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(widget_genou);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(270, 1180, 381, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(widget_genou);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(270, 1460, 381, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(widget_genou);
        line_6->setObjectName("line_6");
        line_6->setGeometry(QRect(250, 1740, 381, 20));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        groupBox_controleGenou_g = new QGroupBox(widget_genou);
        groupBox_controleGenou_g->setObjectName("groupBox_controleGenou_g");
        groupBox_controleGenou_g->setGeometry(QRect(50, 520, 461, 191));
        groupBox_controleGenou_g->setFlat(false);
        groupBox_2 = new QGroupBox(groupBox_controleGenou_g);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 120, 431, 61));
        groupBox_2->setFlat(false);
        radioButton_g_controleGenouValgus = new QRadioButton(groupBox_2);
        radioButton_g_controleGenouValgus->setObjectName("radioButton_g_controleGenouValgus");
        radioButton_g_controleGenouValgus->setGeometry(QRect(10, 30, 301, 24));
        radioButton_g_controleGenouFrontal = new QRadioButton(groupBox_2);
        radioButton_g_controleGenouFrontal->setObjectName("radioButton_g_controleGenouFrontal");
        radioButton_g_controleGenouFrontal->setGeometry(QRect(10, 0, 321, 24));
        radioButton_g_controleGenouFrontal->setChecked(true);
        groupBox = new QGroupBox(groupBox_controleGenou_g);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 30, 431, 71));
        groupBox->setFlat(false);
        radioButton_g_angleFlexionNOK = new QRadioButton(groupBox);
        radioButton_g_angleFlexionNOK->setObjectName("radioButton_g_angleFlexionNOK");
        radioButton_g_angleFlexionNOK->setGeometry(QRect(10, 40, 431, 24));
        radioButton_g_angleFlexionOK = new QRadioButton(groupBox);
        radioButton_g_angleFlexionOK->setObjectName("radioButton_g_angleFlexionOK");
        radioButton_g_angleFlexionOK->setGeometry(QRect(10, 10, 401, 24));
        radioButton_g_angleFlexionOK->setChecked(true);
        groupBox_repartitionCharge_g = new QGroupBox(widget_genou);
        groupBox_repartitionCharge_g->setObjectName("groupBox_repartitionCharge_g");
        groupBox_repartitionCharge_g->setGeometry(QRect(50, 740, 511, 151));
        groupBox_repartitionCharge_g->setFlat(false);
        groupBox_repartitionCharge_g->setCheckable(false);
        checkBox_g_receptionMedioPied = new QCheckBox(groupBox_repartitionCharge_g);
        checkBox_g_receptionMedioPied->setObjectName("checkBox_g_receptionMedioPied");
        checkBox_g_receptionMedioPied->setGeometry(QRect(30, 30, 201, 24));
        checkBox_g_receptionAvantPied = new QCheckBox(groupBox_repartitionCharge_g);
        checkBox_g_receptionAvantPied->setObjectName("checkBox_g_receptionAvantPied");
        checkBox_g_receptionAvantPied->setGeometry(QRect(30, 60, 291, 21));
        checkBox_g_receptionBordInterne = new QCheckBox(groupBox_repartitionCharge_g);
        checkBox_g_receptionBordInterne->setObjectName("checkBox_g_receptionBordInterne");
        checkBox_g_receptionBordInterne->setGeometry(QRect(30, 90, 341, 24));
        checkBox_g_receptionTalon = new QCheckBox(groupBox_repartitionCharge_g);
        checkBox_g_receptionTalon->setObjectName("checkBox_g_receptionTalon");
        checkBox_g_receptionTalon->setGeometry(QRect(30, 120, 321, 24));
        line_11 = new QFrame(widget_genou);
        line_11->setObjectName("line_11");
        line_11->setGeometry(QRect(270, 900, 381, 20));
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);
        groupBox_troncBassin_g = new QGroupBox(widget_genou);
        groupBox_troncBassin_g->setObjectName("groupBox_troncBassin_g");
        groupBox_troncBassin_g->setGeometry(QRect(550, 520, 351, 111));
        groupBox_troncBassin_g->setFlat(false);
        radioButton_g_controleTroncOK = new QRadioButton(groupBox_troncBassin_g);
        radioButton_g_controleTroncOK->setObjectName("radioButton_g_controleTroncOK");
        radioButton_g_controleTroncOK->setGeometry(QRect(20, 30, 301, 24));
        radioButton_g_controleTroncOK->setChecked(true);
        radioButton_g_controleTroncNOK = new QRadioButton(groupBox_troncBassin_g);
        radioButton_g_controleTroncNOK->setObjectName("radioButton_g_controleTroncNOK");
        radioButton_g_controleTroncNOK->setGeometry(QRect(20, 60, 321, 24));
        line_18 = new QFrame(widget_genou);
        line_18->setObjectName("line_18");
        line_18->setGeometry(QRect(270, 340, 381, 20));
        line_18->setFrameShape(QFrame::HLine);
        line_18->setFrameShadow(QFrame::Sunken);
        layoutWidget1 = new QWidget(widget_genou);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(400, 1500, 423, 154));
        gridLayout_3 = new QGridLayout(layoutWidget1);
        gridLayout_3->setSpacing(15);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_test_dj = new QLabel(layoutWidget1);
        label_test_dj->setObjectName("label_test_dj");
        label_test_dj->setTextFormat(Qt::RichText);

        gridLayout_3->addWidget(label_test_dj, 0, 0, 1, 1);

        label_opere_7 = new QLabel(layoutWidget1);
        label_opere_7->setObjectName("label_opere_7");

        gridLayout_3->addWidget(label_opere_7, 0, 1, 1, 1);

        label_non_opere_7 = new QLabel(layoutWidget1);
        label_non_opere_7->setObjectName("label_non_opere_7");

        gridLayout_3->addWidget(label_non_opere_7, 0, 2, 1, 1);

        label_hauteur_saut_dj = new QLabel(layoutWidget1);
        label_hauteur_saut_dj->setObjectName("label_hauteur_saut_dj");

        gridLayout_3->addWidget(label_hauteur_saut_dj, 1, 0, 1, 1);

        doubleSpinBox_g_hauteurSautDjO = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBox_g_hauteurSautDjO->setObjectName("doubleSpinBox_g_hauteurSautDjO");
        doubleSpinBox_g_hauteurSautDjO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_hauteurSautDjO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_hauteurSautDjO->setAccelerated(true);
        doubleSpinBox_g_hauteurSautDjO->setDecimals(1);
        doubleSpinBox_g_hauteurSautDjO->setMaximum(100000.000000000000000);

        gridLayout_3->addWidget(doubleSpinBox_g_hauteurSautDjO, 1, 1, 1, 1);

        doubleSpinBox_g_hauteurSautDjNO = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBox_g_hauteurSautDjNO->setObjectName("doubleSpinBox_g_hauteurSautDjNO");
        doubleSpinBox_g_hauteurSautDjNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_hauteurSautDjNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_hauteurSautDjNO->setAccelerated(true);
        doubleSpinBox_g_hauteurSautDjNO->setDecimals(1);
        doubleSpinBox_g_hauteurSautDjNO->setMaximum(100000.000000000000000);

        gridLayout_3->addWidget(doubleSpinBox_g_hauteurSautDjNO, 1, 2, 1, 1);

        label_rfdmax_dj = new QLabel(layoutWidget1);
        label_rfdmax_dj->setObjectName("label_rfdmax_dj");

        gridLayout_3->addWidget(label_rfdmax_dj, 2, 0, 1, 1);

        doubleSpinBox_g_rfdmaxDjO = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBox_g_rfdmaxDjO->setObjectName("doubleSpinBox_g_rfdmaxDjO");
        doubleSpinBox_g_rfdmaxDjO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_rfdmaxDjO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_rfdmaxDjO->setAccelerated(true);
        doubleSpinBox_g_rfdmaxDjO->setDecimals(1);
        doubleSpinBox_g_rfdmaxDjO->setMaximum(10000000.000000000000000);

        gridLayout_3->addWidget(doubleSpinBox_g_rfdmaxDjO, 2, 1, 1, 1);

        doubleSpinBox_g_rfdmaxDjNO = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBox_g_rfdmaxDjNO->setObjectName("doubleSpinBox_g_rfdmaxDjNO");
        doubleSpinBox_g_rfdmaxDjNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_rfdmaxDjNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_rfdmaxDjNO->setAccelerated(true);
        doubleSpinBox_g_rfdmaxDjNO->setDecimals(1);
        doubleSpinBox_g_rfdmaxDjNO->setMaximum(10000000.000000000000000);

        gridLayout_3->addWidget(doubleSpinBox_g_rfdmaxDjNO, 2, 2, 1, 1);

        label_tps_contact_dj = new QLabel(layoutWidget1);
        label_tps_contact_dj->setObjectName("label_tps_contact_dj");

        gridLayout_3->addWidget(label_tps_contact_dj, 3, 0, 1, 1);

        doubleSpinBox_g_tempsContactDjO = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBox_g_tempsContactDjO->setObjectName("doubleSpinBox_g_tempsContactDjO");
        doubleSpinBox_g_tempsContactDjO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_tempsContactDjO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_tempsContactDjO->setAccelerated(true);
        doubleSpinBox_g_tempsContactDjO->setDecimals(1);
        doubleSpinBox_g_tempsContactDjO->setMaximum(100000.000000000000000);

        gridLayout_3->addWidget(doubleSpinBox_g_tempsContactDjO, 3, 1, 1, 1);

        doubleSpinBox_g_tempsContactDjNO = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBox_g_tempsContactDjNO->setObjectName("doubleSpinBox_g_tempsContactDjNO");
        doubleSpinBox_g_tempsContactDjNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_tempsContactDjNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_tempsContactDjNO->setAccelerated(true);
        doubleSpinBox_g_tempsContactDjNO->setDecimals(1);
        doubleSpinBox_g_tempsContactDjNO->setMaximum(100000.000000000000000);

        gridLayout_3->addWidget(doubleSpinBox_g_tempsContactDjNO, 3, 2, 1, 1);

        layoutWidget2 = new QWidget(widget_genou);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(380, 1240, 355, 66));
        gridLayout_2 = new QGridLayout(layoutWidget2);
        gridLayout_2->setSpacing(15);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_test_cmj = new QLabel(layoutWidget2);
        label_test_cmj->setObjectName("label_test_cmj");
        label_test_cmj->setTextFormat(Qt::RichText);

        gridLayout_2->addWidget(label_test_cmj, 0, 0, 1, 1);

        label_opere_6 = new QLabel(layoutWidget2);
        label_opere_6->setObjectName("label_opere_6");

        gridLayout_2->addWidget(label_opere_6, 0, 1, 1, 1);

        label_non_opere_6 = new QLabel(layoutWidget2);
        label_non_opere_6->setObjectName("label_non_opere_6");

        gridLayout_2->addWidget(label_non_opere_6, 0, 2, 1, 1);

        label_hauteur_saut_cmj = new QLabel(layoutWidget2);
        label_hauteur_saut_cmj->setObjectName("label_hauteur_saut_cmj");

        gridLayout_2->addWidget(label_hauteur_saut_cmj, 1, 0, 1, 1);

        doubleSpinBox_g_hauteurSautCmjO = new QDoubleSpinBox(layoutWidget2);
        doubleSpinBox_g_hauteurSautCmjO->setObjectName("doubleSpinBox_g_hauteurSautCmjO");
        doubleSpinBox_g_hauteurSautCmjO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_hauteurSautCmjO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_hauteurSautCmjO->setAccelerated(true);
        doubleSpinBox_g_hauteurSautCmjO->setDecimals(1);
        doubleSpinBox_g_hauteurSautCmjO->setMaximum(100000.000000000000000);

        gridLayout_2->addWidget(doubleSpinBox_g_hauteurSautCmjO, 1, 1, 1, 1);

        doubleSpinBox_g_hauteurSautCmjNO = new QDoubleSpinBox(layoutWidget2);
        doubleSpinBox_g_hauteurSautCmjNO->setObjectName("doubleSpinBox_g_hauteurSautCmjNO");
        doubleSpinBox_g_hauteurSautCmjNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_hauteurSautCmjNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_hauteurSautCmjNO->setAccelerated(true);
        doubleSpinBox_g_hauteurSautCmjNO->setDecimals(1);
        doubleSpinBox_g_hauteurSautCmjNO->setMaximum(100000.000000000000000);

        gridLayout_2->addWidget(doubleSpinBox_g_hauteurSautCmjNO, 1, 2, 1, 1);

        layoutWidget_22 = new QWidget(widget_genou);
        layoutWidget_22->setObjectName("layoutWidget_22");
        layoutWidget_22->setGeometry(QRect(50, 370, 465, 110));
        gridLayout_ratioIJ_2 = new QGridLayout(layoutWidget_22);
        gridLayout_ratioIJ_2->setSpacing(15);
        gridLayout_ratioIJ_2->setObjectName("gridLayout_ratioIJ_2");
        gridLayout_ratioIJ_2->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox_g_force90McCallNO = new QDoubleSpinBox(layoutWidget_22);
        doubleSpinBox_g_force90McCallNO->setObjectName("doubleSpinBox_g_force90McCallNO");
        doubleSpinBox_g_force90McCallNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_force90McCallNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_force90McCallNO->setAccelerated(true);
        doubleSpinBox_g_force90McCallNO->setDecimals(1);
        doubleSpinBox_g_force90McCallNO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_2->addWidget(doubleSpinBox_g_force90McCallNO, 2, 2, 1, 1);

        label_non_opere_16 = new QLabel(layoutWidget_22);
        label_non_opere_16->setObjectName("label_non_opere_16");

        gridLayout_ratioIJ_2->addWidget(label_non_opere_16, 0, 2, 1, 1);

        doubleSpinBox_g_force30McCallO = new QDoubleSpinBox(layoutWidget_22);
        doubleSpinBox_g_force30McCallO->setObjectName("doubleSpinBox_g_force30McCallO");
        doubleSpinBox_g_force30McCallO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_force30McCallO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_force30McCallO->setAccelerated(true);
        doubleSpinBox_g_force30McCallO->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_g_force30McCallO->setDecimals(1);
        doubleSpinBox_g_force30McCallO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_2->addWidget(doubleSpinBox_g_force30McCallO, 1, 1, 1, 1);

        label_opere_17 = new QLabel(layoutWidget_22);
        label_opere_17->setObjectName("label_opere_17");

        gridLayout_ratioIJ_2->addWidget(label_opere_17, 0, 1, 1, 1);

        label_ration_ij_quadri_2 = new QLabel(layoutWidget_22);
        label_ration_ij_quadri_2->setObjectName("label_ration_ij_quadri_2");
        label_ration_ij_quadri_2->setTextFormat(Qt::RichText);

        gridLayout_ratioIJ_2->addWidget(label_ration_ij_quadri_2, 0, 0, 1, 1);

        label_f30_mccall = new QLabel(layoutWidget_22);
        label_f30_mccall->setObjectName("label_f30_mccall");

        gridLayout_ratioIJ_2->addWidget(label_f30_mccall, 1, 0, 1, 1);

        doubleSpinBox_g_force30McCallNO = new QDoubleSpinBox(layoutWidget_22);
        doubleSpinBox_g_force30McCallNO->setObjectName("doubleSpinBox_g_force30McCallNO");
        doubleSpinBox_g_force30McCallNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_force30McCallNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_force30McCallNO->setAccelerated(true);
        doubleSpinBox_g_force30McCallNO->setDecimals(1);
        doubleSpinBox_g_force30McCallNO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_2->addWidget(doubleSpinBox_g_force30McCallNO, 1, 2, 1, 1);

        label_f90_mccall = new QLabel(layoutWidget_22);
        label_f90_mccall->setObjectName("label_f90_mccall");

        gridLayout_ratioIJ_2->addWidget(label_f90_mccall, 2, 0, 1, 1);

        doubleSpinBox_g_force90McCallO = new QDoubleSpinBox(layoutWidget_22);
        doubleSpinBox_g_force90McCallO->setObjectName("doubleSpinBox_g_force90McCallO");
        doubleSpinBox_g_force90McCallO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_force90McCallO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_force90McCallO->setAccelerated(true);
        doubleSpinBox_g_force90McCallO->setDecimals(1);
        doubleSpinBox_g_force90McCallO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_2->addWidget(doubleSpinBox_g_force90McCallO, 2, 1, 1, 1);

        line_19 = new QFrame(widget_genou);
        line_19->setObjectName("line_19");
        line_19->setGeometry(QRect(330, 490, 381, 20));
        line_19->setFrameShape(QFrame::HLine);
        line_19->setFrameShadow(QFrame::Sunken);
        layoutWidget3 = new QWidget(widget_genou);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(40, 1210, 356, 198));
        gridLayout = new QGridLayout(layoutWidget3);
        gridLayout->setSpacing(15);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_test_cmjB = new QLabel(layoutWidget3);
        label_test_cmjB->setObjectName("label_test_cmjB");
        label_test_cmjB->setTextFormat(Qt::RichText);

        gridLayout->addWidget(label_test_cmjB, 0, 0, 1, 1);

        label_hauteur_saut_cmjB = new QLabel(layoutWidget3);
        label_hauteur_saut_cmjB->setObjectName("label_hauteur_saut_cmjB");

        gridLayout->addWidget(label_hauteur_saut_cmjB, 1, 0, 1, 1);

        doubleSpinBox_g_hauteurSautCmjB = new QDoubleSpinBox(layoutWidget3);
        doubleSpinBox_g_hauteurSautCmjB->setObjectName("doubleSpinBox_g_hauteurSautCmjB");
        doubleSpinBox_g_hauteurSautCmjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_hauteurSautCmjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_hauteurSautCmjB->setAccelerated(true);
        doubleSpinBox_g_hauteurSautCmjB->setDecimals(1);
        doubleSpinBox_g_hauteurSautCmjB->setMaximum(100000.000000000000000);

        gridLayout->addWidget(doubleSpinBox_g_hauteurSautCmjB, 1, 1, 1, 1);

        label_tps_stabilisation_cmj_2 = new QLabel(layoutWidget3);
        label_tps_stabilisation_cmj_2->setObjectName("label_tps_stabilisation_cmj_2");

        gridLayout->addWidget(label_tps_stabilisation_cmj_2, 2, 0, 1, 1);

        doubleSpinBox_g_tempsMvmtCmjB = new QDoubleSpinBox(layoutWidget3);
        doubleSpinBox_g_tempsMvmtCmjB->setObjectName("doubleSpinBox_g_tempsMvmtCmjB");
        doubleSpinBox_g_tempsMvmtCmjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_tempsMvmtCmjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_tempsMvmtCmjB->setAccelerated(true);
        doubleSpinBox_g_tempsMvmtCmjB->setDecimals(1);
        doubleSpinBox_g_tempsMvmtCmjB->setMaximum(100000.000000000000000);

        gridLayout->addWidget(doubleSpinBox_g_tempsMvmtCmjB, 2, 1, 1, 1);

        label_fmax_cmjB = new QLabel(layoutWidget3);
        label_fmax_cmjB->setObjectName("label_fmax_cmjB");

        gridLayout->addWidget(label_fmax_cmjB, 3, 0, 1, 1);

        doubleSpinBox_g_rfdDecelerationOCmjB = new QDoubleSpinBox(layoutWidget3);
        doubleSpinBox_g_rfdDecelerationOCmjB->setObjectName("doubleSpinBox_g_rfdDecelerationOCmjB");
        doubleSpinBox_g_rfdDecelerationOCmjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_rfdDecelerationOCmjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_rfdDecelerationOCmjB->setAccelerated(true);
        doubleSpinBox_g_rfdDecelerationOCmjB->setDecimals(1);
        doubleSpinBox_g_rfdDecelerationOCmjB->setMaximum(100000.000000000000000);

        gridLayout->addWidget(doubleSpinBox_g_rfdDecelerationOCmjB, 3, 1, 1, 1);

        label_RFDdeceleration = new QLabel(layoutWidget3);
        label_RFDdeceleration->setObjectName("label_RFDdeceleration");

        gridLayout->addWidget(label_RFDdeceleration, 4, 0, 1, 1);

        doubleSpinBox_g_rfdDecelerationNOCmjB = new QDoubleSpinBox(layoutWidget3);
        doubleSpinBox_g_rfdDecelerationNOCmjB->setObjectName("doubleSpinBox_g_rfdDecelerationNOCmjB");
        doubleSpinBox_g_rfdDecelerationNOCmjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_rfdDecelerationNOCmjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_rfdDecelerationNOCmjB->setAccelerated(true);
        doubleSpinBox_g_rfdDecelerationNOCmjB->setDecimals(1);
        doubleSpinBox_g_rfdDecelerationNOCmjB->setMaximum(1000000.000000000000000);

        gridLayout->addWidget(doubleSpinBox_g_rfdDecelerationNOCmjB, 4, 1, 1, 1);

        layoutWidget4 = new QWidget(widget_genou);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(40, 1490, 286, 242));
        gridLayout_4 = new QGridLayout(layoutWidget4);
        gridLayout_4->setSpacing(15);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_test_djB = new QLabel(layoutWidget4);
        label_test_djB->setObjectName("label_test_djB");
        label_test_djB->setTextFormat(Qt::RichText);

        gridLayout_4->addWidget(label_test_djB, 0, 0, 1, 2);

        label_hauteur_saut_djB = new QLabel(layoutWidget4);
        label_hauteur_saut_djB->setObjectName("label_hauteur_saut_djB");

        gridLayout_4->addWidget(label_hauteur_saut_djB, 1, 0, 1, 1);

        doubleSpinBox_g_hauteurSautDjB = new QDoubleSpinBox(layoutWidget4);
        doubleSpinBox_g_hauteurSautDjB->setObjectName("doubleSpinBox_g_hauteurSautDjB");
        doubleSpinBox_g_hauteurSautDjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_hauteurSautDjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_hauteurSautDjB->setAccelerated(true);
        doubleSpinBox_g_hauteurSautDjB->setDecimals(1);
        doubleSpinBox_g_hauteurSautDjB->setMaximum(100000.000000000000000);

        gridLayout_4->addWidget(doubleSpinBox_g_hauteurSautDjB, 1, 1, 1, 1);

        label_tps_vol_djB = new QLabel(layoutWidget4);
        label_tps_vol_djB->setObjectName("label_tps_vol_djB");

        gridLayout_4->addWidget(label_tps_vol_djB, 2, 0, 1, 1);

        doubleSpinBox_g_tempsVolDjB = new QDoubleSpinBox(layoutWidget4);
        doubleSpinBox_g_tempsVolDjB->setObjectName("doubleSpinBox_g_tempsVolDjB");
        doubleSpinBox_g_tempsVolDjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_tempsVolDjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_tempsVolDjB->setAccelerated(true);
        doubleSpinBox_g_tempsVolDjB->setDecimals(1);
        doubleSpinBox_g_tempsVolDjB->setMaximum(100000.000000000000000);

        gridLayout_4->addWidget(doubleSpinBox_g_tempsVolDjB, 2, 1, 1, 1);

        label_tps_contact_djB = new QLabel(layoutWidget4);
        label_tps_contact_djB->setObjectName("label_tps_contact_djB");

        gridLayout_4->addWidget(label_tps_contact_djB, 3, 0, 1, 1);

        doubleSpinBox_g_tempsContactDjB = new QDoubleSpinBox(layoutWidget4);
        doubleSpinBox_g_tempsContactDjB->setObjectName("doubleSpinBox_g_tempsContactDjB");
        doubleSpinBox_g_tempsContactDjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_tempsContactDjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_tempsContactDjB->setAccelerated(true);
        doubleSpinBox_g_tempsContactDjB->setDecimals(1);
        doubleSpinBox_g_tempsContactDjB->setMaximum(100000.000000000000000);

        gridLayout_4->addWidget(doubleSpinBox_g_tempsContactDjB, 3, 1, 1, 1);

        label_fmax_djB = new QLabel(layoutWidget4);
        label_fmax_djB->setObjectName("label_fmax_djB");

        gridLayout_4->addWidget(label_fmax_djB, 4, 0, 1, 1);

        doubleSpinBox_g_rfdmaxODjB = new QDoubleSpinBox(layoutWidget4);
        doubleSpinBox_g_rfdmaxODjB->setObjectName("doubleSpinBox_g_rfdmaxODjB");
        doubleSpinBox_g_rfdmaxODjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_rfdmaxODjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_rfdmaxODjB->setAccelerated(true);
        doubleSpinBox_g_rfdmaxODjB->setDecimals(1);
        doubleSpinBox_g_rfdmaxODjB->setMaximum(100000.000000000000000);

        gridLayout_4->addWidget(doubleSpinBox_g_rfdmaxODjB, 4, 1, 1, 1);

        label_rfdmax_djB = new QLabel(layoutWidget4);
        label_rfdmax_djB->setObjectName("label_rfdmax_djB");

        gridLayout_4->addWidget(label_rfdmax_djB, 5, 0, 1, 1);

        doubleSpinBox_g_rfdmaxNODjB = new QDoubleSpinBox(layoutWidget4);
        doubleSpinBox_g_rfdmaxNODjB->setObjectName("doubleSpinBox_g_rfdmaxNODjB");
        doubleSpinBox_g_rfdmaxNODjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_g_rfdmaxNODjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_g_rfdmaxNODjB->setAccelerated(true);
        doubleSpinBox_g_rfdmaxNODjB->setDecimals(1);
        doubleSpinBox_g_rfdmaxNODjB->setMaximum(10000000.000000000000000);

        gridLayout_4->addWidget(doubleSpinBox_g_rfdmaxNODjB, 5, 1, 1, 1);

        widget_generation_rapport_genou = new QWidget(centralwidget);
        widget_generation_rapport_genou->setObjectName("widget_generation_rapport_genou");
        widget_generation_rapport_genou->setGeometry(QRect(30, 2770, 901, 1481));
        textEdit_interpretationKine = new QTextEdit(widget_generation_rapport_genou);
        textEdit_interpretationKine->setObjectName("textEdit_interpretationKine");
        textEdit_interpretationKine->setGeometry(QRect(90, 50, 721, 321));
        textEdit_interpretationKine->setFrameShape(QFrame::Box);
        label_axes = new QLabel(widget_generation_rapport_genou);
        label_axes->setObjectName("label_axes");
        label_axes->setGeometry(QRect(90, 450, 451, 20));
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        label_axes->setFont(font);
        label_axes->setTextFormat(Qt::RichText);
        line_7 = new QFrame(widget_generation_rapport_genou);
        line_7->setObjectName("line_7");
        line_7->setGeometry(QRect(300, 410, 321, 16));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        label_axes_2 = new QLabel(widget_generation_rapport_genou);
        label_axes_2->setObjectName("label_axes_2");
        label_axes_2->setGeometry(QRect(90, 20, 271, 20));
        QFont font1;
        font1.setBold(true);
        label_axes_2->setFont(font1);
        label_axes_2->setTextFormat(Qt::RichText);
        pushButton_validerRapport = new QPushButton(widget_generation_rapport_genou);
        pushButton_validerRapport->setObjectName("pushButton_validerRapport");
        pushButton_validerRapport->setGeometry(QRect(280, 1430, 201, 51));
        line_8 = new QFrame(widget_generation_rapport_genou);
        line_8->setObjectName("line_8");
        line_8->setGeometry(QRect(270, 1280, 321, 16));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        toolButton_g = new QToolButton(widget_generation_rapport_genou);
        toolButton_g->setObjectName("toolButton_g");
        toolButton_g->setGeometry(QRect(570, 1360, 61, 26));
        label_axes_3 = new QLabel(widget_generation_rapport_genou);
        label_axes_3->setObjectName("label_axes_3");
        label_axes_3->setGeometry(QRect(100, 1300, 151, 31));
        label_axes_3->setFont(font);
        label_axes_3->setTextFormat(Qt::RichText);
        lineEdit_g_pathAnnexes = new QLineEdit(widget_generation_rapport_genou);
        lineEdit_g_pathAnnexes->setObjectName("lineEdit_g_pathAnnexes");
        lineEdit_g_pathAnnexes->setGeometry(QRect(170, 1360, 371, 26));
        lineEdit_g_pathAnnexes->setReadOnly(true);
        layoutWidget5 = new QWidget(widget_generation_rapport_genou);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(100, 490, 691, 771));
        verticalLayout_axesAmeliorer = new QVBoxLayout(layoutWidget5);
        verticalLayout_axesAmeliorer->setSpacing(15);
        verticalLayout_axesAmeliorer->setObjectName("verticalLayout_axesAmeliorer");
        verticalLayout_axesAmeliorer->setContentsMargins(0, 0, 0, 0);
        checkBox_g_tricepsSural = new QCheckBox(layoutWidget5);
        checkBox_g_tricepsSural->setObjectName("checkBox_g_tricepsSural");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_tricepsSural);

        checkBox_g_excentriqueQuadri = new QCheckBox(layoutWidget5);
        checkBox_g_excentriqueQuadri->setObjectName("checkBox_g_excentriqueQuadri");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_excentriqueQuadri);

        checkBox_g_concentriqueQuadri = new QCheckBox(layoutWidget5);
        checkBox_g_concentriqueQuadri->setObjectName("checkBox_g_concentriqueQuadri");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_concentriqueQuadri);

        checkBox_g_ij = new QCheckBox(layoutWidget5);
        checkBox_g_ij->setObjectName("checkBox_g_ij");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_ij);

        checkBox_g_renfoStabilisateurs = new QCheckBox(layoutWidget5);
        checkBox_g_renfoStabilisateurs->setObjectName("checkBox_g_renfoStabilisateurs");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_renfoStabilisateurs);

        checkBox_g_intrinseque = new QCheckBox(layoutWidget5);
        checkBox_g_intrinseque->setObjectName("checkBox_g_intrinseque");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_intrinseque);

        checkBox_g_renforcementAdducteurs = new QCheckBox(layoutWidget5);
        checkBox_g_renforcementAdducteurs->setObjectName("checkBox_g_renforcementAdducteurs");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_renforcementAdducteurs);

        checkBox_g_changementDirection = new QCheckBox(layoutWidget5);
        checkBox_g_changementDirection->setObjectName("checkBox_g_changementDirection");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_changementDirection);

        checkBox_g_plioHorizontaleAxe = new QCheckBox(layoutWidget5);
        checkBox_g_plioHorizontaleAxe->setObjectName("checkBox_g_plioHorizontaleAxe");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_plioHorizontaleAxe);

        checkBox_g_plioVerticaleAxe = new QCheckBox(layoutWidget5);
        checkBox_g_plioVerticaleAxe->setObjectName("checkBox_g_plioVerticaleAxe");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_plioVerticaleAxe);

        checkBox_g_plioMulti = new QCheckBox(layoutWidget5);
        checkBox_g_plioMulti->setObjectName("checkBox_g_plioMulti");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_plioMulti);

        checkBox_g_controleGenou = new QCheckBox(layoutWidget5);
        checkBox_g_controleGenou->setObjectName("checkBox_g_controleGenou");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_controleGenou);

        checkBox_g_controleComplexe = new QCheckBox(layoutWidget5);
        checkBox_g_controleComplexe->setObjectName("checkBox_g_controleComplexe");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_controleComplexe);

        checkBox_g_force = new QCheckBox(layoutWidget5);
        checkBox_g_force->setObjectName("checkBox_g_force");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_force);

        checkBox_g_explosivite = new QCheckBox(layoutWidget5);
        checkBox_g_explosivite->setObjectName("checkBox_g_explosivite");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_explosivite);

        checkBox_g_deceleration = new QCheckBox(layoutWidget5);
        checkBox_g_deceleration->setObjectName("checkBox_g_deceleration");

        verticalLayout_axesAmeliorer->addWidget(checkBox_g_deceleration);

        label = new QLabel(widget_generation_rapport_genou);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 370, 611, 20));
        QFont font2;
        font2.setPointSize(8);
        label->setFont(font2);
        pushButton_annulerEditionBilan = new QPushButton(centralwidget);
        pushButton_annulerEditionBilan->setObjectName("pushButton_annulerEditionBilan");
        pushButton_annulerEditionBilan->setGeometry(QRect(560, 140, 181, 31));
        pushButton_annulerEditionRapport = new QPushButton(centralwidget);
        pushButton_annulerEditionRapport->setObjectName("pushButton_annulerEditionRapport");
        pushButton_annulerEditionRapport->setGeometry(QRect(800, 140, 181, 31));
        label_nombreBilan = new QLabel(centralwidget);
        label_nombreBilan->setObjectName("label_nombreBilan");
        label_nombreBilan->setGeometry(QRect(380, 20, 171, 31));
        widget_epaule = new QWidget(centralwidget);
        widget_epaule->setObjectName("widget_epaule");
        widget_epaule->setGeometry(QRect(20, 4290, 921, 1701));
        layoutWidget_13 = new QWidget(widget_epaule);
        layoutWidget_13->setObjectName("layoutWidget_13");
        layoutWidget_13->setGeometry(QRect(30, 380, 540, 30));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_13);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_testApprehension = new QLabel(layoutWidget_13);
        label_testApprehension->setObjectName("label_testApprehension");
        label_testApprehension->setFont(font1);

        horizontalLayout_2->addWidget(label_testApprehension);

        comboBox_e_testInstabiliteA = new QComboBox(layoutWidget_13);
        comboBox_e_testInstabiliteA->addItem(QString());
        comboBox_e_testInstabiliteA->addItem(QString());
        comboBox_e_testInstabiliteA->addItem(QString());
        comboBox_e_testInstabiliteA->addItem(QString());
        comboBox_e_testInstabiliteA->setObjectName("comboBox_e_testInstabiliteA");

        horizontalLayout_2->addWidget(comboBox_e_testInstabiliteA);

        layoutWidget_9 = new QWidget(widget_epaule);
        layoutWidget_9->setObjectName("layoutWidget_9");
        layoutWidget_9->setGeometry(QRect(30, 570, 436, 110));
        gridLayout_RERI1 = new QGridLayout(layoutWidget_9);
        gridLayout_RERI1->setSpacing(15);
        gridLayout_RERI1->setObjectName("gridLayout_RERI1");
        gridLayout_RERI1->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_RERI1->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox_e_fmaxRIR1O = new QDoubleSpinBox(layoutWidget_9);
        doubleSpinBox_e_fmaxRIR1O->setObjectName("doubleSpinBox_e_fmaxRIR1O");
        doubleSpinBox_e_fmaxRIR1O->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxRIR1O->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxRIR1O->setAccelerated(true);
        doubleSpinBox_e_fmaxRIR1O->setDecimals(1);
        doubleSpinBox_e_fmaxRIR1O->setMaximum(100000.000000000000000);

        gridLayout_RERI1->addWidget(doubleSpinBox_e_fmaxRIR1O, 2, 1, 1, 1);

        label_testRotationR1 = new QLabel(layoutWidget_9);
        label_testRotationR1->setObjectName("label_testRotationR1");
        label_testRotationR1->setFont(font1);
        label_testRotationR1->setTextFormat(Qt::RichText);

        gridLayout_RERI1->addWidget(label_testRotationR1, 0, 0, 1, 1);

        label_fmaxRIR1 = new QLabel(layoutWidget_9);
        label_fmaxRIR1->setObjectName("label_fmaxRIR1");

        gridLayout_RERI1->addWidget(label_fmaxRIR1, 2, 0, 1, 1);

        label_opere_10 = new QLabel(layoutWidget_9);
        label_opere_10->setObjectName("label_opere_10");

        gridLayout_RERI1->addWidget(label_opere_10, 0, 1, 1, 1);

        doubleSpinBox_e_fmaxRIR1NO = new QDoubleSpinBox(layoutWidget_9);
        doubleSpinBox_e_fmaxRIR1NO->setObjectName("doubleSpinBox_e_fmaxRIR1NO");
        doubleSpinBox_e_fmaxRIR1NO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxRIR1NO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxRIR1NO->setAccelerated(true);
        doubleSpinBox_e_fmaxRIR1NO->setDecimals(1);
        doubleSpinBox_e_fmaxRIR1NO->setMaximum(100000.000000000000000);

        gridLayout_RERI1->addWidget(doubleSpinBox_e_fmaxRIR1NO, 2, 2, 1, 1);

        doubleSpinBox_e_fmaxRER1O = new QDoubleSpinBox(layoutWidget_9);
        doubleSpinBox_e_fmaxRER1O->setObjectName("doubleSpinBox_e_fmaxRER1O");
        doubleSpinBox_e_fmaxRER1O->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxRER1O->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxRER1O->setAccelerated(true);
        doubleSpinBox_e_fmaxRER1O->setDecimals(1);
        doubleSpinBox_e_fmaxRER1O->setMaximum(100000.000000000000000);

        gridLayout_RERI1->addWidget(doubleSpinBox_e_fmaxRER1O, 1, 1, 1, 1);

        label_fmaxRER1 = new QLabel(layoutWidget_9);
        label_fmaxRER1->setObjectName("label_fmaxRER1");

        gridLayout_RERI1->addWidget(label_fmaxRER1, 1, 0, 1, 1);

        label_non_opere_10 = new QLabel(layoutWidget_9);
        label_non_opere_10->setObjectName("label_non_opere_10");

        gridLayout_RERI1->addWidget(label_non_opere_10, 0, 2, 1, 1);

        doubleSpinBox_e_fmaxRER1NO = new QDoubleSpinBox(layoutWidget_9);
        doubleSpinBox_e_fmaxRER1NO->setObjectName("doubleSpinBox_e_fmaxRER1NO");
        doubleSpinBox_e_fmaxRER1NO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxRER1NO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxRER1NO->setAccelerated(true);
        doubleSpinBox_e_fmaxRER1NO->setDecimals(1);
        doubleSpinBox_e_fmaxRER1NO->setMaximum(100000.000000000000000);

        gridLayout_RERI1->addWidget(doubleSpinBox_e_fmaxRER1NO, 1, 2, 1, 1);

        layoutWidget_14 = new QWidget(widget_epaule);
        layoutWidget_14->setObjectName("layoutWidget_14");
        layoutWidget_14->setGeometry(QRect(480, 570, 436, 110));
        gridLayout_RERI2 = new QGridLayout(layoutWidget_14);
        gridLayout_RERI2->setSpacing(15);
        gridLayout_RERI2->setObjectName("gridLayout_RERI2");
        gridLayout_RERI2->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_RERI2->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox_e_fmaxRIR2O = new QDoubleSpinBox(layoutWidget_14);
        doubleSpinBox_e_fmaxRIR2O->setObjectName("doubleSpinBox_e_fmaxRIR2O");
        doubleSpinBox_e_fmaxRIR2O->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxRIR2O->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxRIR2O->setAccelerated(true);
        doubleSpinBox_e_fmaxRIR2O->setDecimals(1);
        doubleSpinBox_e_fmaxRIR2O->setMaximum(100000.000000000000000);

        gridLayout_RERI2->addWidget(doubleSpinBox_e_fmaxRIR2O, 2, 1, 1, 1);

        label_testRotationR2 = new QLabel(layoutWidget_14);
        label_testRotationR2->setObjectName("label_testRotationR2");
        label_testRotationR2->setFont(font1);
        label_testRotationR2->setTextFormat(Qt::RichText);

        gridLayout_RERI2->addWidget(label_testRotationR2, 0, 0, 1, 1);

        label_fmaxRIR2 = new QLabel(layoutWidget_14);
        label_fmaxRIR2->setObjectName("label_fmaxRIR2");

        gridLayout_RERI2->addWidget(label_fmaxRIR2, 2, 0, 1, 1);

        label_opere_11 = new QLabel(layoutWidget_14);
        label_opere_11->setObjectName("label_opere_11");

        gridLayout_RERI2->addWidget(label_opere_11, 0, 1, 1, 1);

        doubleSpinBox_e_fmaxRIR2NO = new QDoubleSpinBox(layoutWidget_14);
        doubleSpinBox_e_fmaxRIR2NO->setObjectName("doubleSpinBox_e_fmaxRIR2NO");
        doubleSpinBox_e_fmaxRIR2NO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxRIR2NO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxRIR2NO->setAccelerated(true);
        doubleSpinBox_e_fmaxRIR2NO->setDecimals(1);
        doubleSpinBox_e_fmaxRIR2NO->setMaximum(100000.000000000000000);

        gridLayout_RERI2->addWidget(doubleSpinBox_e_fmaxRIR2NO, 2, 2, 1, 1);

        doubleSpinBox_e_fmaxRER2O = new QDoubleSpinBox(layoutWidget_14);
        doubleSpinBox_e_fmaxRER2O->setObjectName("doubleSpinBox_e_fmaxRER2O");
        doubleSpinBox_e_fmaxRER2O->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxRER2O->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxRER2O->setAccelerated(true);
        doubleSpinBox_e_fmaxRER2O->setDecimals(1);
        doubleSpinBox_e_fmaxRER2O->setMaximum(100000.000000000000000);

        gridLayout_RERI2->addWidget(doubleSpinBox_e_fmaxRER2O, 1, 1, 1, 1);

        label_fmaxRER2 = new QLabel(layoutWidget_14);
        label_fmaxRER2->setObjectName("label_fmaxRER2");

        gridLayout_RERI2->addWidget(label_fmaxRER2, 1, 0, 1, 1);

        label_non_opere_11 = new QLabel(layoutWidget_14);
        label_non_opere_11->setObjectName("label_non_opere_11");

        gridLayout_RERI2->addWidget(label_non_opere_11, 0, 2, 1, 1);

        doubleSpinBox_e_fmaxRER2NO = new QDoubleSpinBox(layoutWidget_14);
        doubleSpinBox_e_fmaxRER2NO->setObjectName("doubleSpinBox_e_fmaxRER2NO");
        doubleSpinBox_e_fmaxRER2NO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxRER2NO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxRER2NO->setAccelerated(true);
        doubleSpinBox_e_fmaxRER2NO->setDecimals(1);
        doubleSpinBox_e_fmaxRER2NO->setMaximum(100000.000000000000000);

        gridLayout_RERI2->addWidget(doubleSpinBox_e_fmaxRER2NO, 1, 2, 1, 1);

        layoutWidget_15 = new QWidget(widget_epaule);
        layoutWidget_15->setObjectName("layoutWidget_15");
        layoutWidget_15->setGeometry(QRect(30, 910, 440, 154));
        gridLayout_UqYbt = new QGridLayout(layoutWidget_15);
        gridLayout_UqYbt->setSpacing(15);
        gridLayout_UqYbt->setObjectName("gridLayout_UqYbt");
        gridLayout_UqYbt->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_UqYbt->setContentsMargins(0, 0, 0, 0);
        label_distanceSL = new QLabel(layoutWidget_15);
        label_distanceSL->setObjectName("label_distanceSL");

        gridLayout_UqYbt->addWidget(label_distanceSL, 1, 0, 1, 1);

        doubleSpinBox_e_distanceSLNO = new QDoubleSpinBox(layoutWidget_15);
        doubleSpinBox_e_distanceSLNO->setObjectName("doubleSpinBox_e_distanceSLNO");
        doubleSpinBox_e_distanceSLNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_distanceSLNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_distanceSLNO->setAccelerated(true);
        doubleSpinBox_e_distanceSLNO->setDecimals(1);
        doubleSpinBox_e_distanceSLNO->setMaximum(100000.000000000000000);

        gridLayout_UqYbt->addWidget(doubleSpinBox_e_distanceSLNO, 1, 2, 1, 1);

        label_opere_12 = new QLabel(layoutWidget_15);
        label_opere_12->setObjectName("label_opere_12");

        gridLayout_UqYbt->addWidget(label_opere_12, 0, 1, 1, 1);

        label_distanceM = new QLabel(layoutWidget_15);
        label_distanceM->setObjectName("label_distanceM");

        gridLayout_UqYbt->addWidget(label_distanceM, 3, 0, 1, 1);

        label_distanceIL = new QLabel(layoutWidget_15);
        label_distanceIL->setObjectName("label_distanceIL");

        gridLayout_UqYbt->addWidget(label_distanceIL, 2, 0, 1, 1);

        label_non_opere_12 = new QLabel(layoutWidget_15);
        label_non_opere_12->setObjectName("label_non_opere_12");

        gridLayout_UqYbt->addWidget(label_non_opere_12, 0, 2, 1, 1);

        label_test_uqYbt = new QLabel(layoutWidget_15);
        label_test_uqYbt->setObjectName("label_test_uqYbt");
        label_test_uqYbt->setFont(font1);
        label_test_uqYbt->setTextFormat(Qt::RichText);

        gridLayout_UqYbt->addWidget(label_test_uqYbt, 0, 0, 1, 1);

        doubleSpinBox_e_distanceSLO = new QDoubleSpinBox(layoutWidget_15);
        doubleSpinBox_e_distanceSLO->setObjectName("doubleSpinBox_e_distanceSLO");
        doubleSpinBox_e_distanceSLO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_distanceSLO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_distanceSLO->setAccelerated(true);
        doubleSpinBox_e_distanceSLO->setDecimals(1);
        doubleSpinBox_e_distanceSLO->setMaximum(100000.000000000000000);

        gridLayout_UqYbt->addWidget(doubleSpinBox_e_distanceSLO, 1, 1, 1, 1);

        doubleSpinBox_e_distanceIO = new QDoubleSpinBox(layoutWidget_15);
        doubleSpinBox_e_distanceIO->setObjectName("doubleSpinBox_e_distanceIO");
        doubleSpinBox_e_distanceIO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_distanceIO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_distanceIO->setAccelerated(true);
        doubleSpinBox_e_distanceIO->setDecimals(1);
        doubleSpinBox_e_distanceIO->setMaximum(100000.000000000000000);

        gridLayout_UqYbt->addWidget(doubleSpinBox_e_distanceIO, 2, 1, 1, 1);

        doubleSpinBox_e_distanceINO = new QDoubleSpinBox(layoutWidget_15);
        doubleSpinBox_e_distanceINO->setObjectName("doubleSpinBox_e_distanceINO");
        doubleSpinBox_e_distanceINO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_distanceINO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_distanceINO->setAccelerated(true);
        doubleSpinBox_e_distanceINO->setDecimals(1);
        doubleSpinBox_e_distanceINO->setMaximum(100000.000000000000000);

        gridLayout_UqYbt->addWidget(doubleSpinBox_e_distanceINO, 2, 2, 1, 1);

        doubleSpinBox_e_distanceMO = new QDoubleSpinBox(layoutWidget_15);
        doubleSpinBox_e_distanceMO->setObjectName("doubleSpinBox_e_distanceMO");
        doubleSpinBox_e_distanceMO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_distanceMO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_distanceMO->setAccelerated(true);
        doubleSpinBox_e_distanceMO->setDecimals(1);
        doubleSpinBox_e_distanceMO->setMaximum(100000.000000000000000);

        gridLayout_UqYbt->addWidget(doubleSpinBox_e_distanceMO, 3, 1, 1, 1);

        doubleSpinBox_e_distanceMNO = new QDoubleSpinBox(layoutWidget_15);
        doubleSpinBox_e_distanceMNO->setObjectName("doubleSpinBox_e_distanceMNO");
        doubleSpinBox_e_distanceMNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_distanceMNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_distanceMNO->setAccelerated(true);
        doubleSpinBox_e_distanceMNO->setDecimals(1);
        doubleSpinBox_e_distanceMNO->setMaximum(100000.000000000000000);

        gridLayout_UqYbt->addWidget(doubleSpinBox_e_distanceMNO, 3, 2, 1, 1);

        layoutWidget_3 = new QWidget(widget_epaule);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(30, 1130, 262, 58));
        gridLayout_testCkCuest = new QGridLayout(layoutWidget_3);
        gridLayout_testCkCuest->setObjectName("gridLayout_testCkCuest");
        gridLayout_testCkCuest->setContentsMargins(0, 0, 0, 0);
        label_testCkCuest = new QLabel(layoutWidget_3);
        label_testCkCuest->setObjectName("label_testCkCuest");
        label_testCkCuest->setFont(font1);
        label_testCkCuest->setTextFormat(Qt::RichText);

        gridLayout_testCkCuest->addWidget(label_testCkCuest, 0, 0, 1, 1);

        label_opere_13 = new QLabel(layoutWidget_3);
        label_opere_13->setObjectName("label_opere_13");

        gridLayout_testCkCuest->addWidget(label_opere_13, 0, 1, 1, 1);

        label_nbTouches = new QLabel(layoutWidget_3);
        label_nbTouches->setObjectName("label_nbTouches");

        gridLayout_testCkCuest->addWidget(label_nbTouches, 1, 0, 1, 1);

        doubleSpinBox_e_nbTouches = new QDoubleSpinBox(layoutWidget_3);
        doubleSpinBox_e_nbTouches->setObjectName("doubleSpinBox_e_nbTouches");
        doubleSpinBox_e_nbTouches->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_nbTouches->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_nbTouches->setAccelerated(true);
        doubleSpinBox_e_nbTouches->setDecimals(1);
        doubleSpinBox_e_nbTouches->setMaximum(100000.000000000000000);

        gridLayout_testCkCuest->addWidget(doubleSpinBox_e_nbTouches, 1, 1, 1, 1);

        layoutWidget_16 = new QWidget(widget_epaule);
        layoutWidget_16->setObjectName("layoutWidget_16");
        layoutWidget_16->setGeometry(QRect(30, 1210, 359, 58));
        gridLayout_testSasspt = new QGridLayout(layoutWidget_16);
        gridLayout_testSasspt->setObjectName("gridLayout_testSasspt");
        gridLayout_testSasspt->setContentsMargins(0, 0, 0, 0);
        label_testSasspt = new QLabel(layoutWidget_16);
        label_testSasspt->setObjectName("label_testSasspt");
        label_testSasspt->setFont(font1);
        label_testSasspt->setTextFormat(Qt::RichText);

        gridLayout_testSasspt->addWidget(label_testSasspt, 0, 0, 1, 1);

        label_opere_14 = new QLabel(layoutWidget_16);
        label_opere_14->setObjectName("label_opere_14");

        gridLayout_testSasspt->addWidget(label_opere_14, 0, 1, 1, 1);

        label_non_opere_14 = new QLabel(layoutWidget_16);
        label_non_opere_14->setObjectName("label_non_opere_14");

        gridLayout_testSasspt->addWidget(label_non_opere_14, 0, 2, 1, 1);

        label_distanceLancer = new QLabel(layoutWidget_16);
        label_distanceLancer->setObjectName("label_distanceLancer");

        gridLayout_testSasspt->addWidget(label_distanceLancer, 1, 0, 1, 1);

        doubleSpinBox_e_distanceLanceO = new QDoubleSpinBox(layoutWidget_16);
        doubleSpinBox_e_distanceLanceO->setObjectName("doubleSpinBox_e_distanceLanceO");
        doubleSpinBox_e_distanceLanceO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_distanceLanceO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_distanceLanceO->setAccelerated(true);
        doubleSpinBox_e_distanceLanceO->setDecimals(1);
        doubleSpinBox_e_distanceLanceO->setMaximum(100000.000000000000000);

        gridLayout_testSasspt->addWidget(doubleSpinBox_e_distanceLanceO, 1, 1, 1, 1);

        doubleSpinBox_e_distanceLanceNO = new QDoubleSpinBox(layoutWidget_16);
        doubleSpinBox_e_distanceLanceNO->setObjectName("doubleSpinBox_e_distanceLanceNO");
        doubleSpinBox_e_distanceLanceNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_distanceLanceNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_distanceLanceNO->setAccelerated(true);
        doubleSpinBox_e_distanceLanceNO->setDecimals(1);
        doubleSpinBox_e_distanceLanceNO->setMaximum(100000.000000000000000);

        gridLayout_testSasspt->addWidget(doubleSpinBox_e_distanceLanceNO, 1, 2, 1, 1);

        layoutWidget_17 = new QWidget(widget_epaule);
        layoutWidget_17->setObjectName("layoutWidget_17");
        layoutWidget_17->setGeometry(QRect(30, 1290, 337, 58));
        gridLayout_testUlrt = new QGridLayout(layoutWidget_17);
        gridLayout_testUlrt->setObjectName("gridLayout_testUlrt");
        gridLayout_testUlrt->setContentsMargins(0, 0, 0, 0);
        label_testUlrt = new QLabel(layoutWidget_17);
        label_testUlrt->setObjectName("label_testUlrt");
        label_testUlrt->setFont(font1);
        label_testUlrt->setTextFormat(Qt::RichText);

        gridLayout_testUlrt->addWidget(label_testUlrt, 0, 0, 1, 1);

        label_opere_15 = new QLabel(layoutWidget_17);
        label_opere_15->setObjectName("label_opere_15");

        gridLayout_testUlrt->addWidget(label_opere_15, 0, 1, 1, 1);

        label_non_opere_15 = new QLabel(layoutWidget_17);
        label_non_opere_15->setObjectName("label_non_opere_15");

        gridLayout_testUlrt->addWidget(label_non_opere_15, 0, 2, 1, 1);

        label_nbRepetitions = new QLabel(layoutWidget_17);
        label_nbRepetitions->setObjectName("label_nbRepetitions");

        gridLayout_testUlrt->addWidget(label_nbRepetitions, 1, 0, 1, 1);

        spinBox_e_nbRepetitionsO = new QSpinBox(layoutWidget_17);
        spinBox_e_nbRepetitionsO->setObjectName("spinBox_e_nbRepetitionsO");
        spinBox_e_nbRepetitionsO->setCursor(QCursor(Qt::ArrowCursor));
        spinBox_e_nbRepetitionsO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinBox_e_nbRepetitionsO->setAccelerated(true);

        gridLayout_testUlrt->addWidget(spinBox_e_nbRepetitionsO, 1, 1, 1, 1);

        spinBox_e_nbRepetitionsNO = new QSpinBox(layoutWidget_17);
        spinBox_e_nbRepetitionsNO->setObjectName("spinBox_e_nbRepetitionsNO");
        spinBox_e_nbRepetitionsNO->setCursor(QCursor(Qt::ArrowCursor));
        spinBox_e_nbRepetitionsNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinBox_e_nbRepetitionsNO->setAccelerated(true);

        gridLayout_testUlrt->addWidget(spinBox_e_nbRepetitionsNO, 1, 2, 1, 1);

        line_9 = new QFrame(widget_epaule);
        line_9->setObjectName("line_9");
        line_9->setGeometry(QRect(180, 350, 381, 20));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);
        line_12 = new QFrame(widget_epaule);
        line_12->setObjectName("line_12");
        line_12->setGeometry(QRect(210, 540, 381, 20));
        line_12->setFrameShape(QFrame::HLine);
        line_12->setFrameShadow(QFrame::Sunken);
        line_13 = new QFrame(widget_epaule);
        line_13->setObjectName("line_13");
        line_13->setGeometry(QRect(210, 690, 381, 20));
        line_13->setFrameShape(QFrame::HLine);
        line_13->setFrameShadow(QFrame::Sunken);
        layoutWidget_19 = new QWidget(widget_epaule);
        layoutWidget_19->setObjectName("layoutWidget_19");
        layoutWidget_19->setGeometry(QRect(30, 1550, 231, 75));
        gridLayout_siRsi = new QGridLayout(layoutWidget_19);
        gridLayout_siRsi->setSpacing(15);
        gridLayout_siRsi->setObjectName("gridLayout_siRsi");
        gridLayout_siRsi->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_siRsi->setContentsMargins(0, 0, 0, 0);
        label_kStart_3 = new QLabel(layoutWidget_19);
        label_kStart_3->setObjectName("label_kStart_3");
        label_kStart_3->setFont(font1);

        gridLayout_siRsi->addWidget(label_kStart_3, 1, 0, 1, 1);

        label_siRsi = new QLabel(layoutWidget_19);
        label_siRsi->setObjectName("label_siRsi");
        label_siRsi->setFont(font1);

        gridLayout_siRsi->addWidget(label_siRsi, 0, 0, 1, 1);

        spinBox_e_sStart = new QSpinBox(layoutWidget_19);
        spinBox_e_sStart->setObjectName("spinBox_e_sStart");
        spinBox_e_sStart->setEnabled(false);
        spinBox_e_sStart->setCursor(QCursor(Qt::ArrowCursor));
        spinBox_e_sStart->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinBox_e_sStart->setAccelerated(true);
        spinBox_e_sStart->setMaximum(100000);

        gridLayout_siRsi->addWidget(spinBox_e_sStart, 1, 1, 1, 1);

        label_sur_cent_3 = new QLabel(layoutWidget_19);
        label_sur_cent_3->setObjectName("label_sur_cent_3");

        gridLayout_siRsi->addWidget(label_sur_cent_3, 0, 2, 1, 1);

        spinBox_e_testSIRSI = new QSpinBox(layoutWidget_19);
        spinBox_e_testSIRSI->setObjectName("spinBox_e_testSIRSI");
        spinBox_e_testSIRSI->setCursor(QCursor(Qt::ArrowCursor));
        spinBox_e_testSIRSI->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinBox_e_testSIRSI->setAccelerated(true);
        spinBox_e_testSIRSI->setMaximum(100000);

        gridLayout_siRsi->addWidget(spinBox_e_testSIRSI, 0, 1, 1, 1);

        label_sur_cent_5 = new QLabel(layoutWidget_19);
        label_sur_cent_5->setObjectName("label_sur_cent_5");

        gridLayout_siRsi->addWidget(label_sur_cent_5, 1, 2, 1, 1);

        line_14 = new QFrame(widget_epaule);
        line_14->setObjectName("line_14");
        line_14->setGeometry(QRect(210, 1360, 381, 20));
        line_14->setFrameShape(QFrame::HLine);
        line_14->setFrameShadow(QFrame::Sunken);
        pushButton_valider_bilan_epaule = new QPushButton(widget_epaule);
        pushButton_valider_bilan_epaule->setObjectName("pushButton_valider_bilan_epaule");
        pushButton_valider_bilan_epaule->setGeometry(QRect(270, 1630, 311, 51));
        layoutWidget6 = new QWidget(widget_epaule);
        layoutWidget6->setObjectName("layoutWidget6");
        layoutWidget6->setGeometry(QRect(30, 50, 443, 309));
        gridLayout_amplitudes_epaule = new QGridLayout(layoutWidget6);
        gridLayout_amplitudes_epaule->setObjectName("gridLayout_amplitudes_epaule");
        gridLayout_amplitudes_epaule->setContentsMargins(0, 0, 0, 0);
        label_amplitude_articulaire_2 = new QLabel(layoutWidget6);
        label_amplitude_articulaire_2->setObjectName("label_amplitude_articulaire_2");
        label_amplitude_articulaire_2->setFont(font1);
        label_amplitude_articulaire_2->setTextFormat(Qt::RichText);

        gridLayout_amplitudes_epaule->addWidget(label_amplitude_articulaire_2, 0, 0, 1, 1);

        label_opere_8 = new QLabel(layoutWidget6);
        label_opere_8->setObjectName("label_opere_8");

        gridLayout_amplitudes_epaule->addWidget(label_opere_8, 0, 1, 1, 1);

        label_non_opere_8 = new QLabel(layoutWidget6);
        label_non_opere_8->setObjectName("label_non_opere_8");

        gridLayout_amplitudes_epaule->addWidget(label_non_opere_8, 0, 2, 1, 1);

        label_elevationAnterieure = new QLabel(layoutWidget6);
        label_elevationAnterieure->setObjectName("label_elevationAnterieure");

        gridLayout_amplitudes_epaule->addWidget(label_elevationAnterieure, 1, 0, 1, 1);

        doubleSpinBox_e_elevationAnterieureO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_elevationAnterieureO->setObjectName("doubleSpinBox_e_elevationAnterieureO");
        doubleSpinBox_e_elevationAnterieureO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_elevationAnterieureO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_elevationAnterieureO->setAccelerated(true);
        doubleSpinBox_e_elevationAnterieureO->setDecimals(1);
        doubleSpinBox_e_elevationAnterieureO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_elevationAnterieureO, 1, 1, 1, 1);

        doubleSpinBox_e_elevationAnterieureNO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_elevationAnterieureNO->setObjectName("doubleSpinBox_e_elevationAnterieureNO");
        doubleSpinBox_e_elevationAnterieureNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_elevationAnterieureNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_elevationAnterieureNO->setAccelerated(true);
        doubleSpinBox_e_elevationAnterieureNO->setDecimals(1);
        doubleSpinBox_e_elevationAnterieureNO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_elevationAnterieureNO, 1, 2, 1, 1);

        label_elevationLaterale = new QLabel(layoutWidget6);
        label_elevationLaterale->setObjectName("label_elevationLaterale");

        gridLayout_amplitudes_epaule->addWidget(label_elevationLaterale, 2, 0, 1, 1);

        doubleSpinBox_e_elevationLateraleO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_elevationLateraleO->setObjectName("doubleSpinBox_e_elevationLateraleO");
        doubleSpinBox_e_elevationLateraleO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_elevationLateraleO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_elevationLateraleO->setAccelerated(true);
        doubleSpinBox_e_elevationLateraleO->setDecimals(1);
        doubleSpinBox_e_elevationLateraleO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_elevationLateraleO, 2, 1, 1, 1);

        doubleSpinBox_e_elevationLateraleNO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_elevationLateraleNO->setObjectName("doubleSpinBox_e_elevationLateraleNO");
        doubleSpinBox_e_elevationLateraleNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_elevationLateraleNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_elevationLateraleNO->setAccelerated(true);
        doubleSpinBox_e_elevationLateraleNO->setDecimals(1);
        doubleSpinBox_e_elevationLateraleNO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_elevationLateraleNO, 2, 2, 1, 1);

        label_extensionE = new QLabel(layoutWidget6);
        label_extensionE->setObjectName("label_extensionE");

        gridLayout_amplitudes_epaule->addWidget(label_extensionE, 3, 0, 1, 1);

        doubleSpinBox_e_extensionEO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_extensionEO->setObjectName("doubleSpinBox_e_extensionEO");
        doubleSpinBox_e_extensionEO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_extensionEO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_extensionEO->setAccelerated(true);
        doubleSpinBox_e_extensionEO->setDecimals(1);
        doubleSpinBox_e_extensionEO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_extensionEO, 3, 1, 1, 1);

        doubleSpinBox_e_extensionENO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_extensionENO->setObjectName("doubleSpinBox_e_extensionENO");
        doubleSpinBox_e_extensionENO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_extensionENO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_extensionENO->setAccelerated(true);
        doubleSpinBox_e_extensionENO->setDecimals(1);
        doubleSpinBox_e_extensionENO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_extensionENO, 3, 2, 1, 1);

        label_adductionHorizontale = new QLabel(layoutWidget6);
        label_adductionHorizontale->setObjectName("label_adductionHorizontale");

        gridLayout_amplitudes_epaule->addWidget(label_adductionHorizontale, 4, 0, 1, 1);

        doubleSpinBox_e_adductionHorizontaleO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_adductionHorizontaleO->setObjectName("doubleSpinBox_e_adductionHorizontaleO");
        doubleSpinBox_e_adductionHorizontaleO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_adductionHorizontaleO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_adductionHorizontaleO->setAccelerated(true);
        doubleSpinBox_e_adductionHorizontaleO->setDecimals(1);
        doubleSpinBox_e_adductionHorizontaleO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_adductionHorizontaleO, 4, 1, 1, 1);

        doubleSpinBox_e_adductionHorizontaleNO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_adductionHorizontaleNO->setObjectName("doubleSpinBox_e_adductionHorizontaleNO");
        doubleSpinBox_e_adductionHorizontaleNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_adductionHorizontaleNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_adductionHorizontaleNO->setAccelerated(true);
        doubleSpinBox_e_adductionHorizontaleNO->setDecimals(1);
        doubleSpinBox_e_adductionHorizontaleNO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_adductionHorizontaleNO, 4, 2, 1, 1);

        label_rotationInterneR1 = new QLabel(layoutWidget6);
        label_rotationInterneR1->setObjectName("label_rotationInterneR1");

        gridLayout_amplitudes_epaule->addWidget(label_rotationInterneR1, 5, 0, 1, 1);

        label_rotationExterneR1 = new QLabel(layoutWidget6);
        label_rotationExterneR1->setObjectName("label_rotationExterneR1");

        gridLayout_amplitudes_epaule->addWidget(label_rotationExterneR1, 6, 0, 1, 1);

        doubleSpinBox_e_rotationExterneR1O = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_rotationExterneR1O->setObjectName("doubleSpinBox_e_rotationExterneR1O");
        doubleSpinBox_e_rotationExterneR1O->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_rotationExterneR1O->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_rotationExterneR1O->setAccelerated(true);
        doubleSpinBox_e_rotationExterneR1O->setDecimals(1);
        doubleSpinBox_e_rotationExterneR1O->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_rotationExterneR1O, 6, 1, 1, 1);

        doubleSpinBox_e_rotationExterneR1NO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_rotationExterneR1NO->setObjectName("doubleSpinBox_e_rotationExterneR1NO");
        doubleSpinBox_e_rotationExterneR1NO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_rotationExterneR1NO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_rotationExterneR1NO->setAccelerated(true);
        doubleSpinBox_e_rotationExterneR1NO->setDecimals(1);
        doubleSpinBox_e_rotationExterneR1NO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_rotationExterneR1NO, 6, 2, 1, 1);

        label_rotationInterneR2 = new QLabel(layoutWidget6);
        label_rotationInterneR2->setObjectName("label_rotationInterneR2");

        gridLayout_amplitudes_epaule->addWidget(label_rotationInterneR2, 7, 0, 1, 1);

        doubleSpinBox_e_rotationInterneR2O = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_rotationInterneR2O->setObjectName("doubleSpinBox_e_rotationInterneR2O");
        doubleSpinBox_e_rotationInterneR2O->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_rotationInterneR2O->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_rotationInterneR2O->setAccelerated(true);
        doubleSpinBox_e_rotationInterneR2O->setDecimals(1);
        doubleSpinBox_e_rotationInterneR2O->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_rotationInterneR2O, 7, 1, 1, 1);

        doubleSpinBox_e_rotationInterneR2NO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_rotationInterneR2NO->setObjectName("doubleSpinBox_e_rotationInterneR2NO");
        doubleSpinBox_e_rotationInterneR2NO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_rotationInterneR2NO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_rotationInterneR2NO->setAccelerated(true);
        doubleSpinBox_e_rotationInterneR2NO->setDecimals(1);
        doubleSpinBox_e_rotationInterneR2NO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_rotationInterneR2NO, 7, 2, 1, 1);

        label_rotationExterneR2 = new QLabel(layoutWidget6);
        label_rotationExterneR2->setObjectName("label_rotationExterneR2");

        gridLayout_amplitudes_epaule->addWidget(label_rotationExterneR2, 8, 0, 1, 1);

        doubleSpinBox_e_rotationExterneR2O = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_rotationExterneR2O->setObjectName("doubleSpinBox_e_rotationExterneR2O");
        doubleSpinBox_e_rotationExterneR2O->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_rotationExterneR2O->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_rotationExterneR2O->setAccelerated(true);
        doubleSpinBox_e_rotationExterneR2O->setDecimals(1);
        doubleSpinBox_e_rotationExterneR2O->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_rotationExterneR2O, 8, 1, 1, 1);

        doubleSpinBox_e_rotationExterneR2NO = new QDoubleSpinBox(layoutWidget6);
        doubleSpinBox_e_rotationExterneR2NO->setObjectName("doubleSpinBox_e_rotationExterneR2NO");
        doubleSpinBox_e_rotationExterneR2NO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_rotationExterneR2NO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_rotationExterneR2NO->setAccelerated(true);
        doubleSpinBox_e_rotationExterneR2NO->setDecimals(1);
        doubleSpinBox_e_rotationExterneR2NO->setMaximum(360.000000000000000);

        gridLayout_amplitudes_epaule->addWidget(doubleSpinBox_e_rotationExterneR2NO, 8, 2, 1, 1);

        comboBox_e_rotationInterneR1O = new QComboBox(layoutWidget6);
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->addItem(QString());
        comboBox_e_rotationInterneR1O->setObjectName("comboBox_e_rotationInterneR1O");

        gridLayout_amplitudes_epaule->addWidget(comboBox_e_rotationInterneR1O, 5, 1, 1, 1);

        comboBox_e_rotationInterneR1NO = new QComboBox(layoutWidget6);
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->addItem(QString());
        comboBox_e_rotationInterneR1NO->setObjectName("comboBox_e_rotationInterneR1NO");

        gridLayout_amplitudes_epaule->addWidget(comboBox_e_rotationInterneR1NO, 5, 2, 1, 1);

        layoutWidget7 = new QWidget(widget_epaule);
        layoutWidget7->setObjectName("layoutWidget7");
        layoutWidget7->setGeometry(QRect(30, 470, 297, 58));
        gridLayout_testGrip = new QGridLayout(layoutWidget7);
        gridLayout_testGrip->setObjectName("gridLayout_testGrip");
        gridLayout_testGrip->setContentsMargins(0, 0, 0, 0);
        label_testGrip = new QLabel(layoutWidget7);
        label_testGrip->setObjectName("label_testGrip");
        label_testGrip->setFont(font1);
        label_testGrip->setTextFormat(Qt::RichText);

        gridLayout_testGrip->addWidget(label_testGrip, 0, 0, 1, 1);

        label_opere_9 = new QLabel(layoutWidget7);
        label_opere_9->setObjectName("label_opere_9");

        gridLayout_testGrip->addWidget(label_opere_9, 0, 1, 1, 1);

        label_non_opere_9 = new QLabel(layoutWidget7);
        label_non_opere_9->setObjectName("label_non_opere_9");

        gridLayout_testGrip->addWidget(label_non_opere_9, 0, 2, 1, 1);

        label_elevationAnterieure_2 = new QLabel(layoutWidget7);
        label_elevationAnterieure_2->setObjectName("label_elevationAnterieure_2");

        gridLayout_testGrip->addWidget(label_elevationAnterieure_2, 1, 0, 1, 1);

        doubleSpinBox_e_fmaxGripO = new QDoubleSpinBox(layoutWidget7);
        doubleSpinBox_e_fmaxGripO->setObjectName("doubleSpinBox_e_fmaxGripO");
        doubleSpinBox_e_fmaxGripO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxGripO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxGripO->setAccelerated(true);
        doubleSpinBox_e_fmaxGripO->setDecimals(1);
        doubleSpinBox_e_fmaxGripO->setMaximum(100000.000000000000000);

        gridLayout_testGrip->addWidget(doubleSpinBox_e_fmaxGripO, 1, 1, 1, 1);

        doubleSpinBox_e_fmaxGripNO = new QDoubleSpinBox(layoutWidget7);
        doubleSpinBox_e_fmaxGripNO->setObjectName("doubleSpinBox_e_fmaxGripNO");
        doubleSpinBox_e_fmaxGripNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxGripNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxGripNO->setAccelerated(true);
        doubleSpinBox_e_fmaxGripNO->setDecimals(1);
        doubleSpinBox_e_fmaxGripNO->setMaximum(100000.000000000000000);

        gridLayout_testGrip->addWidget(doubleSpinBox_e_fmaxGripNO, 1, 2, 1, 1);

        label_3 = new QLabel(widget_epaule);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 10, 91, 21));
        comboBox_e_brasOpere = new QComboBox(widget_epaule);
        comboBox_e_brasOpere->addItem(QString());
        comboBox_e_brasOpere->addItem(QString());
        comboBox_e_brasOpere->setObjectName("comboBox_e_brasOpere");
        comboBox_e_brasOpere->setGeometry(QRect(110, 10, 111, 26));
        layoutWidget_20 = new QWidget(widget_epaule);
        layoutWidget_20->setObjectName("layoutWidget_20");
        layoutWidget_20->setGeometry(QRect(30, 1390, 310, 110));
        gridLayout_RERI1_2 = new QGridLayout(layoutWidget_20);
        gridLayout_RERI1_2->setSpacing(15);
        gridLayout_RERI1_2->setObjectName("gridLayout_RERI1_2");
        gridLayout_RERI1_2->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_RERI1_2->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox_e_psetWO = new QDoubleSpinBox(layoutWidget_20);
        doubleSpinBox_e_psetWO->setObjectName("doubleSpinBox_e_psetWO");
        doubleSpinBox_e_psetWO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_psetWO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_psetWO->setAccelerated(true);
        doubleSpinBox_e_psetWO->setDecimals(1);
        doubleSpinBox_e_psetWO->setMaximum(100000.000000000000000);

        gridLayout_RERI1_2->addWidget(doubleSpinBox_e_psetWO, 2, 1, 1, 1);

        label_testRotationR1_2 = new QLabel(layoutWidget_20);
        label_testRotationR1_2->setObjectName("label_testRotationR1_2");
        label_testRotationR1_2->setFont(font1);
        label_testRotationR1_2->setTextFormat(Qt::RichText);

        gridLayout_RERI1_2->addWidget(label_testRotationR1_2, 0, 0, 1, 1);

        label_fmaxRIR1_2 = new QLabel(layoutWidget_20);
        label_fmaxRIR1_2->setObjectName("label_fmaxRIR1_2");

        gridLayout_RERI1_2->addWidget(label_fmaxRIR1_2, 2, 0, 1, 1);

        label_opere_16 = new QLabel(layoutWidget_20);
        label_opere_16->setObjectName("label_opere_16");

        gridLayout_RERI1_2->addWidget(label_opere_16, 0, 1, 1, 1);

        doubleSpinBox_e_psetWNO = new QDoubleSpinBox(layoutWidget_20);
        doubleSpinBox_e_psetWNO->setObjectName("doubleSpinBox_e_psetWNO");
        doubleSpinBox_e_psetWNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_psetWNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_psetWNO->setAccelerated(true);
        doubleSpinBox_e_psetWNO->setDecimals(1);
        doubleSpinBox_e_psetWNO->setMaximum(100000.000000000000000);

        gridLayout_RERI1_2->addWidget(doubleSpinBox_e_psetWNO, 2, 2, 1, 1);

        doubleSpinBox_e_psetYO = new QDoubleSpinBox(layoutWidget_20);
        doubleSpinBox_e_psetYO->setObjectName("doubleSpinBox_e_psetYO");
        doubleSpinBox_e_psetYO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_psetYO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_psetYO->setAccelerated(true);
        doubleSpinBox_e_psetYO->setDecimals(1);
        doubleSpinBox_e_psetYO->setMaximum(100000.000000000000000);

        gridLayout_RERI1_2->addWidget(doubleSpinBox_e_psetYO, 1, 1, 1, 1);

        label_fmaxRER1_2 = new QLabel(layoutWidget_20);
        label_fmaxRER1_2->setObjectName("label_fmaxRER1_2");

        gridLayout_RERI1_2->addWidget(label_fmaxRER1_2, 1, 0, 1, 1);

        label_non_opere_13 = new QLabel(layoutWidget_20);
        label_non_opere_13->setObjectName("label_non_opere_13");

        gridLayout_RERI1_2->addWidget(label_non_opere_13, 0, 2, 1, 1);

        doubleSpinBox_e_psetYNO = new QDoubleSpinBox(layoutWidget_20);
        doubleSpinBox_e_psetYNO->setObjectName("doubleSpinBox_e_psetYNO");
        doubleSpinBox_e_psetYNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_psetYNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_psetYNO->setAccelerated(true);
        doubleSpinBox_e_psetYNO->setDecimals(1);
        doubleSpinBox_e_psetYNO->setMaximum(100000.000000000000000);

        gridLayout_RERI1_2->addWidget(doubleSpinBox_e_psetYNO, 1, 2, 1, 1);

        line_17 = new QFrame(widget_epaule);
        line_17->setObjectName("line_17");
        line_17->setGeometry(QRect(210, 1510, 381, 20));
        line_17->setFrameShape(QFrame::HLine);
        line_17->setFrameShadow(QFrame::Sunken);
        layoutWidget_21 = new QWidget(widget_epaule);
        layoutWidget_21->setObjectName("layoutWidget_21");
        layoutWidget_21->setGeometry(QRect(30, 420, 548, 30));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_21);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_testApprehension_2 = new QLabel(layoutWidget_21);
        label_testApprehension_2->setObjectName("label_testApprehension_2");
        label_testApprehension_2->setFont(font1);

        horizontalLayout_3->addWidget(label_testApprehension_2);

        comboBox_e_testInstabiliteP = new QComboBox(layoutWidget_21);
        comboBox_e_testInstabiliteP->addItem(QString());
        comboBox_e_testInstabiliteP->addItem(QString());
        comboBox_e_testInstabiliteP->addItem(QString());
        comboBox_e_testInstabiliteP->addItem(QString());
        comboBox_e_testInstabiliteP->setObjectName("comboBox_e_testInstabiliteP");

        horizontalLayout_3->addWidget(comboBox_e_testInstabiliteP);

        textEdit_schemaYBT = new QTextEdit(widget_epaule);
        textEdit_schemaYBT->setObjectName("textEdit_schemaYBT");
        textEdit_schemaYBT->setGeometry(QRect(500, 880, 351, 181));
        textEdit_schemaYBT->setFrameShape(QFrame::NoFrame);
        textEdit_schemaYBT->setReadOnly(true);
        label_4 = new QLabel(widget_epaule);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(290, 10, 131, 21));
        comboBox_e_mainDominante = new QComboBox(widget_epaule);
        comboBox_e_mainDominante->addItem(QString());
        comboBox_e_mainDominante->addItem(QString());
        comboBox_e_mainDominante->addItem(QString());
        comboBox_e_mainDominante->setObjectName("comboBox_e_mainDominante");
        comboBox_e_mainDominante->setGeometry(QRect(420, 10, 111, 26));
        layoutWidget8 = new QWidget(widget_epaule);
        layoutWidget8->setObjectName("layoutWidget8");
        layoutWidget8->setGeometry(QRect(30, 1080, 552, 31));
        formLayout = new QFormLayout(layoutWidget8);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_distanceM_2 = new QLabel(layoutWidget8);
        label_distanceM_2->setObjectName("label_distanceM_2");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_distanceM_2);

        doubleSpinBox_e_longueurBras = new QDoubleSpinBox(layoutWidget8);
        doubleSpinBox_e_longueurBras->setObjectName("doubleSpinBox_e_longueurBras");
        doubleSpinBox_e_longueurBras->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_longueurBras->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_longueurBras->setAccelerated(true);
        doubleSpinBox_e_longueurBras->setDecimals(1);
        doubleSpinBox_e_longueurBras->setMaximum(100000.000000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, doubleSpinBox_e_longueurBras);

        line_20 = new QFrame(widget_epaule);
        line_20->setObjectName("line_20");
        line_20->setGeometry(QRect(210, 850, 381, 20));
        line_20->setFrameShape(QFrame::HLine);
        line_20->setFrameShadow(QFrame::Sunken);
        layoutWidget9 = new QWidget(widget_epaule);
        layoutWidget9->setObjectName("layoutWidget9");
        layoutWidget9->setGeometry(QRect(40, 723, 349, 154));
        gridLayout_5 = new QGridLayout(layoutWidget9);
        gridLayout_5->setSpacing(15);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_testRotationR1_3 = new QLabel(layoutWidget9);
        label_testRotationR1_3->setObjectName("label_testRotationR1_3");
        label_testRotationR1_3->setFont(font1);
        label_testRotationR1_3->setTextFormat(Qt::RichText);

        gridLayout_5->addWidget(label_testRotationR1_3, 0, 0, 1, 1);

        label_opere_18 = new QLabel(layoutWidget9);
        label_opere_18->setObjectName("label_opere_18");

        gridLayout_5->addWidget(label_opere_18, 0, 1, 1, 1);

        label_non_opere_17 = new QLabel(layoutWidget9);
        label_non_opere_17->setObjectName("label_non_opere_17");

        gridLayout_5->addWidget(label_non_opere_17, 0, 2, 1, 1);

        label_fmaxRER1_3 = new QLabel(layoutWidget9);
        label_fmaxRER1_3->setObjectName("label_fmaxRER1_3");

        gridLayout_5->addWidget(label_fmaxRER1_3, 1, 0, 1, 1);

        doubleSpinBox_e_fmaxIO = new QDoubleSpinBox(layoutWidget9);
        doubleSpinBox_e_fmaxIO->setObjectName("doubleSpinBox_e_fmaxIO");
        doubleSpinBox_e_fmaxIO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxIO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxIO->setAccelerated(true);
        doubleSpinBox_e_fmaxIO->setDecimals(1);
        doubleSpinBox_e_fmaxIO->setMaximum(100000.000000000000000);

        gridLayout_5->addWidget(doubleSpinBox_e_fmaxIO, 1, 1, 1, 1);

        doubleSpinBox_e_fmaxINO = new QDoubleSpinBox(layoutWidget9);
        doubleSpinBox_e_fmaxINO->setObjectName("doubleSpinBox_e_fmaxINO");
        doubleSpinBox_e_fmaxINO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxINO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxINO->setAccelerated(true);
        doubleSpinBox_e_fmaxINO->setDecimals(1);
        doubleSpinBox_e_fmaxINO->setMaximum(100000.000000000000000);

        gridLayout_5->addWidget(doubleSpinBox_e_fmaxINO, 1, 2, 1, 1);

        label_fmaxRIR1_3 = new QLabel(layoutWidget9);
        label_fmaxRIR1_3->setObjectName("label_fmaxRIR1_3");

        gridLayout_5->addWidget(label_fmaxRIR1_3, 2, 0, 1, 1);

        doubleSpinBox_e_fmaxYO = new QDoubleSpinBox(layoutWidget9);
        doubleSpinBox_e_fmaxYO->setObjectName("doubleSpinBox_e_fmaxYO");
        doubleSpinBox_e_fmaxYO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxYO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxYO->setAccelerated(true);
        doubleSpinBox_e_fmaxYO->setDecimals(1);
        doubleSpinBox_e_fmaxYO->setMaximum(100000.000000000000000);

        gridLayout_5->addWidget(doubleSpinBox_e_fmaxYO, 2, 1, 1, 1);

        doubleSpinBox_e_fmaxYNO = new QDoubleSpinBox(layoutWidget9);
        doubleSpinBox_e_fmaxYNO->setObjectName("doubleSpinBox_e_fmaxYNO");
        doubleSpinBox_e_fmaxYNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxYNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxYNO->setAccelerated(true);
        doubleSpinBox_e_fmaxYNO->setDecimals(1);
        doubleSpinBox_e_fmaxYNO->setMaximum(100000.000000000000000);

        gridLayout_5->addWidget(doubleSpinBox_e_fmaxYNO, 2, 2, 1, 1);

        label_fmaxRIR1_4 = new QLabel(layoutWidget9);
        label_fmaxRIR1_4->setObjectName("label_fmaxRIR1_4");

        gridLayout_5->addWidget(label_fmaxRIR1_4, 3, 0, 1, 1);

        doubleSpinBox_e_fmaxTO = new QDoubleSpinBox(layoutWidget9);
        doubleSpinBox_e_fmaxTO->setObjectName("doubleSpinBox_e_fmaxTO");
        doubleSpinBox_e_fmaxTO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxTO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxTO->setAccelerated(true);
        doubleSpinBox_e_fmaxTO->setDecimals(1);
        doubleSpinBox_e_fmaxTO->setMaximum(100000.000000000000000);

        gridLayout_5->addWidget(doubleSpinBox_e_fmaxTO, 3, 1, 1, 1);

        doubleSpinBox_e_fmaxTNO = new QDoubleSpinBox(layoutWidget9);
        doubleSpinBox_e_fmaxTNO->setObjectName("doubleSpinBox_e_fmaxTNO");
        doubleSpinBox_e_fmaxTNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_e_fmaxTNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_e_fmaxTNO->setAccelerated(true);
        doubleSpinBox_e_fmaxTNO->setDecimals(1);
        doubleSpinBox_e_fmaxTNO->setMaximum(100000.000000000000000);

        gridLayout_5->addWidget(doubleSpinBox_e_fmaxTNO, 3, 2, 1, 1);

        widget_generation_rapport_epaule = new QWidget(centralwidget);
        widget_generation_rapport_epaule->setObjectName("widget_generation_rapport_epaule");
        widget_generation_rapport_epaule->setGeometry(QRect(20, 6320, 911, 1371));
        textEdit_interpretationKine_2 = new QTextEdit(widget_generation_rapport_epaule);
        textEdit_interpretationKine_2->setObjectName("textEdit_interpretationKine_2");
        textEdit_interpretationKine_2->setGeometry(QRect(90, 50, 721, 321));
        textEdit_interpretationKine_2->setFrameShape(QFrame::Box);
        label_axes_4 = new QLabel(widget_generation_rapport_epaule);
        label_axes_4->setObjectName("label_axes_4");
        label_axes_4->setGeometry(QRect(90, 450, 451, 20));
        label_axes_4->setFont(font);
        label_axes_4->setTextFormat(Qt::RichText);
        line_15 = new QFrame(widget_generation_rapport_epaule);
        line_15->setObjectName("line_15");
        line_15->setGeometry(QRect(300, 410, 321, 16));
        line_15->setFrameShape(QFrame::HLine);
        line_15->setFrameShadow(QFrame::Sunken);
        label_axes_5 = new QLabel(widget_generation_rapport_epaule);
        label_axes_5->setObjectName("label_axes_5");
        label_axes_5->setGeometry(QRect(90, 20, 271, 20));
        label_axes_5->setFont(font1);
        label_axes_5->setTextFormat(Qt::RichText);
        pushButton_validerRapport_epaule = new QPushButton(widget_generation_rapport_epaule);
        pushButton_validerRapport_epaule->setObjectName("pushButton_validerRapport_epaule");
        pushButton_validerRapport_epaule->setGeometry(QRect(280, 1310, 201, 51));
        line_16 = new QFrame(widget_generation_rapport_epaule);
        line_16->setObjectName("line_16");
        line_16->setGeometry(QRect(270, 1160, 321, 16));
        line_16->setFrameShape(QFrame::HLine);
        line_16->setFrameShadow(QFrame::Sunken);
        toolButton_e = new QToolButton(widget_generation_rapport_epaule);
        toolButton_e->setObjectName("toolButton_e");
        toolButton_e->setGeometry(QRect(570, 1240, 61, 26));
        label_axes_6 = new QLabel(widget_generation_rapport_epaule);
        label_axes_6->setObjectName("label_axes_6");
        label_axes_6->setGeometry(QRect(100, 1180, 151, 31));
        label_axes_6->setFont(font);
        label_axes_6->setTextFormat(Qt::RichText);
        lineEdit_e_pathAnnexes = new QLineEdit(widget_generation_rapport_epaule);
        lineEdit_e_pathAnnexes->setObjectName("lineEdit_e_pathAnnexes");
        lineEdit_e_pathAnnexes->setGeometry(QRect(170, 1240, 371, 26));
        lineEdit_e_pathAnnexes->setReadOnly(true);
        layoutWidget_18 = new QWidget(widget_generation_rapport_epaule);
        layoutWidget_18->setObjectName("layoutWidget_18");
        layoutWidget_18->setGeometry(QRect(100, 490, 691, 650));
        verticalLayout_axesAmeliorer_2 = new QVBoxLayout(layoutWidget_18);
        verticalLayout_axesAmeliorer_2->setSpacing(15);
        verticalLayout_axesAmeliorer_2->setObjectName("verticalLayout_axesAmeliorer_2");
        verticalLayout_axesAmeliorer_2->setContentsMargins(0, 0, 0, 0);
        checkBox_e_AugmenterAmplitudes = new QCheckBox(layoutWidget_18);
        checkBox_e_AugmenterAmplitudes->setObjectName("checkBox_e_AugmenterAmplitudes");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_AugmenterAmplitudes);

        checkBox_e_renfoExternes = new QCheckBox(layoutWidget_18);
        checkBox_e_renfoExternes->setObjectName("checkBox_e_renfoExternes");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_renfoExternes);

        checkBox_e_renfoInternes = new QCheckBox(layoutWidget_18);
        checkBox_e_renfoInternes->setObjectName("checkBox_e_renfoInternes");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_renfoInternes);

        checkBox_e_renfoTrapeze = new QCheckBox(layoutWidget_18);
        checkBox_e_renfoTrapeze->setObjectName("checkBox_e_renfoTrapeze");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_renfoTrapeze);

        checkBox_e_renfoDentele = new QCheckBox(layoutWidget_18);
        checkBox_e_renfoDentele->setObjectName("checkBox_e_renfoDentele");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_renfoDentele);

        checkBox_e_forceGrip = new QCheckBox(layoutWidget_18);
        checkBox_e_forceGrip->setObjectName("checkBox_e_forceGrip");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_forceGrip);

        checkBox_e_pousseeHorizontale = new QCheckBox(layoutWidget_18);
        checkBox_e_pousseeHorizontale->setObjectName("checkBox_e_pousseeHorizontale");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_pousseeHorizontale);

        checkBox_e_coiffeFixateur = new QCheckBox(layoutWidget_18);
        checkBox_e_coiffeFixateur->setObjectName("checkBox_e_coiffeFixateur");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_coiffeFixateur);

        checkBox_e_controleArme = new QCheckBox(layoutWidget_18);
        checkBox_e_controleArme->setObjectName("checkBox_e_controleArme");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_controleArme);

        checkBox_e_controleOverhead = new QCheckBox(layoutWidget_18);
        checkBox_e_controleOverhead->setObjectName("checkBox_e_controleOverhead");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_controleOverhead);

        checkBox_e_explosivite = new QCheckBox(layoutWidget_18);
        checkBox_e_explosivite->setObjectName("checkBox_e_explosivite");

        verticalLayout_axesAmeliorer_2->addWidget(checkBox_e_explosivite);

        label_2 = new QLabel(widget_generation_rapport_epaule);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(100, 370, 611, 20));
        label_2->setFont(font2);
        pushButton_modifier_bilan = new QPushButton(centralwidget);
        pushButton_modifier_bilan->setObjectName("pushButton_modifier_bilan");
        pushButton_modifier_bilan->setGeometry(QRect(350, 100, 191, 29));
        widget_hanche = new QWidget(centralwidget);
        widget_hanche->setObjectName("widget_hanche");
        widget_hanche->setGeometry(QRect(20, 7720, 921, 1921));
        layoutWidget_2 = new QWidget(widget_hanche);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(540, 10, 350, 154));
        gridLayout_perimetres_2 = new QGridLayout(layoutWidget_2);
        gridLayout_perimetres_2->setSpacing(15);
        gridLayout_perimetres_2->setObjectName("gridLayout_perimetres_2");
        gridLayout_perimetres_2->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_perimetres_2->setContentsMargins(0, 0, 0, 0);
        label_perimetre_2 = new QLabel(layoutWidget_2);
        label_perimetre_2->setObjectName("label_perimetre_2");
        label_perimetre_2->setTextFormat(Qt::RichText);

        gridLayout_perimetres_2->addWidget(label_perimetre_2, 0, 0, 1, 1);

        label_opere_19 = new QLabel(layoutWidget_2);
        label_opere_19->setObjectName("label_opere_19");

        gridLayout_perimetres_2->addWidget(label_opere_19, 0, 1, 1, 1);

        label_non_opere_18 = new QLabel(layoutWidget_2);
        label_non_opere_18->setObjectName("label_non_opere_18");

        gridLayout_perimetres_2->addWidget(label_non_opere_18, 0, 2, 1, 1);

        label_mollet_2 = new QLabel(layoutWidget_2);
        label_mollet_2->setObjectName("label_mollet_2");

        gridLayout_perimetres_2->addWidget(label_mollet_2, 1, 0, 1, 1);

        label_sommet_rotule_dix_2 = new QLabel(layoutWidget_2);
        label_sommet_rotule_dix_2->setObjectName("label_sommet_rotule_dix_2");

        gridLayout_perimetres_2->addWidget(label_sommet_rotule_dix_2, 2, 0, 1, 1);

        label_sommet_rotule_vingt_2 = new QLabel(layoutWidget_2);
        label_sommet_rotule_vingt_2->setObjectName("label_sommet_rotule_vingt_2");

        gridLayout_perimetres_2->addWidget(label_sommet_rotule_vingt_2, 3, 0, 1, 1);

        doubleSpinBox_h_perimetreMolletNO = new QDoubleSpinBox(layoutWidget_2);
        doubleSpinBox_h_perimetreMolletNO->setObjectName("doubleSpinBox_h_perimetreMolletNO");
        doubleSpinBox_h_perimetreMolletNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_perimetreMolletNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_perimetreMolletNO->setAccelerated(true);
        doubleSpinBox_h_perimetreMolletNO->setDecimals(1);
        doubleSpinBox_h_perimetreMolletNO->setMaximum(100000.000000000000000);

        gridLayout_perimetres_2->addWidget(doubleSpinBox_h_perimetreMolletNO, 1, 2, 1, 1);

        doubleSpinBox_h_perimetreMolletO = new QDoubleSpinBox(layoutWidget_2);
        doubleSpinBox_h_perimetreMolletO->setObjectName("doubleSpinBox_h_perimetreMolletO");
        doubleSpinBox_h_perimetreMolletO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_perimetreMolletO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_perimetreMolletO->setAccelerated(true);
        doubleSpinBox_h_perimetreMolletO->setDecimals(1);
        doubleSpinBox_h_perimetreMolletO->setMaximum(100000.000000000000000);

        gridLayout_perimetres_2->addWidget(doubleSpinBox_h_perimetreMolletO, 1, 1, 1, 1);

        doubleSpinBox_h_perimetreRotuleDixO = new QDoubleSpinBox(layoutWidget_2);
        doubleSpinBox_h_perimetreRotuleDixO->setObjectName("doubleSpinBox_h_perimetreRotuleDixO");
        doubleSpinBox_h_perimetreRotuleDixO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_perimetreRotuleDixO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_perimetreRotuleDixO->setAccelerated(true);
        doubleSpinBox_h_perimetreRotuleDixO->setDecimals(1);
        doubleSpinBox_h_perimetreRotuleDixO->setMaximum(100000.000000000000000);

        gridLayout_perimetres_2->addWidget(doubleSpinBox_h_perimetreRotuleDixO, 2, 1, 1, 1);

        doubleSpinBox_h_perimetreRotuleDixNO = new QDoubleSpinBox(layoutWidget_2);
        doubleSpinBox_h_perimetreRotuleDixNO->setObjectName("doubleSpinBox_h_perimetreRotuleDixNO");
        doubleSpinBox_h_perimetreRotuleDixNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_perimetreRotuleDixNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_perimetreRotuleDixNO->setAccelerated(true);
        doubleSpinBox_h_perimetreRotuleDixNO->setDecimals(1);
        doubleSpinBox_h_perimetreRotuleDixNO->setMaximum(100000.000000000000000);

        gridLayout_perimetres_2->addWidget(doubleSpinBox_h_perimetreRotuleDixNO, 2, 2, 1, 1);

        doubleSpinBox_h_perimetreRotuleVingtO = new QDoubleSpinBox(layoutWidget_2);
        doubleSpinBox_h_perimetreRotuleVingtO->setObjectName("doubleSpinBox_h_perimetreRotuleVingtO");
        doubleSpinBox_h_perimetreRotuleVingtO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_perimetreRotuleVingtO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_perimetreRotuleVingtO->setAccelerated(true);
        doubleSpinBox_h_perimetreRotuleVingtO->setDecimals(1);
        doubleSpinBox_h_perimetreRotuleVingtO->setMaximum(100000.000000000000000);

        gridLayout_perimetres_2->addWidget(doubleSpinBox_h_perimetreRotuleVingtO, 3, 1, 1, 1);

        doubleSpinBox_h_perimetreRotuleVingtNO = new QDoubleSpinBox(layoutWidget_2);
        doubleSpinBox_h_perimetreRotuleVingtNO->setObjectName("doubleSpinBox_h_perimetreRotuleVingtNO");
        doubleSpinBox_h_perimetreRotuleVingtNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_perimetreRotuleVingtNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_perimetreRotuleVingtNO->setAccelerated(true);
        doubleSpinBox_h_perimetreRotuleVingtNO->setDecimals(1);
        doubleSpinBox_h_perimetreRotuleVingtNO->setMaximum(100000.000000000000000);

        gridLayout_perimetres_2->addWidget(doubleSpinBox_h_perimetreRotuleVingtNO, 3, 2, 1, 1);

        layoutWidget_24 = new QWidget(widget_hanche);
        layoutWidget_24->setObjectName("layoutWidget_24");
        layoutWidget_24->setGeometry(QRect(40, 350, 391, 30));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_24);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_test_accroupissement_2 = new QLabel(layoutWidget_24);
        label_test_accroupissement_2->setObjectName("label_test_accroupissement_2");

        horizontalLayout_4->addWidget(label_test_accroupissement_2);

        comboBox_h_testAccroupissement = new QComboBox(layoutWidget_24);
        comboBox_h_testAccroupissement->addItem(QString());
        comboBox_h_testAccroupissement->addItem(QString());
        comboBox_h_testAccroupissement->addItem(QString());
        comboBox_h_testAccroupissement->addItem(QString());
        comboBox_h_testAccroupissement->setObjectName("comboBox_h_testAccroupissement");

        horizontalLayout_4->addWidget(comboBox_h_testAccroupissement);

        layoutWidget_25 = new QWidget(widget_hanche);
        layoutWidget_25->setObjectName("layoutWidget_25");
        layoutWidget_25->setGeometry(QRect(500, 410, 420, 110));
        gridLayout_rationAA_2 = new QGridLayout(layoutWidget_25);
        gridLayout_rationAA_2->setSpacing(15);
        gridLayout_rationAA_2->setObjectName("gridLayout_rationAA_2");
        gridLayout_rationAA_2->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_rationAA_2->setContentsMargins(0, 0, 0, 0);
        label_fmax_abducteurs_2 = new QLabel(layoutWidget_25);
        label_fmax_abducteurs_2->setObjectName("label_fmax_abducteurs_2");

        gridLayout_rationAA_2->addWidget(label_fmax_abducteurs_2, 2, 0, 1, 1);

        label_opere_20 = new QLabel(layoutWidget_25);
        label_opere_20->setObjectName("label_opere_20");

        gridLayout_rationAA_2->addWidget(label_opere_20, 0, 1, 1, 1);

        label_ration_add_abb_2 = new QLabel(layoutWidget_25);
        label_ration_add_abb_2->setObjectName("label_ration_add_abb_2");
        label_ration_add_abb_2->setTextFormat(Qt::RichText);

        gridLayout_rationAA_2->addWidget(label_ration_add_abb_2, 0, 0, 1, 1);

        label_non_opere_19 = new QLabel(layoutWidget_25);
        label_non_opere_19->setObjectName("label_non_opere_19");

        gridLayout_rationAA_2->addWidget(label_non_opere_19, 0, 2, 1, 1);

        label_fmax_adducteurs_2 = new QLabel(layoutWidget_25);
        label_fmax_adducteurs_2->setObjectName("label_fmax_adducteurs_2");

        gridLayout_rationAA_2->addWidget(label_fmax_adducteurs_2, 1, 0, 1, 1);

        doubleSpinBox_h_fmaxAdducteursO = new QDoubleSpinBox(layoutWidget_25);
        doubleSpinBox_h_fmaxAdducteursO->setObjectName("doubleSpinBox_h_fmaxAdducteursO");
        doubleSpinBox_h_fmaxAdducteursO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_fmaxAdducteursO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_fmaxAdducteursO->setAccelerated(true);
        doubleSpinBox_h_fmaxAdducteursO->setDecimals(1);
        doubleSpinBox_h_fmaxAdducteursO->setMaximum(100000.000000000000000);

        gridLayout_rationAA_2->addWidget(doubleSpinBox_h_fmaxAdducteursO, 1, 1, 1, 1);

        doubleSpinBox_h_fmaxAdducteursNO = new QDoubleSpinBox(layoutWidget_25);
        doubleSpinBox_h_fmaxAdducteursNO->setObjectName("doubleSpinBox_h_fmaxAdducteursNO");
        doubleSpinBox_h_fmaxAdducteursNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_fmaxAdducteursNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_fmaxAdducteursNO->setAccelerated(true);
        doubleSpinBox_h_fmaxAdducteursNO->setDecimals(1);
        doubleSpinBox_h_fmaxAdducteursNO->setMaximum(100000.000000000000000);

        gridLayout_rationAA_2->addWidget(doubleSpinBox_h_fmaxAdducteursNO, 1, 2, 1, 1);

        doubleSpinBox_h_fmaxAbducteursO = new QDoubleSpinBox(layoutWidget_25);
        doubleSpinBox_h_fmaxAbducteursO->setObjectName("doubleSpinBox_h_fmaxAbducteursO");
        doubleSpinBox_h_fmaxAbducteursO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_fmaxAbducteursO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_fmaxAbducteursO->setAccelerated(true);
        doubleSpinBox_h_fmaxAbducteursO->setDecimals(1);
        doubleSpinBox_h_fmaxAbducteursO->setMaximum(100000.000000000000000);

        gridLayout_rationAA_2->addWidget(doubleSpinBox_h_fmaxAbducteursO, 2, 1, 1, 1);

        doubleSpinBox_h_fmaxAbducteursNO = new QDoubleSpinBox(layoutWidget_25);
        doubleSpinBox_h_fmaxAbducteursNO->setObjectName("doubleSpinBox_h_fmaxAbducteursNO");
        doubleSpinBox_h_fmaxAbducteursNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_fmaxAbducteursNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_fmaxAbducteursNO->setAccelerated(true);
        doubleSpinBox_h_fmaxAbducteursNO->setDecimals(1);
        doubleSpinBox_h_fmaxAbducteursNO->setMaximum(100000.000000000000000);

        gridLayout_rationAA_2->addWidget(doubleSpinBox_h_fmaxAbducteursNO, 2, 2, 1, 1);

        pushButton_valider_bilan_hanche = new QPushButton(widget_hanche);
        pushButton_valider_bilan_hanche->setObjectName("pushButton_valider_bilan_hanche");
        pushButton_valider_bilan_hanche->setGeometry(QRect(310, 1860, 311, 51));
        layoutWidget_26 = new QWidget(widget_hanche);
        layoutWidget_26->setObjectName("layoutWidget_26");
        layoutWidget_26->setGeometry(QRect(50, 1120, 317, 198));
        gridLayout_sjB_2 = new QGridLayout(layoutWidget_26);
        gridLayout_sjB_2->setSpacing(15);
        gridLayout_sjB_2->setObjectName("gridLayout_sjB_2");
        gridLayout_sjB_2->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_sjB_2->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox_h_rfdmaxNOSj = new QDoubleSpinBox(layoutWidget_26);
        doubleSpinBox_h_rfdmaxNOSj->setObjectName("doubleSpinBox_h_rfdmaxNOSj");
        doubleSpinBox_h_rfdmaxNOSj->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rfdmaxNOSj->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rfdmaxNOSj->setAccelerated(true);
        doubleSpinBox_h_rfdmaxNOSj->setDecimals(1);
        doubleSpinBox_h_rfdmaxNOSj->setMaximum(100000.000000000000000);

        gridLayout_sjB_2->addWidget(doubleSpinBox_h_rfdmaxNOSj, 3, 1, 1, 1);

        label_hauteur_saut_sj_2 = new QLabel(layoutWidget_26);
        label_hauteur_saut_sj_2->setObjectName("label_hauteur_saut_sj_2");

        gridLayout_sjB_2->addWidget(label_hauteur_saut_sj_2, 1, 0, 1, 1);

        label_test_sjB_2 = new QLabel(layoutWidget_26);
        label_test_sjB_2->setObjectName("label_test_sjB_2");
        label_test_sjB_2->setTextFormat(Qt::RichText);

        gridLayout_sjB_2->addWidget(label_test_sjB_2, 0, 0, 1, 1);

        label_fmax_sj_2 = new QLabel(layoutWidget_26);
        label_fmax_sj_2->setObjectName("label_fmax_sj_2");

        gridLayout_sjB_2->addWidget(label_fmax_sj_2, 2, 0, 1, 1);

        label_pmax_Sj_2 = new QLabel(layoutWidget_26);
        label_pmax_Sj_2->setObjectName("label_pmax_Sj_2");

        gridLayout_sjB_2->addWidget(label_pmax_Sj_2, 3, 0, 1, 1);

        doubleSpinBox_h_rfdmaxOSj = new QDoubleSpinBox(layoutWidget_26);
        doubleSpinBox_h_rfdmaxOSj->setObjectName("doubleSpinBox_h_rfdmaxOSj");
        doubleSpinBox_h_rfdmaxOSj->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rfdmaxOSj->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rfdmaxOSj->setAccelerated(true);
        doubleSpinBox_h_rfdmaxOSj->setDecimals(1);
        doubleSpinBox_h_rfdmaxOSj->setMaximum(100000.000000000000000);

        gridLayout_sjB_2->addWidget(doubleSpinBox_h_rfdmaxOSj, 2, 1, 1, 1);

        doubleSpinBox_h_hauteurSautSj = new QDoubleSpinBox(layoutWidget_26);
        doubleSpinBox_h_hauteurSautSj->setObjectName("doubleSpinBox_h_hauteurSautSj");
        doubleSpinBox_h_hauteurSautSj->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_hauteurSautSj->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_hauteurSautSj->setAccelerated(true);
        doubleSpinBox_h_hauteurSautSj->setDecimals(1);
        doubleSpinBox_h_hauteurSautSj->setMaximum(100000.000000000000000);

        gridLayout_sjB_2->addWidget(doubleSpinBox_h_hauteurSautSj, 1, 1, 1, 1);

        layoutWidget_27 = new QWidget(widget_hanche);
        layoutWidget_27->setObjectName("layoutWidget_27");
        layoutWidget_27->setGeometry(QRect(40, 410, 457, 110));
        gridLayout_ratioIJ_3 = new QGridLayout(layoutWidget_27);
        gridLayout_ratioIJ_3->setSpacing(15);
        gridLayout_ratioIJ_3->setObjectName("gridLayout_ratioIJ_3");
        gridLayout_ratioIJ_3->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox_h_fmaxQuadriNO = new QDoubleSpinBox(layoutWidget_27);
        doubleSpinBox_h_fmaxQuadriNO->setObjectName("doubleSpinBox_h_fmaxQuadriNO");
        doubleSpinBox_h_fmaxQuadriNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_fmaxQuadriNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_fmaxQuadriNO->setAccelerated(true);
        doubleSpinBox_h_fmaxQuadriNO->setDecimals(1);
        doubleSpinBox_h_fmaxQuadriNO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_3->addWidget(doubleSpinBox_h_fmaxQuadriNO, 2, 2, 1, 1);

        label_non_opere_20 = new QLabel(layoutWidget_27);
        label_non_opere_20->setObjectName("label_non_opere_20");

        gridLayout_ratioIJ_3->addWidget(label_non_opere_20, 0, 2, 1, 1);

        doubleSpinBox_h_fmaxIschioO = new QDoubleSpinBox(layoutWidget_27);
        doubleSpinBox_h_fmaxIschioO->setObjectName("doubleSpinBox_h_fmaxIschioO");
        doubleSpinBox_h_fmaxIschioO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_fmaxIschioO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_fmaxIschioO->setAccelerated(true);
        doubleSpinBox_h_fmaxIschioO->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_h_fmaxIschioO->setDecimals(1);
        doubleSpinBox_h_fmaxIschioO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_3->addWidget(doubleSpinBox_h_fmaxIschioO, 1, 1, 1, 1);

        label_opere_21 = new QLabel(layoutWidget_27);
        label_opere_21->setObjectName("label_opere_21");

        gridLayout_ratioIJ_3->addWidget(label_opere_21, 0, 1, 1, 1);

        label_ration_ij_quadri_3 = new QLabel(layoutWidget_27);
        label_ration_ij_quadri_3->setObjectName("label_ration_ij_quadri_3");
        label_ration_ij_quadri_3->setTextFormat(Qt::RichText);

        gridLayout_ratioIJ_3->addWidget(label_ration_ij_quadri_3, 0, 0, 1, 1);

        label_fmax_ij_2 = new QLabel(layoutWidget_27);
        label_fmax_ij_2->setObjectName("label_fmax_ij_2");

        gridLayout_ratioIJ_3->addWidget(label_fmax_ij_2, 1, 0, 1, 1);

        doubleSpinBox_h_fmaxIschioNO = new QDoubleSpinBox(layoutWidget_27);
        doubleSpinBox_h_fmaxIschioNO->setObjectName("doubleSpinBox_h_fmaxIschioNO");
        doubleSpinBox_h_fmaxIschioNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_fmaxIschioNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_fmaxIschioNO->setAccelerated(true);
        doubleSpinBox_h_fmaxIschioNO->setDecimals(1);
        doubleSpinBox_h_fmaxIschioNO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_3->addWidget(doubleSpinBox_h_fmaxIschioNO, 1, 2, 1, 1);

        label_fmax_quadri_2 = new QLabel(layoutWidget_27);
        label_fmax_quadri_2->setObjectName("label_fmax_quadri_2");

        gridLayout_ratioIJ_3->addWidget(label_fmax_quadri_2, 2, 0, 1, 1);

        doubleSpinBox_h_fmaxQuadriO = new QDoubleSpinBox(layoutWidget_27);
        doubleSpinBox_h_fmaxQuadriO->setObjectName("doubleSpinBox_h_fmaxQuadriO");
        doubleSpinBox_h_fmaxQuadriO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_fmaxQuadriO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_fmaxQuadriO->setAccelerated(true);
        doubleSpinBox_h_fmaxQuadriO->setDecimals(1);
        doubleSpinBox_h_fmaxQuadriO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_3->addWidget(doubleSpinBox_h_fmaxQuadriO, 2, 1, 1, 1);

        line_2 = new QFrame(widget_hanche);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(270, 380, 381, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_10 = new QFrame(widget_hanche);
        line_10->setObjectName("line_10");
        line_10->setGeometry(QRect(270, 1330, 381, 20));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);
        line_21 = new QFrame(widget_hanche);
        line_21->setObjectName("line_21");
        line_21->setGeometry(QRect(270, 1560, 381, 20));
        line_21->setFrameShape(QFrame::HLine);
        line_21->setFrameShadow(QFrame::Sunken);
        groupBox_controleGenou_h = new QGroupBox(widget_hanche);
        groupBox_controleGenou_h->setObjectName("groupBox_controleGenou_h");
        groupBox_controleGenou_h->setGeometry(QRect(50, 710, 461, 191));
        groupBox_controleGenou_h->setFlat(false);
        groupBox_3 = new QGroupBox(groupBox_controleGenou_h);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(20, 120, 431, 61));
        groupBox_3->setFlat(false);
        radioButton_h_controleGenouValgus = new QRadioButton(groupBox_3);
        radioButton_h_controleGenouValgus->setObjectName("radioButton_h_controleGenouValgus");
        radioButton_h_controleGenouValgus->setGeometry(QRect(10, 30, 301, 24));
        radioButton_h_controleGenouFrontal = new QRadioButton(groupBox_3);
        radioButton_h_controleGenouFrontal->setObjectName("radioButton_h_controleGenouFrontal");
        radioButton_h_controleGenouFrontal->setGeometry(QRect(10, 0, 321, 24));
        radioButton_h_controleGenouFrontal->setChecked(true);
        groupBox_4 = new QGroupBox(groupBox_controleGenou_h);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(20, 30, 431, 71));
        groupBox_4->setFlat(false);
        radioButton_h_angleFlexionNOK = new QRadioButton(groupBox_4);
        radioButton_h_angleFlexionNOK->setObjectName("radioButton_h_angleFlexionNOK");
        radioButton_h_angleFlexionNOK->setGeometry(QRect(10, 40, 431, 24));
        radioButton_h_angleFlexionOK = new QRadioButton(groupBox_4);
        radioButton_h_angleFlexionOK->setObjectName("radioButton_h_angleFlexionOK");
        radioButton_h_angleFlexionOK->setGeometry(QRect(10, 10, 401, 24));
        radioButton_h_angleFlexionOK->setChecked(true);
        groupBox_repartitionCharge_h = new QGroupBox(widget_hanche);
        groupBox_repartitionCharge_h->setObjectName("groupBox_repartitionCharge_h");
        groupBox_repartitionCharge_h->setGeometry(QRect(50, 910, 511, 151));
        groupBox_repartitionCharge_h->setFlat(false);
        groupBox_repartitionCharge_h->setCheckable(false);
        checkBox_h_receptionMedioPied = new QCheckBox(groupBox_repartitionCharge_h);
        checkBox_h_receptionMedioPied->setObjectName("checkBox_h_receptionMedioPied");
        checkBox_h_receptionMedioPied->setGeometry(QRect(30, 30, 201, 24));
        checkBox_h_receptionAvantPied = new QCheckBox(groupBox_repartitionCharge_h);
        checkBox_h_receptionAvantPied->setObjectName("checkBox_h_receptionAvantPied");
        checkBox_h_receptionAvantPied->setGeometry(QRect(30, 60, 291, 21));
        checkBox_h_receptionBordInterne = new QCheckBox(groupBox_repartitionCharge_h);
        checkBox_h_receptionBordInterne->setObjectName("checkBox_h_receptionBordInterne");
        checkBox_h_receptionBordInterne->setGeometry(QRect(30, 90, 341, 24));
        checkBox_h_receptionTalon = new QCheckBox(groupBox_repartitionCharge_h);
        checkBox_h_receptionTalon->setObjectName("checkBox_h_receptionTalon");
        checkBox_h_receptionTalon->setGeometry(QRect(30, 120, 321, 24));
        line_23 = new QFrame(widget_hanche);
        line_23->setObjectName("line_23");
        line_23->setGeometry(QRect(270, 1090, 381, 20));
        line_23->setFrameShape(QFrame::HLine);
        line_23->setFrameShadow(QFrame::Sunken);
        groupBox_troncBassin_h = new QGroupBox(widget_hanche);
        groupBox_troncBassin_h->setObjectName("groupBox_troncBassin_h");
        groupBox_troncBassin_h->setGeometry(QRect(550, 710, 351, 111));
        groupBox_troncBassin_h->setFlat(false);
        radioButton_h_controleTroncOK = new QRadioButton(groupBox_troncBassin_h);
        radioButton_h_controleTroncOK->setObjectName("radioButton_h_controleTroncOK");
        radioButton_h_controleTroncOK->setGeometry(QRect(20, 30, 301, 24));
        radioButton_h_controleTroncOK->setChecked(true);
        radioButton_h_controleTroncNOK = new QRadioButton(groupBox_troncBassin_h);
        radioButton_h_controleTroncNOK->setObjectName("radioButton_h_controleTroncNOK");
        radioButton_h_controleTroncNOK->setGeometry(QRect(20, 60, 321, 24));
        line_24 = new QFrame(widget_hanche);
        line_24->setObjectName("line_24");
        line_24->setGeometry(QRect(270, 530, 381, 20));
        line_24->setFrameShape(QFrame::HLine);
        line_24->setFrameShadow(QFrame::Sunken);
        layoutWidget_4 = new QWidget(widget_hanche);
        layoutWidget_4->setObjectName("layoutWidget_4");
        layoutWidget_4->setGeometry(QRect(400, 1590, 423, 154));
        gridLayout_6 = new QGridLayout(layoutWidget_4);
        gridLayout_6->setSpacing(15);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        label_test_dj_2 = new QLabel(layoutWidget_4);
        label_test_dj_2->setObjectName("label_test_dj_2");
        label_test_dj_2->setTextFormat(Qt::RichText);

        gridLayout_6->addWidget(label_test_dj_2, 0, 0, 1, 1);

        label_opere_22 = new QLabel(layoutWidget_4);
        label_opere_22->setObjectName("label_opere_22");

        gridLayout_6->addWidget(label_opere_22, 0, 1, 1, 1);

        label_non_opere_21 = new QLabel(layoutWidget_4);
        label_non_opere_21->setObjectName("label_non_opere_21");

        gridLayout_6->addWidget(label_non_opere_21, 0, 2, 1, 1);

        label_hauteur_saut_dj_2 = new QLabel(layoutWidget_4);
        label_hauteur_saut_dj_2->setObjectName("label_hauteur_saut_dj_2");

        gridLayout_6->addWidget(label_hauteur_saut_dj_2, 1, 0, 1, 1);

        doubleSpinBox_h_hauteurSautDjO = new QDoubleSpinBox(layoutWidget_4);
        doubleSpinBox_h_hauteurSautDjO->setObjectName("doubleSpinBox_h_hauteurSautDjO");
        doubleSpinBox_h_hauteurSautDjO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_hauteurSautDjO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_hauteurSautDjO->setAccelerated(true);
        doubleSpinBox_h_hauteurSautDjO->setDecimals(1);
        doubleSpinBox_h_hauteurSautDjO->setMaximum(100000.000000000000000);

        gridLayout_6->addWidget(doubleSpinBox_h_hauteurSautDjO, 1, 1, 1, 1);

        doubleSpinBox_h_hauteurSautDjNO = new QDoubleSpinBox(layoutWidget_4);
        doubleSpinBox_h_hauteurSautDjNO->setObjectName("doubleSpinBox_h_hauteurSautDjNO");
        doubleSpinBox_h_hauteurSautDjNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_hauteurSautDjNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_hauteurSautDjNO->setAccelerated(true);
        doubleSpinBox_h_hauteurSautDjNO->setDecimals(1);
        doubleSpinBox_h_hauteurSautDjNO->setMaximum(100000.000000000000000);

        gridLayout_6->addWidget(doubleSpinBox_h_hauteurSautDjNO, 1, 2, 1, 1);

        label_rfdmax_dj_2 = new QLabel(layoutWidget_4);
        label_rfdmax_dj_2->setObjectName("label_rfdmax_dj_2");

        gridLayout_6->addWidget(label_rfdmax_dj_2, 2, 0, 1, 1);

        doubleSpinBox_h_rfdmaxDjO = new QDoubleSpinBox(layoutWidget_4);
        doubleSpinBox_h_rfdmaxDjO->setObjectName("doubleSpinBox_h_rfdmaxDjO");
        doubleSpinBox_h_rfdmaxDjO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rfdmaxDjO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rfdmaxDjO->setAccelerated(true);
        doubleSpinBox_h_rfdmaxDjO->setDecimals(1);
        doubleSpinBox_h_rfdmaxDjO->setMaximum(10000000.000000000000000);

        gridLayout_6->addWidget(doubleSpinBox_h_rfdmaxDjO, 2, 1, 1, 1);

        doubleSpinBox_h_rfdmaxDjNO = new QDoubleSpinBox(layoutWidget_4);
        doubleSpinBox_h_rfdmaxDjNO->setObjectName("doubleSpinBox_h_rfdmaxDjNO");
        doubleSpinBox_h_rfdmaxDjNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rfdmaxDjNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rfdmaxDjNO->setAccelerated(true);
        doubleSpinBox_h_rfdmaxDjNO->setDecimals(1);
        doubleSpinBox_h_rfdmaxDjNO->setMaximum(10000000.000000000000000);

        gridLayout_6->addWidget(doubleSpinBox_h_rfdmaxDjNO, 2, 2, 1, 1);

        label_tps_contact_dj_2 = new QLabel(layoutWidget_4);
        label_tps_contact_dj_2->setObjectName("label_tps_contact_dj_2");

        gridLayout_6->addWidget(label_tps_contact_dj_2, 3, 0, 1, 1);

        doubleSpinBox_h_tempsContactDjO = new QDoubleSpinBox(layoutWidget_4);
        doubleSpinBox_h_tempsContactDjO->setObjectName("doubleSpinBox_h_tempsContactDjO");
        doubleSpinBox_h_tempsContactDjO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_tempsContactDjO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_tempsContactDjO->setAccelerated(true);
        doubleSpinBox_h_tempsContactDjO->setDecimals(1);
        doubleSpinBox_h_tempsContactDjO->setMaximum(100000.000000000000000);

        gridLayout_6->addWidget(doubleSpinBox_h_tempsContactDjO, 3, 1, 1, 1);

        doubleSpinBox_h_tempsContactDjNO = new QDoubleSpinBox(layoutWidget_4);
        doubleSpinBox_h_tempsContactDjNO->setObjectName("doubleSpinBox_h_tempsContactDjNO");
        doubleSpinBox_h_tempsContactDjNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_tempsContactDjNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_tempsContactDjNO->setAccelerated(true);
        doubleSpinBox_h_tempsContactDjNO->setDecimals(1);
        doubleSpinBox_h_tempsContactDjNO->setMaximum(100000.000000000000000);

        gridLayout_6->addWidget(doubleSpinBox_h_tempsContactDjNO, 3, 2, 1, 1);

        layoutWidget_28 = new QWidget(widget_hanche);
        layoutWidget_28->setObjectName("layoutWidget_28");
        layoutWidget_28->setGeometry(QRect(420, 1360, 355, 66));
        gridLayout_7 = new QGridLayout(layoutWidget_28);
        gridLayout_7->setSpacing(15);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        label_test_cmj_2 = new QLabel(layoutWidget_28);
        label_test_cmj_2->setObjectName("label_test_cmj_2");
        label_test_cmj_2->setTextFormat(Qt::RichText);

        gridLayout_7->addWidget(label_test_cmj_2, 0, 0, 1, 1);

        label_opere_23 = new QLabel(layoutWidget_28);
        label_opere_23->setObjectName("label_opere_23");

        gridLayout_7->addWidget(label_opere_23, 0, 1, 1, 1);

        label_non_opere_22 = new QLabel(layoutWidget_28);
        label_non_opere_22->setObjectName("label_non_opere_22");

        gridLayout_7->addWidget(label_non_opere_22, 0, 2, 1, 1);

        label_hauteur_saut_cmj_2 = new QLabel(layoutWidget_28);
        label_hauteur_saut_cmj_2->setObjectName("label_hauteur_saut_cmj_2");

        gridLayout_7->addWidget(label_hauteur_saut_cmj_2, 1, 0, 1, 1);

        doubleSpinBox_h_hauteurSautCmjO = new QDoubleSpinBox(layoutWidget_28);
        doubleSpinBox_h_hauteurSautCmjO->setObjectName("doubleSpinBox_h_hauteurSautCmjO");
        doubleSpinBox_h_hauteurSautCmjO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_hauteurSautCmjO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_hauteurSautCmjO->setAccelerated(true);
        doubleSpinBox_h_hauteurSautCmjO->setDecimals(1);
        doubleSpinBox_h_hauteurSautCmjO->setMaximum(100000.000000000000000);

        gridLayout_7->addWidget(doubleSpinBox_h_hauteurSautCmjO, 1, 1, 1, 1);

        doubleSpinBox_h_hauteurSautCmjNO = new QDoubleSpinBox(layoutWidget_28);
        doubleSpinBox_h_hauteurSautCmjNO->setObjectName("doubleSpinBox_h_hauteurSautCmjNO");
        doubleSpinBox_h_hauteurSautCmjNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_hauteurSautCmjNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_hauteurSautCmjNO->setAccelerated(true);
        doubleSpinBox_h_hauteurSautCmjNO->setDecimals(1);
        doubleSpinBox_h_hauteurSautCmjNO->setMaximum(100000.000000000000000);

        gridLayout_7->addWidget(doubleSpinBox_h_hauteurSautCmjNO, 1, 2, 1, 1);

        layoutWidget_29 = new QWidget(widget_hanche);
        layoutWidget_29->setObjectName("layoutWidget_29");
        layoutWidget_29->setGeometry(QRect(50, 560, 465, 110));
        gridLayout_ratioIJ_4 = new QGridLayout(layoutWidget_29);
        gridLayout_ratioIJ_4->setSpacing(15);
        gridLayout_ratioIJ_4->setObjectName("gridLayout_ratioIJ_4");
        gridLayout_ratioIJ_4->setContentsMargins(0, 0, 0, 0);
        doubleSpinBox_h_force90McCallNO = new QDoubleSpinBox(layoutWidget_29);
        doubleSpinBox_h_force90McCallNO->setObjectName("doubleSpinBox_h_force90McCallNO");
        doubleSpinBox_h_force90McCallNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_force90McCallNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_force90McCallNO->setAccelerated(true);
        doubleSpinBox_h_force90McCallNO->setDecimals(1);
        doubleSpinBox_h_force90McCallNO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_4->addWidget(doubleSpinBox_h_force90McCallNO, 2, 2, 1, 1);

        label_non_opere_23 = new QLabel(layoutWidget_29);
        label_non_opere_23->setObjectName("label_non_opere_23");

        gridLayout_ratioIJ_4->addWidget(label_non_opere_23, 0, 2, 1, 1);

        doubleSpinBox_h_force30McCallO = new QDoubleSpinBox(layoutWidget_29);
        doubleSpinBox_h_force30McCallO->setObjectName("doubleSpinBox_h_force30McCallO");
        doubleSpinBox_h_force30McCallO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_force30McCallO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_force30McCallO->setAccelerated(true);
        doubleSpinBox_h_force30McCallO->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_h_force30McCallO->setDecimals(1);
        doubleSpinBox_h_force30McCallO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_4->addWidget(doubleSpinBox_h_force30McCallO, 1, 1, 1, 1);

        label_opere_24 = new QLabel(layoutWidget_29);
        label_opere_24->setObjectName("label_opere_24");

        gridLayout_ratioIJ_4->addWidget(label_opere_24, 0, 1, 1, 1);

        label_ration_ij_quadri_4 = new QLabel(layoutWidget_29);
        label_ration_ij_quadri_4->setObjectName("label_ration_ij_quadri_4");
        label_ration_ij_quadri_4->setTextFormat(Qt::RichText);

        gridLayout_ratioIJ_4->addWidget(label_ration_ij_quadri_4, 0, 0, 1, 1);

        label_f30_mccall_2 = new QLabel(layoutWidget_29);
        label_f30_mccall_2->setObjectName("label_f30_mccall_2");

        gridLayout_ratioIJ_4->addWidget(label_f30_mccall_2, 1, 0, 1, 1);

        doubleSpinBox_h_force30McCallNO = new QDoubleSpinBox(layoutWidget_29);
        doubleSpinBox_h_force30McCallNO->setObjectName("doubleSpinBox_h_force30McCallNO");
        doubleSpinBox_h_force30McCallNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_force30McCallNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_force30McCallNO->setAccelerated(true);
        doubleSpinBox_h_force30McCallNO->setDecimals(1);
        doubleSpinBox_h_force30McCallNO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_4->addWidget(doubleSpinBox_h_force30McCallNO, 1, 2, 1, 1);

        label_f90_mccall_2 = new QLabel(layoutWidget_29);
        label_f90_mccall_2->setObjectName("label_f90_mccall_2");

        gridLayout_ratioIJ_4->addWidget(label_f90_mccall_2, 2, 0, 1, 1);

        doubleSpinBox_h_force90McCallO = new QDoubleSpinBox(layoutWidget_29);
        doubleSpinBox_h_force90McCallO->setObjectName("doubleSpinBox_h_force90McCallO");
        doubleSpinBox_h_force90McCallO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_force90McCallO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_force90McCallO->setAccelerated(true);
        doubleSpinBox_h_force90McCallO->setDecimals(1);
        doubleSpinBox_h_force90McCallO->setMaximum(100000.000000000000000);

        gridLayout_ratioIJ_4->addWidget(doubleSpinBox_h_force90McCallO, 2, 1, 1, 1);

        line_25 = new QFrame(widget_hanche);
        line_25->setObjectName("line_25");
        line_25->setGeometry(QRect(330, 680, 381, 20));
        line_25->setFrameShape(QFrame::HLine);
        line_25->setFrameShadow(QFrame::Sunken);
        layoutWidget_30 = new QWidget(widget_hanche);
        layoutWidget_30->setObjectName("layoutWidget_30");
        layoutWidget_30->setGeometry(QRect(40, 1360, 356, 198));
        gridLayout_8 = new QGridLayout(layoutWidget_30);
        gridLayout_8->setSpacing(15);
        gridLayout_8->setObjectName("gridLayout_8");
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        label_test_cmjB_2 = new QLabel(layoutWidget_30);
        label_test_cmjB_2->setObjectName("label_test_cmjB_2");
        label_test_cmjB_2->setTextFormat(Qt::RichText);

        gridLayout_8->addWidget(label_test_cmjB_2, 0, 0, 1, 1);

        label_hauteur_saut_cmjB_2 = new QLabel(layoutWidget_30);
        label_hauteur_saut_cmjB_2->setObjectName("label_hauteur_saut_cmjB_2");

        gridLayout_8->addWidget(label_hauteur_saut_cmjB_2, 1, 0, 1, 1);

        doubleSpinBox_h_hauteurSautCmjB = new QDoubleSpinBox(layoutWidget_30);
        doubleSpinBox_h_hauteurSautCmjB->setObjectName("doubleSpinBox_h_hauteurSautCmjB");
        doubleSpinBox_h_hauteurSautCmjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_hauteurSautCmjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_hauteurSautCmjB->setAccelerated(true);
        doubleSpinBox_h_hauteurSautCmjB->setDecimals(1);
        doubleSpinBox_h_hauteurSautCmjB->setMaximum(100000.000000000000000);

        gridLayout_8->addWidget(doubleSpinBox_h_hauteurSautCmjB, 1, 1, 1, 1);

        label_tps_stabilisation_cmj_3 = new QLabel(layoutWidget_30);
        label_tps_stabilisation_cmj_3->setObjectName("label_tps_stabilisation_cmj_3");

        gridLayout_8->addWidget(label_tps_stabilisation_cmj_3, 2, 0, 1, 1);

        doubleSpinBox_h_tempsMvmtCmjB = new QDoubleSpinBox(layoutWidget_30);
        doubleSpinBox_h_tempsMvmtCmjB->setObjectName("doubleSpinBox_h_tempsMvmtCmjB");
        doubleSpinBox_h_tempsMvmtCmjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_tempsMvmtCmjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_tempsMvmtCmjB->setAccelerated(true);
        doubleSpinBox_h_tempsMvmtCmjB->setDecimals(1);
        doubleSpinBox_h_tempsMvmtCmjB->setMaximum(100000.000000000000000);

        gridLayout_8->addWidget(doubleSpinBox_h_tempsMvmtCmjB, 2, 1, 1, 1);

        label_fmax_cmjB_2 = new QLabel(layoutWidget_30);
        label_fmax_cmjB_2->setObjectName("label_fmax_cmjB_2");

        gridLayout_8->addWidget(label_fmax_cmjB_2, 3, 0, 1, 1);

        doubleSpinBox_h_rfdDecelerationOCmjB = new QDoubleSpinBox(layoutWidget_30);
        doubleSpinBox_h_rfdDecelerationOCmjB->setObjectName("doubleSpinBox_h_rfdDecelerationOCmjB");
        doubleSpinBox_h_rfdDecelerationOCmjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rfdDecelerationOCmjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rfdDecelerationOCmjB->setAccelerated(true);
        doubleSpinBox_h_rfdDecelerationOCmjB->setDecimals(1);
        doubleSpinBox_h_rfdDecelerationOCmjB->setMaximum(100000.000000000000000);

        gridLayout_8->addWidget(doubleSpinBox_h_rfdDecelerationOCmjB, 3, 1, 1, 1);

        label_RFDdeceleration_2 = new QLabel(layoutWidget_30);
        label_RFDdeceleration_2->setObjectName("label_RFDdeceleration_2");

        gridLayout_8->addWidget(label_RFDdeceleration_2, 4, 0, 1, 1);

        doubleSpinBox_h_rfdDecelerationNOCmjB = new QDoubleSpinBox(layoutWidget_30);
        doubleSpinBox_h_rfdDecelerationNOCmjB->setObjectName("doubleSpinBox_h_rfdDecelerationNOCmjB");
        doubleSpinBox_h_rfdDecelerationNOCmjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rfdDecelerationNOCmjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rfdDecelerationNOCmjB->setAccelerated(true);
        doubleSpinBox_h_rfdDecelerationNOCmjB->setDecimals(1);
        doubleSpinBox_h_rfdDecelerationNOCmjB->setMaximum(1000000.000000000000000);

        gridLayout_8->addWidget(doubleSpinBox_h_rfdDecelerationNOCmjB, 4, 1, 1, 1);

        layoutWidget_31 = new QWidget(widget_hanche);
        layoutWidget_31->setObjectName("layoutWidget_31");
        layoutWidget_31->setGeometry(QRect(40, 1590, 286, 242));
        gridLayout_9 = new QGridLayout(layoutWidget_31);
        gridLayout_9->setSpacing(15);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        label_test_djB_2 = new QLabel(layoutWidget_31);
        label_test_djB_2->setObjectName("label_test_djB_2");
        label_test_djB_2->setTextFormat(Qt::RichText);

        gridLayout_9->addWidget(label_test_djB_2, 0, 0, 1, 2);

        label_hauteur_saut_djB_2 = new QLabel(layoutWidget_31);
        label_hauteur_saut_djB_2->setObjectName("label_hauteur_saut_djB_2");

        gridLayout_9->addWidget(label_hauteur_saut_djB_2, 1, 0, 1, 1);

        doubleSpinBox_h_hauteurSautDjB = new QDoubleSpinBox(layoutWidget_31);
        doubleSpinBox_h_hauteurSautDjB->setObjectName("doubleSpinBox_h_hauteurSautDjB");
        doubleSpinBox_h_hauteurSautDjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_hauteurSautDjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_hauteurSautDjB->setAccelerated(true);
        doubleSpinBox_h_hauteurSautDjB->setDecimals(1);
        doubleSpinBox_h_hauteurSautDjB->setMaximum(100000.000000000000000);

        gridLayout_9->addWidget(doubleSpinBox_h_hauteurSautDjB, 1, 1, 1, 1);

        label_tps_vol_djB_2 = new QLabel(layoutWidget_31);
        label_tps_vol_djB_2->setObjectName("label_tps_vol_djB_2");

        gridLayout_9->addWidget(label_tps_vol_djB_2, 2, 0, 1, 1);

        doubleSpinBox_h_tempsVolDjB = new QDoubleSpinBox(layoutWidget_31);
        doubleSpinBox_h_tempsVolDjB->setObjectName("doubleSpinBox_h_tempsVolDjB");
        doubleSpinBox_h_tempsVolDjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_tempsVolDjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_tempsVolDjB->setAccelerated(true);
        doubleSpinBox_h_tempsVolDjB->setDecimals(1);
        doubleSpinBox_h_tempsVolDjB->setMaximum(100000.000000000000000);

        gridLayout_9->addWidget(doubleSpinBox_h_tempsVolDjB, 2, 1, 1, 1);

        label_tps_contact_djB_2 = new QLabel(layoutWidget_31);
        label_tps_contact_djB_2->setObjectName("label_tps_contact_djB_2");

        gridLayout_9->addWidget(label_tps_contact_djB_2, 3, 0, 1, 1);

        doubleSpinBox_h_tempsContactDjB = new QDoubleSpinBox(layoutWidget_31);
        doubleSpinBox_h_tempsContactDjB->setObjectName("doubleSpinBox_h_tempsContactDjB");
        doubleSpinBox_h_tempsContactDjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_tempsContactDjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_tempsContactDjB->setAccelerated(true);
        doubleSpinBox_h_tempsContactDjB->setDecimals(1);
        doubleSpinBox_h_tempsContactDjB->setMaximum(100000.000000000000000);

        gridLayout_9->addWidget(doubleSpinBox_h_tempsContactDjB, 3, 1, 1, 1);

        label_fmax_djB_2 = new QLabel(layoutWidget_31);
        label_fmax_djB_2->setObjectName("label_fmax_djB_2");

        gridLayout_9->addWidget(label_fmax_djB_2, 4, 0, 1, 1);

        doubleSpinBox_h_rfdmaxODjB = new QDoubleSpinBox(layoutWidget_31);
        doubleSpinBox_h_rfdmaxODjB->setObjectName("doubleSpinBox_h_rfdmaxODjB");
        doubleSpinBox_h_rfdmaxODjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rfdmaxODjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rfdmaxODjB->setAccelerated(true);
        doubleSpinBox_h_rfdmaxODjB->setDecimals(1);
        doubleSpinBox_h_rfdmaxODjB->setMaximum(100000.000000000000000);

        gridLayout_9->addWidget(doubleSpinBox_h_rfdmaxODjB, 4, 1, 1, 1);

        label_rfdmax_djB_2 = new QLabel(layoutWidget_31);
        label_rfdmax_djB_2->setObjectName("label_rfdmax_djB_2");

        gridLayout_9->addWidget(label_rfdmax_djB_2, 5, 0, 1, 1);

        doubleSpinBox_h_rfdmaxNODjB = new QDoubleSpinBox(layoutWidget_31);
        doubleSpinBox_h_rfdmaxNODjB->setObjectName("doubleSpinBox_h_rfdmaxNODjB");
        doubleSpinBox_h_rfdmaxNODjB->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rfdmaxNODjB->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rfdmaxNODjB->setAccelerated(true);
        doubleSpinBox_h_rfdmaxNODjB->setDecimals(1);
        doubleSpinBox_h_rfdmaxNODjB->setMaximum(10000000.000000000000000);

        gridLayout_9->addWidget(doubleSpinBox_h_rfdmaxNODjB, 5, 1, 1, 1);

        layoutWidget10 = new QWidget(widget_hanche);
        layoutWidget10->setObjectName("layoutWidget10");
        layoutWidget10->setGeometry(QRect(40, 10, 407, 330));
        gridLayout_10 = new QGridLayout(layoutWidget10);
        gridLayout_10->setSpacing(15);
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        label_amplitude_articulaire_3 = new QLabel(layoutWidget10);
        label_amplitude_articulaire_3->setObjectName("label_amplitude_articulaire_3");
        label_amplitude_articulaire_3->setTextFormat(Qt::RichText);

        gridLayout_10->addWidget(label_amplitude_articulaire_3, 0, 0, 1, 1);

        label_opere_2 = new QLabel(layoutWidget10);
        label_opere_2->setObjectName("label_opere_2");

        gridLayout_10->addWidget(label_opere_2, 0, 1, 1, 1);

        label_non_opere_2 = new QLabel(layoutWidget10);
        label_non_opere_2->setObjectName("label_non_opere_2");

        gridLayout_10->addWidget(label_non_opere_2, 0, 2, 1, 1);

        label_flexion_2 = new QLabel(layoutWidget10);
        label_flexion_2->setObjectName("label_flexion_2");

        gridLayout_10->addWidget(label_flexion_2, 1, 0, 1, 1);

        doubleSpinBox_h_flexionO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_flexionO->setObjectName("doubleSpinBox_h_flexionO");
        doubleSpinBox_h_flexionO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_flexionO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_flexionO->setAccelerated(true);
        doubleSpinBox_h_flexionO->setDecimals(1);
        doubleSpinBox_h_flexionO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_flexionO, 1, 1, 1, 1);

        doubleSpinBox_h_flexionNO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_flexionNO->setObjectName("doubleSpinBox_h_flexionNO");
        doubleSpinBox_h_flexionNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_flexionNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_flexionNO->setAccelerated(true);
        doubleSpinBox_h_flexionNO->setDecimals(1);
        doubleSpinBox_h_flexionNO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_flexionNO, 1, 2, 1, 1);

        label_extension_2 = new QLabel(layoutWidget10);
        label_extension_2->setObjectName("label_extension_2");

        gridLayout_10->addWidget(label_extension_2, 2, 0, 1, 1);

        doubleSpinBox_h_extensionO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_extensionO->setObjectName("doubleSpinBox_h_extensionO");
        doubleSpinBox_h_extensionO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_extensionO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_extensionO->setAccelerated(true);
        doubleSpinBox_h_extensionO->setDecimals(1);
        doubleSpinBox_h_extensionO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_extensionO, 2, 1, 1, 1);

        doubleSpinBox_h_extensionNO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_extensionNO->setObjectName("doubleSpinBox_h_extensionNO");
        doubleSpinBox_h_extensionNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_extensionNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_extensionNO->setAccelerated(true);
        doubleSpinBox_h_extensionNO->setDecimals(1);
        doubleSpinBox_h_extensionNO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_extensionNO, 2, 2, 1, 1);

        label_flexion_3 = new QLabel(layoutWidget10);
        label_flexion_3->setObjectName("label_flexion_3");

        gridLayout_10->addWidget(label_flexion_3, 3, 0, 1, 1);

        doubleSpinBox_h_abductionO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_abductionO->setObjectName("doubleSpinBox_h_abductionO");
        doubleSpinBox_h_abductionO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_abductionO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_abductionO->setAccelerated(true);
        doubleSpinBox_h_abductionO->setDecimals(1);
        doubleSpinBox_h_abductionO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_abductionO, 3, 1, 1, 1);

        doubleSpinBox_h_abductionNO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_abductionNO->setObjectName("doubleSpinBox_h_abductionNO");
        doubleSpinBox_h_abductionNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_abductionNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_abductionNO->setAccelerated(true);
        doubleSpinBox_h_abductionNO->setDecimals(1);
        doubleSpinBox_h_abductionNO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_abductionNO, 3, 2, 1, 1);

        label_flexion_7 = new QLabel(layoutWidget10);
        label_flexion_7->setObjectName("label_flexion_7");

        gridLayout_10->addWidget(label_flexion_7, 4, 0, 1, 1);

        doubleSpinBox_h_adductionO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_adductionO->setObjectName("doubleSpinBox_h_adductionO");
        doubleSpinBox_h_adductionO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_adductionO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_adductionO->setAccelerated(true);
        doubleSpinBox_h_adductionO->setDecimals(1);
        doubleSpinBox_h_adductionO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_adductionO, 4, 1, 1, 1);

        doubleSpinBox_h_adductionNO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_adductionNO->setObjectName("doubleSpinBox_h_adductionNO");
        doubleSpinBox_h_adductionNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_adductionNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_adductionNO->setAccelerated(true);
        doubleSpinBox_h_adductionNO->setDecimals(1);
        doubleSpinBox_h_adductionNO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_adductionNO, 4, 2, 1, 1);

        label_flexion_4 = new QLabel(layoutWidget10);
        label_flexion_4->setObjectName("label_flexion_4");

        gridLayout_10->addWidget(label_flexion_4, 5, 0, 1, 1);

        doubleSpinBox_h_rotationInterneO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_rotationInterneO->setObjectName("doubleSpinBox_h_rotationInterneO");
        doubleSpinBox_h_rotationInterneO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rotationInterneO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rotationInterneO->setAccelerated(true);
        doubleSpinBox_h_rotationInterneO->setDecimals(1);
        doubleSpinBox_h_rotationInterneO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_rotationInterneO, 5, 1, 1, 1);

        doubleSpinBox_h_rotationInterneNO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_rotationInterneNO->setObjectName("doubleSpinBox_h_rotationInterneNO");
        doubleSpinBox_h_rotationInterneNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rotationInterneNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rotationInterneNO->setAccelerated(true);
        doubleSpinBox_h_rotationInterneNO->setDecimals(1);
        doubleSpinBox_h_rotationInterneNO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_rotationInterneNO, 5, 2, 1, 1);

        label_flexion_5 = new QLabel(layoutWidget10);
        label_flexion_5->setObjectName("label_flexion_5");

        gridLayout_10->addWidget(label_flexion_5, 6, 0, 1, 1);

        doubleSpinBox_h_rotationExterneO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_rotationExterneO->setObjectName("doubleSpinBox_h_rotationExterneO");
        doubleSpinBox_h_rotationExterneO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rotationExterneO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rotationExterneO->setAccelerated(true);
        doubleSpinBox_h_rotationExterneO->setDecimals(1);
        doubleSpinBox_h_rotationExterneO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_rotationExterneO, 6, 1, 1, 1);

        doubleSpinBox_h_rotationExterneNO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_rotationExterneNO->setObjectName("doubleSpinBox_h_rotationExterneNO");
        doubleSpinBox_h_rotationExterneNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_rotationExterneNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_rotationExterneNO->setAccelerated(true);
        doubleSpinBox_h_rotationExterneNO->setDecimals(1);
        doubleSpinBox_h_rotationExterneNO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_rotationExterneNO, 6, 2, 1, 1);

        label_flexion_6 = new QLabel(layoutWidget10);
        label_flexion_6->setObjectName("label_flexion_6");

        gridLayout_10->addWidget(label_flexion_6, 7, 0, 1, 1);

        doubleSpinBox_h_bkfoO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_bkfoO->setObjectName("doubleSpinBox_h_bkfoO");
        doubleSpinBox_h_bkfoO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_bkfoO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_bkfoO->setAccelerated(true);
        doubleSpinBox_h_bkfoO->setDecimals(1);
        doubleSpinBox_h_bkfoO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_bkfoO, 7, 1, 1, 1);

        doubleSpinBox_h_bkfoNO = new QDoubleSpinBox(layoutWidget10);
        doubleSpinBox_h_bkfoNO->setObjectName("doubleSpinBox_h_bkfoNO");
        doubleSpinBox_h_bkfoNO->setCursor(QCursor(Qt::ArrowCursor));
        doubleSpinBox_h_bkfoNO->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        doubleSpinBox_h_bkfoNO->setAccelerated(true);
        doubleSpinBox_h_bkfoNO->setDecimals(1);
        doubleSpinBox_h_bkfoNO->setMaximum(360.000000000000000);

        gridLayout_10->addWidget(doubleSpinBox_h_bkfoNO, 7, 2, 1, 1);

        widget_generation_rapport_hanche = new QWidget(centralwidget);
        widget_generation_rapport_hanche->setObjectName("widget_generation_rapport_hanche");
        widget_generation_rapport_hanche->setGeometry(QRect(20, 9680, 901, 1491));
        textEdit_interpretationKine_hanche = new QTextEdit(widget_generation_rapport_hanche);
        textEdit_interpretationKine_hanche->setObjectName("textEdit_interpretationKine_hanche");
        textEdit_interpretationKine_hanche->setGeometry(QRect(90, 50, 721, 321));
        textEdit_interpretationKine_hanche->setFrameShape(QFrame::Box);
        label_axes_7 = new QLabel(widget_generation_rapport_hanche);
        label_axes_7->setObjectName("label_axes_7");
        label_axes_7->setGeometry(QRect(90, 450, 451, 20));
        label_axes_7->setFont(font);
        label_axes_7->setTextFormat(Qt::RichText);
        line_22 = new QFrame(widget_generation_rapport_hanche);
        line_22->setObjectName("line_22");
        line_22->setGeometry(QRect(300, 410, 321, 16));
        line_22->setFrameShape(QFrame::HLine);
        line_22->setFrameShadow(QFrame::Sunken);
        label_axes_8 = new QLabel(widget_generation_rapport_hanche);
        label_axes_8->setObjectName("label_axes_8");
        label_axes_8->setGeometry(QRect(90, 20, 271, 20));
        label_axes_8->setFont(font1);
        label_axes_8->setTextFormat(Qt::RichText);
        pushButton_validerRapport_hanche = new QPushButton(widget_generation_rapport_hanche);
        pushButton_validerRapport_hanche->setObjectName("pushButton_validerRapport_hanche");
        pushButton_validerRapport_hanche->setGeometry(QRect(280, 1430, 201, 51));
        line_26 = new QFrame(widget_generation_rapport_hanche);
        line_26->setObjectName("line_26");
        line_26->setGeometry(QRect(270, 1280, 321, 16));
        line_26->setFrameShape(QFrame::HLine);
        line_26->setFrameShadow(QFrame::Sunken);
        toolButton_h = new QToolButton(widget_generation_rapport_hanche);
        toolButton_h->setObjectName("toolButton_h");
        toolButton_h->setGeometry(QRect(570, 1360, 61, 26));
        label_axes_9 = new QLabel(widget_generation_rapport_hanche);
        label_axes_9->setObjectName("label_axes_9");
        label_axes_9->setGeometry(QRect(100, 1300, 151, 31));
        label_axes_9->setFont(font);
        label_axes_9->setTextFormat(Qt::RichText);
        lineEdit_h_pathAnnexes = new QLineEdit(widget_generation_rapport_hanche);
        lineEdit_h_pathAnnexes->setObjectName("lineEdit_h_pathAnnexes");
        lineEdit_h_pathAnnexes->setGeometry(QRect(170, 1360, 371, 26));
        lineEdit_h_pathAnnexes->setReadOnly(true);
        layoutWidget_8 = new QWidget(widget_generation_rapport_hanche);
        layoutWidget_8->setObjectName("layoutWidget_8");
        layoutWidget_8->setGeometry(QRect(100, 490, 691, 771));
        verticalLayout_axesAmeliorer_3 = new QVBoxLayout(layoutWidget_8);
        verticalLayout_axesAmeliorer_3->setSpacing(15);
        verticalLayout_axesAmeliorer_3->setObjectName("verticalLayout_axesAmeliorer_3");
        verticalLayout_axesAmeliorer_3->setContentsMargins(0, 0, 0, 0);
        checkBox_h_tricepsSural = new QCheckBox(layoutWidget_8);
        checkBox_h_tricepsSural->setObjectName("checkBox_h_tricepsSural");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_tricepsSural);

        checkBox_h_excentriqueQuadri = new QCheckBox(layoutWidget_8);
        checkBox_h_excentriqueQuadri->setObjectName("checkBox_h_excentriqueQuadri");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_excentriqueQuadri);

        checkBox_h_concentriqueQuadri = new QCheckBox(layoutWidget_8);
        checkBox_h_concentriqueQuadri->setObjectName("checkBox_h_concentriqueQuadri");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_concentriqueQuadri);

        checkBox_h_ij = new QCheckBox(layoutWidget_8);
        checkBox_h_ij->setObjectName("checkBox_h_ij");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_ij);

        checkBox_h_renfoStabilisateurs = new QCheckBox(layoutWidget_8);
        checkBox_h_renfoStabilisateurs->setObjectName("checkBox_h_renfoStabilisateurs");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_renfoStabilisateurs);

        checkBox_h_intrinseque = new QCheckBox(layoutWidget_8);
        checkBox_h_intrinseque->setObjectName("checkBox_h_intrinseque");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_intrinseque);

        checkBox_h_renforcementAdducteurs = new QCheckBox(layoutWidget_8);
        checkBox_h_renforcementAdducteurs->setObjectName("checkBox_h_renforcementAdducteurs");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_renforcementAdducteurs);

        checkBox_h_changementDirection = new QCheckBox(layoutWidget_8);
        checkBox_h_changementDirection->setObjectName("checkBox_h_changementDirection");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_changementDirection);

        checkBox_h_plioHorizontaleAxe = new QCheckBox(layoutWidget_8);
        checkBox_h_plioHorizontaleAxe->setObjectName("checkBox_h_plioHorizontaleAxe");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_plioHorizontaleAxe);

        checkBox_h_plioVerticaleAxe = new QCheckBox(layoutWidget_8);
        checkBox_h_plioVerticaleAxe->setObjectName("checkBox_h_plioVerticaleAxe");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_plioVerticaleAxe);

        checkBox_h_plioMulti = new QCheckBox(layoutWidget_8);
        checkBox_h_plioMulti->setObjectName("checkBox_h_plioMulti");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_plioMulti);

        checkBox_h_controleGenou = new QCheckBox(layoutWidget_8);
        checkBox_h_controleGenou->setObjectName("checkBox_h_controleGenou");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_controleGenou);

        checkBox_h_controleComplexe = new QCheckBox(layoutWidget_8);
        checkBox_h_controleComplexe->setObjectName("checkBox_h_controleComplexe");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_controleComplexe);

        checkBox_h_force = new QCheckBox(layoutWidget_8);
        checkBox_h_force->setObjectName("checkBox_h_force");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_force);

        checkBox_h_explosivite = new QCheckBox(layoutWidget_8);
        checkBox_h_explosivite->setObjectName("checkBox_h_explosivite");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_explosivite);

        checkBox_h_deceleration = new QCheckBox(layoutWidget_8);
        checkBox_h_deceleration->setObjectName("checkBox_h_deceleration");

        verticalLayout_axesAmeliorer_3->addWidget(checkBox_h_deceleration);

        label_5 = new QLabel(widget_generation_rapport_hanche);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(100, 370, 611, 20));
        label_5->setFont(font2);
        pushButton_annulerModificationBilan = new QPushButton(centralwidget);
        pushButton_annulerModificationBilan->setObjectName("pushButton_annulerModificationBilan");
        pushButton_annulerModificationBilan->setGeometry(QRect(560, 100, 181, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionGestionPatient->setText(QCoreApplication::translate("MainWindow", "Gestion des patients", nullptr));
        label_date_bilan->setText(QCoreApplication::translate("MainWindow", "Date du bilan ", nullptr));
        label_patient_courant->setText(QCoreApplication::translate("MainWindow", "Patient courant", nullptr));
        pushButton_rechercher->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        label_type_bilan->setText(QCoreApplication::translate("MainWindow", "Type de bilan", nullptr));
        pushButton_generer_rapport->setText(QCoreApplication::translate("MainWindow", "Generer le rapport", nullptr));
        pushButton_editer_bilan->setText(QCoreApplication::translate("MainWindow", "Ajouter un nouveau bilan", nullptr));
        label_perimetre->setText(QCoreApplication::translate("MainWindow", "Perimetres (cm) :", nullptr));
        label_opere_3->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_3->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_mollet->setText(QCoreApplication::translate("MainWindow", "Mollet", nullptr));
        label_sommet_rotule_dix->setText(QCoreApplication::translate("MainWindow", "Sommet  rotule +10", nullptr));
        label_sommet_rotule_vingt->setText(QCoreApplication::translate("MainWindow", "Sommet  rotule +20", nullptr));
        label_kStart->setText(QCoreApplication::translate("MainWindow", "Kstart", nullptr));
        label_rsi->setText(QCoreApplication::translate("MainWindow", "Test ACL - RSI", nullptr));
        label_sur_cent->setText(QCoreApplication::translate("MainWindow", "/ 100", nullptr));
        label_sur_cent_2->setText(QCoreApplication::translate("MainWindow", "/ 100", nullptr));
        label_amplitude_articulaire->setText(QCoreApplication::translate("MainWindow", "Amplitude articulaire :", nullptr));
        label_opere->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_flexion->setText(QCoreApplication::translate("MainWindow", "Flexion (\302\260)", nullptr));
        label_extension->setText(QCoreApplication::translate("MainWindow", "Extension (\302\260)", nullptr));
        label_test_accroupissement->setText(QCoreApplication::translate("MainWindow", "Test d accroupissement", nullptr));
        comboBox_g_testAccroupissement->setItemText(0, QCoreApplication::translate("MainWindow", " Impossible", nullptr));
        comboBox_g_testAccroupissement->setItemText(1, QCoreApplication::translate("MainWindow", "Douloureux avec EVA > 2/10", nullptr));
        comboBox_g_testAccroupissement->setItemText(2, QCoreApplication::translate("MainWindow", "Genant avec EVA < 2/10 ", nullptr));
        comboBox_g_testAccroupissement->setItemText(3, QCoreApplication::translate("MainWindow", "Bon avec EVA = 0", nullptr));

        label_fmax_abducteurs->setText(QCoreApplication::translate("MainWindow", "FMax Abducteurs (N.kg-1)", nullptr));
        label_opere_5->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_ration_add_abb->setText(QCoreApplication::translate("MainWindow", "Ratio Adducteurs / Abducteurs", nullptr));
        label_non_opere_5->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_fmax_adducteurs->setText(QCoreApplication::translate("MainWindow", "FMax Adducteurs (N.kg-1)", nullptr));
        pushButton_valider_bilan->setText(QCoreApplication::translate("MainWindow", "Valider le bilan", nullptr));
        label_hauteur_saut_sj->setText(QCoreApplication::translate("MainWindow", "Hauteur de saut (cm)", nullptr));
        label_test_sjB->setText(QCoreApplication::translate("MainWindow", "Squat jump Bipodal :", nullptr));
        label_fmax_sj->setText(QCoreApplication::translate("MainWindow", "RFDmax genou opere (N.s)", nullptr));
        label_pmax_Sj->setText(QCoreApplication::translate("MainWindow", "RFDmax genou non opere (N.s)", nullptr));
        label_non_opere_4->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_opere_4->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_ration_ij_quadri->setText(QCoreApplication::translate("MainWindow", "Ratio Ischios Jambiers / Quadriceps :", nullptr));
        label_fmax_ij->setText(QCoreApplication::translate("MainWindow", "FMax Ischio (N.kg-1)", nullptr));
        label_fmax_quadri->setText(QCoreApplication::translate("MainWindow", "FMax Quadriceps (N.kg-1)", nullptr));
        groupBox_controleGenou_g->setTitle(QCoreApplication::translate("MainWindow", "Controle du genou  ", nullptr));
        groupBox_2->setTitle(QString());
        radioButton_g_controleGenouValgus->setText(QCoreApplication::translate("MainWindow", "Valgus excessif du genou", nullptr));
        radioButton_g_controleGenouFrontal->setText(QCoreApplication::translate("MainWindow", "Bon controle du genou dans le plan frontal", nullptr));
        groupBox->setTitle(QString());
        radioButton_g_angleFlexionNOK->setText(QCoreApplication::translate("MainWindow", "R\303\251c\303\251ption avec angle de flexion insuffisant, mauvais amorti", nullptr));
        radioButton_g_angleFlexionOK->setText(QCoreApplication::translate("MainWindow", "R\303\251c\303\251ption avec angle de flexion suffisant, bon amorti", nullptr));
        groupBox_repartitionCharge_g->setTitle(QCoreApplication::translate("MainWindow", "Repartition de la charge au niveau du pied   ", nullptr));
        checkBox_g_receptionMedioPied->setText(QCoreApplication::translate("MainWindow", "Centr\303\251e au medio pied", nullptr));
        checkBox_g_receptionAvantPied->setText(QCoreApplication::translate("MainWindow", "R\303\251c\303\251ption exager\303\251e sur avant du pied", nullptr));
        checkBox_g_receptionBordInterne->setText(QCoreApplication::translate("MainWindow", "R\303\251c\303\251ption exager\303\251e sur le bord interne du pied", nullptr));
        checkBox_g_receptionTalon->setText(QCoreApplication::translate("MainWindow", "R\303\251c\303\251ption exager\303\251e sur le talon", nullptr));
        groupBox_troncBassin_g->setTitle(QCoreApplication::translate("MainWindow", "Controle du tronc/bassin   ", nullptr));
        radioButton_g_controleTroncOK->setText(QCoreApplication::translate("MainWindow", "Bon controle du tronc", nullptr));
        radioButton_g_controleTroncNOK->setText(QCoreApplication::translate("MainWindow", "Flexion ou inclinaison excessive du tronc", nullptr));
        label_test_dj->setText(QCoreApplication::translate("MainWindow", "Test Drop Jump Unipodal :", nullptr));
        label_opere_7->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_7->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_hauteur_saut_dj->setText(QCoreApplication::translate("MainWindow", "Hauteur de saut (cm)", nullptr));
        label_rfdmax_dj->setText(QCoreApplication::translate("MainWindow", "RFDmax (N.s)", nullptr));
        label_tps_contact_dj->setText(QCoreApplication::translate("MainWindow", "Temps contact (ms)", nullptr));
        label_test_cmj->setText(QCoreApplication::translate("MainWindow", "Test CMJ Unipodal :", nullptr));
        label_opere_6->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_6->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_hauteur_saut_cmj->setText(QCoreApplication::translate("MainWindow", "Hauteur de saut (cm)", nullptr));
        label_non_opere_16->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_opere_17->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_ration_ij_quadri_2->setText(QCoreApplication::translate("MainWindow", "Test Mc Call", nullptr));
        label_f30_mccall->setText(QCoreApplication::translate("MainWindow", "Force isom\303\251trique du genou \303\240 30\302\260 (N)", nullptr));
        label_f90_mccall->setText(QCoreApplication::translate("MainWindow", "Force isom\303\251trique du genou \303\240 90\302\260 (N)", nullptr));
        label_test_cmjB->setText(QCoreApplication::translate("MainWindow", "Test CMJ Bipodal :", nullptr));
        label_hauteur_saut_cmjB->setText(QCoreApplication::translate("MainWindow", "Hauteur de saut (cm)", nullptr));
        label_tps_stabilisation_cmj_2->setText(QCoreApplication::translate("MainWindow", "Temps mouvement (ms)", nullptr));
        label_fmax_cmjB->setText(QCoreApplication::translate("MainWindow", "RFD Deceleration opere  (N.s-1)", nullptr));
        label_RFDdeceleration->setText(QCoreApplication::translate("MainWindow", "RFD Deceleration non opere  (N.s-1)", nullptr));
        label_test_djB->setText(QCoreApplication::translate("MainWindow", "Test Drop Jump Bipodal :", nullptr));
        label_hauteur_saut_djB->setText(QCoreApplication::translate("MainWindow", "Hauteur de saut (cm)", nullptr));
        label_tps_vol_djB->setText(QCoreApplication::translate("MainWindow", "Temps vol (ms)", nullptr));
        label_tps_contact_djB->setText(QCoreApplication::translate("MainWindow", "Temps contact (ms)", nullptr));
        label_fmax_djB->setText(QCoreApplication::translate("MainWindow", "RFDmax opere (N.s)", nullptr));
        label_rfdmax_djB->setText(QCoreApplication::translate("MainWindow", "RFDmax non opere (N.s)", nullptr));
        label_axes->setText(QCoreApplication::translate("MainWindow", "Axes \303\240 am\303\251liorer :", nullptr));
        label_axes_2->setText(QCoreApplication::translate("MainWindow", "Interpr\303\251tation du kinesith\303\251rapeute :", nullptr));
        pushButton_validerRapport->setText(QCoreApplication::translate("MainWindow", "Valider le rapport", nullptr));
        toolButton_g->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_axes_3->setText(QCoreApplication::translate("MainWindow", "Ajout des annexes", nullptr));
        checkBox_g_tricepsSural->setText(QCoreApplication::translate("MainWindow", "Renforcement du triceps sural", nullptr));
        checkBox_g_excentriqueQuadri->setText(QCoreApplication::translate("MainWindow", "Renforcement excentrique quadriceps", nullptr));
        checkBox_g_concentriqueQuadri->setText(QCoreApplication::translate("MainWindow", "Renforcement concentrique quadriceps", nullptr));
        checkBox_g_ij->setText(QCoreApplication::translate("MainWindow", "Renforcement des ischios jambiers", nullptr));
        checkBox_g_renfoStabilisateurs->setText(QCoreApplication::translate("MainWindow", "Renforcement des muscles stabilisateurs lat\303\251raux (moyen fessiers et pelvi-trochanterien)", nullptr));
        checkBox_g_intrinseque->setText(QCoreApplication::translate("MainWindow", "Renforcement des muscles intrinseques stabilisateurs du pied", nullptr));
        checkBox_g_renforcementAdducteurs->setText(QCoreApplication::translate("MainWindow", "Renforcement des adducteurs", nullptr));
        checkBox_g_changementDirection->setText(QCoreApplication::translate("MainWindow", "Travail de changement de direction", nullptr));
        checkBox_g_plioHorizontaleAxe->setText(QCoreApplication::translate("MainWindow", "Travail de pliom\303\251trie horizontale dans l axe", nullptr));
        checkBox_g_plioVerticaleAxe->setText(QCoreApplication::translate("MainWindow", "Travail de pliom\303\251trie verticale dans l axe", nullptr));
        checkBox_g_plioMulti->setText(QCoreApplication::translate("MainWindow", "Travail de pliom\303\251trie multidirectionnelle", nullptr));
        checkBox_g_controleGenou->setText(QCoreApplication::translate("MainWindow", "Controle moteur du genou (controle du valgus dynamique)", nullptr));
        checkBox_g_controleComplexe->setText(QCoreApplication::translate("MainWindow", "Controle moteur du complexe lombo-pelvien", nullptr));
        checkBox_g_force->setText(QCoreApplication::translate("MainWindow", "Force", nullptr));
        checkBox_g_explosivite->setText(QCoreApplication::translate("MainWindow", "Explosivite", nullptr));
        checkBox_g_deceleration->setText(QCoreApplication::translate("MainWindow", "Travail de d\303\251c\303\251leration", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Pour mettre le texte en gras dans le rapport, mettre des crochets. Exemple : Le [genou] droit", nullptr));
        pushButton_annulerEditionBilan->setText(QCoreApplication::translate("MainWindow", "Annuler edition du bilan", nullptr));
        pushButton_annulerEditionRapport->setText(QCoreApplication::translate("MainWindow", "Annuler edition rapport", nullptr));
        label_nombreBilan->setText(QCoreApplication::translate("MainWindow", "Nombre de bilans faits: ", nullptr));
        label_testApprehension->setText(QCoreApplication::translate("MainWindow", "Test d instabilite anterieure", nullptr));
        comboBox_e_testInstabiliteA->setItemText(0, QCoreApplication::translate("MainWindow", "Apprehensions et douleurs", nullptr));
        comboBox_e_testInstabiliteA->setItemText(1, QCoreApplication::translate("MainWindow", "Pas d apprehension mais douloureux (EVA > 2)", nullptr));
        comboBox_e_testInstabiliteA->setItemText(2, QCoreApplication::translate("MainWindow", "Pas d apprehension mais genant (EVA < 2)", nullptr));
        comboBox_e_testInstabiliteA->setItemText(3, QCoreApplication::translate("MainWindow", "Pas d apprehension ni de douleur", nullptr));

        label_testRotationR1->setText(QCoreApplication::translate("MainWindow", "Test rotation RE/RI (R1)", nullptr));
        label_fmaxRIR1->setText(QCoreApplication::translate("MainWindow", "Fmax Rotateurs Internes (N.kg-1)", nullptr));
        label_opere_10->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_fmaxRER1->setText(QCoreApplication::translate("MainWindow", "Fmax Rotateurs Externes (N.kg-1)", nullptr));
        label_non_opere_10->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_testRotationR2->setText(QCoreApplication::translate("MainWindow", "Test rotation RE/RI (R2)", nullptr));
        label_fmaxRIR2->setText(QCoreApplication::translate("MainWindow", "Fmax Rotateurs Internes (N.kg-1)", nullptr));
        label_opere_11->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_fmaxRER2->setText(QCoreApplication::translate("MainWindow", "Fmax Rotateurs Externes (N.kg-1)", nullptr));
        label_non_opere_11->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_distanceSL->setText(QCoreApplication::translate("MainWindow", "Distance supero-laterale DSL (cm)", nullptr));
        label_opere_12->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_distanceM->setText(QCoreApplication::translate("MainWindow", "Distance mediale DM (cm)", nullptr));
        label_distanceIL->setText(QCoreApplication::translate("MainWindow", "Distance infero-laterale DIL (cm)", nullptr));
        label_non_opere_12->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_test_uqYbt->setText(QCoreApplication::translate("MainWindow", "Test UQ - YBT :", nullptr));
        label_testCkCuest->setText(QCoreApplication::translate("MainWindow", "Test CK - CUEST", nullptr));
        label_opere_13->setText(QCoreApplication::translate("MainWindow", "Valeur", nullptr));
        label_nbTouches->setText(QCoreApplication::translate("MainWindow", "Nombre de touches (N) ", nullptr));
        label_testSasspt->setText(QCoreApplication::translate("MainWindow", "Test SASSPT", nullptr));
        label_opere_14->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_14->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_distanceLancer->setText(QCoreApplication::translate("MainWindow", "Distance de lancer ( cm)", nullptr));
        label_testUlrt->setText(QCoreApplication::translate("MainWindow", "Test ULRT", nullptr));
        label_opere_15->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_15->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_nbRepetitions->setText(QCoreApplication::translate("MainWindow", "Nombre de repetitions", nullptr));
        label_kStart_3->setText(QCoreApplication::translate("MainWindow", "S-start", nullptr));
        label_siRsi->setText(QCoreApplication::translate("MainWindow", "Test SI - RSI", nullptr));
        label_sur_cent_3->setText(QCoreApplication::translate("MainWindow", "/ 100", nullptr));
        label_sur_cent_5->setText(QCoreApplication::translate("MainWindow", "/ 100", nullptr));
        pushButton_valider_bilan_epaule->setText(QCoreApplication::translate("MainWindow", "Valider le bilan", nullptr));
        label_amplitude_articulaire_2->setText(QCoreApplication::translate("MainWindow", "Amplitudes articulaires :", nullptr));
        label_opere_8->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_8->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_elevationAnterieure->setText(QCoreApplication::translate("MainWindow", "Elevation anterieure (\302\260)", nullptr));
        label_elevationLaterale->setText(QCoreApplication::translate("MainWindow", "Elevation laterale (\302\260)", nullptr));
        label_extensionE->setText(QCoreApplication::translate("MainWindow", "Extension (\302\260)", nullptr));
        label_adductionHorizontale->setText(QCoreApplication::translate("MainWindow", "Adduction horizontale (\302\260)", nullptr));
        label_rotationInterneR1->setText(QCoreApplication::translate("MainWindow", "Rotation interne R1  - epineuse de ", nullptr));
        label_rotationExterneR1->setText(QCoreApplication::translate("MainWindow", "Rotation externe R1 (\302\260) ", nullptr));
        label_rotationInterneR2->setText(QCoreApplication::translate("MainWindow", "Rotation interne R2 (\302\260) ", nullptr));
        label_rotationExterneR2->setText(QCoreApplication::translate("MainWindow", "Rotation externe R2 (\302\260) ", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(0, QCoreApplication::translate("MainWindow", "T1", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(1, QCoreApplication::translate("MainWindow", "T2", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(2, QCoreApplication::translate("MainWindow", "T3", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(3, QCoreApplication::translate("MainWindow", "T4", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(4, QCoreApplication::translate("MainWindow", "T5", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(5, QCoreApplication::translate("MainWindow", "T6", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(6, QCoreApplication::translate("MainWindow", "T7", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(7, QCoreApplication::translate("MainWindow", "T8", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(8, QCoreApplication::translate("MainWindow", "T9", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(9, QCoreApplication::translate("MainWindow", "T10", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(10, QCoreApplication::translate("MainWindow", "T11", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(11, QCoreApplication::translate("MainWindow", "T12", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(12, QCoreApplication::translate("MainWindow", "L1", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(13, QCoreApplication::translate("MainWindow", "L2", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(14, QCoreApplication::translate("MainWindow", "L3", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(15, QCoreApplication::translate("MainWindow", "L4", nullptr));
        comboBox_e_rotationInterneR1O->setItemText(16, QCoreApplication::translate("MainWindow", "L5", nullptr));

        comboBox_e_rotationInterneR1NO->setItemText(0, QCoreApplication::translate("MainWindow", "T1", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(1, QCoreApplication::translate("MainWindow", "T2", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(2, QCoreApplication::translate("MainWindow", "T3", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(3, QCoreApplication::translate("MainWindow", "T4", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(4, QCoreApplication::translate("MainWindow", "T5", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(5, QCoreApplication::translate("MainWindow", "T6", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(6, QCoreApplication::translate("MainWindow", "T7", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(7, QCoreApplication::translate("MainWindow", "T8", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(8, QCoreApplication::translate("MainWindow", "T9", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(9, QCoreApplication::translate("MainWindow", "T10", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(10, QCoreApplication::translate("MainWindow", "T11", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(11, QCoreApplication::translate("MainWindow", "T12", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(12, QCoreApplication::translate("MainWindow", "L1", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(13, QCoreApplication::translate("MainWindow", "L2", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(14, QCoreApplication::translate("MainWindow", "L3", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(15, QCoreApplication::translate("MainWindow", "L4", nullptr));
        comboBox_e_rotationInterneR1NO->setItemText(16, QCoreApplication::translate("MainWindow", "L5", nullptr));

        label_testGrip->setText(QCoreApplication::translate("MainWindow", "Test Grip", nullptr));
        label_opere_9->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_9->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_elevationAnterieure_2->setText(QCoreApplication::translate("MainWindow", "Fmax  (N.kg-1)", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Bras opere", nullptr));
        comboBox_e_brasOpere->setItemText(0, QCoreApplication::translate("MainWindow", "Droit", nullptr));
        comboBox_e_brasOpere->setItemText(1, QCoreApplication::translate("MainWindow", "Gauche", nullptr));

        label_testRotationR1_2->setText(QCoreApplication::translate("MainWindow", "PSET modifie", nullptr));
        label_fmaxRIR1_2->setText(QCoreApplication::translate("MainWindow", "Score W (s)", nullptr));
        label_opere_16->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_fmaxRER1_2->setText(QCoreApplication::translate("MainWindow", "Score Y (s)", nullptr));
        label_non_opere_13->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_testApprehension_2->setText(QCoreApplication::translate("MainWindow", "Test d instabilite posterieure", nullptr));
        comboBox_e_testInstabiliteP->setItemText(0, QCoreApplication::translate("MainWindow", "Apprehensions et douleurs", nullptr));
        comboBox_e_testInstabiliteP->setItemText(1, QCoreApplication::translate("MainWindow", "Pas d apprehension mais douloureux (EVA > 2)", nullptr));
        comboBox_e_testInstabiliteP->setItemText(2, QCoreApplication::translate("MainWindow", "Pas d apprehension mais genant (EVA < 2)", nullptr));
        comboBox_e_testInstabiliteP->setItemText(3, QCoreApplication::translate("MainWindow", "Pas d apprehension ni de douleur", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "Main dominante :", nullptr));
        comboBox_e_mainDominante->setItemText(0, QCoreApplication::translate("MainWindow", "Droite", nullptr));
        comboBox_e_mainDominante->setItemText(1, QCoreApplication::translate("MainWindow", "Gauche", nullptr));
        comboBox_e_mainDominante->setItemText(2, QCoreApplication::translate("MainWindow", "Ambidextre", nullptr));

        label_distanceM_2->setText(QCoreApplication::translate("MainWindow", "longueur bras (distance \303\251pineuse de C7 - extremit\303\251 du 3\303\250me doigt) :", nullptr));
        label_testRotationR1_3->setText(QCoreApplication::translate("MainWindow", "Test IYT (ASH Test)", nullptr));
        label_opere_18->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_17->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_fmaxRER1_3->setText(QCoreApplication::translate("MainWindow", "FMax I (180\302\260)", nullptr));
        label_fmaxRIR1_3->setText(QCoreApplication::translate("MainWindow", "FMax Y (135\302\260)", nullptr));
        label_fmaxRIR1_4->setText(QCoreApplication::translate("MainWindow", "FMax T (90\302\260)", nullptr));
        label_axes_4->setText(QCoreApplication::translate("MainWindow", "Axes \303\240 am\303\251liorer :", nullptr));
        label_axes_5->setText(QCoreApplication::translate("MainWindow", "Interpr\303\251tation du kinesith\303\251rapeute :", nullptr));
        pushButton_validerRapport_epaule->setText(QCoreApplication::translate("MainWindow", "Valider le rapport", nullptr));
        toolButton_e->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_axes_6->setText(QCoreApplication::translate("MainWindow", "Ajout des annexes", nullptr));
        checkBox_e_AugmenterAmplitudes->setText(QCoreApplication::translate("MainWindow", "Augmenter les amplitudes articulaires passives et actives (contr\303\264le moteur en fin d\342\200\231amplitude)", nullptr));
        checkBox_e_renfoExternes->setText(QCoreApplication::translate("MainWindow", "Renforcement  des rotateurs externes de l\342\200\231\303\251paule", nullptr));
        checkBox_e_renfoInternes->setText(QCoreApplication::translate("MainWindow", "Renforcement des rotateurs internes de l\342\200\231\303\251paule ", nullptr));
        checkBox_e_renfoTrapeze->setText(QCoreApplication::translate("MainWindow", "Renforcement du trap\303\250ze inferieur ", nullptr));
        checkBox_e_renfoDentele->setText(QCoreApplication::translate("MainWindow", "Renforcement du dentel\303\251 ant\303\251rieur ", nullptr));
        checkBox_e_forceGrip->setText(QCoreApplication::translate("MainWindow", "Force de grip", nullptr));
        checkBox_e_pousseeHorizontale->setText(QCoreApplication::translate("MainWindow", "Force de pouss\303\251e horizontale ", nullptr));
        checkBox_e_coiffeFixateur->setText(QCoreApplication::translate("MainWindow", "Travail endurance de la coiffe post\303\251rieure et des fixateurs de l\342\200\231omoplate", nullptr));
        checkBox_e_controleArme->setText(QCoreApplication::translate("MainWindow", "Contr\303\264le moteur et proprioceptif de l\342\200\231\303\251paule en position d\342\200\231arm\303\251 ", nullptr));
        checkBox_e_controleOverhead->setText(QCoreApplication::translate("MainWindow", "Contr\303\264le moteur et proprioceptif de l\342\200\231\303\251paule en position d\342\200\231overhead (bras au zenith) ", nullptr));
        checkBox_e_explosivite->setText(QCoreApplication::translate("MainWindow", "Explosivite", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Pour mettre le texte en gras dans le rapport, mettre des crochets. Exemple : Le [genou] droit", nullptr));
        pushButton_modifier_bilan->setText(QCoreApplication::translate("MainWindow", "Modifier le bilan", nullptr));
        label_perimetre_2->setText(QCoreApplication::translate("MainWindow", "Perimetres (cm) :", nullptr));
        label_opere_19->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_18->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_mollet_2->setText(QCoreApplication::translate("MainWindow", "Mollet", nullptr));
        label_sommet_rotule_dix_2->setText(QCoreApplication::translate("MainWindow", "Sommet  rotule +10", nullptr));
        label_sommet_rotule_vingt_2->setText(QCoreApplication::translate("MainWindow", "Sommet  rotule +20", nullptr));
        label_test_accroupissement_2->setText(QCoreApplication::translate("MainWindow", "Test d accroupissement", nullptr));
        comboBox_h_testAccroupissement->setItemText(0, QCoreApplication::translate("MainWindow", " Impossible", nullptr));
        comboBox_h_testAccroupissement->setItemText(1, QCoreApplication::translate("MainWindow", "Douloureux avec EVA > 2/10", nullptr));
        comboBox_h_testAccroupissement->setItemText(2, QCoreApplication::translate("MainWindow", "Genant avec EVA < 2/10 ", nullptr));
        comboBox_h_testAccroupissement->setItemText(3, QCoreApplication::translate("MainWindow", "Bon avec EVA = 0", nullptr));

        label_fmax_abducteurs_2->setText(QCoreApplication::translate("MainWindow", "FMax Abducteurs (N.kg-1)", nullptr));
        label_opere_20->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_ration_add_abb_2->setText(QCoreApplication::translate("MainWindow", "Ratio Adducteurs / Abducteurs", nullptr));
        label_non_opere_19->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_fmax_adducteurs_2->setText(QCoreApplication::translate("MainWindow", "FMax Adducteurs (N.kg-1)", nullptr));
        pushButton_valider_bilan_hanche->setText(QCoreApplication::translate("MainWindow", "Valider le bilan", nullptr));
        label_hauteur_saut_sj_2->setText(QCoreApplication::translate("MainWindow", "Hauteur de saut (cm)", nullptr));
        label_test_sjB_2->setText(QCoreApplication::translate("MainWindow", "Squat jump Bipodal :", nullptr));
        label_fmax_sj_2->setText(QCoreApplication::translate("MainWindow", "RFDmax genou opere (N.s)", nullptr));
        label_pmax_Sj_2->setText(QCoreApplication::translate("MainWindow", "RFDmax genou non opere (N.s)", nullptr));
        label_non_opere_20->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_opere_21->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_ration_ij_quadri_3->setText(QCoreApplication::translate("MainWindow", "Ratio Ischios Jambiers / Quadriceps :", nullptr));
        label_fmax_ij_2->setText(QCoreApplication::translate("MainWindow", "FMax Ischio (N.kg-1)", nullptr));
        label_fmax_quadri_2->setText(QCoreApplication::translate("MainWindow", "FMax Quadriceps (N.kg-1)", nullptr));
        groupBox_controleGenou_h->setTitle(QCoreApplication::translate("MainWindow", "Controle du genou  ", nullptr));
        groupBox_3->setTitle(QString());
        radioButton_h_controleGenouValgus->setText(QCoreApplication::translate("MainWindow", "Valgus excessif du genou", nullptr));
        radioButton_h_controleGenouFrontal->setText(QCoreApplication::translate("MainWindow", "Bon controle du genou dans le plan frontal", nullptr));
        groupBox_4->setTitle(QString());
        radioButton_h_angleFlexionNOK->setText(QCoreApplication::translate("MainWindow", "R\303\251c\303\251ption avec angle de flexion insuffisant, mauvais amorti", nullptr));
        radioButton_h_angleFlexionOK->setText(QCoreApplication::translate("MainWindow", "R\303\251c\303\251ption avec angle de flexion suffisant, bon amorti", nullptr));
        groupBox_repartitionCharge_h->setTitle(QCoreApplication::translate("MainWindow", "Repartition de la charge au niveau du pied   ", nullptr));
        checkBox_h_receptionMedioPied->setText(QCoreApplication::translate("MainWindow", "Centr\303\251e au medio pied", nullptr));
        checkBox_h_receptionAvantPied->setText(QCoreApplication::translate("MainWindow", "R\303\251c\303\251ption exager\303\251e sur avant du pied", nullptr));
        checkBox_h_receptionBordInterne->setText(QCoreApplication::translate("MainWindow", "R\303\251c\303\251ption exager\303\251e sur le bord interne du pied", nullptr));
        checkBox_h_receptionTalon->setText(QCoreApplication::translate("MainWindow", "R\303\251c\303\251ption exager\303\251e sur le talon", nullptr));
        groupBox_troncBassin_h->setTitle(QCoreApplication::translate("MainWindow", "Controle du tronc/bassin   ", nullptr));
        radioButton_h_controleTroncOK->setText(QCoreApplication::translate("MainWindow", "Bon controle du tronc", nullptr));
        radioButton_h_controleTroncNOK->setText(QCoreApplication::translate("MainWindow", "Flexion ou inclinaison excessive du tronc", nullptr));
        label_test_dj_2->setText(QCoreApplication::translate("MainWindow", "Test Drop Jump Unipodal :", nullptr));
        label_opere_22->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_21->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_hauteur_saut_dj_2->setText(QCoreApplication::translate("MainWindow", "Hauteur de saut (cm)", nullptr));
        label_rfdmax_dj_2->setText(QCoreApplication::translate("MainWindow", "RFDmax (N.s)", nullptr));
        label_tps_contact_dj_2->setText(QCoreApplication::translate("MainWindow", "Temps contact (ms)", nullptr));
        label_test_cmj_2->setText(QCoreApplication::translate("MainWindow", "Test CMJ Unipodal :", nullptr));
        label_opere_23->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_22->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_hauteur_saut_cmj_2->setText(QCoreApplication::translate("MainWindow", "Hauteur de saut (cm)", nullptr));
        label_non_opere_23->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_opere_24->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_ration_ij_quadri_4->setText(QCoreApplication::translate("MainWindow", "Test Mc Call", nullptr));
        label_f30_mccall_2->setText(QCoreApplication::translate("MainWindow", "Force isom\303\251trique du genou \303\240 30\302\260 (N)", nullptr));
        label_f90_mccall_2->setText(QCoreApplication::translate("MainWindow", "Force isom\303\251trique du genou \303\240 90\302\260 (N)", nullptr));
        label_test_cmjB_2->setText(QCoreApplication::translate("MainWindow", "Test CMJ Bipodal :", nullptr));
        label_hauteur_saut_cmjB_2->setText(QCoreApplication::translate("MainWindow", "Hauteur de saut (cm)", nullptr));
        label_tps_stabilisation_cmj_3->setText(QCoreApplication::translate("MainWindow", "Temps mouvement (ms)", nullptr));
        label_fmax_cmjB_2->setText(QCoreApplication::translate("MainWindow", "RFD Deceleration opere  (N.s-1)", nullptr));
        label_RFDdeceleration_2->setText(QCoreApplication::translate("MainWindow", "RFD Deceleration non opere  (N.s-1)", nullptr));
        label_test_djB_2->setText(QCoreApplication::translate("MainWindow", "Test Drop Jump Bipodal :", nullptr));
        label_hauteur_saut_djB_2->setText(QCoreApplication::translate("MainWindow", "Hauteur de saut (cm)", nullptr));
        label_tps_vol_djB_2->setText(QCoreApplication::translate("MainWindow", "Temps vol (ms)", nullptr));
        label_tps_contact_djB_2->setText(QCoreApplication::translate("MainWindow", "Temps contact (ms)", nullptr));
        label_fmax_djB_2->setText(QCoreApplication::translate("MainWindow", "RFDmax opere (N.s)", nullptr));
        label_rfdmax_djB_2->setText(QCoreApplication::translate("MainWindow", "RFDmax non opere (N.s)", nullptr));
        label_amplitude_articulaire_3->setText(QCoreApplication::translate("MainWindow", "Amplitude articulaire :", nullptr));
        label_opere_2->setText(QCoreApplication::translate("MainWindow", "Opere", nullptr));
        label_non_opere_2->setText(QCoreApplication::translate("MainWindow", "Non opere", nullptr));
        label_flexion_2->setText(QCoreApplication::translate("MainWindow", "Flexion (\302\260)", nullptr));
        label_extension_2->setText(QCoreApplication::translate("MainWindow", "Extension (\302\260)", nullptr));
        label_flexion_3->setText(QCoreApplication::translate("MainWindow", "Abduction (\302\260)", nullptr));
        label_flexion_7->setText(QCoreApplication::translate("MainWindow", "Adduction (\302\260)", nullptr));
        label_flexion_4->setText(QCoreApplication::translate("MainWindow", "Rotation Interne  (90 de flexion\302\260)", nullptr));
        label_flexion_5->setText(QCoreApplication::translate("MainWindow", "Rotation Externe  (90 de flexion\302\260)", nullptr));
        label_flexion_6->setText(QCoreApplication::translate("MainWindow", "Test Bent Knee Fall Out - BKFO (cm)", nullptr));
        label_axes_7->setText(QCoreApplication::translate("MainWindow", "Axes \303\240 am\303\251liorer :", nullptr));
        label_axes_8->setText(QCoreApplication::translate("MainWindow", "Interpr\303\251tation du kinesith\303\251rapeute :", nullptr));
        pushButton_validerRapport_hanche->setText(QCoreApplication::translate("MainWindow", "Valider le rapport", nullptr));
        toolButton_h->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_axes_9->setText(QCoreApplication::translate("MainWindow", "Ajout des annexes", nullptr));
        checkBox_h_tricepsSural->setText(QCoreApplication::translate("MainWindow", "Renforcement du triceps sural", nullptr));
        checkBox_h_excentriqueQuadri->setText(QCoreApplication::translate("MainWindow", "Renforcement excentrique quadriceps", nullptr));
        checkBox_h_concentriqueQuadri->setText(QCoreApplication::translate("MainWindow", "Renforcement concentrique quadriceps", nullptr));
        checkBox_h_ij->setText(QCoreApplication::translate("MainWindow", "Renforcement des ischios jambiers", nullptr));
        checkBox_h_renfoStabilisateurs->setText(QCoreApplication::translate("MainWindow", "Renforcement des muscles stabilisateurs lat\303\251raux (moyen fessiers et pelvi-trochanterien)", nullptr));
        checkBox_h_intrinseque->setText(QCoreApplication::translate("MainWindow", "Renforcement des muscles intrinseques stabilisateurs du pied", nullptr));
        checkBox_h_renforcementAdducteurs->setText(QCoreApplication::translate("MainWindow", "Renforcement des adducteurs", nullptr));
        checkBox_h_changementDirection->setText(QCoreApplication::translate("MainWindow", "Travail de changement de direction", nullptr));
        checkBox_h_plioHorizontaleAxe->setText(QCoreApplication::translate("MainWindow", "Travail de pliom\303\251trie horizontale dans l axe", nullptr));
        checkBox_h_plioVerticaleAxe->setText(QCoreApplication::translate("MainWindow", "Travail de pliom\303\251trie verticale dans l axe", nullptr));
        checkBox_h_plioMulti->setText(QCoreApplication::translate("MainWindow", "Travail de pliom\303\251trie multidirectionnelle", nullptr));
        checkBox_h_controleGenou->setText(QCoreApplication::translate("MainWindow", "Controle moteur du genou (controle du valgus dynamique)", nullptr));
        checkBox_h_controleComplexe->setText(QCoreApplication::translate("MainWindow", "Controle moteur du complexe lombo-pelvien", nullptr));
        checkBox_h_force->setText(QCoreApplication::translate("MainWindow", "Force", nullptr));
        checkBox_h_explosivite->setText(QCoreApplication::translate("MainWindow", "Explosivite", nullptr));
        checkBox_h_deceleration->setText(QCoreApplication::translate("MainWindow", "Travail de d\303\251c\303\251leration", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Pour mettre le texte en gras dans le rapport, mettre des crochets. Exemple : Le [genou] droit", nullptr));
        pushButton_annulerModificationBilan->setText(QCoreApplication::translate("MainWindow", "Annuler edition du bilan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
