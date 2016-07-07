#ifndef DATAMODELFACADE_H
#define DATAMODELFACADE_H

#include <QScopedPointer>
#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

class CurrentRequestModel;
class CurrentUserModel;
class EmployeeModel;

namespace Impl {
struct DataModelFacadeRepresentation;
}

class RMS_LOGIC_SHARED DataModelFacade
{
public:
    DataModelFacade();
    ~DataModelFacade();

    CurrentRequestModel *currentRequestModel() const;
    CurrentUserModel *currentUserModel() const;
    EmployeeModel *employeeModel() const;

private:
    Q_DISABLE_COPY(DataModelFacade)
    QScopedPointer<Impl::DataModelFacadeRepresentation> m;
};

RMS_LOGIC_SHARED DataModelFacade *dataModelFacade();

} // namespace MapService
} // namespace Rsl

#endif // DATAMODELFACADE_H
