#include <QPainter>
#include "itemdelegatestyler.h"
#include "user.h"
#include "itemmodels/currentusermodel.h"
#include "currentusereditor.h"
#include "editedsignaltrigger.h"

#include "currentuserdelegate.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct CurrentUserDelegateRepresentation
{
    void init(CurrentUserDelegate *q);

    ItemDelegateStyler styler;

    QScopedPointer<CurrentUserEditor> presenter;
    EditedSignalTrigger *userEditedSignalTrigger;
};

void CurrentUserDelegateRepresentation::init(CurrentUserDelegate *q)
{
    presenter.reset(new CurrentUserEditor);
    presenter->setPresentationMode(true);

    userEditedSignalTrigger = new EditedSignalTrigger(q);
}

} // namespace Impl

CurrentUserDelegate::CurrentUserDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
    , m(new Impl::CurrentUserDelegateRepresentation)
{
    m->init(this);
}

CurrentUserDelegate::~CurrentUserDelegate()
{
}

void CurrentUserDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    bool selected = option.state & QStyle::State_Selected;
    if (selected) {
        painter->fillRect(option.rect, option.palette.highlight().color());
    }

    m->presenter->setHallNumber(index.data(CurrentUserModel::DataRole_HallNumber).toInt());
    m->presenter->setCardNumber(index.data(CurrentUserModel::DataRole_CardNumber).toInt());
    m->presenter->setOff(index.data(CurrentUserModel::DataRole_IsOff).toBool());
    m->presenter->setName(index.data(CurrentUserModel::DataRole_Name).toString());
    m->presenter->setId(index.data(CurrentUserModel::DataRole_Id).toInt());

    m->presenter->setPalette(m->styler.palette(option.palette, selected));
    m->presenter->setFixedWidth(option.rect.width());

    QPixmap pixmap(m->styler.sizeHint(option, m->presenter.data()));
    m->presenter->render(&pixmap);
    painter->drawPixmap(option.rect.topLeft(), pixmap);
}

QSize CurrentUserDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    return m->styler.sizeHint(option, m->presenter.data());
}

QWidget *CurrentUserDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    Q_UNUSED(option);
    return new CurrentUserEditor(parent);
}

void CurrentUserDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    CurrentUserEditor *currentUserEditor = qobject_cast<CurrentUserEditor *>(editor);
    Q_ASSERT(currentUserEditor);

    User user = index.data(Qt::EditRole).value<User>();
    currentUserEditor->setHallNumber(user.hallNumber());
    currentUserEditor->setCardNumber(user.cardNumber());
    currentUserEditor->setOff(user.isOff());
    currentUserEditor->setName(user.name());
    currentUserEditor->setId(user.id());
}

void CurrentUserDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    CurrentUserEditor *currentUserEditor = qobject_cast<CurrentUserEditor *>(editor);
    Q_ASSERT(currentUserEditor);

    User user;
    user.setHallNumber(currentUserEditor->hallNumber());
    user.setCardNumber(currentUserEditor->cardNumber());
    user.setName(currentUserEditor->name().simplified());
    user.setOff(currentUserEditor->isOff());

    bool editAccepted = model->setData(index, QVariant::fromValue(user), Qt::EditRole);
    m->userEditedSignalTrigger->setAccepted(editAccepted);
    m->userEditedSignalTrigger->activate();
}

EditedSignalTrigger *CurrentUserDelegate::userEdited() const
{
    return m->userEditedSignalTrigger;
}

} // namespace MapService
} // namespace Rsl
