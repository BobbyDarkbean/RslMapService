#ifndef REQUEST_H
#define REQUEST_H

#include <QMetaType>
#include <QSharedDataPointer>
#include "rms_shared.h"

namespace Rsl {
namespace MapService {

namespace Impl {
class RequestSharedRepresentation;
}

class RMS_CORE_SHARED Request
{
public:
    Request();
    Request(const Request &);
    Request &operator=(const Request &);
    ~Request();

    int userId() const;
    void setUserId(int);

    QString docTitle() const;
    void setDocTitle(const QString &);

    int docType() const;
    void setDocType(int);

    int itemCount() const;
    void setItemCount(int);

    int status() const;
    void setStatus(int);

private:
    QSharedDataPointer<Impl::RequestSharedRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

Q_DECLARE_METATYPE(Rsl::MapService::Request)

#endif // REQUEST_H
