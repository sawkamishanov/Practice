#ifndef MUSEUMCLASS_H
#define MUSEUMCLASS_H
#include "EventClass/eventclass.h"

class Museum
{
public:
    Museum()  {}
    Museum(const Museum&);
    Museum(Museum&&);
    ~Museum() {}
    void setType(QString _type) { type = _type; }
    void setOfficialSite(QString _site) { site = _site; }
    QString getType() const { return type; }
    QString getOfficialSite() const { return site; }
private:
    QString type,
            site;
};

#endif // MUSEUMCLASS_H
