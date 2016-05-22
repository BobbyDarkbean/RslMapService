#include <QSqlQuery>
#include <QStringList>
#include "queryloader.h"

#include "datastorageconfigurator.h"

namespace Rsl {
namespace MapService {

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
    if (queries.isEmpty())
        return false;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    foreach (const QString &queryStr, queries) {
        if (!query.exec(queryStr))
            return false;
    }

    return true;
}

} // namespace MapService
} // namespace Rsl
