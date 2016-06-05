#include <QStackedWidget>
#include <QStatusBar>
#include <QEvent>
#include <QMap>
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
    void retranslateUi();

    QStackedWidget *centralWidget;

    QMap<int, int> centralWidgetMapping;
};

void MainWindowRepresentation::init(MainWindow *w)
{
    centralWidget = new QStackedWidget;

    EmployeeManagementWidget *employeeManagementWidget = new EmployeeManagementWidget;
    int employeeManagementWidgetIndex = centralWidget->addWidget(employeeManagementWidget);

    centralWidgetMapping[CentralWidgetMode_EmployeeManagement] = employeeManagementWidgetIndex;

    typedef MainWindow W;
    typedef EmployeeManagementWidget EMW;

    QObject::connect(employeeManagementWidget,  &EMW::employeeEditPerformed,        w,  &W::reportEmployeeEdited);
    QObject::connect(employeeManagementWidget,  &EMW::employeeAppendingPerformed,   w,  &W::reportEmployeeAppending);
    QObject::connect(employeeManagementWidget,  &EMW::employeeRemovalPerformed,     w,  &W::reportEmployeeRemoval);

    w->setCentralWidget(centralWidget);
}

void MainWindowRepresentation::retranslateUi()
{
}

} // namespace Impl

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m(new Impl::MainWindowRepresentation)
{
    m->init(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        m->retranslateUi();
    else
        QMainWindow::changeEvent(e);
}

void MainWindow::reportEmployeeEdited(bool success)
{ statusBar()->showMessage(success ? tr("EMPLOYEE_EDIT_ACCEPTED") : tr("EMPLOYEE_EDIT_FAILED")); }

void MainWindow::reportEmployeeAppending(bool success)
{ statusBar()->showMessage(success ? tr("EMPLOYEE_APPEND_ACCEPTED") : tr("EMPLOYEE_APPEND_FAILED")); }

void MainWindow::reportEmployeeRemoval(int count)
{ statusBar()->showMessage(tr("EMPLOYEES_REMOVED_%1").arg(count)); }

} // namespace MapService
} // namespace Rsl
