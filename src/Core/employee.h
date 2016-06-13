#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QMetaType>
#include <QSharedDataPointer>
#include "rmscore_shared.h"

namespace Rsl {
namespace MapService {

namespace Impl {
class EmployeeSharedRepresentation;
}

class RMS_CORE_SHARED Employee
{
public:
    Employee();
    Employee(const Employee &);
    Employee &operator=(const Employee &);
    ~Employee();

    int id() const;
    void setId(int);

    QString name() const;
    void setName(const QString &);

    bool isActive() const;
    void setActive(bool);

private:
    QSharedDataPointer<Impl::EmployeeSharedRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

Q_DECLARE_METATYPE(Rsl::MapService::Employee)

#endif // EMPLOYEE_H
