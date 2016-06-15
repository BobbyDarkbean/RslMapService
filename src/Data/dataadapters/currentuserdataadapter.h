#ifndef CURRENTUSERDATAADAPTER_H
#define CURRENTUSERDATAADAPTER_H

#include <QScopedPointer>
#include "rmsdata_shared.h"

namespace Rsl {
namespace MapService {

class User;

namespace Impl {
struct CurrentUserDataAdapterRepresentation;
}

class RMS_DATA_SHARED CurrentUserDataAdapter
{
public:
    CurrentUserDataAdapter();
    ~CurrentUserDataAdapter();

    QList<User> select() const;
    bool insert(const User &);
    bool update(const User &);
    bool deleteById(int id);

private:
    Q_DISABLE_COPY(CurrentUserDataAdapter)
    QScopedPointer<Impl::CurrentUserDataAdapterRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTUSERDATAADAPTER_H
