#include "defaultsignaltrigger.h"

namespace Rsl {
namespace MapService {

DefaultSignalTrigger::DefaultSignalTrigger(QObject *parent)
    : SignalTrigger(parent)
{
}

DefaultSignalTrigger::~DefaultSignalTrigger()
{
}

void DefaultSignalTrigger::reset()
{
    // do nothing
}

void DefaultSignalTrigger::call()
{
    emit activated();
}

} // namespace MapService
} // namespace Rsl
