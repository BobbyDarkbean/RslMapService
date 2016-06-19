#include <QSharedData>
#include <QString>
#include "callnumber.h"
#include "rms_global.h"

#include "request.h"

namespace Rsl {
namespace MapService {

namespace Impl {

class RequestSharedRepresentation : public QSharedData
{
public:
    RequestSharedRepresentation();

    int id;
    int userId;
    CallNumber callNumber;
    QString docTitle;
    int docType;
    int itemCount;
    int status;

private:
    RequestSharedRepresentation &operator=(const RequestSharedRepresentation &) Q_DECL_EQ_DELETE;
};

RequestSharedRepresentation::RequestSharedRepresentation()
    : id(0)
    , userId(0)
    , callNumber()
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

int Request::id() const
{ return m->id; }

void Request::setId(int value)
{ m->id = value; }

int Request::userId() const
{ return m->userId; }

void Request::setUserId(int value)
{ m->userId = value; }

CallNumber Request::callNumber() const
{ return m->callNumber; }

void Request::setCallNumber(const CallNumber &value)
{ m->callNumber = value; }

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
