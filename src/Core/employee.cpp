#include <QSharedData>
#include <QString>

#include "employee.h"

namespace Rsl {
namespace MapService {

namespace Impl {

class EmployeeSharedRepresentation : public QSharedData
{
public:
    EmployeeSharedRepresentation();

    int id;
    QString name;
    bool isActive;

private:
    EmployeeSharedRepresentation &operator=(const EmployeeSharedRepresentation &) Q_DECL_EQ_DELETE;
};

EmployeeSharedRepresentation::EmployeeSharedRepresentation()
    : id(0)
    , name()
    , isActive(false)
{
}

} // namespace Impl

Employee::Employee()
    : m(new Impl::EmployeeSharedRepresentation)
{
}

Employee::Employee(const Employee &other)
    : m(other.m)
{
}

Employee &Employee::operator=(const Employee &other)
{
    m = other.m;
    return *this;
}

Employee::~Employee()
{
}

int Employee::id() const
{ return m->id; }

void Employee::setId(int value)
{ m->id = value; }

QString Employee::name() const
{ return m->name; }

void Employee::setName(const QString &value)
{ m->name = value; }

bool Employee::isActive() const
{ return m->isActive; }

void Employee::setActive(bool value)
{ m->isActive = value; }

} // namespace MapService
} // namespace Rsl
