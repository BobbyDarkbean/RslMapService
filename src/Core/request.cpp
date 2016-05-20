#include <QSharedData>
#include <QString>
#include "rms_global.h"

#include "request.h"

namespace Rsl {
namespace MapService {

namespace Impl {

class RequestSharedRepresentation : public QSharedData
{
public:
    RequestSharedRepresentation();

    int userId;
    QString docTitle;
    int docType;
    int itemCount;
    int status;

private:
    RequestSharedRepresentation &operator=(const RequestSharedRepresentation &) Q_DECL_EQ_DELETE;
};

RequestSharedRepresentation::RequestSharedRepresentation()
    : userId(-1)
    , docTitle()
    , docType(DocumentType_Map)
    , itemCount(0)
    , status(RequestStatus_Filling)
{
}

} // namespace Impl

Request::Request()
    : m(new Impl::RequestSharedRepresentation)
{
}

Request::Request(const Request &other)
    : m(other.m)
{
}

Request &Request::operator=(const Request &other)
{
    m = other.m;
    return *this;
}

Request::~Request()
{
}

int Request::userId() const
{ return m->userId; }

void Request::setUserId(int value)
{ m->userId = value; }

QString Request::docTitle() const
{ return m->docTitle; }

void Request::setDocTitle(const QString &value)
{ m->docTitle = value; }

int Request::docType() const
{ return m->docType; }

void Request::setDocType(int value)
{ m->docType = value; }

int Request::itemCount() const
{ return m->itemCount; }

void Request::setItemCount(int value)
{ m->itemCount = value; }

int Request::status() const
{ return m->status; }

void Request::setStatus(int value)
{ m->status = value; }

} // namespace MapService
} // namespace Rsl
