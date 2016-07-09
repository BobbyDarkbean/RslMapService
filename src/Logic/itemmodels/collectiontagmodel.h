#ifndef COLLECTIONTAGMODEL_H
#define COLLECTIONTAGMODEL_H

#include <QAbstractListModel>
#include <QScopedPointer>
#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

namespace Impl {
struct CollectionTagModelRepresentation;
}

class RMS_LOGIC_SHARED CollectionTagModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRole {
        DataRole_Tag    = Qt::DisplayRole,
        DataRole_Id     = Qt::UserRole
    };

    explicit CollectionTagModel(QObject *parent = 0);
    ~CollectionTagModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(CollectionTagModel)
    QScopedPointer<Impl::CollectionTagModelRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // COLLECTIONTAGMODEL_H
