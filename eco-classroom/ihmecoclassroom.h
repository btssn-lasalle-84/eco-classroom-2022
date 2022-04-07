#ifndef IHMECOCLASSROOM_H
#define IHMECOCLASSROOM_H

/**
 * @file ihmecoclassroom.h
 * @brief Déclaration de la classe IHMEcoClassroom
 * @author Zeryouhi Mohamed Amine
 * @version 0.2
 */

#include <QtWidgets>

/**
 * @def NOM_APPLICATION
 * @brief Le nom de l'application
 */
#define NOM_APPLICATION "Eco-Classroom"

/**
 * @def VERSION_APPLICATION
 * @brief La version de l'application
 */
#define VERSION "0.2"

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMEcoClassroom;
}

class BaseDeDonnees;
QT_END_NAMESPACE

/**
 * @class IHMEcoClassroom
 * @brief Déclaration de la classe IHMEcoClassroom
 * @details Cette classe s'occupe de l'affichage de la fenêtre principale
 */
class IHMEcoClassroom : public QMainWindow
{
    Q_OBJECT

  public:
    IHMEcoClassroom(QWidget* parent = nullptr);
    ~IHMEcoClassroom();

  private:
    Ui::IHMEcoClassroom* ui; //!< La fenêtre graphique associée à cette classe
    BaseDeDonnees*       baseDeDonnees; //!< Base de donnes
    QStringList          nomColonnes;   //!< Liste de nom des colonnes
    int                  nbLignesSalle; //!< Nombre de lignes
    QVector<QStringList> salles;        //!< Les salles
    QStandardItemModel*  modeleSalle;   //!< Modèle pour le QTableView
    int salleSelectionnee; //!< L'indice de la salle sélectionnée à éditer sinon
                           // -1

    /**
     * @enum Fenetre
     * @brief Définit les différentes fenêtres de l'IHM
     *
     */
    enum Fenetre
    {
        Fenetre1 = 0,
        Fenetre2,
        Fenetre3,
        NbFenetres
    };

    /**
     * @enum ColonneSalle
     * @brief Définit les différentes colonne du QTableView
     */
    enum ColonneSalle
    {
        COLONNE_SALLE_NOM,               //!< Emplacement de nom
        COLONNE_SALLE_DESCRIPTION,       //!< Emplacement de description
        COLONNE_SALLE_INDICE_DE_CONFORT, //!< Emplacement d'indice de confort
        COLONNE_SALLE_QUALITE_AIR, //!< Emplacement d'indice de qualité d'air
        COLONNE_SALLE_FENETRES,    //!< Emplacement des fenétres
        COLONNE_SALLE_LUMIERES,    //!< Emplacement des lumières
        NB_COLONNES
    };

    void initialiserAffichage();
    void ajouterMenuAide();
    void gererEvenements();

  public slots:
    void chargerSalles();
    void afficherSalleTable(QStringList salle);
    void effacerTableSalles();
    void selectionner(QModelIndex index);
    void verifierCode();
    void afficherFenetre(IHMEcoClassroom::Fenetre fenetre);
    void afficherFenetrePrincipale();
    void afficherFenetrePrecedent();
    void afficherAPropos();
};

#endif // IHMECOCLASSROOM_H
