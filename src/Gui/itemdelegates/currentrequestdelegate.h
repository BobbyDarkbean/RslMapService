#ifndef CURRENTREQUESTDELEGATE_H
#define CURRENTREQUESTDELEGATE_H

#include <QStyledItemDelegate>
#include <QScopedPointer>

namespace Rsl {
namespace MapService {

class CurrentRequestEditor;
class EditedSignalTrigger;

namespace Impl {
struct CurrentRequestDelegateRepresentation;
}

class CurrentRequestDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit CurrentRequestDelegate(QWidget *parent = 0);
    ~CurrentRequestDelegate();

    CurrentRequestEditor *presenter() const;
    void setPresenter(CurrentRequestEditor *);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

    EditedSignalTrigger *requestEdited() const;

private:
    Q_DISABLE_COPY(CurrentRequestDelegate)
    QScopedPointer<Impl::CurrentRequestDelegateRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTREQUESTDELEGATE_H
