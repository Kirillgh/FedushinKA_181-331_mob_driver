#include "passmodal.h"
#include <QMap>
#include <QDebug>


record::record(const QString &getName, const QString &getSurname, const QString &getPhoto, const QString &getId)
    :   m_name(getName),
        m_surname(getSurname),
        m_photo(getPhoto),
        m_friend_id(getId)
{
 //
}

recordsModal::recordsModal(QObject *parent) : QAbstractListModel(parent)
{
    //пусто
}

QString record::getName() const{ // функция для получения имени друга
    return m_name;
}

QString record::getSurname() const{ // функция для получения фамилии друга
    return m_surname;
}

QString record::getPhoto() const{ // функция для получения фото друга
    return m_photo;
}

QString record::getId() const{ // функция для получения id друга
    return m_friend_id;
}

void recordsModal::addItem(const record & newItem){
    // не изменяется
  // благодаря beginInsertRows() и endInsertRows() QML реагирует на изменения модели
    //ЧАСТЬ сигнальной системы уведомлений qml об изменениях модели и переде  в qml на какую позицию и сколько элементов вставляется
    beginInsertRows(QModelIndex(), //по умолчанию
                    rowCount(), //номер строки вставки
                    rowCount());// номер строки концу вставляемого участка
    m_items << newItem;// вставка нового элемента данных
    // сообзает listview о том что изменение модели закончено и можно обновить
    endInsertRows();
}

int recordsModal::rowCount(const QModelIndex &parent) const
{
    // не изменяется
   // метод используется ListView в QML для определения числа элементов
    Q_UNUSED(parent); // макрос который скрыввает сообзение qt о тоом что параметр не использется
    return m_items.count(); //возвращает кол во элементов в списке
}

QVariant recordsModal::data(const QModelIndex & index,
                                int role) const
{
     // метод используется в QML для получения значения одного поля под обозначением role одного элемента модели index
    //проверка на поппадание в список
    if (index.row() < 0 || (index.row() >= m_items.count()))
        return QVariant();//обертка

  //получение ссылки на обьект с нужным индексом
    const record&itemToReturn = m_items[index.row()];
    //получение значения нужного поля выбранного обьекта
    if (role == FriendName)
    return itemToReturn.getName(); //при любом return этой функции значение преобразуется в QVariant
    else if (role == FriendSurname)
    return itemToReturn.getSurname();
    else if (role == FriendPhoto)
    return itemToReturn.getPhoto();
    else if (role == Friend_id)
    return itemToReturn.getId();

    return QVariant();
}

QHash<int, QByteArray> recordsModal::roleNames() const
{
    // метод используется в QML для сопоставления полей данных со строковыми названиями
     // TODO сопоставить полям данных строковые имена
    //метод отвечает за конвертацию за заполнение словаря "стрококвое_имя":роль
    QHash<int, QByteArray> roles;//обьяляется хэш таблица

    roles[FriendName] = "name"; // строка будет в таком виде выхываться в qml
    roles[FriendSurname] = "surname";
    roles[FriendPhoto] = "photo";//
    roles[Friend_id] = "friend_id";//
    return roles;
}

QVariantMap recordsModal::get(int idx) const
{
    // не изменяется
   // метод используется ListView в QML для получения значений полей idx-го элемента модели
    //формирует выгрузку всех полей элемента списка под номером idx
    //QVariantMap {"роль":"значение"}
    QVariantMap map; //словарь
    foreach(int k, roleNames().keys())
    {
        map[roleNames().value(k)] = data(index(idx, 0), k);//выгружаются данные  слвать
    }
    return map;//
}

void recordsModal::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);//аналагичнов в additem
    m_items.clear();//сообственно удаление элементов списка
    endRemoveRows();
}










