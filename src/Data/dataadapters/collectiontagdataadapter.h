#ifndef COLLECTIONTAGDATAADAPTER_H
#define COLLECTIONTAGDATAADAPTER_H

#include <QScopedPointer>
#include "rmsdata_shared.h"

class QStringList;

namespace Rsl {
namespace MapService {

namespace Impl {
struct CollectionTagDataAdapterRepresentation;
}

class RMS_DATA_SHARED CollectionTagDataAdapter
{
public:
    CollectionTagDataAdapter();
    ~CollectionTagDataAdapter();

    QStringList select() const;

private:
    Q_DISABLE_COPY(CollectionTagDataAdapter)
    QScopedPointer<Impl::CollectionTagDataAdapterRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // COLLECTIONTAGDATAADAPTER_H
