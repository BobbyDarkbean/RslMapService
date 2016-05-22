#include <QSqlDatabase>
#include "datastorageconfigurator.h"

#include "workflow.h"

namespace Rsl {
namespace MapService {

namespace {
const QString DB_DRIVER("QSQLITE");
const QString DB_NAME("db_map_service");
}

WorkFlow::WorkFlow()
{
}

WorkFlow::~WorkFlow()
{
}

bool WorkFlow::connectDataStorage()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(DB_DRIVER);
    db.setDatabaseName(DB_NAME);
    return db.open();
}

bool WorkFlow::initDataStorage()
{
    DataStorageConfigurator configurator;
    return configurator.init();
}

bool WorkFlow::configureDataStorage()
{
    DataStorageConfigurator configurator;
    return configurator.configure();
}

} // namespace MapService
} // namespace Rsl
