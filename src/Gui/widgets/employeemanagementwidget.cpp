#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QGroupBox>
#include <QListView>
#include <QBoxLayout>
#include <QMessageBox>
#include <QEvent>
#include "rms_global.h"
#include "employee.h"
#include "itemmodels/employeemodel.h"
#include "itemmodels/employeesortfilterproxymodel.h"
#include "itemdelegates/employeedelegate.h"
#include "itemdelegates/editedsignaltrigger.h"

#include "employeemanagementwidget.h"

namespace Rsl {
namespace MapService {

namespace Impl {

const int ListSortColumn = 0;

struct EmployeeManagementWidgetRepresentation
{
    void init(EmployeeManagementWidget *);
    void retranslateUi();

    QLabel *filterCriterionLabel;
    QComboBox *filterCriterionBox;
    QLabel *sortCriterionLabel;
    QComboBox *sortCriterionBox;
    QFrame *sortFilterOptionsFrame;

    QListView *employeesView;
    QGroupBox *employeesGroup;

    QRadioButton *ascOrderButton;
    QRadioButton *descOrderButton;
    QGroupBox *sortOrderBox;

    QPushButton *reloadEmployeesButton;
    QPushButton *removeEmployeeButton;

    QLabel *newEmployeeLabel;
    QLineEdit *newEmployeeBox;
    QPushButton *addEmployeeButton;
    QGroupBox *newEmployeeGroup;

