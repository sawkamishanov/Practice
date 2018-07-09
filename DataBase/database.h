#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#include "EventClass/eventclass.h"

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "DataBase"
#define PATH_DATABASE       "C:/Users/alx-m/Documents/GitHub/Practice/DataBase/DataBase.db"

#define EVENT                  "EventTable"
#define MUSEUM                 "MuseumTable"
#define EVENT_NAME             "EventName"
#define EVENT_TYPE             "Type"
#define EVENT_LOCATION         "Location"
#define EVENT_INFORMATION      "Information"
#define EVENT_OFFICIAL_SITE    "OfficialSite"
#define EVENT_AGE              "Age"
#define EVENT_HOURS            "Hours"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    bool inserIntoEventTable(const QVariantList &data);

    QString getPathDB() { return pathDB; }
    QString getHostnameDB() { return hostname; }
    void setPathDB(QString _pathDB) { pathDB = _pathDB; }
    void setHostnameDB(QString _hostname) { hostname = _hostname; }

private:
    QSqlDatabase db;
    QString pathDB,
            hostname;
    Event event;

    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createEventTable();
};

#endif // DATABASE_H
