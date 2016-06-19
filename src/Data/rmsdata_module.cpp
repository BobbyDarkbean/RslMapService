#include <QVariantMap>
#include <QStringList>
#include <QFile>
#include <QSqlQuery>
#include "log.h"

#include "rmsdata_module.h"

namespace Rsl {
namespace MapService {

const QString RmsDataTag("Data");

namespace {
const char *file_io_status_strings[] = {
    "file open for reading",    // FileIOStatus_OpenForReading
    "file open for writing",    // FileIOStatus_OpenForWriting
    "file open error",          // FileIOStatus_OpenError
    "file is already open"      // FileIOStatus_AlreadyOpen
};
}

void logFileIO(const QString &context, int fileIOStatus, const QFile *file)
{
    const QString Statement(file_io_status_strings[fileIOStatus]);
    const QString ErrorString(file->error() == QFile::NoError ? QString() : file->errorString());

    Log::write(RmsDataTag, context, Statement,
               QString("`%1` %2").arg(file->fileName(), ErrorString));
}

void logQueryReading(const QString &context, const QString &queryString)
{
    const QString Statement("query read");
    Log::write(RmsDataTag, context, Statement, QString("`%1`").arg(queryString));
}

void logQueryReading(const QString &context, int queriesRead)
{
    const QString Statement("queries read:");
    Log::write(RmsDataTag, context, Statement, QString::number(queriesRead));
}

void logQueryExecution(const QString &context, const QSqlQuery &query, bool success)
{
    const QString Statement(success ? "query executed" : "query failed");
    const QString BoundValuesSep(", ");

    QStringList boundValuesList;
    QVariantMap boundValues = query.boundValues();
    foreach (const QString &placeHolder, boundValues.keys()) {
        boundValuesList << QString("%1 = %2").arg(placeHolder, boundValues.value(placeHolder).toString());
    }

    Log::write(RmsDataTag, context, Statement,
               QString("`%1` %2").arg(query.lastQuery(), boundValuesList.join(BoundValuesSep)));
}

void logQuerySequenceIsEmpty(const QString &context)
{
    const QString Statement("query sequence is empty");
    Log::write(RmsDataTag, context, Statement);
}

void logQuerySequenceExecution(const QString &context, int actualSize, int expectedSize)
{
    const QString Statement(actualSize == expectedSize ? "query sequence completed"
                                                       : "query sequence interrupted");

    Log::write(RmsDataTag, context,
               QString("%1, %2/%3").arg(Statement, QString::number(actualSize), QString::number(expectedSize)));
}

bool queryLoggedExec(const QString &context, QSqlQuery query)
{
    bool success = query.exec();
    logQueryExecution(context, query, success);
    return success;
}

} // namespace MapService
} // namespace Rsl