    EmployeeModel *employeeModel;
    EmployeeSortFilterProxyModel *employeeProxyModel;
    EmployeeDelegate *employeeDelegate;
};

void EmployeeManagementWidgetRepresentation::init(EmployeeManagementWidget *w)
{
    // Creation
    filterCriterionLabel = new QLabel;
    filterCriterionBox = new QComboBox;
    sortCriterionLabel = new QLabel;
    sortCriterionBox = new QComboBox;
    sortFilterOptionsFrame = new QFrame;

    employeesView = new QListView;
    employeesGroup = new QGroupBox;

    ascOrderButton = new QRadioButton;
    descOrderButton = new QRadioButton;
    sortOrderBox = new QGroupBox;

    reloadEmployeesButton = new QPushButton;
    removeEmployeeButton = new QPushButton;

    newEmployeeLabel = new QLabel;
    newEmployeeBox = new QLineEdit;
    addEmployeeButton = new QPushButton;
    newEmployeeGroup = new QGroupBox;

    employeeModel = new EmployeeModel(w);
    employeeProxyModel = new EmployeeSortFilterProxyModel(w);
    employeeDelegate = new EmployeeDelegate(w);

    // Initialization
    employeeProxyModel->setSourceModel(employeeModel);
    employeeProxyModel->setFilterCriterion(EmployeeSortFilterProxyModel::FilterCriterion_AcceptAll);
    employeeProxyModel->setSortCriterion(EmployeeSortFilterProxyModel::SortCriterion_Name);
    employeeProxyModel->sort(Impl::ListSortColumn, Qt::AscendingOrder);

    employeesView->setModel(employeeProxyModel);
    employeesView->setItemDelegate(employeeDelegate);
    employeesView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    removeEmployeeButton->setDisabled(true);

    filterCriterionLabel->setBuddy(filterCriterionBox);
    sortCriterionLabel->setBuddy(sortCriterionBox);
    newEmployeeLabel->setBuddy(newEmployeeBox);

    newEmployeeBox->setValidator(new QRegExpValidator(QRegExp(WrittenNameRegExp), newEmployeeBox));

    filterCriterionBox->addItem(QString(), EmployeeSortFilterProxyModel::FilterCriterion_AcceptActive);
    filterCriterionBox->addItem(QString(), EmployeeSortFilterProxyModel::FilterCriterion_AcceptInactive);
    filterCriterionBox->addItem(QString(), EmployeeSortFilterProxyModel::FilterCriterion_AcceptAll);

    sortCriterionBox->addItem(QString(), EmployeeSortFilterProxyModel::SortCriterion_Id);
    sortCriterionBox->addItem(QString(), EmployeeSortFilterProxyModel::SortCriterion_Name);
    sortCriterionBox->addItem(QString(), EmployeeSortFilterProxyModel::SortCriterion_IsActive);

    filterCriterionBox->setCurrentIndex(employeeProxyModel->filterCriterion());
    sortCriterionBox->setCurrentIndex(employeeProxyModel->sortCriterion());

    switch (employeeProxyModel->sortOrder()) {
    case Qt::AscendingOrder:    ascOrderButton->setChecked(true);   break;
    case Qt::DescendingOrder:   descOrderButton->setChecked(true);  break;
    }

    // Connections
    typedef EmployeeManagementWidget W;

    QItemSelectionModel *selectionModel = employeesView->selectionModel();
    QObject::connect(selectionModel,        &QItemSelectionModel::selectionChanged, w,  &W::updateRemoveButtonState);

    EditedSignalTrigger *employeeEditedSignal = employeeDelegate->employeeEdited();
    QObject::connect(employeeEditedSignal,  &EditedSignalTrigger::activated,        w,  &W::employeeEditPerformed);

    void (QComboBox::*qComboBoxCurrentIndexChanged)(int) = &QComboBox::currentIndexChanged;

    QObject::connect(filterCriterionBox,    qComboBoxCurrentIndexChanged,           w,  &W::filterEmployees);
    QObject::connect(sortCriterionBox,      qComboBoxCurrentIndexChanged,           w,  &W::sortEmployees);

    QObject::connect(ascOrderButton,        &QAbstractButton::toggled,              w,  &W::changeSortOrder);
    QObject::connect(descOrderButton,       &QAbstractButton::toggled,              w,  &W::changeSortOrder);

    QObject::connect(addEmployeeButton,     &QAbstractButton::clicked,              w,  &W::submitNewEmployee);
    QObject::connect(removeEmployeeButton,  &QAbstractButton::clicked,              w,  &W::submitSelectedEmployeeRemoval);
    QObject::connect(reloadEmployeesButton, &QAbstractButton::clicked,              w,  &W::reloadModelData);

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

    QBoxLayout *employeesViewLayout = new QVBoxLayout;
    employeesViewLayout->addWidget(employeesView);

    QBoxLayout *sortOrderLayout = new QVBoxLayout;
    sortOrderLayout->addWidget(ascOrderButton);
    sortOrderLayout->addWidget(descOrderButton);
    sortOrderBox->setLayout(sortOrderLayout);

    QBoxLayout *dataControlLayout = new QVBoxLayout;
    dataControlLayout->addWidget(reloadEmployeesButton);
    dataControlLayout->addWidget(removeEmployeeButton);

    QBoxLayout *dataControlWrapperLayout = new QHBoxLayout;
    dataControlWrapperLayout->addStretch();
    dataControlWrapperLayout->addLayout(dataControlLayout);

    QBoxLayout *sortOrderDataControlLayout = new QVBoxLayout;
    sortOrderDataControlLayout->addWidget(sortOrderBox);
    sortOrderDataControlLayout->addStretch();
    sortOrderDataControlLayout->addLayout(dataControlWrapperLayout);

    QBoxLayout *employeesLayout = new QHBoxLayout;
    employeesLayout->addLayout(employeesViewLayout, 2);
    employeesLayout->addLayout(sortOrderDataControlLayout, 1);
    employeesGroup->setLayout(employeesLayout);

    QBoxLayout *newEmployeeLayout = new QHBoxLayout;
    newEmployeeLayout->addWidget(newEmployeeLabel);
    newEmployeeLayout->addWidget(newEmployeeBox);
    newEmployeeLayout->addWidget(addEmployeeButton);
    newEmployeeGroup->setLayout(newEmployeeLayout);

    QBoxLayout *employeeManagementLayout = new QVBoxLayout;
    employeeManagementLayout->addWidget(sortFilterOptionsFrame);
    employeeManagementLayout->addWidget(employeesGroup);
    employeeManagementLayout->addWidget(newEmployeeGroup);
    w->setLayout(employeeManagementLayout);
}

void EmployeeManagementWidgetRepresentation::retranslateUi()
{
    typedef EmployeeSortFilterProxyModel PrxMdl;

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

    employeesGroup->setTitle(EmployeeManagementWidget::tr("EMPLOYEES"));
    reloadEmployeesButton->setText(QObject::tr("UPDATE"));
    removeEmployeeButton->setText(QObject::tr("REMOVE"));

    newEmployeeGroup->setTitle(EmployeeManagementWidget::tr("NEW_EMPLOYEE"));
    newEmployeeLabel->setText(QObject::tr("NAME"));
    addEmployeeButton->setText(QObject::tr("ADD"));
}

} // namespace Impl

EmployeeManagementWidget::EmployeeManagementWidget(QWidget *parent)
    : QWidget(parent)
    , m(new Impl::EmployeeManagementWidgetRepresentation)
{
    m->init(this);
    m->retranslateUi();
}

EmployeeManagementWidget::~EmployeeManagementWidget()
{
}

void EmployeeManagementWidget::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        m->retranslateUi();
    else
        QWidget::changeEvent(e);
}

void EmployeeManagementWidget::filterEmployees(int filterCriterion)
{
    m->employeeProxyModel->setFilterCriterion(EmployeeSortFilterProxyModel::FilterCriterion(filterCriterion));
    m->employeeProxyModel->reapplyFilter();
}

void EmployeeManagementWidget::sortEmployees(int sortCriterion)
{
    m->employeeProxyModel->setSortCriterion(EmployeeSortFilterProxyModel::SortCriterion(sortCriterion));
    m->employeeProxyModel->sort(Impl::ListSortColumn, m->employeeProxyModel->sortOrder());
    // model remapping required since neither sorting column nor sort order has been changed
    m->employeeProxyModel->invalidate();
}

void EmployeeManagementWidget::changeSortOrder()
{
    if (m->ascOrderButton->isChecked()) {
        m->employeeProxyModel->sort(Impl::ListSortColumn, Qt::AscendingOrder);
    } else if (m->descOrderButton->isChecked()) {
        m->employeeProxyModel->sort(Impl::ListSortColumn, Qt::DescendingOrder);
    }
}

void EmployeeManagementWidget::submitNewEmployee()
{
    QString name = m->newEmployeeBox->text().trimmed().simplified();
    if (name.isEmpty())
        return;

    Employee employee;
    employee.setName(name);
    employee.setActive(true);

    bool dataAppended = m->employeeModel->appendData(employee);
    if (dataAppended)
        m->newEmployeeBox->clear();

    emit employeeAppendingPerformed(dataAppended);
}

void EmployeeManagementWidget::submitSelectedEmployeeRemoval()
{
    if (QMessageBox::question(this, tr("CONFIRM_REMOVE_TITLE"), tr("CONFIRM_REMOVE_TEXT")) != QMessageBox::Yes)
        return;

    QVector<int> idsToRemove;
    QItemSelectionModel *selectionModel = m->employeesView->selectionModel();
    foreach (const QModelIndex &index, selectionModel->selectedIndexes())
        idsToRemove << index.data(EmployeeModel::DataRole_Id).toInt();

    int removedRecordsCount = m->employeeModel->removeData(idsToRemove);
    emit employeeRemovalPerformed(removedRecordsCount);
}

void EmployeeManagementWidget::reloadModelData()
{
    m->employeesView->selectionModel()->clear();
    m->employeeModel->reload();
}

void EmployeeManagementWidget::updateRemoveButtonState(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QItemSelectionModel *selectionModel = m->employeesView->selectionModel();
    m->removeEmployeeButton->setDisabled(selectionModel->selectedIndexes().isEmpty());
}

} // namespace MapService
} // namespace Rsl
