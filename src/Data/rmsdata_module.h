#ifndef RMSDATA_MODULE_H
#define RMSDATA_MODULE_H

#include "rmsdata_shared.h"

class QSqlQuery;

namespace Rsl {
namespace MapService {

extern RMS_DATA_SHARED const QString RmsDataTag;

void logQueryExecution(const QString &context, const QSqlQuery &query, bool success);

} // namespace MapService
} // namespace Rsl

#endif // RMSDATA_MODULE_H
