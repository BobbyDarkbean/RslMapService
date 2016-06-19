#ifndef REQUEST_H
#define REQUEST_H

#include <QMetaType>
#include <QSharedDataPointer>
#include "rmscore_shared.h"

namespace Rsl {
namespace MapService {

class CallNumber;

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

    CallNumber callNumber() const;
    void setCallNumber(const CallNumber &);

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
