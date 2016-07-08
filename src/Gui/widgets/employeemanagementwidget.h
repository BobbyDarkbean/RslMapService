#ifndef EMPLOYEEMANAGEMENTWIDGET_H
#define EMPLOYEEMANAGEMENTWIDGET_H

#include <QWidget>
#include <QScopedPointer>
#include "rmsgui_shared.h"

class QItemSelection;

namespace Rsl {
namespace MapService {

namespace Impl {
struct EmployeeManagementWidgetRepresentation;
}

class RMS_GUI_SHARED EmployeeManagementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeManagementWidget(QWidget *parent = 0);
    ~EmployeeManagementWidget();

signals:
    void employeeEditPerformed(bool success);
    void employeeAppendingPerformed(bool success);
    void employeeRemovalPerformed(int count);

protected:
    void changeEvent(QEvent *);

private slots:
    void filterEmployees(int filterCriterion);
    void sortEmployees(int sortCriterion);
    void changeSortOrder();

    void submitNewEmployee();
    void submitSelectedEmployeeRemoval();

    void updateRemoveButtonState(const QItemSelection &selected, const QItemSelection &deselected);

private:
    Q_DISABLE_COPY(EmployeeManagementWidget)

    friend class Impl::EmployeeManagementWidgetRepresentation;
    QScopedPointer<Impl::EmployeeManagementWidgetRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // EMPLOYEEMANAGEMENTWIDGET_H
