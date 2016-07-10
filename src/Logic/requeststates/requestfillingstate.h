#ifndef REQUESTFILLINGSTATE_H
#define REQUESTFILLINGSTATE_H

#include "requeststate.h"

namespace Rsl {
namespace MapService {

class RequestFillingState : public RequestState
{
public:
    RequestFillingState();
    ~RequestFillingState();
};

} // namespace MapService
} // namespace Rsl

#endif // REQUESTFILLINGSTATE_H
