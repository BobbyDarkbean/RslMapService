#include <QSharedData>
#include <QString>
#include "rms_global.h"

#include "callnumber.h"

namespace Rsl {
namespace MapService {

namespace Impl {

class CallNumberSharedRepresentation : public QSharedData
{
public:
    CallNumberSharedRepresentation();

    int collection;
    QString rack;
    int shelf;
    QString position;

private:
    CallNumberSharedRepresentation &operator=(const CallNumberSharedRepresentation &) Q_DECL_EQ_DELETE;
};

CallNumberSharedRepresentation::CallNumberSharedRepresentation()
    : collection(Collection_Native)
    , rack()
    , shelf(ShelfNumberMinimum)
    , position()
{
}

} // namespace Impl

CallNumber::CallNumber()
    : m(new Impl::CallNumberSharedRepresentation)
{
}

CallNumber::CallNumber(const CallNumber &other)
    : m(other.m)
{
}

CallNumber &CallNumber::operator=(const CallNumber &other)
{
    m = other.m;
    return *this;
}

CallNumber::~CallNumber()
{
}

int CallNumber::collection() const
{ return m->collection; }

void CallNumber::setCollection(int value)
{ m->collection = value; }

QString CallNumber::rack() const
{ return m->rack; }

void CallNumber::setRack(const QString &value)
{ m->rack = value; }

int CallNumber::shelf() const
{ return m->shelf; }

void CallNumber::setShelf(int value)
{ m->shelf = value; }

QString CallNumber::position() const
{ return m->position; }

void CallNumber::setPosition(const QString &value)
{ m->position = value; }

bool operator==(const CallNumber &a, const CallNumber &b)
{
    return a.collection() == b.collection()
            && a.rack().localeAwareCompare(b.rack()) == 0
            && a.shelf() == b.shelf()
            && a.position().localeAwareCompare(b.position()) == 0;
}

bool operator!=(const CallNumber &a, const CallNumber &b)
{ return !(a == b); }

bool operator<(const CallNumber &a, const CallNumber &b)
{
    if (a.collection() == b.collection()) {
        int rackCompare = a.rack().localeAwareCompare(b.rack());
        if (rackCompare == 0) {
            if (a.shelf() == b.shelf())
                return a.position().localeAwareCompare(b.position()) < 0;
            return a.shelf() < b.shelf();
        }
        return rackCompare < 0;
    }
    return a.collection() < b.collection();
}

bool operator>(const CallNumber &a, const CallNumber &b)
{ return b < a; }

bool operator<=(const CallNumber &a, const CallNumber &b)
{ return !(b < a); }

bool operator>=(const CallNumber &a, const CallNumber &b)
{ return !(a < b); }

} // namespace MapService
} // namespace Rsl
