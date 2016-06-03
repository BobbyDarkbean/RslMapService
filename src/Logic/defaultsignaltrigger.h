#ifndef DEFAULTSIGNALTRIGGER_H
#define DEFAULTSIGNALTRIGGER_H

#include "signaltrigger.h"

namespace Rsl {
namespace MapService {

class RMS_LOGIC_SHARED DefaultSignalTrigger : public SignalTrigger
{
    Q_OBJECT

public:
    explicit DefaultSignalTrigger(QObject *parent = 0);
    ~DefaultSignalTrigger();

    void reset();
    void call();

signals:
    void activated();

private:
    Q_DISABLE_COPY(DefaultSignalTrigger)
};

} // namespace MapService
} // namespace Rsl

#endif // DEFAULTSIGNALTRIGGER_H
