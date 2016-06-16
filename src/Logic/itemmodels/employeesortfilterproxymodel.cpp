#include "employee.h"
#include "employeemodel.h"

#include "employeesortfilterproxymodel.h"

namespace Rsl {
namespace MapService {

namespace Impl {

bool employeeLessThanById(const Employee &a, const Employee &b)
{
    return a.id() < b.id();
}

bool employeeLessThanByName(const Employee &a, const Employee &b)
{
    int nameCompare = QString::localeAwareCompare(a.name(), b.name());
    if (nameCompare == 0) {
        if (a.isActive() == b.isActive())
            return a.id() < b.id();
        return a.isActive();
    }
    return nameCompare < 0;
}

bool employeeLessThanByIsActive(const Employee &a, const Employee &b)
{
    if (a.isActive() == b.isActive())
        return QString::localeAwareCompare(a.name(), b.name()) < 0;
    return a.isActive();
}

struct EmployeeSortFilterProxyModelRepresentation
{
    void init();

    EmployeeSortFilterProxyModel::SortCriterion sortCriterion;
    EmployeeSortFilterProxyModel::FilterCriterion filterCriterion;
};

void EmployeeSortFilterProxyModelRepresentation::init()
{
    sortCriterion = EmployeeSortFilterProxyModel::SortCriterion_Name;
    filterCriterion = EmployeeSortFilterProxyModel::FilterCriterion_AcceptAll;
}

} // namespace Impl

EmployeeSortFilterProxyModel::EmployeeSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , m(new Impl::EmployeeSortFilterProxyModelRepresentation)
{
    m->init();
}

EmployeeSortFilterProxyModel::~EmployeeSortFilterProxyModel()
{
}

EmployeeSortFilterProxyModel::SortCriterion EmployeeSortFilterProxyModel::sortCriterion() const
{ return m->sortCriterion; }

void EmployeeSortFilterProxyModel::setSortCriterion(SortCriterion value)
{ m->sortCriterion = value; }

QString EmployeeSortFilterProxyModel::toString(SortCriterion sortCriterion)
{
    switch (sortCriterion) {
    case SortCriterion_Id:          return tr("ID", "sortCriterion");
    case SortCriterion_Name:        return tr("NAME", "sortCriterion");
    case SortCriterion_IsActive:    return tr("IS_ACTIVE", "sortCriterion");
    default:
        break;
    }

    return QString();
}

EmployeeSortFilterProxyModel::FilterCriterion EmployeeSortFilterProxyModel::filterCriterion() const
{ return m->filterCriterion; }

void EmployeeSortFilterProxyModel::setFilterCriterion(FilterCriterion value)
{ m->filterCriterion = value; }

QString EmployeeSortFilterProxyModel::toString(FilterCriterion filterCriterion)
{
    switch (filterCriterion) {
    case FilterCriterion_AcceptActive:      return tr("ACTIVE", "filterCriterion");
    case FilterCriterion_AcceptInactive:    return tr("INACTIVE", "filterCriterion");
    case FilterCriterion_AcceptAll:         return tr("ALL", "filterCriterion");
    default:
        break;
    }

    return QString();
}

void EmployeeSortFilterProxyModel::reapplyFilter()
{
    // to control from outside
    invalidateFilter();
}

bool EmployeeSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    Employee leftEmployee = sourceModel()->data(left, Qt::EditRole).value<Employee>();
    Employee rightEmployee = sourceModel()->data(right, Qt::EditRole).value<Employee>();

    switch (m->sortCriterion) {
    case SortCriterion_Id:          return Impl::employeeLessThanById(leftEmployee, rightEmployee);
    case SortCriterion_Name:        return Impl::employeeLessThanByName(leftEmployee, rightEmployee);
    case SortCriterion_IsActive:    return Impl::employeeLessThanByIsActive(leftEmployee, rightEmployee);
    default:
        break;
    }

    return false;
}

bool EmployeeSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    bool isActive = sourceModel()->data(sourceIndex, EmployeeModel::DataRole_IsActive).toBool();

    switch (m->filterCriterion) {
    case FilterCriterion_AcceptActive:      return isActive;
    case FilterCriterion_AcceptInactive:    return !isActive;
    case FilterCriterion_AcceptAll:
    default:
        break;
    }

    return true;
}

} // namespace MapService
} // namespace Rsl
