#ifndef CURRENTUSERMODEL_H
#define CURRENTUSERMODEL_H

#include <QAbstractListModel>
#include <QScopedPointer>
#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

class User;

namespace Impl {
struct CurrentUserModelRepresentation;
}

class RMS_LOGIC_SHARED CurrentUserModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRole {
        DataRole_User       = Qt::EditRole,
        DataRole_Id         = Qt::UserRole,
        DataRole_HallNumber,
        DataRole_CardNumber,
        DataRole_Name,
        DataRole_IsOff
    };

    explicit CurrentUserModel(QObject *parent = 0);
    ~CurrentUserModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    bool appendData(const User &);
    int removeData(const QVector<int> &ids);

    void reload();

private:
    Q_DISABLE_COPY(CurrentUserModel)
    QScopedPointer<Impl::CurrentUserModelRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTUSERMODEL_H
