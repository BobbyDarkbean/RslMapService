#include "dataadapters/collectiontagdataadapter.h"
#include "collectiontagmodel.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct CollectionTagModelRepresentation
{
    QStringList tags;
};

} // namespace Impl

CollectionTagModel::CollectionTagModel(QObject *parent)
    : QAbstractListModel(parent)
    , m(new Impl::CollectionTagModelRepresentation)
{
    CollectionTagDataAdapter dataAdapter;
    m->tags = dataAdapter.select();
}

CollectionTagModel::~CollectionTagModel()
{
}

QVariant CollectionTagModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount())
        return QVariant();

    int row = index.row();
    QVariant result;

    switch (role) {
    case DataRole_Tag:
        result = m->tags.at(row);
        break;
    case DataRole_Id:
        result = row;
        break;
    default:
        break;
    }

    return result;
}

int CollectionTagModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m->tags.size();
}

} // namespace MapService
} // namespace Rsl
