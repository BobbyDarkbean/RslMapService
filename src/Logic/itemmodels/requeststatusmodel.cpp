#include "requeststatemachine.h"
#include "rms_global.h"

#include "requeststatusmodel.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct RequestStatusModelRepresentation
{
    RequestStateMachine rsm;
};

} // namespace Impl

RequestStatusModel::RequestStatusModel(QObject *parent)
    : QAbstractListModel(parent)
    , m(new Impl::RequestStatusModelRepresentation)
{
    m->rsm.setState(RequestStatus_Filling);
}

RequestStatusModel::~RequestStatusModel()
{
}

QVariant RequestStatusModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount())
        return QVariant();

    int row = index.row();
    QVariant result;

    switch (role) {
    case DataRole_StatusText:
        result = toString(RequestStatus(row));
        break;
    case DataRole_Status:
        result = row;
        break;
    case DataRole_Availability:
        result = m->rsm.canTransit(row);
        break;
    default:
        break;
    }

    return result;
}

int RequestStatusModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return RequestStatus_COUNT;
}

Qt::ItemFlags RequestStatusModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractListModel::flags(index);

    Qt::ItemFlags result = QAbstractListModel::flags(index);
    if (data(index, DataRole_Availability).toBool()) {
        result |= Qt::ItemIsEnabled;
    } else {
        result &= ~Qt::ItemIsEnabled;
    }

    return result;
}

int RequestStatusModel::currentState() const
{
    return m->rsm.state();
}

bool RequestStatusModel::setCurrentState(int state)
{
    if (!m->rsm.canTransit(state))
        return false;

    m->rsm.setState(state);
    return true;
}

void RequestStatusModel::reload()
{
    beginResetModel();
    endResetModel();
}

} // namespace MapService
} // namespace Rsl
