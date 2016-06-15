#ifndef CURRENTUSERSORTFILTERPROXYMODEL_H
#define CURRENTUSERSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QScopedPointer>
#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

namespace Impl {
struct CurrentUserSortFilterProxyModelRepresentation;
}

class RMS_LOGIC_SHARED CurrentUserSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    enum SortCriterion {
        SortCriterion_Id,
        SortCriterion_FullNumber,
        SortCriterion_CardNumber,
        SortCriterion_Name,
        SortCriterion_IsOff
    };

    enum FilterCriterion {
        FilterCriterion_AcceptPresent,
        FilterCriterion_AcceptAbsent,
        FilterCriterion_AcceptAll
    };

    explicit CurrentUserSortFilterProxyModel(QObject *parent = 0);
    ~CurrentUserSortFilterProxyModel();

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
    Q_DISABLE_COPY(CurrentUserSortFilterProxyModel)
    QScopedPointer<Impl::CurrentUserSortFilterProxyModelRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTUSERSORTFILTERPROXYMODEL_H
