#ifndef PASSMODAL_H
#define PASSMODAL_H

#include <QVariant>
#include <QObject>
#include <QList>
#include <QModelIndex>
#include <QAbstractListModel>
#include <QUrl>


class record
{
public:
   record(const QString &p_name,
               const QString &p_surname,
                 const QString &p_photo,
               const QString &p_friend_id);

   QString getName() const;
   QString getSurname() const;
   QString getPhoto() const;
   QString getId() const;

private:
   QString m_name;
   QString m_surname;
   QString m_photo;
   QString m_friend_id;
};


class recordsModal : public QAbstractListModel{
    //  класс QAbstractListModel обеспечивает
    // 1 по мимо хранения элементов модели в Qlist также
    // 2 Трансляцию строковых запросов QML в адреса (свойств и методов) С++
    // 3 Интерактивность и обновление QML-связанных view в qml посредстровам спец сигнальной системы
    Q_OBJECT
public:
    //должно быть столько индетефикаторов сколько свойсвта модели обьекта
    //нельзя начинать с 0 только с UserRole 256
    //
    enum enmRoles {
        FriendName = Qt::UserRole + 1,
        FriendSurname,//258
        FriendPhoto,//259
        Friend_id//260
    };
    recordsModal(QObject *parent = nullptr);

    void addItem(const record & newItem);// добавление айтема

    int rowCount(const QModelIndex & parent = QModelIndex()) const; // необходим чтобы автоматом определляли кол во жлементов и строили разметку

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;//необходим для получения данных обьекта index соотв заданному с помощью role свойству элемента
    QVariantMap get(int idx) const;//для выгрузки i-элемента списка целиком со всеми свойствами

    void clear();// очистка всего списка


 protected:
    QHash<int, QByteArray> roleNames() const;

 private:
   QList<record> m_items;

};







//class passModal
//{
//public:
//    passModal();
//};

#endif // PASSMODAL_H
