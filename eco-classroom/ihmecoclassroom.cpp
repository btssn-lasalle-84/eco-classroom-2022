#include "ihmecoclassroom.h"
#include "ui_ihmecoclassroom.h"
#include "basededonnees.h"
#include "salle.h"
#include "mesure.h"
#include <QDebug>

/**
 * @file ihmecoclassroom.cpp
 * @brief Définition de la classe IHMEcoClassroom
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe IHMEcoClassroom
 *
 * @fn IHMEcoClassroom::IHMEcoClassroom
 * @param parent L'adresse de l'objet parent, si nullptr IHMEcoClassroom sera la
 * fenêtre principale de l'application
 */
IHMEcoClassroom::IHMEcoClassroom(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMEcoClassroom), nbLignesSalle(0)
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);
    baseDeDonnees = BaseDeDonnees::getInstance();
    baseDeDonnees->ouvrir("/home/zeryouhi/Téléchargements/eco-classroom.db");
    ajouterMenuAide();
    initialiserAffichage();

    gererEvenements();
}

/**
 * @brief Destructeur de la classe IHMEcoClassroom
 *
 * @fn IHMEcoClassroom::~IHMEcoClassroom
 * @details Libère les ressources de l'application
 */
IHMEcoClassroom::~IHMEcoClassroom()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

void IHMEcoClassroom::initialiserAffichage()
{
    qDebug() << Q_FUNC_INFO;
    ui->statusbar->showMessage(QString::fromUtf8(NOM_APPLICATION) + " " +
                               QString::fromUtf8(VERSION));

    // Initialise le QTableView pour les salles
    nomColonnes << "Nom"
                << "Description"
                << "Indice de confort"
                << "Fenêtres"
                << "Lumières";
    modeleSalle = new QStandardItemModel(0, nomColonnes.size());
    modeleSalle->setHorizontalHeaderLabels(nomColonnes);
    ui->tableViewSalles->setModel(modeleSalle);
    ui->tableViewSalles->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewSalles->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
    nbLignesSalle = modeleSalle->rowCount();

    chargerSalles();
    afficherFenetre(IHMEcoClassroom::Fenetre1);
}

/**
 * @brief assla connexion des signaux et slots
 *
 * @fn IHMEcoClassroom::gererEvenements()
 */
void IHMEcoClassroom::gererEvenements()
{
    qDebug() << Q_FUNC_INFO;
    connect(ui->boutonCharger,
            SIGNAL(clicked(bool)),
            this,
            SLOT(chargerSalles()));
    connect(ui->boutonEffacer,
            SIGNAL(clicked(bool)),
            this,
            SLOT(effacerTableSalles()));
    connect(ui->tableViewSalles,
            SIGNAL(clicked(QModelIndex)),
            this,
            SLOT(selectionner(QModelIndex)));
    connect(ui->buttonAccueil,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherFenetrePrincipale()));
}

/**
 * @brief Charge les données des salles dans le QTableView
 *
 * @fn IHMEcoClassroom::chargerSalles
 */
void IHMEcoClassroom::chargerSalles()
{
    effacerTableSalles();

    QString requete = "SELECT * FROM Salle";
    bool    retour;

    retour = baseDeDonnees->recuperer(requete, salles);
    qDebug() << Q_FUNC_INFO << retour;
    qDebug() << Q_FUNC_INFO << salles;
    for(int i = 0; i < salles.size(); ++i)
        afficherSalleTable(salles.at(i));
}

/**
 * @brief Affiche les données d'une salle dans le QTableView
 *
 * @fn IHMEcoClassroom::afficherSalleTable
 * @param salle Les informations sur une salle
 */
