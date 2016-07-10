#include "requeststate.h"

namespace Rsl {
namespace MapService {

RequestState::~RequestState()
{
}

bool RequestState::isTransitionEnabled(int status)
{
    return m_transitionMap.value(status, false);
}

} // namespace MapService
} // namespace Rsl
