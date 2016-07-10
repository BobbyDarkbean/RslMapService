#ifndef REQUESTSTATE_H
#define REQUESTSTATE_H

#include <QMap>

namespace Rsl {
namespace MapService {

class RequestState
{
public:
    virtual ~RequestState() = 0;
    bool isTransitionEnabled(int status);

protected:
    QMap<int, bool> m_transitionMap;
};

} // namespace MapService
} // namespace Rsl

#endif // REQUESTSTATE_H
