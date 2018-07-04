#ifndef MUSEUMCLASS_H
#define MUSEUMCLASS_H
#include "EventClass/eventclass.h"

class Musem : public Event
{
public:
    Musem() : name(0), type(0), location(0), price(0), information(0) {}
    Musem(const Musem&);
    Musem(Musem&&);
    ~Musem();
private:
    std::string name;
    std::string type;
    std::string location;
    float price;
    std::string information;
};

#endif // MUSEUMCLASS_H
