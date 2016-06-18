#include <QVariantMap>
#include <QStringList>
#include <QSqlQuery>
#include "log.h"

#include "rmsdata_module.h"

namespace Rsl {
namespace MapService {

const QString RmsDataTag("Data");

void logQueryExecution(const QString &context, const QSqlQuery &query, bool success)
{
    const QString BoundValuesSep(", ");

    QStringList boundValuesList;
    QVariantMap boundValues = query.boundValues();
    foreach (const QString &placeHolder, boundValues.keys()) {
        boundValuesList << QString("%1 = %2").arg(placeHolder, boundValues.value(placeHolder).toString());
    }

    Log::write(RmsDataTag, context, success ? "query executed" : "query failed",
               QString("`%1` %2").arg(query.lastQuery(), boundValuesList.join(BoundValuesSep)));
}

} // namespace MapService
} // namespace Rsl
