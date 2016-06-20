#ifndef CURRENTREQUESTDATAADAPTER_H
#define CURRENTREQUESTDATAADAPTER_H

#include <QScopedPointer>
#include "rmsdata_shared.h"

namespace Rsl {
namespace MapService {

class Request;

namespace Impl {
struct CurrentRequestDataAdapterRepresentation;
}

class RMS_DATA_SHARED CurrentRequestDataAdapter
{
public:
    CurrentRequestDataAdapter();
    ~CurrentRequestDataAdapter();

    QList<Request> select() const;
    bool insert(const Request &);
    bool update(const Request &);
    bool deleteById(int id);

private:
    Q_DISABLE_COPY(CurrentRequestDataAdapter)
    QScopedPointer<Impl::CurrentRequestDataAdapterRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTREQUESTDATAADAPTER_H
