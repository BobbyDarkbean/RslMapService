#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QGroupBox>
#include <QListView>
#include <QBoxLayout>
#include <QMessageBox>
#include <QEvent>
#include "user.h"
#include "datamodelfacade.h"
#include "itemmodels/currentusermodel.h"
#include "itemmodels/currentusersortfilterproxymodel.h"
#include "itemdelegates/currentuserdelegate.h"
#include "itemdelegates/editedsignaltrigger.h"

#include "currentusermanagementwidget.h"

namespace Rsl {
namespace MapService {

namespace Impl {

const int ListSortColumn = 0;

struct CurrentUserManagementWidgetRepresentation
{
    void init(CurrentUserManagementWidget *);
    void retranslateUi();

    QLabel *filterCriterionLabel;
    QComboBox *filterCriterionBox;
    QLabel *sortCriterionLabel;
    QComboBox *sortCriterionBox;
    QFrame *sortFilterOptionsFrame;

    QListView *usersView;
    QGroupBox *usersGroup;

    QRadioButton *ascOrderButton;
    QRadioButton *descOrderButton;
    QGroupBox *sortOrderBox;

    QPushButton *reloadUsersButton;
    QPushButton *addUserButton;
    QPushButton *removeUserButton;

    CurrentUserModel *userModel;
    CurrentUserSortFilterProxyModel *userProxyModel;
    CurrentUserDelegate *userDelegate;
};

void CurrentUserManagementWidgetRepresentation::init(CurrentUserManagementWidget *w)
{
    // Creation
    filterCriterionLabel = new QLabel;
    filterCriterionBox = new QComboBox;
    sortCriterionLabel = new QLabel;
    sortCriterionBox = new QComboBox;
    sortFilterOptionsFrame = new QFrame;

    usersView = new QListView;
    usersGroup = new QGroupBox;

    ascOrderButton = new QRadioButton;
    descOrderButton = new QRadioButton;
    sortOrderBox = new QGroupBox;

    reloadUsersButton = new QPushButton;
    addUserButton = new QPushButton;
    removeUserButton = new QPushButton;

    userModel = dataModelFacade()->currentUserModel();
    userProxyModel = new CurrentUserSortFilterProxyModel(w);
    userDelegate = new CurrentUserDelegate(w);

    // Initialization
    userProxyModel->setSourceModel(userModel);
    userProxyModel->setFilterCriterion(CurrentUserSortFilterProxyModel::FilterCriterion_AcceptAll);
    userProxyModel->setSortCriterion(CurrentUserSortFilterProxyModel::SortCriterion_Id);
    userProxyModel->sort(Impl::ListSortColumn, Qt::AscendingOrder);

    usersView->setModel(userProxyModel);
    usersView->setItemDelegate(userDelegate);
    usersView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    removeUserButton->setDisabled(true);

    filterCriterionLabel->setBuddy(filterCriterionBox);
    sortCriterionLabel->setBuddy(sortCriterionBox);

    filterCriterionBox->addItem(QString(), CurrentUserSortFilterProxyModel::FilterCriterion_AcceptPresent);
    filterCriterionBox->addItem(QString(), CurrentUserSortFilterProxyModel::FilterCriterion_AcceptAbsent);
    filterCriterionBox->addItem(QString(), CurrentUserSortFilterProxyModel::FilterCriterion_AcceptAll);

    sortCriterionBox->addItem(QString(), CurrentUserSortFilterProxyModel::SortCriterion_Id);
    sortCriterionBox->addItem(QString(), CurrentUserSortFilterProxyModel::SortCriterion_FullNumber);
    sortCriterionBox->addItem(QString(), CurrentUserSortFilterProxyModel::SortCriterion_CardNumber);
    sortCriterionBox->addItem(QString(), CurrentUserSortFilterProxyModel::SortCriterion_Name);
    sortCriterionBox->addItem(QString(), CurrentUserSortFilterProxyModel::SortCriterion_IsOff);

    filterCriterionBox->setCurrentIndex(userProxyModel->filterCriterion());
    sortCriterionBox->setCurrentIndex(userProxyModel->sortCriterion());

    switch (userProxyModel->sortOrder()) {
    case Qt::AscendingOrder:    ascOrderButton->setChecked(true);   break;
    case Qt::DescendingOrder:   descOrderButton->setChecked(true);  break;
    }

    // Connections
    typedef CurrentUserManagementWidget W;
    typedef CurrentUserModel M;

    QItemSelectionModel *selectionModel = usersView->selectionModel();
    QObject::connect(selectionModel,        &QItemSelectionModel::selectionChanged, w,  &W::updateRemoveButtonState);
    QObject::connect(userModel,             &M::modelAboutToBeReset,   selectionModel,  &QItemSelectionModel::clear);

    EditedSignalTrigger *userEditedSignal = userDelegate->userEdited();
    QObject::connect(userEditedSignal,      &EditedSignalTrigger::activated,        w,  &W::userEditPerformed);

    void (QComboBox::*qComboBoxCurrentIndexChanged)(int) = &QComboBox::currentIndexChanged;

    QObject::connect(filterCriterionBox,    qComboBoxCurrentIndexChanged,           w,  &W::filterUsers);
    QObject::connect(sortCriterionBox,      qComboBoxCurrentIndexChanged,           w,  &W::sortUsers);

    QObject::connect(ascOrderButton,        &QAbstractButton::toggled,              w,  &W::changeSortOrder);
    QObject::connect(descOrderButton,       &QAbstractButton::toggled,              w,  &W::changeSortOrder);

    QObject::connect(addUserButton,         &QAbstractButton::clicked,              w,  &W::submitNewUser);
    QObject::connect(removeUserButton,      &QAbstractButton::clicked,              w,  &W::submitSelectedUserRemoval);
    QObject::connect(reloadUsersButton,     &QAbstractButton::clicked,      userModel,  &M::reload);

    // Layout
    QBoxLayout *sortFilterOptionsLayout = new QHBoxLayout;
    sortFilterOptionsLayout->addStretch();
    sortFilterOptionsLayout->addWidget(filterCriterionLabel);
    sortFilterOptionsLayout->addWidget(filterCriterionBox);
    sortFilterOptionsLayout->addStretch();
    sortFilterOptionsLayout->addWidget(sortCriterionLabel);
    sortFilterOptionsLayout->addWidget(sortCriterionBox);
    sortFilterOptionsLayout->addStretch();
    sortFilterOptionsFrame->setLayout(sortFilterOptionsLayout);

    QBoxLayout *sortOrderLayout = new QHBoxLayout;
    sortOrderLayout->addWidget(ascOrderButton);
    sortOrderLayout->addWidget(descOrderButton);
    sortOrderBox->setLayout(sortOrderLayout);

    QBoxLayout *dataControlLayout = new QVBoxLayout;
    dataControlLayout->addStretch();
    dataControlLayout->addWidget(reloadUsersButton);
    dataControlLayout->addWidget(addUserButton);
    dataControlLayout->addWidget(removeUserButton);

    QBoxLayout *sortOrderDataControlLayout = new QHBoxLayout;
    sortOrderDataControlLayout->addWidget(sortOrderBox);
    sortOrderDataControlLayout->addStretch();
    sortOrderDataControlLayout->addLayout(dataControlLayout);

    QBoxLayout *usersLayout = new QVBoxLayout;
    usersLayout->addWidget(usersView, 1);
    usersLayout->addLayout(sortOrderDataControlLayout, 0);
    usersGroup->setLayout(usersLayout);

    QBoxLayout *userManagementLayout = new QVBoxLayout;
    userManagementLayout->addWidget(sortFilterOptionsFrame);
    userManagementLayout->addWidget(usersGroup);
    w->setLayout(userManagementLayout);
}

void CurrentUserManagementWidgetRepresentation::retranslateUi()
{
    typedef CurrentUserSortFilterProxyModel PrxMdl;

    filterCriterionLabel->setText(QObject::tr("FILTER_CRITERION", "labeltext"));

    for (int i = 0; i < filterCriterionBox->count(); ++i) {
        PrxMdl::FilterCriterion filterCriterion = PrxMdl::FilterCriterion(i);
        filterCriterionBox->setItemText(i, PrxMdl::toString(filterCriterion));
    }

    sortCriterionLabel->setText(QObject::tr("SORT_CRITERION", "labeltext"));

    for (int i = 0; i < sortCriterionBox->count(); ++i) {
        PrxMdl::SortCriterion sortCriterion = PrxMdl::SortCriterion(i);
        sortCriterionBox->setItemText(i, PrxMdl::toString(sortCriterion));
    }

    sortOrderBox->setTitle(QObject::tr("SORT_ORDER"));
    ascOrderButton->setText(QObject::tr("ASCENDING", "sortOrder"));
    descOrderButton->setText(QObject::tr("DESCENDING", "sortOrder"));

    usersGroup->setTitle(CurrentUserManagementWidget::tr("USERS"));
    reloadUsersButton->setText(QObject::tr("UPDATE"));
    addUserButton->setText(QObject::tr("ADD"));
    removeUserButton->setText(QObject::tr("REMOVE"));
}

} // namespace Impl

CurrentUserManagementWidget::CurrentUserManagementWidget(QWidget *parent)
    : QWidget(parent)
    , m(new Impl::CurrentUserManagementWidgetRepresentation)
{
    m->init(this);
    m->retranslateUi();
}

CurrentUserManagementWidget::~CurrentUserManagementWidget()
{
}

void CurrentUserManagementWidget::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        m->retranslateUi();
    else
        QWidget::changeEvent(e);
}

void CurrentUserManagementWidget::filterUsers(int filterCriterion)
{
    m->userProxyModel->setFilterCriterion(CurrentUserSortFilterProxyModel::FilterCriterion(filterCriterion));
    m->userProxyModel->reapplyFilter();
}

void CurrentUserManagementWidget::sortUsers(int sortCriterion)
{
    m->userProxyModel->setSortCriterion(CurrentUserSortFilterProxyModel::SortCriterion(sortCriterion));
    m->userProxyModel->sort(Impl::ListSortColumn, m->userProxyModel->sortOrder());
    // model remapping required since neither sorting column nor sort order has been changed
    m->userProxyModel->invalidate();
}

void CurrentUserManagementWidget::changeSortOrder()
{
    if (m->ascOrderButton->isChecked()) {
        m->userProxyModel->sort(Impl::ListSortColumn, Qt::AscendingOrder);
    } else if (m->descOrderButton->isChecked()) {
        m->userProxyModel->sort(Impl::ListSortColumn, Qt::DescendingOrder);
    }
}

void CurrentUserManagementWidget::submitNewUser()
{
    User user;

    bool dataAppended = m->userModel->appendData(user);
    emit userAppendingPerformed(dataAppended);
}

void CurrentUserManagementWidget::submitSelectedUserRemoval()
{
    if (QMessageBox::question(this, tr("CONFIRM_REMOVE_TITLE"), tr("CONFIRM_REMOVE_TEXT")) != QMessageBox::Yes)
        return;

    QVector<int> idsToRemove;
    QItemSelectionModel *selectionModel = m->usersView->selectionModel();
    foreach (const QModelIndex &index, selectionModel->selectedIndexes())
        idsToRemove << index.data(CurrentUserModel::DataRole_Id).toInt();

    int removedRecordsCount = m->userModel->removeData(idsToRemove);
    emit userRemovalPerformed(removedRecordsCount);
}

void CurrentUserManagementWidget::updateRemoveButtonState(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QItemSelectionModel *selectionModel = m->usersView->selectionModel();
    m->removeUserButton->setDisabled(selectionModel->selectedIndexes().isEmpty());
}

} // namespace MapService
} // namespace Rsl
