#ifndef CURRENTREQUESTMODEL_H
#define CURRENTREQUESTMODEL_H

#include <QAbstractListModel>
#include <QScopedPointer>
#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

class Request;

namespace Impl {
struct CurrentRequestModelRepresentation;
}

class RMS_LOGIC_SHARED CurrentRequestModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRole {
        DataRole_Id                     = Qt::UserRole,
        DataRole_UserId,
        DataRole_CallNumber,
        DataRole_CallNumberCollection,
        DataRole_CallNumberRack,
        DataRole_CallNumberShelf,
        DataRole_CallNumberPosition,
        DataRole_DocTitle,
        DataRole_DocType,
        DataRole_ItemCount,
        DataRole_Status
    };

    explicit CurrentRequestModel(QObject *parent = 0);
    ~CurrentRequestModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    bool appendData(const Request &);
    int removeData(const QVector<int> &ids);

    void reload();

private:
    Q_DISABLE_COPY(CurrentRequestModel)
    QScopedPointer<Impl::CurrentRequestModelRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTREQUESTMODEL_H
