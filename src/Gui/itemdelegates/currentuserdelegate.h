#ifndef CURRENTUSERDELEGATE_H
#define CURRENTUSERDELEGATE_H

#include <QStyledItemDelegate>
#include <QScopedPointer>

namespace Rsl {
namespace MapService {

class EditedSignalTrigger;

namespace Impl {
struct CurrentUserDelegateRepresentation;
}

class CurrentUserDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit CurrentUserDelegate(QWidget *parent = 0);
    ~CurrentUserDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

    EditedSignalTrigger *userEdited() const;

private:
    Q_DISABLE_COPY(CurrentUserDelegate)
    QScopedPointer<Impl::CurrentUserDelegateRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTUSERDELEGATE_H
