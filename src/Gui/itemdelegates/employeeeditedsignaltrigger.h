#ifndef EMPLOYEEEDITEDSIGNALTRIGGER_H
#define EMPLOYEEEDITEDSIGNALTRIGGER_H

#include <QScopedPointer>
#include "signaltrigger.h"

namespace Rsl {
namespace MapService {

namespace Impl {
struct EmployeeEditedSignalTriggerRepresentation;
}

class EmployeeEditedSignalTrigger : public SignalTrigger
{
    Q_OBJECT

public:
    explicit EmployeeEditedSignalTrigger(QObject *parent = 0);
    ~EmployeeEditedSignalTrigger();

    bool accepted() const;
    void setAccepted(bool);

    void reset();
    void call();

signals:
    void activated(bool);

private:
    Q_DISABLE_COPY(EmployeeEditedSignalTrigger)
    QScopedPointer<Impl::EmployeeEditedSignalTriggerRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // EMPLOYEEEDITEDSIGNALTRIGGER_H
