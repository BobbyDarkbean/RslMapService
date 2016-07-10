#ifndef REQUESTPUTONHOLDSTATE_H
#define REQUESTPUTONHOLDSTATE_H

#include "requeststate.h"

namespace Rsl {
namespace MapService {

class RequestPutOnHoldState : public RequestState
{
public:
    RequestPutOnHoldState();
    ~RequestPutOnHoldState();
};

} // namespace MapService
} // namespace Rsl

#endif // REQUESTPUTONHOLDSTATE_H
