#ifndef EMPLOYEEEDITOR_H
#define EMPLOYEEEDITOR_H

#include <QWidget>
#include <QScopedPointer>
#include "rmsgui_shared.h"

namespace Rsl {
namespace MapService {

namespace Impl {
struct EmployeeEditorRepresentation;
}

class RMS_GUI_SHARED EmployeeEditor : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeEditor(QWidget *parent = 0);
    ~EmployeeEditor();

    bool isPresentationMode() const;
    void setPresentationMode(bool);

    bool isActive() const;
    void setActive(bool);

    QString name() const;
    void setName(const QString &);

    void setId(int);

private:
    Q_DISABLE_COPY(EmployeeEditor)
    QScopedPointer<Impl::EmployeeEditorRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // EMPLOYEEEDITOR_H
