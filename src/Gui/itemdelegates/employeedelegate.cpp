#include <QPainter>
#include <QScopedPointer>
#include "employee.h"
#include "itemmodels/employeemodel.h"
#include "employeeeditor.h"

#include "employeedelegate.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct EmployeeDelegateRepresentation
{
    void init();
    QPalette palette(const QPalette &originalPalette, bool selected) const;
    QSize sizeHint(const QRect &optionRect) const;

    QScopedPointer<EmployeeEditor> presenter;
};

void EmployeeDelegateRepresentation::init()
{
    presenter.reset(new EmployeeEditor);
    presenter->setPresentationMode(true);
}

QPalette EmployeeDelegateRepresentation::palette(const QPalette &originalPalette, bool selected) const
{
    QPalette result(originalPalette);
    result.setBrush(QPalette::Active, QPalette::WindowText, selected ? originalPalette.highlightedText()
                                                                     : originalPalette.text());
    result.setBrush(QPalette::Active, QPalette::Text, selected ? originalPalette.highlightedText()
                                                               : originalPalette.text());
    result.setBrush(QPalette::Active, QPalette::Base, selected ? originalPalette.highlight()
                                                               : originalPalette.base());
    result.setBrush(QPalette::Active, QPalette::Window, selected ? originalPalette.highlight()
                                                                 : originalPalette.base());
    return result;
}

QSize EmployeeDelegateRepresentation::sizeHint(const QRect &optionRect) const
{
    return QSize(optionRect.width(), presenter->sizeHint().height());
}

} // namespace Impl

EmployeeDelegate::EmployeeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m(new Impl::EmployeeDelegateRepresentation)
{
    m->init();
}

EmployeeDelegate::~EmployeeDelegate()
{
}

void EmployeeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;

    bool selected = opt.state & QStyle::State_Selected;
    if (selected) {
        painter->fillRect(opt.rect, opt.palette.highlight().color());
    }

    m->presenter->setActive(index.data(EmployeeModel::DataRole_IsActive).toBool());
    m->presenter->setName(index.data(EmployeeModel::DataRole_Name).toString());
    m->presenter->setId(index.data(EmployeeModel::DataRole_Id).toInt());

    m->presenter->setPalette(m->palette(opt.palette, selected));
    m->presenter->setFixedWidth(opt.rect.width());

    QPixmap pixmap(m->sizeHint(option.rect));
    m->presenter->render(&pixmap);
    painter->drawPixmap(opt.rect.topLeft(), pixmap);

    if (opt.state & QStyle::State_MouseOver) {
        QStyledItemDelegate::paint(painter, opt, index);
    }
}

QSize EmployeeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    return m->sizeHint(option.rect);
}

QWidget *EmployeeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    Q_UNUSED(option);
    return new EmployeeEditor(parent);
}

void EmployeeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    EmployeeEditor *employeeEditor = qobject_cast<EmployeeEditor *>(editor);
    Q_ASSERT(employeeEditor);

    Employee employee = index.data(Qt::EditRole).value<Employee>();
    employeeEditor->setActive(employee.isActive());
    employeeEditor->setName(employee.name());
    employeeEditor->setId(employee.id());
}

void EmployeeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    EmployeeEditor *employeeEditor = qobject_cast<EmployeeEditor *>(editor);
    Q_ASSERT(employeeEditor);

    Employee employee;
    employee.setName(employeeEditor->name().trimmed().simplified());
    employee.setActive(employeeEditor->isActive());

    model->setData(index, QVariant::fromValue(employee), Qt::EditRole);
}

} // namespace MapService
} // namespace Rsl
