#ifndef CURRENTUSERMANAGEMENTWIDGET_H
#define CURRENTUSERMANAGEMENTWIDGET_H

#include <QWidget>
#include <QScopedPointer>
#include "rmsgui_shared.h"

class QItemSelection;

namespace Rsl {
namespace MapService {

namespace Impl {
struct CurrentUserManagementWidgetRepresentation;
}

class RMS_GUI_SHARED CurrentUserManagementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentUserManagementWidget(QWidget *parent = 0);
    ~CurrentUserManagementWidget();

signals:
    void userEditPerformed(bool success);
    void userAppendingPerformed(bool success);
    void userRemovalPerformed(int count);

protected:
    void changeEvent(QEvent *);

private slots:
    void filterUsers(int filterCriterion);
    void sortUsers(int sortCriterion);
    void changeSortOrder();

    void submitNewUser();
    void submitSelectedUserRemoval();
    void reloadModelData();

    void updateRemoveButtonState(const QItemSelection &selected, const QItemSelection &deselected);

private:
    Q_DISABLE_COPY(CurrentUserManagementWidget)

    friend class Impl::CurrentUserManagementWidgetRepresentation;
    QScopedPointer<Impl::CurrentUserManagementWidgetRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTUSERMANAGEMENTWIDGET_H
