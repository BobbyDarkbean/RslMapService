#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include "queryloader.h"
#include "user.h"

#include "currentuserdataadapter.h"

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

struct CurrentUserDataAdapterRepresentation
{
    void init();

    QMap<int, QString> scripts;
};

void CurrentUserDataAdapterRepresentation::init()
{
    QMap<int, QString> scriptKeys;
    scriptKeys[Select] = "select";
    scriptKeys[Insert] = "insert";
    scriptKeys[Update] = "update";
    scriptKeys[Delete] = "delete";

    foreach (int i, scriptKeys.keys()) {
        QString path = QString(":/data/currentuser-%1.sql").arg(scriptKeys.value(i));
        QueryLoader loader(path);
        if (loader.isOpen()) {
            QStringList scriptList = loader.load();
            scripts[i] = scriptList.first();
        }
    }
}

} // namespace Impl

CurrentUserDataAdapter::CurrentUserDataAdapter()
    : m(new Impl::CurrentUserDataAdapterRepresentation)
{
    m->init();
}

CurrentUserDataAdapter::~CurrentUserDataAdapter()
{
}

QList<User> CurrentUserDataAdapter::select() const
{
    QList<User> names;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.exec(m->scripts[Select]);

    QSqlRecord record = query.record();
    int idFieldIndex = record.indexOf("id");
    int hallnumFieldIndex = record.indexOf("hallnum");
    int cardnumFieldIndex = record.indexOf("cardnum");
    int nameFieldIndex = record.indexOf("name");
    int isOffFieldIndex = record.indexOf("isoff");

    while (query.next()) {
        User user;
        user.setId(query.value(idFieldIndex).toInt());
        user.setHallNumber(query.value(hallnumFieldIndex).toInt());
        user.setCardNumber(query.value(cardnumFieldIndex).toInt());
        user.setName(query.value(nameFieldIndex).toString());
        user.setOff(query.value(isOffFieldIndex).toBool());

        names << user;
    }

    return names;
}

bool CurrentUserDataAdapter::insert(const User &user)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(m->scripts[Insert]);

    query.bindValue(":hallnum", user.hallNumber());
    query.bindValue(":cardnum", user.cardNumber());
    query.bindValue(":name", user.name());
    query.bindValue(":isoff", user.isOff());

    return query.exec();
}

bool CurrentUserDataAdapter::update(const User &user)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(m->scripts[Update]);

    query.bindValue(":hallnum", user.hallNumber());
    query.bindValue(":cardnum", user.cardNumber());
    query.bindValue(":name", user.name());
    query.bindValue(":isoff", user.isOff());
    query.bindValue(":id", user.id());

    return query.exec();
}

bool CurrentUserDataAdapter::deleteById(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(m->scripts[Delete]);

    query.bindValue(":id", id);

    return query.exec();
}

} // namespace MapService
} // namespace Rsl
