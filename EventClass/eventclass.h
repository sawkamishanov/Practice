#ifndef EVENTCLASS_H
#define EVENTCLASS_H

#include <iostream>
#include <vector>
#include <QString>

/**
 *  Абстрактный класс - "событие"
 */

class Event
{
public:
    Event() : name("-"), location("-"), information("-"), age("-"), data("-") {}
    virtual ~Event() {}      // Виртуальный деструктор

    // Сеттеры
    void setName(QString _name) { name = _name; }
    void setType(QString _type) { type = _type; }
    void setLocation(QString _location) { location = _location; }
    void setBriefInformation(QString _information) { information = _information; }
    void setAgeOfVisitor(QString _age) { age = _age; }
    void setDate(QString _data) { data = _data; }



    // Геттеры
    QString getName() const { return name; }
    QString getType() const { return type; }
    QString getLocation() const { return location; }
    QString getBriefInformation() const { return information; }
    QString getAgeOfVisitor() const { return age; }
    QString getDate() const { return data; }
private:
    QString name,
            type,
            location,
            information,
            age,
            data;
};
#endif // EVENTCLASS_H
