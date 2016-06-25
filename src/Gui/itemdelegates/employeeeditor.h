#ifndef EMPLOYEEEDITOR_H
#define EMPLOYEEEDITOR_H

#include <QScopedPointer>
#include "itemeditor.h"

namespace Rsl {
namespace MapService {

namespace Impl {
struct EmployeeEditorRepresentation;
}

class EmployeeEditor : public ItemEditor
{
    Q_OBJECT

public:
    explicit EmployeeEditor(QWidget *parent = 0);
    ~EmployeeEditor();

    bool isActive() const;
    void setActive(bool);

    QString name() const;
    void setName(const QString &);

    void setId(int);

protected:
    void applyMode();

private:
    Q_DISABLE_COPY(EmployeeEditor)
    QScopedPointer<Impl::EmployeeEditorRepresentation> m_EmployeeEditor;
};

} // namespace MapService
} // namespace Rsl

#endif // EMPLOYEEEDITOR_H
