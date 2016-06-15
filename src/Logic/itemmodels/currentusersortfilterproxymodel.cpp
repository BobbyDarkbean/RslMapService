#include "user.h"
#include "currentusermodel.h"

#include "currentusersortfilterproxymodel.h"

namespace Rsl {
namespace MapService {

namespace Impl {

bool userLessThanById(const User &a, const User &b)
{
    return a.id() < b.id();
}

bool userLessThanByCardNumber(const User &a, const User &b)
{
    if (a.cardNumber() == b.cardNumber())
        return userLessThanById(a, b);
    return a.cardNumber() < b.cardNumber();
}

bool userLessThanByFullNumber(const User &a, const User &b)
{
    if (a.hallNumber() == b.hallNumber())
        return userLessThanByCardNumber(a, b);
    return a.hallNumber() < b.hallNumber();
}

bool userLessThanByName(const User &a, const User &b)
{
    int nameCompare = QString::localeAwareCompare(a.name(), b.name());
    if (nameCompare == 0)
        return userLessThanByFullNumber(a, b);
    return nameCompare < 0;
}

bool userLessThanByIsOff(const User &a, const User &b)
{
    if (a.isOff() == b.isOff())
        return userLessThanByName(a, b);
    return !a.isOff();
}

struct CurrentUserSortFilterProxyModelRepresentation
{
    void init();

    CurrentUserSortFilterProxyModel::SortCriterion sortCriterion;
    CurrentUserSortFilterProxyModel::FilterCriterion filterCriterion;
};

void CurrentUserSortFilterProxyModelRepresentation::init()
{
    sortCriterion = CurrentUserSortFilterProxyModel::SortCriterion_Id;
    filterCriterion = CurrentUserSortFilterProxyModel::FilterCriterion_AcceptAll;
}

} // namespace Impl

CurrentUserSortFilterProxyModel::CurrentUserSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , m(new Impl::CurrentUserSortFilterProxyModelRepresentation)
{
    m->init();
}

CurrentUserSortFilterProxyModel::~CurrentUserSortFilterProxyModel()
{
}

CurrentUserSortFilterProxyModel::SortCriterion CurrentUserSortFilterProxyModel::sortCriterion() const
{ return m->sortCriterion; }

void CurrentUserSortFilterProxyModel::setSortCriterion(CurrentUserSortFilterProxyModel::SortCriterion value)
{ m->sortCriterion = value; }

QString CurrentUserSortFilterProxyModel::toString(CurrentUserSortFilterProxyModel::SortCriterion sortCriterion)
{
    switch (sortCriterion) {
    case SortCriterion_Id:          return tr("ID", "sortCriterion");
    case SortCriterion_FullNumber:  return tr("FULL_NUMBER", "sortCriterion");
    case SortCriterion_CardNumber:  return tr("CARD_NUMBER", "sortCriterion");
    case SortCriterion_Name:        return tr("NAME", "sortCriterion");
    case SortCriterion_IsOff:       return tr("IS_OFF", "sortCriterion");
    default:
        break;
    }

    return QString();
}

CurrentUserSortFilterProxyModel::FilterCriterion CurrentUserSortFilterProxyModel::filterCriterion() const
{ return m->filterCriterion; }

void CurrentUserSortFilterProxyModel::setFilterCriterion(CurrentUserSortFilterProxyModel::FilterCriterion value)
{ m->filterCriterion = value; }

QString CurrentUserSortFilterProxyModel::toString(CurrentUserSortFilterProxyModel::FilterCriterion filterCriterion)
{
    switch (filterCriterion) {
    case FilterCriterion_AcceptPresent:     return tr("PRESENT", "filterCriterion");
    case FilterCriterion_AcceptAbsent:      return tr("ABSENT", "filterCriterion");
    case FilterCriterion_AcceptAll:         return tr("ALL", "filterCriterion");
    default:
        break;
    }

    return QString();
}

void CurrentUserSortFilterProxyModel::reapplyFilter()
{
    // to control from outside
    invalidateFilter();
}

bool CurrentUserSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    User leftUser = sourceModel()->data(left, Qt::EditRole).value<User>();
    User rightUser = sourceModel()->data(right, Qt::EditRole).value<User>();

    switch (m->sortCriterion) {
    case SortCriterion_Id:          return Impl::userLessThanById(leftUser, rightUser);
    case SortCriterion_FullNumber:  return Impl::userLessThanByFullNumber(leftUser, rightUser);
    case SortCriterion_CardNumber:  return Impl::userLessThanByCardNumber(leftUser, rightUser);
    case SortCriterion_Name:        return Impl::userLessThanByName(leftUser, rightUser);
    case SortCriterion_IsOff:       return Impl::userLessThanByIsOff(leftUser, rightUser);
    default:
        break;
    }

    return false;
}

bool CurrentUserSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    bool isOff = sourceModel()->data(sourceIndex, CurrentUserModel::DataRole_IsOff).toBool();

    switch (m->filterCriterion) {
    case FilterCriterion_AcceptPresent:     return !isOff;
    case FilterCriterion_AcceptAbsent:      return isOff;
    case FilterCriterion_AcceptAll:
    default:
        break;
    }

    return true;
}

} // namespace MapService
} // namespace Rsl
