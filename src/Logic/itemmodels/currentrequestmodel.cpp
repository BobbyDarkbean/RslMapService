#include "request.h"
#include "callnumber.h"
#include "dataadapters/currentrequestdataadapter.h"

#include "currentrequestmodel.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct CurrentRequestModelRepresentation
{
    QList<Request> requests;
    CurrentRequestDataAdapter dataAdapter;
};

} // namespace Impl

CurrentRequestModel::CurrentRequestModel(QObject *parent)
    : QAbstractListModel(parent)
    , m(new Impl::CurrentRequestModelRepresentation)
{
    m->requests = m->dataAdapter.select();
}

CurrentRequestModel::~CurrentRequestModel()
{
}

QVariant CurrentRequestModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount())
        return QVariant();

    int row = index.row();
    QVariant result;

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        result = QVariant::fromValue(m->requests.at(row));
        break;
    case DataRole_Id:
        result = m->requests.at(row).id();
        break;
    case DataRole_UserId:
        result = m->requests.at(row).userId();
        break;
    case DataRole_CallNumber:
        result = QVariant::fromValue(m->requests.at(row).callNumber());
        break;
    case DataRole_CallNumberCollection:
        result = m->requests.at(row).callNumber().collection();
        break;
    case DataRole_CallNumberRack:
        result = m->requests.at(row).callNumber().rack();
        break;
    case DataRole_CallNumberShelf:
        result = m->requests.at(row).callNumber().shelf();
        break;
    case DataRole_CallNumberPosition:
        result = m->requests.at(row).callNumber().position();
        break;
    case DataRole_DocTitle:
        result = m->requests.at(row).docTitle();
        break;
    case DataRole_DocType:
        result = m->requests.at(row).docType();
        break;
    case DataRole_ItemCount:
        result = m->requests.at(row).itemCount();
        break;
    case DataRole_Status:
        result = m->requests.at(row).status();
        break;
    default:
        break;
    }

    return result;
}

bool CurrentRequestModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= rowCount())
        return false;

    if (role != Qt::EditRole)
        return false;

    int row = index.row();
    Request request = value.value<Request>();
    request.setId(m->requests.at(row).id());

    if (!m->dataAdapter.update(request))
        return false;

    m->requests[row] = request;
    emit dataChanged(index, index, QVector<int>() << role);

    return true;
}

int CurrentRequestModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m->requests.size();
}

Qt::ItemFlags CurrentRequestModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractListModel::flags(index);

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool CurrentRequestModel::appendData(const Request &request)
{
    if (!m->dataAdapter.insert(request))
        return false;

    reload();
    return true;
}

int CurrentRequestModel::removeData(const QVector<int> &ids)
{
    int result = 0;
    foreach (int id, ids) {
        if (m->dataAdapter.deleteById(id))
            ++result;
    }

    if (result)
        reload();
    return result;
}

void CurrentRequestModel::reload()
{
    beginResetModel();
    m->requests = m->dataAdapter.select();
    endResetModel();
}

} // namespace MapService
} // namespace Rsl
