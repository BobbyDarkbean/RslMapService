#include "requestdenystate.h"
#include "rms_global.h"

namespace Rsl {
namespace MapService {

RequestDenyState::RequestDenyState()
    : RequestState()
{
    m_transitionMap[RequestStatus_Filling] = false;
    m_transitionMap[RequestStatus_Pickup] = false;
    m_transitionMap[RequestStatus_Delivered] = true;
    m_transitionMap[RequestStatus_DenyDepartmentsOccupied] = true;
    m_transitionMap[RequestStatus_DenyEmployeesOccupied] = true;
    m_transitionMap[RequestStatus_DenyExhibitionOccupied] = true;
    m_transitionMap[RequestStatus_DenyIlesOccupied] = true;
    m_transitionMap[RequestStatus_DenyStock] = true;
    m_transitionMap[RequestStatus_DenyNull] = true;
    m_transitionMap[RequestStatus_Returned] = false;
    m_transitionMap[RequestStatus_PutOnHold] = true;
}

RequestDenyState::~RequestDenyState()
{
}

} // namespace MapService
} // namespace Rsl
