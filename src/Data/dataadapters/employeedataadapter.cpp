#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include "queryloader.h"
#include "employee.h"

#include "employeedataadapter.h"

namespace Rsl {
namespace MapService {

namespace {

enum {
    Select,
    Insert,
    Update,
    Delete
};

}

namespace Impl {

struct EmployeeDataAdapterRepresentation
{
    void init();

    QMap<int, QString> scripts;
};

void EmployeeDataAdapterRepresentation::init()
{
    QMap<int, QString> scriptKeys;
    scriptKeys[Select] = "select";
    scriptKeys[Insert] = "insert";
    scriptKeys[Update] = "update";
    scriptKeys[Delete] = "delete";

    foreach (int i, scriptKeys.keys()) {
        QString path = QString(":/data/employee-%1.sql").arg(scriptKeys.value(i));
        QueryLoader loader(path);
        if (loader.isOpen()) {
            QStringList scriptList = loader.load();
            scripts[i] = scriptList.first();
        }
    }
}

} // namespace Impl

EmployeeDataAdapter::EmployeeDataAdapter()
    : m(new Impl::EmployeeDataAdapterRepresentation)
{
    m->init();
}

EmployeeDataAdapter::~EmployeeDataAdapter()
{
}

QList<Employee> EmployeeDataAdapter::select() const
{
    QList<Employee> names;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.exec(m->scripts[Select]);

    int idFieldIndex = query.record().indexOf("id");
    int nameFieldIndex = query.record().indexOf("name");
    int isActiveFieldIndex = query.record().indexOf("isactive");

    while (query.next()) {
        Employee employee;
        employee.setId(query.value(idFieldIndex).toInt());
        employee.setName(query.value(nameFieldIndex).toString());
        employee.setActive(query.value(isActiveFieldIndex).toBool());

        names << employee;
    }

    return names;
}

bool EmployeeDataAdapter::insert(const Employee &employee)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(m->scripts[Insert]);

    query.bindValue(":name", employee.name());
    query.bindValue(":isactive", employee.isActive());

    return query.exec();
}

bool EmployeeDataAdapter::update(const Employee &employee)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(m->scripts[Update]);

    query.bindValue(":name", employee.name());
    query.bindValue(":isactive", employee.isActive());
    query.bindValue(":id", employee.id());

    return query.exec();
}

bool EmployeeDataAdapter::deleteById(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(m->scripts[Delete]);

    query.bindValue(":id", id);

    return query.exec();
}

} // namespace MapService
} // namespace Rsl
