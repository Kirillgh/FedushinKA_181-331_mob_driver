#include "creasop.h"
#include "passmodal.h"
#include "aes.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QtWidgets/QApplication>
#include <QtGui/QClipboard>
#include <QDesktopServices>
#include <QJsonArray>
#include <QSaveFile>

Creasop::Creasop(QObject *QMLObject) : viewer(QMLObject)
{
    records_modal = new recordsModal();
}

bool Creasop::parseJson(QString pin, QString searchSubstring){
    QFile file(":/test/pass.txt");
    if( file.open( QIODevice::ReadOnly ) )
    {
        QByteArray bytes = file.readAll();
        file.close();
        //qDebug() << bytes;
        QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
        QString key(pin);
        QString iv(pin);
        QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
        QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
        QByteArray decodeText = encryption.decode(bytes, hashKey, hashIV);
        QByteArray decodedString = encryption.removePadding(decodeText);
        bytes = decodedString;
       // qDebug() << decodedString;


        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
        if( jsonError.error != QJsonParseError::NoError )
        {
            qDebug() << jsonError.errorString();
            qDebug() << "11111111111111";
            return false;
        }
        else if(document.isObject())
        {
            QJsonObject main = document.object();
            QJsonValue first = main.value("records");
            QJsonArray last = first.toArray();
            if (records_modal->rowCount() > 0) {
                records_modal->clear();
            }
            for(int i = 0; i < last.count(); i++){
                QJsonObject list = last.at(i).toObject();
                QString name = list.value("img").toString();
                QString surname = list.value("url").toString();
                QString friend_id = list.value("login").toString();
                QString photo = list.value("password").toString();

                //                QUrl photo = list.value("password").toString();
                //                qDebug() << photo;
                if (surname.contains(searchSubstring))
                    records_modal->addItem(record(name, surname, photo, friend_id));
            }
        }
    }
    return true;
}

void Creasop::copyToClipboard(int index, QString param, QString pin){
    QString data = records_modal->get(index).take(param).toString();

    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QString key(pin);
    QString iv(pin);
    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
    QByteArray encodeText = encryption.encode(data.toLocal8Bit(), hashKey, hashIV);
    QByteArray decodeText = encryption.decode(data.toLocal8Bit(), hashKey, hashIV);
    QString decodedString = QString(encryption.removePadding(decodeText));

    QFile file("C:/Users/Кирилл/Desktop/pass.txt");
    file.open(QIODevice::WriteOnly);
    file.write(encodeText);
    file.close();


    QApplication::clipboard()->setText(decodedString);

//    QFile file1(":/test/hhj.txt");
//    file1.open(QIODevice::ReadOnly);
//    QByteArray bytes = file1.readAll();
//    file1.close();

//    QByteArray encodeText = encryption.encode(bytes, hashKey, hashIV);
//    QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);
//    QString decodedString = QString(encryption.removePadding(decodeText));
//    QFile file("C:/Users/Кирилл/Desktop/pass.txt");
//    file.open(QIODevice::WriteOnly);
//    file.write(encodeText);
//    file.close();
}

void Creasop::openUrl(){
    QDesktopServices::openUrl(QUrl(";;;;;"));
}












