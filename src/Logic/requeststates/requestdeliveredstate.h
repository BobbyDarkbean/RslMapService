#ifndef REQUESTDELIVEREDSTATE_H
#define REQUESTDELIVEREDSTATE_H

#include "requeststate.h"

namespace Rsl {
namespace MapService {

class RequestDeliveredState : public RequestState
{
public:
    RequestDeliveredState();
    ~RequestDeliveredState();
};

} // namespace MapService
} // namespace Rsl

#endif // REQUESTDELIVEREDSTATE_H