void IHMEcoClassroom::afficherSalleTable(QStringList salle)
{
    qDebug() << Q_FUNC_INFO << salle;

    // Crée les items pour les cellules d'une ligne
    QStandardItem* nom = new QStandardItem(salle.at(Salle::NOM));
    QStandardItem* description =
      new QStandardItem(salle.at(Salle::DESCRIPTION));
    QStandardItem* indiceDeConfort =
      new QStandardItem(salle.at(Salle::INDICE_DE_CONFORT));
    QStandardItem* fenetres =
      new QStandardItem(salle.at(Salle::ETAT_DES_FENETRES));
    QStandardItem* lumieres =
      new QStandardItem(salle.at(Salle::ETAT_DES_LUMIERES));

    // Ajoute les items dans le modèle de données
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_NOM,
                         nom);
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_DESCRIPTION,
                         description);
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_INDICE_DE_CONFORT,
                         indiceDeConfort);
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_FENETRES,
                         fenetres);
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_LUMIERES,
                         lumieres);

    // Personnalise l'affichage d'une ligne
    QFont texte;
    texte.setPointSize(12);
    texte.setBold(true);
    for(int i = 0; i < nomColonnes.size(); ++i)
    {
        QStandardItem* item = modeleSalle->item(nbLignesSalle, i);
        item->setBackground(QColor(255, 223, 0));
        item->setFont(texte);
    }

    // Incrémente le nombre de lignes
    qDebug() << Q_FUNC_INFO << "nbLignesUtilisateurs" << nbLignesSalle;
    nbLignesSalle += 1;

    // Configure l'affichage du QTableView
    ui->tableViewSalles->setSizePolicy(QSizePolicy::Minimum,
                                       QSizePolicy::Minimum);
    ui->tableViewSalles->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableViewSalles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableViewSalles->setFixedHeight(
      ui->tableViewSalles->verticalHeader()->length() +
      ui->tableViewSalles->horizontalHeader()->height());
}

/**
 * @brief Efface les salles du QTableView
 *
 * @fn IHMEcoClassroom::effacerTableSalles
 */
void IHMEcoClassroom::effacerTableSalles()
{
    qDebug() << Q_FUNC_INFO;
  
    salles.clear();
    modeleSalle->clear();
    modeleSalle->setHorizontalHeaderLabels(nomColonnes);
    ui->tableViewSalles->setModel(modeleSalle);
    nbLignesSalle = 0;
}

void IHMEcoClassroom::selectionner(QModelIndex index)
{
    qDebug() << Q_FUNC_INFO << index.row(); // le numéro de ligne
    qDebug() << Q_FUNC_INFO
             << index.data().toString(); // le contenu de la cellule
    qDebug() << Q_FUNC_INFO << modeleSalle->item(index.row(), 0)->text(); //
    qDebug() << Q_FUNC_INFO << salles.at(index.row());

    ui->labelNom->setText(salles.at(index.row()).at(Salle::NOM));
    ui->labelLieu->setText(salles.at(index.row()).at(Salle::LIEU));
    ui->labelDescription->setText(
      salles.at(index.row()).at(Salle::DESCRIPTION));
    ui->labelSurface->setText(salles.at(index.row()).at(Salle::SUPERFICIE));
    ui->labelAir->setText(
      salles.at(index.row()).at(Salle::LIBELLE_QUALITE_AIR));
    ui->labelIndicDeConfort->setText(
      salles.at(index.row()).at(Salle::INDICE_DE_CONFORT));
    ui->labelCo2->setText(salles.at(index.row()).at(Mesure::CO2));
    ui->labelTemperateur->setText(
      salles.at(index.row()).at(Mesure::TEMPERATEUR));

    // Affiche la fenêtre associée
    afficherFenetre(IHMEcoClassroom::Fenetre2);
}

/**
 * @brief Méthode qui permet d'afficher une fenêtre de la pile
 * QStackedWidget
 *
 * @fn IHMEcoClassroom::afficherFenetre
 * @param fenetre le numéro de fenêtre à afficher
 */
void IHMEcoClassroom::afficherFenetre(IHMEcoClassroom::Fenetre fenetre)
{
    qDebug() << Q_FUNC_INFO << "fenetre" << fenetre;
    ui->fenetres->setCurrentIndex(fenetre);
}

/**
 * @brief Affiche la première fenêtre
 *
 * @fn IHMEcoClassroom:afficherFenetrePrincipale
 */
void IHMEcoClassroom::afficherFenetrePrincipale()
{
    qDebug() << Q_FUNC_INFO;
    afficherFenetre(IHMEcoClassroom::Fenetre1);
}

void IHMEcoClassroom::ajouterMenuAide()
{
    qDebug() << Q_FUNC_INFO;
    QMenu* menuAide = new QMenu(QString::fromUtf8("&Aide"), this);
    menuBar()->addMenu(menuAide);

    menuAide->addAction(QString::fromUtf8("À propos ") +
                          QString::fromUtf8(NOM_APPLICATION),
                        this,
                        SLOT(afficherAPropos()));
    menuAide->addAction(QString::fromUtf8("À propos de Qt"),
                        qApp,
                        SLOT(aboutQt()));
}

void IHMEcoClassroom::afficherAPropos()
{
    QMessageBox::about(
      this,
      QString::fromUtf8("À propos ..."),
      QString::fromUtf8("<p><b>") + QString::fromUtf8(NOM_APPLICATION) + " " +
        QString::fromUtf8(VERSION) + QString::fromUtf8("</b><br/>...</p>"));
}
