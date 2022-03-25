#include "salle.h"
#include <QDebug>

/**
 * @file salle.cpp
 * @brief Définition de la classe Salle
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

/**
 * @brief Constructeur par défaut de la classe Salle
 *
 * @fn Salle::Salle
 */
Salle::Salle() :
    nom(""), lieu(""), description(""), surface(0), indiceConfort(""), code(""),
    etatFenetres(false), etatLumieres(false)
{
    qDebug() << Q_FUNC_INFO;
}

Salle::Salle(QStringList salle) :
    salle(salle), nom(""), lieu(""), description(""), surface(0),
    indiceConfort(""), code(""), etatFenetres(false), etatLumieres(false)
{
    qDebug() << Q_FUNC_INFO << salle;
    nom           = salle.at(TABLE_SALLE_NOM);
    description   = salle.at(TABLE_SALLE_DESCRIPTION);
    indiceConfort = salle.at(TABLE_SALLE_INDICE_DE_CONFORT);
}

/**
 * @brief Destructeur de la classe Salle
 *
 * @fn Salle::~Salle
 * @details Libère les ressources
 */
Salle::~Salle()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Retourne les données de la salle
 * @return QStringList
 */
QStringList Salle::getSalle() const
{
    return salle;
}

/**
 * @brief Salle::getNom
 * @return
 */
QString Salle::getNom() const
{
    return nom;
}

/**
 * @brief Salle::getLieu
 * @return
 */
QString Salle::getLieu() const
{
    return lieu;
}

/**
 * @brief Salle::getDesciption
 * @return
 */
QString Salle::getDesciption() const
{
    return description;
}

/**
 * @brief Salle::getSurface
 * @return
 */
int Salle::getSurface() const
{
    return surface;
}

/**
 * @brief Salle::getIndiceConfort
 * @return
 */
QString Salle::getIndiceConfort() const
{
    return indiceConfort;
}

/**
 * @brief Salle::getCode
 * @return
 */
QString Salle::getCode() const
{
    return code;
}

/**
 * @brief Salle::getEtatFenetres
 * @return
 */
bool Salle::getEtatFenetres() const
{
    return etatFenetres;
}

/**
 * @brief Salle::getEtatLumierres
 * @return
 */
bool Salle::getEtatLumierres() const
{
    return etatLumieres;
}
