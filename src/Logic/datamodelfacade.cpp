#include "itemmodels/currentrequestmodel.h"
#include "itemmodels/currentusermodel.h"
#include "itemmodels/employeemodel.h"

#include "datamodelfacade.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct DataModelFacadeRepresentation
{
    CurrentRequestModel currentRequestModel;
    CurrentUserModel currentUserModel;
    EmployeeModel employeeModel;
};

} // namespace Impl

DataModelFacade &dataModelFacadeInstance()
{
    static DataModelFacade dataModelFacade;
    return dataModelFacade;
}

DataModelFacade::DataModelFacade()
    : m(new Impl::DataModelFacadeRepresentation)
{
}

DataModelFacade::~DataModelFacade()
{
}

CurrentRequestModel *DataModelFacade::currentRequestModel() const
{
    return &m->currentRequestModel;
}

CurrentUserModel *DataModelFacade::currentUserModel() const
{
    return &m->currentUserModel;
}

EmployeeModel *DataModelFacade::employeeModel() const
{
    return &m->employeeModel;
}

DataModelFacade *dataModelFacade()
{
    return &dataModelFacadeInstance();
}

} // namespace MapService
} // namespace Rsl
