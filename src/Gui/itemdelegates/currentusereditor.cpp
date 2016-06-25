#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QRegExpValidator>
#include <QSpinBox>
#include <QBoxLayout>
#include <QEvent>
#include "rms_global.h"

#include "currentusereditor.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct CurrentUserEditorRepresentation
{
    void init(CurrentUserEditor *);
    void retranslateUi();
    void applyMode(bool presentationMode);

    QSpinBox *hallNumberBox;
    QSpinBox *cardNumberBox;
    QLineEdit *nameBox;
    QLabel *idLabel;
    QCheckBox *isOffBox;
};

void CurrentUserEditorRepresentation::init(CurrentUserEditor *w)
{
    hallNumberBox = new QSpinBox;
    cardNumberBox = new QSpinBox;
    nameBox = new QLineEdit;
    idLabel = new QLabel;
    isOffBox = new QCheckBox;

    hallNumberBox->setRange(ReadingHall_MIN, ReadingHall_MAX);
    cardNumberBox->setRange(CardNumberMinimum, CardNumberMaximum);

    isOffBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    nameBox->setValidator(new QRegExpValidator(QRegExp(WrittenNameRegExp), nameBox));

    QFont font = w->font();
    font.setItalic(true);
    idLabel->setFont(font);
    idLabel->setDisabled(true);

    const int InterSpacing = 2;

    QBoxLayout *editorLayout = new QHBoxLayout;
    editorLayout->setMargin(0);
    editorLayout->addSpacing(InterSpacing);
    editorLayout->addWidget(hallNumberBox);
    editorLayout->addWidget(cardNumberBox);
    editorLayout->addWidget(nameBox);
    editorLayout->addWidget(idLabel);
    editorLayout->addSpacing(InterSpacing);
    editorLayout->addWidget(isOffBox);
    w->setLayout(editorLayout);

    w->setAutoFillBackground(true);
}

void CurrentUserEditorRepresentation::retranslateUi()
{
    isOffBox->setText(CurrentUserEditor::tr("IS_OFF"));
}

void CurrentUserEditorRepresentation::applyMode(bool presentationMode)
{
    nameBox->setFrame(!presentationMode);
    nameBox->setReadOnly(presentationMode);
}

} // namespace Impl

CurrentUserEditor::CurrentUserEditor(QWidget *parent)
    : ItemEditor(parent)
    , m_CurrentUserEditor(new Impl::CurrentUserEditorRepresentation)
{
    UNIQUE_REP(CurrentUserEditor);
    m->init(this);
    m->retranslateUi();
}

CurrentUserEditor::~CurrentUserEditor()
{
}

int CurrentUserEditor::hallNumber() const
{
    CONST_UNIQUE_REP(CurrentUserEditor);
    return m->hallNumberBox->value();
}

void CurrentUserEditor::setHallNumber(int number)
{
    UNIQUE_REP(CurrentUserEditor);
    m->hallNumberBox->setValue(number);
}

int CurrentUserEditor::cardNumber() const
{
    CONST_UNIQUE_REP(CurrentUserEditor);
    return m->cardNumberBox->value();
}

void CurrentUserEditor::setCardNumber(int number)
{
    UNIQUE_REP(CurrentUserEditor);
    m->cardNumberBox->setValue(number);
}

QString CurrentUserEditor::name() const
{
    CONST_UNIQUE_REP(CurrentUserEditor);
    return m->nameBox->text();
}

void CurrentUserEditor::setName(const QString &name)
{
    UNIQUE_REP(CurrentUserEditor);
    m->nameBox->setText(name);
}

bool CurrentUserEditor::isOff() const
{
    CONST_UNIQUE_REP(CurrentUserEditor);
    return m->isOffBox->isChecked();
}

void CurrentUserEditor::setOff(bool off)
{
    UNIQUE_REP(CurrentUserEditor);
    m->isOffBox->setChecked(off);
}

void CurrentUserEditor::setId(int id)
{
    UNIQUE_REP(CurrentUserEditor);
    m->idLabel->setText(QString("(%1)").arg(id));
}

void CurrentUserEditor::applyMode()
{
    UNIQUE_REP(CurrentUserEditor);
    m->applyMode(isPresentationMode());
}

void CurrentUserEditor::changeEvent(QEvent *e)
{
    UNIQUE_REP(CurrentUserEditor);
    if (e->type() == QEvent::LanguageChange)
        m->retranslateUi();
    else
        QWidget::changeEvent(e);
}

} // namespace MapService
} // namespace Rsl
