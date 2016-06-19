#include <QSqlQuery>
#include <QStringList>
#include "queryloader.h"
#include "rmsdata_module.h"

#include "datastorageconfigurator.h"

namespace Rsl {
namespace MapService {

namespace {
const QString LogContext("DataStorageConfigurator");
}

DataStorageConfigurator::DataStorageConfigurator()
{
}

bool DataStorageConfigurator::init()
{
    QStringList queries = sequence(":/data/dbinit.sql");
    return execSequence(queries);
}

bool DataStorageConfigurator::configure()
{
    QStringList queries = sequence(":/data/dbconfig.sql");
    return execSequence(queries);
}

QStringList DataStorageConfigurator::sequence(const QString &pathToSql)
{
    QueryLoader sequenceLoader(pathToSql);
    Q_ASSERT(sequenceLoader.isOpen());
    return sequenceLoader.load();
}

bool DataStorageConfigurator::execSequence(const QStringList &queries)
{
    if (queries.isEmpty()) {
        logQuerySequenceIsEmpty(LogContext);
        return false;
    }

    int queriesExecuted = 0;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    foreach (const QString &queryStr, queries) {
        bool success = query.exec(queryStr);
        logQueryExecution(LogContext, query, success);

        if (success) {
            ++queriesExecuted;
        } else {
            break;
        }
    }

    logQuerySequenceExecution(LogContext, queriesExecuted, queries.size());
    return (queriesExecuted == queries.size());
}

} // namespace MapService
} // namespace Rsl
