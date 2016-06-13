#ifndef EMPLOYEEDELEGATE_H
#define EMPLOYEEDELEGATE_H

#include <QStyledItemDelegate>
#include <QScopedPointer>

namespace Rsl {
namespace MapService {

class EditedSignalTrigger;

namespace Impl {
struct EmployeeDelegateRepresentation;
}

class EmployeeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit EmployeeDelegate(QObject *parent = 0);
    ~EmployeeDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

    EditedSignalTrigger *employeeEdited() const;

private:
    Q_DISABLE_COPY(EmployeeDelegate)
    QScopedPointer<Impl::EmployeeDelegateRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // EMPLOYEEDELEGATE_H
