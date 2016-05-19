#include <QString>
#include "rms_global.h"

namespace Rsl {
namespace MapService {

namespace {
const char *document_type_strings[] = {
    QT_TRANSLATE_NOOP("DocumentType", "MAP"),
    QT_TRANSLATE_NOOP("DocumentType", "ATLAS"),
    QT_TRANSLATE_NOOP("DocumentType", "GLOBE"),
    QT_TRANSLATE_NOOP("DocumentType", "BOOK"),
    QT_TRANSLATE_NOOP("DocumentType", "BIBLIOGRAPHY"),
    QT_TRANSLATE_NOOP("DocumentType", "PERIODICAL"),
    QT_TRANSLATE_NOOP("DocumentType", "OPTICALDISC")
};

const char *request_status_strings[] = {
    QT_TRANSLATE_NOOP("RequestStatus", "FILLING"),
    QT_TRANSLATE_NOOP("RequestStatus", "PICKUP"),
    QT_TRANSLATE_NOOP("RequestStatus", "DELIVERED"),
    QT_TRANSLATE_NOOP("RequestStatus", "DENY_DEPARTMENTS_OCCUPIED"),
    QT_TRANSLATE_NOOP("RequestStatus", "DENY_EMPLOYEES_OCCUPIED"),
    QT_TRANSLATE_NOOP("RequestStatus", "DENY_EXHIBITION_OCCUPIED"),
    QT_TRANSLATE_NOOP("RequestStatus", "DENY_ILES_OCCUPIED"),
    QT_TRANSLATE_NOOP("RequestStatus", "DENY_STOCK"),
    QT_TRANSLATE_NOOP("RequestStatus", "DENY_NULL"),
    QT_TRANSLATE_NOOP("RequestStatus", "RETURNED"),
    QT_TRANSLATE_NOOP("RequestStatus", "PUT_ON_HOLD")
};
}

QString toString(DocumentType dt)
{
    Q_ASSERT(DocumentType_MIN <= dt && dt <= DocumentType_MAX);
    return document_type_strings[dt];
}

QString toString(RequestStatus rs)
{
    Q_ASSERT(RequestStatus_MIN <= rs && rs <= RequestStatus_MAX);
    return request_status_strings[rs];
}

} // namespace MapService
} // namespace Rsl
