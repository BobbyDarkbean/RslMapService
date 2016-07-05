#include <QPainter>
#include "itemdelegatestyler.h"
#include "request.h"
#include "callnumber.h"
#include "itemmodels/currentrequestmodel.h"
#include "currentrequesteditor.h"
#include "editedsignaltrigger.h"

#include "currentrequestdelegate.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct CurrentRequestDelegateRepresentation
{
    void init(CurrentRequestDelegate *q);

    ItemDelegateStyler styler;

    CurrentRequestEditor *presenter;
    EditedSignalTrigger *requestEditedSignalTrigger;
};

void CurrentRequestDelegateRepresentation::init(CurrentRequestDelegate *q)
{
    requestEditedSignalTrigger = new EditedSignalTrigger(q);
}

} // namespace Impl

CurrentRequestDelegate::CurrentRequestDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
    , m(new Impl::CurrentRequestDelegateRepresentation)
{
    m->init(this);
}

CurrentRequestDelegate::~CurrentRequestDelegate()
{
}

CurrentRequestEditor *CurrentRequestDelegate::presenter() const
{ return m->presenter; }

void CurrentRequestDelegate::setPresenter(CurrentRequestEditor *presenter)
{ m->presenter = presenter; }

void CurrentRequestDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    bool selected = option.state & QStyle::State_Selected;
    if (selected) {
        painter->fillRect(option.rect, option.palette.highlight().color());
    }

    m->presenter->setUserId(index.data(CurrentRequestModel::DataRole_UserId).toInt());
    m->presenter->setCallNumber(index.data(CurrentRequestModel::DataRole_CallNumber).value<CallNumber>());
    m->presenter->setDocTitle(index.data(CurrentRequestModel::DataRole_DocTitle).toString());
    m->presenter->setDocType(index.data(CurrentRequestModel::DataRole_DocType).toInt());
    m->presenter->setItemCount(index.data(CurrentRequestModel::DataRole_ItemCount).toInt());
    m->presenter->setStatus(index.data(CurrentRequestModel::DataRole_Status).toInt());

    m->presenter->setPalette(m->styler.palette(option.palette, selected));
    m->presenter->setFixedWidth(option.rect.width());

    QPixmap pixmap(m->styler.sizeHint(option, m->presenter));
    m->presenter->render(&pixmap);
    painter->drawPixmap(option.rect.topLeft(), pixmap);
}

QSize CurrentRequestDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    return m->styler.sizeHint(option, m->presenter);
}

QWidget *CurrentRequestDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    Q_UNUSED(option);
    return new CurrentRequestEditor(parent);
}

void CurrentRequestDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    CurrentRequestEditor *currentRequestEditor = qobject_cast<CurrentRequestEditor *>(editor);
    Q_ASSERT(currentRequestEditor);

    Request request = index.data(Qt::EditRole).value<Request>();
    currentRequestEditor->setUserId(request.userId());
    currentRequestEditor->setCallNumber(request.callNumber());
    currentRequestEditor->setDocTitle(request.docTitle());
    currentRequestEditor->setDocType(request.docType());
    currentRequestEditor->setItemCount(request.itemCount());
    currentRequestEditor->setStatus(request.status());
}

void CurrentRequestDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    CurrentRequestEditor *currentRequestEditor = qobject_cast<CurrentRequestEditor *>(editor);
    Q_ASSERT(currentRequestEditor);

    Request request;
    request.setUserId(currentRequestEditor->userId());
    request.setCallNumber(currentRequestEditor->callNumber());
    request.setDocTitle(currentRequestEditor->docTitle().simplified());
    request.setDocType(currentRequestEditor->docType());
    request.setItemCount(currentRequestEditor->itemCount());
    request.setStatus(currentRequestEditor->status());

    bool editAccepted = model->setData(index, QVariant::fromValue(request), Qt::EditRole);
    m->requestEditedSignalTrigger->setAccepted(editAccepted);
    m->requestEditedSignalTrigger->activate();
}

EditedSignalTrigger *CurrentRequestDelegate::requestEdited() const
{
    return m->requestEditedSignalTrigger;
}

} // namespace MapService
} // namespace Rsl
