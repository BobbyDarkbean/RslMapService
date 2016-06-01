#ifndef EMPLOYEEMODEL_H
#define EMPLOYEEMODEL_H

#include <QAbstractListModel>
#include <QScopedPointer>
#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

class Employee;

namespace Impl {
struct EmployeeModelRepresentation;
}

class RMS_LOGIC_SHARED EmployeeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRole {
        DataRole_Id         = Qt::UserRole,
        DataRole_Name,
        DataRole_IsActive
    };

    explicit EmployeeModel(QObject *parent = 0);
    ~EmployeeModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    bool appendData(const Employee &);
    int removeData(const QVector<int> &ids);

    void reload();

private:
    Q_DISABLE_COPY(EmployeeModel)
    QScopedPointer<Impl::EmployeeModelRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // EMPLOYEEMODEL_H
