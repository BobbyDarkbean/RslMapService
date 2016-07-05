#include "user.h"
#include "dataadapters/currentuserdataadapter.h"

#include "currentusermodel.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct CurrentUserModelRepresentation
{
    QList<User> users;
    CurrentUserDataAdapter dataAdapter;
};

} // namespace Impl

CurrentUserModel::CurrentUserModel(QObject *parent)
    : QAbstractListModel(parent)
    , m(new Impl::CurrentUserModelRepresentation)
{
    m->users = m->dataAdapter.select();
}

CurrentUserModel::~CurrentUserModel()
{
}

QVariant CurrentUserModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount())
        return QVariant();

    int row = index.row();
    QVariant result;

    switch (role) {
    case Qt::EditRole:
        result = QVariant::fromValue(m->users.at(row));
        break;
    case DataRole_Id:
        result = m->users.at(row).id();
        break;
    case DataRole_HallNumber:
        result = m->users.at(row).hallNumber();
        break;
    case DataRole_CardNumber:
        result = m->users.at(row).cardNumber();
        break;
    case Qt::DisplayRole:
    case DataRole_Name:
        result = m->users.at(row).name();
        break;
    case DataRole_IsOff:
        result = m->users.at(row).isOff();
        break;
    default:
        break;
    }

    return result;
}

bool CurrentUserModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= rowCount())
        return false;

    if (role != Qt::EditRole)
        return false;

    int row = index.row();
    User user = value.value<User>();
    user.setId(m->users.at(row).id());

    if (!m->dataAdapter.update(user))
        return false;

    m->users[row] = user;
    emit dataChanged(index, index, QVector<int>() << role);

    return true;
}

int CurrentUserModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m->users.size();
}

Qt::ItemFlags CurrentUserModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractListModel::flags(index);

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool CurrentUserModel::appendData(const User &user)
{
    if (!m->dataAdapter.insert(user))
        return false;

    reload();
    return true;
}

int CurrentUserModel::removeData(const QVector<int> &ids)
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

void CurrentUserModel::reload()
{
    beginResetModel();
    m->users = m->dataAdapter.select();
    endResetModel();
}

} // namespace MapService
} // namespace Rsl
