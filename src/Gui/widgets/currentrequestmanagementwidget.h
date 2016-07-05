#ifndef CURRENTREQUESTMANAGEMENTWIDGET_H
#define CURRENTREQUESTMANAGEMENTWIDGET_H

#include <QWidget>
#include <QScopedPointer>
#include "rmsgui_shared.h"

class QItemSelection;

namespace Rsl {
namespace MapService {

namespace Impl {
struct CurrentRequestManagementWidgetRepresentation;
}

class RMS_GUI_SHARED CurrentRequestManagementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentRequestManagementWidget(QWidget *parent = 0);
    ~CurrentRequestManagementWidget();

signals:
    void requestEditPerformed(bool success);
    void requestAppendingPerformed(bool success);
    void requestRemovalPerformed(int count);

protected:
    void changeEvent(QEvent *);

private slots:
    void submitNewRequest();
    void submitSelectedRequestRemoval();
    void reloadModelData();

    void updateRemoveButtonState(const QItemSelection &selected, const QItemSelection &deselected);

private:
    Q_DISABLE_COPY(CurrentRequestManagementWidget)

    friend class Impl::CurrentRequestManagementWidgetRepresentation;
    QScopedPointer<Impl::CurrentRequestManagementWidgetRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTREQUESTMANAGEMENTWIDGET_H
