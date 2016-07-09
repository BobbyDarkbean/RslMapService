#include <QPushButton>
#include <QGroupBox>
#include <QListView>
#include <QStackedWidget>
#include <QBoxLayout>
#include <QMessageBox>
#include <QEvent>
#include "request.h"
#include "datamodelfacade.h"
#include "itemmodels/currentrequestmodel.h"
#include "itemmodels/currentusermodel.h"
#include "itemdelegates/currentrequestdelegate.h"
#include "itemdelegates/currentrequesteditor.h"
#include "itemdelegates/editedsignaltrigger.h"

#include "currentrequestmanagementwidget.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct CurrentRequestManagementWidgetRepresentation
{
    void init(CurrentRequestManagementWidget *);
    void retranslateUi();

    QStackedWidget *pager;

    QListView *requestsView;
    QPushButton *addRequestButton;
    QPushButton *reloadRequestsButton;
    QPushButton *removeRequestButton;
    QGroupBox *requestsGroup;

    CurrentRequestEditor *requestPresenter;
    QWidget *offScreenPage;

    CurrentRequestModel *requestModel;
    CurrentRequestDelegate *requestDelegate;
};

void CurrentRequestManagementWidgetRepresentation::init(CurrentRequestManagementWidget *w)
{
    // Creation
    pager = new QStackedWidget;

    requestsView = new QListView;
    addRequestButton = new QPushButton;
    reloadRequestsButton = new QPushButton;
    removeRequestButton = new QPushButton;
    requestsGroup = new QGroupBox;

    requestPresenter = new CurrentRequestEditor;
    offScreenPage = new QWidget;

    requestModel = dataModelFacade()->currentRequestModel();
    requestDelegate = new CurrentRequestDelegate(w);

    // Initialization
    requestPresenter->setPresentationMode(true);
    requestPresenter->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    requestDelegate->setPresenter(requestPresenter);

    requestsView->setModel(requestModel);
    requestsView->setItemDelegate(requestDelegate);
    requestsView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    removeRequestButton->setDisabled(true);

    // Connections
    typedef CurrentRequestManagementWidget W;
    typedef CurrentRequestModel M;
    typedef CurrentUserModel U;

    QItemSelectionModel *selectionModel = requestsView->selectionModel();
    QObject::connect(selectionModel,        &QItemSelectionModel::selectionChanged, w,  &W::updateRemoveButtonState);
    QObject::connect(requestModel,          &M::modelAboutToBeReset,   selectionModel,  &QItemSelectionModel::clear);

    EditedSignalTrigger *requestEditedSignal = requestDelegate->requestEdited();
    QObject::connect(requestEditedSignal,   &EditedSignalTrigger::activated,        w,  &W::requestEditPerformed);

    QObject::connect(addRequestButton,      &QAbstractButton::clicked,              w,  &W::submitNewRequest);
    QObject::connect(removeRequestButton,   &QAbstractButton::clicked,              w,  &W::submitSelectedRequestRemoval);
    QObject::connect(reloadRequestsButton,  &QAbstractButton::clicked,   requestModel,  &M::reload);

    CurrentUserModel *userModel = dataModelFacade()->currentUserModel();
    QObject::connect(userModel,             &U::userChanged,             requestModel,  &M::reload);

    // Layout
    QBoxLayout *dataControlLayout = new QHBoxLayout;
    dataControlLayout->addStretch();
    dataControlLayout->addWidget(addRequestButton);
    dataControlLayout->addWidget(reloadRequestsButton);
    dataControlLayout->addWidget(removeRequestButton);

    QBoxLayout *requestsLayout = new QVBoxLayout;
    requestsLayout->addWidget(requestsView, 1);
    requestsLayout->addLayout(dataControlLayout, 0);
    requestsGroup->setLayout(requestsLayout);

    QBoxLayout *offScreenLayout = new QVBoxLayout;
    offScreenLayout->addWidget(requestPresenter);
    offScreenLayout->addStretch();
    offScreenPage->setLayout(offScreenLayout);

    pager->addWidget(requestsGroup);
    pager->addWidget(offScreenPage);

    QBoxLayout *requestManagementLayout = new QVBoxLayout;
    requestManagementLayout->addWidget(pager);
    w->setLayout(requestManagementLayout);
}

void CurrentRequestManagementWidgetRepresentation::retranslateUi()
{
    requestsGroup->setTitle(CurrentRequestManagementWidget::tr("REQUESTS"));
    addRequestButton->setText(QObject::tr("ADD"));
    reloadRequestsButton->setText(QObject::tr("UPDATE"));
    removeRequestButton->setText(QObject::tr("REMOVE"));
}

} // namespace Impl

CurrentRequestManagementWidget::CurrentRequestManagementWidget(QWidget *parent)
    : QWidget(parent)
    , m(new Impl::CurrentRequestManagementWidgetRepresentation)
{
    m->init(this);
    m->retranslateUi();
}

CurrentRequestManagementWidget::~CurrentRequestManagementWidget()
{
}

void CurrentRequestManagementWidget::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        m->retranslateUi();
    else
        QWidget::changeEvent(e);
}

void CurrentRequestManagementWidget::submitNewRequest()
{
    Request request;

    bool dataAppended = m->requestModel->appendData(request);
    emit requestAppendingPerformed(dataAppended);
}

void CurrentRequestManagementWidget::submitSelectedRequestRemoval()
{
    if (QMessageBox::question(this, tr("CONFIRM_REMOVE_TITLE"), tr("CONFIRM_REMOVE_TEXT")) != QMessageBox::Yes)
        return;

    QVector<int> idsToRemove;
    QItemSelectionModel *selectionModel = m->requestsView->selectionModel();
    foreach (const QModelIndex &index, selectionModel->selectedIndexes())
        idsToRemove << index.data(CurrentRequestModel::DataRole_Id).toInt();

    int removedRecordsCount = m->requestModel->removeData(idsToRemove);
    emit requestRemovalPerformed(removedRecordsCount);
}

void CurrentRequestManagementWidget::updateRemoveButtonState(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QItemSelectionModel *selectionModel = m->requestsView->selectionModel();
    m->removeRequestButton->setDisabled(selectionModel->selectedIndexes().isEmpty());
}

} // namespace MapService
} // namespace Rsl
