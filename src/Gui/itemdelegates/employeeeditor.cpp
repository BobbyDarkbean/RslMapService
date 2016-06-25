#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QRegExpValidator>
#include <QBoxLayout>
#include "rms_global.h"

#include "employeeeditor.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct EmployeeEditorRepresentation
{
    void init(EmployeeEditor *);
    void applyMode(bool presentationMode);

    QCheckBox *isActiveBox;
    QLineEdit *nameBox;
    QLabel *idLabel;
};

void EmployeeEditorRepresentation::init(EmployeeEditor *w)
{
    isActiveBox = new QCheckBox;
    nameBox = new QLineEdit;
    idLabel = new QLabel;

    isActiveBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    nameBox->setValidator(new QRegExpValidator(QRegExp(WrittenNameRegExp), nameBox));

    QFont font = w->font();
    font.setItalic(true);
    idLabel->setFont(font);
    idLabel->setDisabled(true);

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

void EmployeeEditorRepresentation::applyMode(bool presentationMode)
{
    nameBox->setFrame(!presentationMode);
    nameBox->setReadOnly(presentationMode);
}

} // namespace Impl

EmployeeEditor::EmployeeEditor(QWidget *parent)
    : ItemEditor(parent)
    , m_EmployeeEditor(new Impl::EmployeeEditorRepresentation)
{
    UNIQUE_REP(EmployeeEditor);
    m->init(this);
}

EmployeeEditor::~EmployeeEditor()
{
}

bool EmployeeEditor::isActive() const
{
    CONST_UNIQUE_REP(EmployeeEditor);
    return m->isActiveBox->isChecked();
}

void EmployeeEditor::setActive(bool active)
{
    UNIQUE_REP(EmployeeEditor);
    m->isActiveBox->setChecked(active);
}

QString EmployeeEditor::name() const
{
    CONST_UNIQUE_REP(EmployeeEditor);
    return m->nameBox->text();
}

void EmployeeEditor::setName(const QString &name)
{
    UNIQUE_REP(EmployeeEditor);
    m->nameBox->setText(name);
}

void EmployeeEditor::setId(int id)
{
    UNIQUE_REP(EmployeeEditor);
    m->idLabel->setText(QString("(%1)").arg(id));
}

void EmployeeEditor::applyMode()
{
    UNIQUE_REP(EmployeeEditor);
    m->applyMode(isPresentationMode());
}

} // namespace MapService
} // namespace Rsl
