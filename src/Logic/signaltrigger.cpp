#include "signaltrigger.h"

namespace Rsl {
namespace MapService {

SignalTrigger::SignalTrigger(QObject *parent)
    : QObject(parent)
{
}

SignalTrigger::~SignalTrigger()
{
}

void SignalTrigger::activate()
{
    call();
    reset();
}

} // namespace MapService
} // namespace Rsl
