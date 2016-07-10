#include "requestdeliveredstate.h"
#include "rms_global.h"

namespace Rsl {
namespace MapService {

RequestDeliveredState::RequestDeliveredState()
    : RequestState()
{
    m_transitionMap[RequestStatus_Filling] = false;
    m_transitionMap[RequestStatus_Pickup] = true;
    m_transitionMap[RequestStatus_Delivered] = true;
    m_transitionMap[RequestStatus_DenyDepartmentsOccupied] = false;
    m_transitionMap[RequestStatus_DenyEmployeesOccupied] = false;
    m_transitionMap[RequestStatus_DenyExhibitionOccupied] = false;
    m_transitionMap[RequestStatus_DenyIlesOccupied] = false;
    m_transitionMap[RequestStatus_DenyStock] = false;
    m_transitionMap[RequestStatus_DenyNull] = false;
    m_transitionMap[RequestStatus_Returned] = true;
    m_transitionMap[RequestStatus_PutOnHold] = true;
}

RequestDeliveredState::~RequestDeliveredState()
{
}

} // namespace MapService
} // namespace Rsl
