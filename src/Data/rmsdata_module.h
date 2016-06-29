#ifndef RMSDATA_MODULE_H
#define RMSDATA_MODULE_H

#include "rmsdata_shared.h"

class QFile;
class QSqlQuery;

namespace Rsl {
namespace MapService {

extern RMS_DATA_SHARED const QString RmsDataTag;

enum {
    FileIOStatus_OpenForReading,
    FileIOStatus_OpenForWriting,
    FileIOStatus_OpenError,
    FileIOStatus_AlreadyOpen,
};

void logFileIO(const QString &context, int fileIOStatus, const QFile *file);
void logXmlDataReading(const QString &context, int entriesRead);
void logQueryReading(const QString &context, const QString &queryString);
void logQueryReading(const QString &context, int queriesRead);
void logQueryExecution(const QString &context, const QSqlQuery &query, bool success);
void logQuerySequenceIsEmpty(const QString &context);
void logQuerySequenceExecution(const QString &context, int actualSize, int expectedSize);

bool queryLoggedExec(const QString &context, QSqlQuery query);

} // namespace MapService
} // namespace Rsl

#endif // RMSDATA_MODULE_H
