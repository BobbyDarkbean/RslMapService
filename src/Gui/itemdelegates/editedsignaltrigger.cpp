#include "editedsignaltrigger.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct EditedSignalTriggerRepresentation
{
    void reinit();

    bool accepted;
};

void EditedSignalTriggerRepresentation::reinit()
{
    accepted = false;
}

} // namespace Impl

EditedSignalTrigger::EditedSignalTrigger(QObject *parent)
    : SignalTrigger(parent)
    , m(new Impl::EditedSignalTriggerRepresentation)
{
    m->reinit();
}

EditedSignalTrigger::~EditedSignalTrigger()
{
}

bool EditedSignalTrigger::accepted() const
{ return m->accepted; }

void EditedSignalTrigger::setAccepted(bool value)
{ m->accepted = value; }

void EditedSignalTrigger::reset()
{
    m->reinit();
}

void EditedSignalTrigger::call()
{
    emit activated(m->accepted);
}

} // namespace MapService
} // namespace Rsl
