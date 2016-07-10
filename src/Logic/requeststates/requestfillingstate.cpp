#include "requestfillingstate.h"
#include "rms_global.h"

namespace Rsl {
namespace MapService {

RequestFillingState::RequestFillingState()
    : RequestState()
{
    m_transitionMap[RequestStatus_Filling] = true;
    m_transitionMap[RequestStatus_Pickup] = true;
    m_transitionMap[RequestStatus_Delivered] = false;
    m_transitionMap[RequestStatus_DenyDepartmentsOccupied] = false;
    m_transitionMap[RequestStatus_DenyEmployeesOccupied] = false;
    m_transitionMap[RequestStatus_DenyExhibitionOccupied] = false;
    m_transitionMap[RequestStatus_DenyIlesOccupied] = false;
    m_transitionMap[RequestStatus_DenyStock] = false;
    m_transitionMap[RequestStatus_DenyNull] = false;
    m_transitionMap[RequestStatus_Returned] = false;
    m_transitionMap[RequestStatus_PutOnHold] = true;
}

RequestFillingState::~RequestFillingState()
{
}

} // namespace MapService
} // namespace Rsl
