#include <QSharedData>
#include <QString>
#include "rms_global.h"

#include "user.h"

namespace Rsl {
namespace MapService {

namespace Impl {

class UserSharedRepresentation : public QSharedData
{
public:
    UserSharedRepresentation();

    int hallNumber;
    int cardNumber;
    QString name;
    bool isOff;

private:
    UserSharedRepresentation &operator=(const UserSharedRepresentation &) Q_DECL_EQ_DELETE;
};

UserSharedRepresentation::UserSharedRepresentation()
    : hallNumber(ReadingHall_Unspecified)
    , cardNumber(0)
    , name()
    , isOff(false)
{
}

} // namespace Impl

User::User()
    : m(new Impl::UserSharedRepresentation)
{
}

User::User(const User &other)
    : m(other.m)
{
}

User &User::operator=(const User &other)
{
    m = other.m;
    return *this;
}

User::~User()
{
}

int User::hallNumber() const
{ return m->hallNumber; }

void User::setHallNumber(int value)
{ m->hallNumber = value; }

int User::cardNumber() const
{ return m->cardNumber; }

void User::setCardNumber(int value)
{ m->cardNumber = value; }

QString User::name() const
{ return m->name; }

void User::setName(const QString &value)
{ m->name = value; }

bool User::isOff() const
{ return m->isOff; }

void User::setOff(bool value)
{ m->isOff = value; }

} // namespace MapService
} // namespace Rsl
