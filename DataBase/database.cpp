#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{
}

DataBase::~DataBase()
{
}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile(PATH_DATABASE DATABASE_NAME).exists())
        this->restoreDataBase();
    else
        this->openDataBase();
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase())
    {
        if(!this->createEventTable())
            return false;
        else
            return true;
    }
    else
    {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(PATH_DATABASE DATABASE_NAME);
    if  (db.open())
        return true;
    else
        return false;
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы устройств в базе данных
 * */
bool DataBase::createEventTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " EVENT " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            EVENT_NAME          " VARCHAR(255)    NOT NULL,"
                            EVENT_TYPE          " VARCHAR(16)     NOT NULL,"
                            EVENT_LOCATION      " VARCHAR(18)     NOT NULL,"
                            EVENT_INFORMATION   " VARCHAR(512)    NOT NULL,"
                            EVENT_OFFICIAL_SITE " VARCHAR(64)     NOT NULL,"
                            EVENT_AGE           " VARCHAR(3)      NOT NULL,"
                            EVENT_HOURS         " VARCHAR(10)     NOT NULL"
                        " )"
                    ))
    {
        qDebug() << "DataBase: error of create " << EVENT;
        qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;
    return false;
}

/* Метод для вставки записи в таблицу устройств
 * */
bool DataBase::inserIntoEventTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " EVENT " ( " EVENT_NAME ", "
                                             EVENT_TYPE ", "
                                             EVENT_LOCATION ", "
                                             EVENT_INFORMATION ", "
                                             EVENT_OFFICIAL_SITE ", "
                                             EVENT_AGE ", "
                                             EVENT_HOURS " ) "
                           "VALUES (:EventName, :Type, :Location, :Information, :OfficialSite, :Age, :Hours )");
                                              /*" VALUES (:" EVENT_NAME ", "
                                                      ": " EVENT_TYPE ", "
                                                      ": " EVENT_LOCATION ", "
                                                      ": " EVENT_INFORMATION ", "
                                                      ": " EVENT_OFFICIAL_SITE ", "
                                                      ": " EVENT_AGE ", "
                                                      ": " EVENT_HOURS ")");*/
    query.bindValue(":EventName",      data[0].toString());
    query.bindValue(":Type",           data[1].toString());
    query.bindValue(":Location",       data[2].toString());
    query.bindValue(":Information" ,   data[3].toString());
    query.bindValue(":OfficialSite" ,  data[4].toString());
    query.bindValue(":Age" ,           data[5].toString());
    query.bindValue(":Hours" ,         data[6].toString());

    // После чего выполняется запросом методом exec()
    if(!query.exec())
    {
        qDebug() << "error insert into " << EVENT;
        qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;
    return false;
}


