#ifndef REQUESTDENYSTATE_H
#define REQUESTDENYSTATE_H

#include "requeststate.h"

namespace Rsl {
namespace MapService {

class RequestDenyState : public RequestState
{
public:
    RequestDenyState();
    ~RequestDenyState();
};

} // namespace MapService
} // namespace Rsl

#endif // REQUESTDENYSTATE_H
