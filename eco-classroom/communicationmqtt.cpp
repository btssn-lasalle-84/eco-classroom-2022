#include "communicationmqtt.h"
#include <QDateTime>
#include <QMessageBox>
#include "salle.h"
#include "mesure.h"
#include <QDebug>

/**
 * @file communicationmqtt.cpp
 * @brief  Définition de la classe CommunicationMQTT
 * @author Zeryouhi Mohamed Amine
 * @version 0.2
 */

/**
 * @brief Constructeur de la classe CommunicationMQTT
 *
 * @fn CommunicationMQTT::CommunicationMQTT
 * @param parent L'adresse de l'objet parent
 */
CommunicationMQTT::CommunicationMQTT(QObject* parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    client = new QMqttClient(this);
    client->setHostname(BROKER_MQTT_HOSTNAME);
    client->setPort(BROKER_MQTT_PORT);

    connect(client, SIGNAL(connected()), this, SLOT(connecte()));
    connect(client, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(client,
            SIGNAL(messageReceived(const QByteArray&, const QMqttTopicName&)),
            this,
            SLOT(recevoir(const QByteArray&, const QMqttTopicName&)));

    connecter();
}

/**
 * @brief Destructeur de la classe CommunicationMQTT
 *
 * @fn CommunicationMQTT::~CommunicationMQTT
 * @details Libère les ressources
 */
CommunicationMQTT::~CommunicationMQTT()
{
    desabonner(QString(TOPIC_RACINE) + QString("/#")); // tous les sujets
    deconnecter();
    qDebug() << Q_FUNC_INFO;
}

void CommunicationMQTT::connecter()
{
    qDebug() << Q_FUNC_INFO;
    client->connectToHost();
}

void CommunicationMQTT::abonner(QString topic)
{
    qDebug() << Q_FUNC_INFO;
    QMqttSubscription* subscription = client->subscribe(topic);
    if(!subscription)
    {
        qDebug() << Q_FUNC_INFO << "erreur subscribe";
        return;
    }
}

void CommunicationMQTT::desabonner(QString topic)
{
    qDebug() << Q_FUNC_INFO;
    client->unsubscribe(topic);
}

void CommunicationMQTT::deconnecter()
{
    qDebug() << Q_FUNC_INFO;
    client->disconnectFromHost();
}

void CommunicationMQTT::recevoir(const QByteArray&     message,
                                 const QMqttTopicName& topic)
{
    qDebug() << Q_FUNC_INFO << QDateTime::currentDateTime().toString()
             << topic.name() << message;
    qDebug() << Q_FUNC_INFO << message.toInt() << message.toDouble();

    double temperature;
    int    humidite, co2, luminosite, indiceConfort, qualiteAir;

    QString nom = "";

    QStringList champs = topic.name().split("/");
    for(int i = 0; i < champs.size(); ++i)
    {
        qDebug() << Q_FUNC_INFO << champs.at(i);

        nom = champs.at(i);

        if(!champs.isEmpty())
        {
            nom           = topic.name();
            temperature   = message.toDouble();
            co2           = message.toInt();
            humidite      = message.toInt();
            indiceConfort = message.toInt();
            luminosite    = message.toInt();
            qualiteAir    = message.toInt();
        }
    }

    emit(temperature, humidite, co2, luminosite, indiceConfort, qualiteAir);

    /**
     * @brief La donnée brute reçue est dans la variable message
     */
    /**
     * @todo Extraire du topic le nom de la salle et le type de donnée reçue
     */
}

void CommunicationMQTT::connecte()
{
    qDebug() << Q_FUNC_INFO;
    abonner("salles/#");
}

void CommunicationMQTT::deconnecte()
{
    qDebug() << Q_FUNC_INFO;
}
