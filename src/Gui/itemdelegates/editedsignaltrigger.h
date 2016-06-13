#ifndef EDITEDSIGNALTRIGGER_H
#define EDITEDSIGNALTRIGGER_H

#include <QScopedPointer>
#include "signaltrigger.h"

namespace Rsl {
namespace MapService {

namespace Impl {
struct EditedSignalTriggerRepresentation;
}

class EditedSignalTrigger : public SignalTrigger
{
    Q_OBJECT

public:
    explicit EditedSignalTrigger(QObject *parent = 0);
    ~EditedSignalTrigger();

    bool accepted() const;
    void setAccepted(bool);

    void reset();
    void call();

signals:
    void activated(bool);

private:
    Q_DISABLE_COPY(EditedSignalTrigger)
    QScopedPointer<Impl::EditedSignalTriggerRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // EDITEDSIGNALTRIGGER_H
