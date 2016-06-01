#ifndef EMPLOYEEDATAADAPTER_H
#define EMPLOYEEDATAADAPTER_H

#include <QScopedPointer>
#include "rmsdata_shared.h"

namespace Rsl {
namespace MapService {

class Employee;

namespace Impl {
struct EmployeeDataAdapterRepresentation;
}

class RMS_DATA_SHARED EmployeeDataAdapter
{
public:
    EmployeeDataAdapter();
    ~EmployeeDataAdapter();

    QList<Employee> select() const;
    bool insert(const Employee &);
    bool update(const Employee &);
    bool deleteById(int id);

private:
    Q_DISABLE_COPY(EmployeeDataAdapter)
    QScopedPointer<Impl::EmployeeDataAdapterRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // EMPLOYEEDATAADAPTER_H
