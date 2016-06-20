#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include "queryloader.h"
#include "rmsdata_module.h"
#include "callnumber.h"
#include "request.h"

#include "currentrequestdataadapter.h"

namespace Rsl {
namespace MapService {

namespace {

enum {
    Select,
    Insert,
    Update,
    Delete
};

const QString LogContext("CurrentRequestDataAdapter");

}

namespace Impl {

struct CurrentRequestDataAdapterRepresentation
{
    void init();

    QMap<int, QString> scripts;
};

void CurrentRequestDataAdapterRepresentation::init()
{
    QMap<int, QString> scriptKeys;
    scriptKeys[Select] = "select";
    scriptKeys[Insert] = "insert";
    scriptKeys[Update] = "update";
    scriptKeys[Delete] = "delete";

    foreach (int i, scriptKeys.keys()) {
        QString path = QString(":/data/currentrequest-%1.sql").arg(scriptKeys.value(i));
        QueryLoader loader(path);
        if (loader.isOpen()) {
            QStringList scriptList = loader.load();
            scripts[i] = scriptList.first();
        }
    }
}

} // namespace Impl

CurrentRequestDataAdapter::CurrentRequestDataAdapter()
    : m(new Impl::CurrentRequestDataAdapterRepresentation)
{
    m->init();
}

CurrentRequestDataAdapter::~CurrentRequestDataAdapter()
{
}

QList<Request> CurrentRequestDataAdapter::select() const
{
    QList<Request> requests;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    bool success = query.exec(m->scripts[Select]);
    logQueryExecution(LogContext, query, success);

    QSqlRecord record = query.record();
    int idFieldIndex = record.indexOf("id");
    int userIdFieldIndex = record.indexOf("userid");
    int collectionFieldIndex = record.indexOf("collection");
    int rackFieldIndex = record.indexOf("rack");
    int shelfFieldIndex = record.indexOf("shelf");
    int positionFieldIndex = record.indexOf("position");
    int docTitleFieldIndex = record.indexOf("doctitle");
    int docTypeFieldIndex = record.indexOf("doctype");
    int itemCountFieldIndex = record.indexOf("itemcount");
    int statusFieldIndex = record.indexOf("status");

    while (query.next()) {
        Request request;
        request.setId(query.value(idFieldIndex).toInt());
        request.setUserId(query.value(userIdFieldIndex).toInt());

        CallNumber callNumber;
        callNumber.setCollection(query.value(collectionFieldIndex).toInt());
        callNumber.setRack(query.value(rackFieldIndex).toString());
        callNumber.setShelf(query.value(shelfFieldIndex).toInt());
        callNumber.setPosition(query.value(positionFieldIndex).toString());
        request.setCallNumber(callNumber);

        request.setDocTitle(query.value(docTitleFieldIndex).toString());
        request.setDocType(query.value(docTypeFieldIndex).toInt());
        request.setItemCount(query.value(itemCountFieldIndex).toInt());
        request.setStatus(query.value(statusFieldIndex).toInt());

        requests << request;
    }

    return requests;
}

bool CurrentRequestDataAdapter::insert(const Request &request)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(m->scripts[Insert]);

    query.bindValue(":userid", request.userId());

    CallNumber callNumber = request.callNumber();
    query.bindValue(":collection", callNumber.collection());
    query.bindValue(":rack", callNumber.rack());
    query.bindValue(":shelf", callNumber.shelf());
    query.bindValue(":position", callNumber.position());

    query.bindValue(":doctitle", request.docTitle());
    query.bindValue(":doctype", request.docType());
    query.bindValue(":itemcount", request.itemCount());
    query.bindValue(":status", request.status());

    return queryLoggedExec(LogContext, query);
}

bool CurrentRequestDataAdapter::update(const Request &request)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(m->scripts[Update]);

    query.bindValue(":userid", request.userId());

    CallNumber callNumber = request.callNumber();
    query.bindValue(":collection", callNumber.collection());
    query.bindValue(":rack", callNumber.rack());
    query.bindValue(":shelf", callNumber.shelf());
    query.bindValue(":position", callNumber.position());

    query.bindValue(":doctitle", request.docTitle());
    query.bindValue(":doctype", request.docType());
    query.bindValue(":itemcount", request.itemCount());
    query.bindValue(":status", request.status());

    query.bindValue(":id", request.id());

    return queryLoggedExec(LogContext, query);
}

bool CurrentRequestDataAdapter::deleteById(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare(m->scripts[Delete]);

    query.bindValue(":id", id);

    return queryLoggedExec(LogContext, query);
}

} // namespace MapService
} // namespace Rsl
