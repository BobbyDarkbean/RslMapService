#ifndef REQUESTSTATUSMODEL_H
#define REQUESTSTATUSMODEL_H

#include <QAbstractListModel>
#include <QScopedPointer>
#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

namespace Impl {
struct RequestStatusModelRepresentation;
}

class RMS_LOGIC_SHARED RequestStatusModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRole {
        DataRole_StatusText     = Qt::DisplayRole,
        DataRole_Status         = Qt::UserRole,
        DataRole_Availability   = Qt::EditRole
    };

    explicit RequestStatusModel(QObject *parent = 0);
    ~RequestStatusModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    int currentState() const;
    bool setCurrentState(int);

    void reload();

private:
    Q_DISABLE_COPY(RequestStatusModel)
    QScopedPointer<Impl::RequestStatusModelRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // REQUESTSTATUSMODEL_H
