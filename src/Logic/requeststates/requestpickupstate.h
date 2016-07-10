#ifndef REQUESTPICKUPSTATE_H
#define REQUESTPICKUPSTATE_H

#include "requeststate.h"

namespace Rsl {
namespace MapService {

class RequestPickupState : public RequestState
{
public:
    RequestPickupState();
    ~RequestPickupState();
};

} // namespace MapService
} // namespace Rsl

#endif // REQUESTPICKUPSTATE_H
