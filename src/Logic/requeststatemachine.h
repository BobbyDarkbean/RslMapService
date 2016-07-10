#ifndef REQUESTSTATEMACHINE_H
#define REQUESTSTATEMACHINE_H

#include <QScopedPointer>
#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

namespace Impl {
struct RequestStateMachineRepresentation;
}

class RMS_LOGIC_SHARED RequestStateMachine
{
public:
    RequestStateMachine();
    ~RequestStateMachine();

    int state() const;
    void setState(int requestState);
    bool canTransit(int requestState);

private:
    Q_DISABLE_COPY(RequestStateMachine)
    QScopedPointer<Impl::RequestStateMachineRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // REQUESTSTATEMACHINE_H
