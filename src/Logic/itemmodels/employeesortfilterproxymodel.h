#ifndef EMPLOYEESORTFILTERPROXYMODEL_H
#define EMPLOYEESORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QScopedPointer>
#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

namespace Impl {
struct EmployeeSortFilterProxyModelRepresentation;
}

class RMS_LOGIC_SHARED EmployeeSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    enum SortCriterion {
        SortCriterion_Id,
        SortCriterion_Name,
        SortCriterion_IsActive
    };

    enum FilterCriterion {
        FilterCriterion_AcceptActive,
        FilterCriterion_AcceptInactive,
        FilterCriterion_AcceptAll
    };

    explicit EmployeeSortFilterProxyModel(QObject *parent = 0);
    ~EmployeeSortFilterProxyModel();

    SortCriterion sortCriterion() const;
    void setSortCriterion(SortCriterion);
    static QString toString(SortCriterion);

    FilterCriterion filterCriterion() const;
    void setFilterCriterion(FilterCriterion);
    static QString toString(FilterCriterion);

    void reapplyFilter();

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(EmployeeSortFilterProxyModel)
    QScopedPointer<Impl::EmployeeSortFilterProxyModelRepresentation> m;
};


} // namespace MapService
} // namespace Rsl

#endif // EMPLOYEESORTFILTERPROXYMODEL_H
