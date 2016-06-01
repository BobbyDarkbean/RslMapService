#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QRegExpValidator>
#include <QBoxLayout>
#include "employee.h"

#include "employeeeditor.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct EmployeeEditorRepresentation
{
    void init(EmployeeEditor *);
    void applyMode();

    QCheckBox *isActiveBox;
    QLineEdit *nameBox;
    QLabel *idLabel;

    bool presentationMode;
};

void EmployeeEditorRepresentation::init(EmployeeEditor *w)
{
    presentationMode = false;

    isActiveBox = new QCheckBox;
    nameBox = new QLineEdit;
    idLabel = new QLabel;

    nameBox->setValidator(new QRegExpValidator(QRegExp(EmployeeNameRegExp), nameBox));

    QFont font = w->font();
    font.setItalic(true);
    idLabel->setFont(font);

    const int InterSpacing = 2;

    QBoxLayout *editorLayout = new QHBoxLayout;
    editorLayout->setMargin(0);
    editorLayout->setSpacing(0);
    editorLayout->addSpacing(InterSpacing);
    editorLayout->addWidget(isActiveBox);
    editorLayout->addSpacing(InterSpacing);
    editorLayout->addWidget(nameBox);
    editorLayout->addSpacing(InterSpacing);
    editorLayout->addWidget(idLabel);
    editorLayout->addSpacing(InterSpacing);
    w->setLayout(editorLayout);

    w->setAutoFillBackground(true);
}

void EmployeeEditorRepresentation::applyMode()
{
    nameBox->setFrame(!presentationMode);
    nameBox->setReadOnly(presentationMode);
}

} // namespace Impl

EmployeeEditor::EmployeeEditor(QWidget *parent)
    : QWidget(parent)
    , m(new Impl::EmployeeEditorRepresentation)
{
    m->init(this);
}

EmployeeEditor::~EmployeeEditor()
{
}

bool EmployeeEditor::isPresentationMode() const
{ return m->presentationMode; }

void EmployeeEditor::setPresentationMode(bool presentationMode)
{
    m->presentationMode = presentationMode;
    m->applyMode();
}

bool EmployeeEditor::isActive() const
{ return m->isActiveBox->isChecked(); }

void EmployeeEditor::setActive(bool active)
{ m->isActiveBox->setChecked(active); }

QString EmployeeEditor::name() const
{ return m->nameBox->text(); }

void EmployeeEditor::setName(const QString &name)
{ m->nameBox->setText(name); }

void EmployeeEditor::setId(int id)
{
    m->idLabel->setText(QString("(%1)").arg(id));
}

} // namespace MapService
} // namespace Rsl
