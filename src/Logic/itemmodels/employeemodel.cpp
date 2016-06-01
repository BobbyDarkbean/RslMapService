#include "employee.h"
#include "dataadapters/employeedataadapter.h"

#include "employeemodel.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct EmployeeModelRepresentation
{
    QList<Employee> employees;
    EmployeeDataAdapter dataAdapter;
};

} // namespace Impl

EmployeeModel::EmployeeModel(QObject *parent)
    : QAbstractListModel(parent)
    , m(new Impl::EmployeeModelRepresentation)
{
    m->employees = m->dataAdapter.select();
}

EmployeeModel::~EmployeeModel()
{
}

QVariant EmployeeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount())
        return QVariant();

    int row = index.row();
    QVariant result;

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        result = QVariant::fromValue(m->employees.at(row));
        break;
    case DataRole_Id:
        result = m->employees.at(row).id();
        break;
    case DataRole_Name:
        result = m->employees.at(row).name();
        break;
    case DataRole_IsActive:
        result = m->employees.at(row).isActive();
        break;
    default:
        break;
    }

    return result;
}

bool EmployeeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= rowCount())
        return false;

    if (role != Qt::EditRole)
        return false;

    int row = index.row();
    Employee employee = value.value<Employee>();
    employee.setId(m->employees.at(row).id());

    if (!m->dataAdapter.update(employee))
        return false;

    m->employees[row] = employee;
    emit dataChanged(index, index, QVector<int>() << role);

    return true;
}

int EmployeeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m->employees.size();
}

Qt::ItemFlags EmployeeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractListModel::flags(index);

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool EmployeeModel::appendData(const Employee &employee)
{
    if (!m->dataAdapter.insert(employee))
        return false;

    reload();
    return true;
}

int EmployeeModel::removeData(const QVector<int> &ids)
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

void EmployeeModel::reload()
{
    beginResetModel();
    m->employees = m->dataAdapter.select();
    endResetModel();
}

} // namespace MapService
} // namespace Rsl
