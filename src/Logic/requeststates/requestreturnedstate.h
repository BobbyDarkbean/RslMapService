#ifndef REQUESTRETURNEDSTATE_H
#define REQUESTRETURNEDSTATE_H

#include "requeststate.h"

namespace Rsl {
namespace MapService {

class RequestReturnedState : public RequestState
{
public:
    RequestReturnedState();
    ~RequestReturnedState();
};

} // namespace MapService
} // namespace Rsl

#endif // REQUESTRETURNEDSTATE_H
