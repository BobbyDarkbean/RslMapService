#ifndef USER_H
#define USER_H

#include <QMetaType>
#include <QSharedDataPointer>
#include "rmscore_shared.h"

namespace Rsl {
namespace MapService {

namespace Impl {
class UserSharedRepresentation;
}

class RMS_CORE_SHARED User
{
public:
    User();
    User(const User &);
    User &operator=(const User &);
    ~User();

    int id() const;
    void setId(int);

    int hallNumber() const;
    void setHallNumber(int);

    int cardNumber() const;
    void setCardNumber(int);

    QString name() const;
    void setName(const QString &);

    bool isOff() const;
    void setOff(bool);

private:
    QSharedDataPointer<Impl::UserSharedRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

Q_DECLARE_METATYPE(Rsl::MapService::User)

#endif // USER_H
