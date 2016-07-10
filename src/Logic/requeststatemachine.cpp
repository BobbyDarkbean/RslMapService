#include <QMap>
#include "rms_global.h"
#include "requeststates/requestdeliveredstate.h"
#include "requeststates/requestdenystate.h"
#include "requeststates/requestfillingstate.h"
#include "requeststates/requestpickupstate.h"
#include "requeststates/requestputonholdstate.h"
#include "requeststates/requestreturnedstate.h"

#include "requeststatemachine.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct RequestStateMachineRepresentation
{
    int state;
    QMap<int, RequestState *> states;
};

} // namespace Impl

RequestStateMachine::RequestStateMachine()
    : m(new Impl::RequestStateMachineRepresentation)
{
    m->states.insert(RequestStatus_Filling, new RequestFillingState);
    m->states.insert(RequestStatus_Pickup, new RequestPickupState);
    m->states.insert(RequestStatus_Delivered, new RequestDeliveredState);
    m->states.insert(RequestStatus_DenyDepartmentsOccupied, new RequestDenyState);
    m->states.insert(RequestStatus_DenyEmployeesOccupied, new RequestDenyState);
    m->states.insert(RequestStatus_DenyExhibitionOccupied, new RequestDenyState);
    m->states.insert(RequestStatus_DenyIlesOccupied, new RequestDenyState);
    m->states.insert(RequestStatus_DenyStock, new RequestDenyState);
    m->states.insert(RequestStatus_DenyNull, new RequestDenyState);
    m->states.insert(RequestStatus_Returned, new RequestReturnedState);
    m->states.insert(RequestStatus_PutOnHold, new RequestPutOnHoldState);
}

RequestStateMachine::~RequestStateMachine()
{
    qDeleteAll(m->states);
}

int RequestStateMachine::state() const
{ return m->state; }

void RequestStateMachine::setState(int requestState)
{ m->state = requestState; }

bool RequestStateMachine::canTransit(int requestState)
{
    RequestState *currentState = m->states.value(m->state, nullptr);
    if (!currentState)
        return false;

    return currentState->isTransitionEnabled(requestState);
}

} // namespace MapService
} // namespace Rsl
