#ifndef EVENTCLASS_H
#define EVENTCLASS_H

#include <iostream>
#include <string>

class Event
{
public:
    Event();
    virtual ~Event();       // Виртуальный деструктор

    // Сеттеры
    virtual void setName(std::string) = 0;
    virtual void setType(std::string) = 0;
    virtual void setLocation(std::string) = 0;
    virtual void setPrice(float) = 0;
    virtual void setBriefInformation(std::string) = 0;
    virtual void setOfficialSite(std::string) = 0;
    virtual void setAgeOfVisitor(short) = 0;
    virtual void setHours() = 0;

    // Геттеры
};


#endif // EVENTCLASS_H
