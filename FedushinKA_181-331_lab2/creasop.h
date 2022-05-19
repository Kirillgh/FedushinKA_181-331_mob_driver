#ifndef CREASOP_H
#define CREASOP_H

#include <QObject>
#include "passmodal.h"

class Creasop : public QObject
{
    Q_OBJECT
public:
    explicit Creasop(QObject *parent = nullptr);
    recordsModal *records_modal;
public slots:
    bool parseJson(QString pin, QString searchSubstring);
    void copyToClipboard(int index, QString param, QString pin);
    void openUrl();



signals:

protected:

QObject *viewer;


};

#endif // CREASOP_H

