#include <QStackedWidget>
#include <QDockWidget>
#include <QStatusBar>
#include <QEvent>
#include <QMap>
#include "widgets/currentusermanagementwidget.h"
#include "widgets/employeemanagementwidget.h"

#include "mainwindow.h"

namespace Rsl {
namespace MapService {

enum CentralWidgetMode {
    CentralWidgetMode_EmployeeManagement
};

namespace Impl {

struct MainWindowRepresentation
{
    void init(MainWindow *);
    void retranslateUi(MainWindow *);

    QStackedWidget *centralWidget;

    QDockWidget *currentUsersDock;

    QMap<int, int> centralWidgetMapping;
};

void MainWindowRepresentation::init(MainWindow *w)
{
    // Modes
    centralWidget = new QStackedWidget;

    EmployeeManagementWidget *employeeManagementWidget = new EmployeeManagementWidget;
    int employeeManagementWidgetIndex = centralWidget->addWidget(employeeManagementWidget);

    centralWidgetMapping[CentralWidgetMode_EmployeeManagement] = employeeManagementWidgetIndex;

    // Widgets
    CurrentUserManagementWidget *userManagementWidget = new CurrentUserManagementWidget(w);

    // Docks
    currentUsersDock = new QDockWidget(w);
    currentUsersDock->setWidget(userManagementWidget);
    currentUsersDock->setFeatures(QDockWidget::DockWidgetMovable);
    currentUsersDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    w->addDockWidget(Qt::LeftDockWidgetArea, currentUsersDock);

    // Connections
    typedef MainWindow W;
    typedef EmployeeManagementWidget EMW;

    QObject::connect(employeeManagementWidget,  &EMW::employeeEditPerformed,        w,  &W::reportEmployeeEdited);
    QObject::connect(employeeManagementWidget,  &EMW::employeeAppendingPerformed,   w,  &W::reportEmployeeAppending);
    QObject::connect(employeeManagementWidget,  &EMW::employeeRemovalPerformed,     w,  &W::reportEmployeeRemoval);

    typedef CurrentUserManagementWidget UMW;

    QObject::connect(userManagementWidget,      &UMW::userEditPerformed,            w,  &W::reportUserEdited);
    QObject::connect(userManagementWidget,      &UMW::userAppendingPerformed,       w,  &W::reportUserAppending);
    QObject::connect(userManagementWidget,      &UMW::userRemovalPerformed,         w,  &W::reportUserRemoval);

    w->setCentralWidget(centralWidget);
}

void MainWindowRepresentation::retranslateUi(MainWindow *w)
{
    w->statusBar()->showMessage(MainWindow::tr("DONE"));
}

} // namespace Impl

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m(new Impl::MainWindowRepresentation)
{
    m->init(this);
    m->retranslateUi(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        m->retranslateUi(this);
    else
        QMainWindow::changeEvent(e);
}

void MainWindow::reportUserEdited(bool success)
{ statusBar()->showMessage(success ? tr("USER_EDIT_ACCEPTED") : tr("USER_EDIT_FAILED")); }

void MainWindow::reportUserAppending(bool success)
{ statusBar()->showMessage(success ? tr("USER_APPEND_ACCEPTED") : tr("USER_APPEND_FAILED")); }

void MainWindow::reportUserRemoval(int count)
{ statusBar()->showMessage(tr("USERS_REMOVED_%1").arg(count)); }

void MainWindow::reportEmployeeEdited(bool success)
{ statusBar()->showMessage(success ? tr("EMPLOYEE_EDIT_ACCEPTED") : tr("EMPLOYEE_EDIT_FAILED")); }

void MainWindow::reportEmployeeAppending(bool success)
{ statusBar()->showMessage(success ? tr("EMPLOYEE_APPEND_ACCEPTED") : tr("EMPLOYEE_APPEND_FAILED")); }

void MainWindow::reportEmployeeRemoval(int count)
{ statusBar()->showMessage(tr("EMPLOYEES_REMOVED_%1").arg(count)); }

} // namespace MapService
} // namespace Rsl
