#include "employeeeditedsignaltrigger.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct EmployeeEditedSignalTriggerRepresentation
{
    void reinit();

    bool accepted;
};

void EmployeeEditedSignalTriggerRepresentation::reinit()
{
    accepted = false;
}

} // namespace Impl

EmployeeEditedSignalTrigger::EmployeeEditedSignalTrigger(QObject *parent)
    : SignalTrigger(parent)
    , m(new Impl::EmployeeEditedSignalTriggerRepresentation)
{
    m->reinit();
}

EmployeeEditedSignalTrigger::~EmployeeEditedSignalTrigger()
{
}

bool EmployeeEditedSignalTrigger::accepted() const
{ return m->accepted; }

void EmployeeEditedSignalTrigger::setAccepted(bool value)
{ m->accepted = value; }

void EmployeeEditedSignalTrigger::reset()
{
    m->reinit();
}

void EmployeeEditedSignalTrigger::call()
{
    emit activated(m->accepted);
}

} // namespace MapService
} // namespace Rsl
