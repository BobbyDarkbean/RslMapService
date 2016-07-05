#include <QString>
#include <QCoreApplication>

#include "rms_global.h"

namespace Rsl {
namespace MapService {

namespace {
const char *document_type_strings[] = {
    QT_TRANSLATE_NOOP("Rsl::MapService::DocumentType", "MAP"),
    QT_TRANSLATE_NOOP("Rsl::MapService::DocumentType", "ATLAS"),
    QT_TRANSLATE_NOOP("Rsl::MapService::DocumentType", "GLOBE"),
    QT_TRANSLATE_NOOP("Rsl::MapService::DocumentType", "BOOK"),
    QT_TRANSLATE_NOOP("Rsl::MapService::DocumentType", "BIBLIOGRAPHY"),
    QT_TRANSLATE_NOOP("Rsl::MapService::DocumentType", "PERIODICAL"),
    QT_TRANSLATE_NOOP("Rsl::MapService::DocumentType", "OPTICALDISC")
};

const char *request_status_strings[] = {
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "FILLING"),
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "PICKUP"),
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "DELIVERED"),
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "DENY_DEPARTMENTS_OCCUPIED"),
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "DENY_EMPLOYEES_OCCUPIED"),
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "DENY_EXHIBITION_OCCUPIED"),
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "DENY_ILES_OCCUPIED"),
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "DENY_STOCK"),
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "DENY_NULL"),
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "RETURNED"),
    QT_TRANSLATE_NOOP("Rsl::MapService::RequestStatus", "PUT_ON_HOLD")
};
}

const QString WrittenNameRegExp(R"([\w\.\,\-\(\)\s]*)");
const QString CallNumberRackRegExp(R"((\w\-?)*)");
const QString CallNumberPositionRegExp(R"(\d+\w?)");

QString toString(DocumentType dt)
{
    Q_ASSERT(DocumentType_MIN <= dt && dt <= DocumentType_MAX);
    return QCoreApplication::translate("Rsl::MapService::DocumentType", document_type_strings[dt]);
}

QString toString(RequestStatus rs)
{
    Q_ASSERT(RequestStatus_MIN <= rs && rs <= RequestStatus_MAX);
    return QCoreApplication::translate("Rsl::MapService::RequestStatus", request_status_strings[rs]);
}

} // namespace MapService
} // namespace Rsl
