#ifndef SIGNALTRIGGER_H
#define SIGNALTRIGGER_H

#include <QObject>
#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

class RMS_LOGIC_SHARED SignalTrigger : public QObject
{
    Q_OBJECT

public:
    explicit SignalTrigger(QObject *parent = 0);
    ~SignalTrigger();

    virtual void reset() = 0;
    virtual void call() = 0;

    void activate();

private:
    Q_DISABLE_COPY(SignalTrigger)
};

} // namespace MapService
} // namespace Rsl

#endif // SIGNALTRIGGER_H
