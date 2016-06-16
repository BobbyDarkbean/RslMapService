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
    void applyMode();

    QSpinBox *hallNumberBox;
    QSpinBox *cardNumberBox;
    QLineEdit *nameBox;
    QLabel *idLabel;
    QCheckBox *isOffBox;

    bool presentationMode;
};

void CurrentUserEditorRepresentation::init(CurrentUserEditor *w)
{
    presentationMode = false;

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

void CurrentUserEditorRepresentation::applyMode()
{
    nameBox->setFrame(!presentationMode);
    nameBox->setReadOnly(presentationMode);
}

} // namespace Impl

CurrentUserEditor::CurrentUserEditor(QWidget *parent)
    : QWidget(parent)
    , m(new Impl::CurrentUserEditorRepresentation)
{
    m->init(this);
    m->retranslateUi();
}

CurrentUserEditor::~CurrentUserEditor()
{
}

bool CurrentUserEditor::isPresentationMode() const
{ return m->presentationMode; }

void CurrentUserEditor::setPresentationMode(bool presentationMode)
{
    m->presentationMode = presentationMode;
    m->applyMode();
}

int CurrentUserEditor::hallNumber() const
{ return m->hallNumberBox->value(); }

void CurrentUserEditor::setHallNumber(int number)
{ m->hallNumberBox->setValue(number); }

int CurrentUserEditor::cardNumber() const
{ return m->cardNumberBox->value(); }

void CurrentUserEditor::setCardNumber(int number)
{ m->cardNumberBox->setValue(number); }

QString CurrentUserEditor::name() const
{ return m->nameBox->text(); }

void CurrentUserEditor::setName(const QString &name)
{ m->nameBox->setText(name); }

bool CurrentUserEditor::isOff() const
{ return m->isOffBox->isChecked(); }

void CurrentUserEditor::setOff(bool off)
{ m->isOffBox->setChecked(off); }

void CurrentUserEditor::setId(int id)
{
    m->idLabel->setText(QString("(%1)").arg(id));
}

void CurrentUserEditor::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        m->retranslateUi();
    else
        QWidget::changeEvent(e);
}

} // namespace MapService
} // namespace Rsl
