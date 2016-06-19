#ifndef CALLNUMBER_H
#define CALLNUMBER_H

#include <QMetaType>
#include <QSharedDataPointer>
#include "rmscore_shared.h"

namespace Rsl {
namespace MapService {

namespace Impl {
class CallNumberSharedRepresentation;
}

class RMS_CORE_SHARED CallNumber
{
public:
    CallNumber();
    CallNumber(const CallNumber &);
    CallNumber &operator=(const CallNumber &);
    ~CallNumber();

    int collection() const;
    void setCollection(int);

    QString rack() const;
    void setRack(const QString &);

    int shelf() const;
    void setShelf(int);

    QString position() const;
    void setPosition(const QString &);

private:
    QSharedDataPointer<Impl::CallNumberSharedRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

Q_DECLARE_METATYPE(Rsl::MapService::CallNumber)

#endif // CALLNUMBER_H
