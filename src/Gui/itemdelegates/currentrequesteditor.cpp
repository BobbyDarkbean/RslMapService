#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QRegExpValidator>
#include <QBoxLayout>
#include <QEvent>
#include "itemmodels/collectiontagmodel.h"
#include "itemmodels/currentusermodel.h"
#include "callnumber.h"
#include "rms_global.h"

#include "currentrequesteditor.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct CurrentRequestEditorRepresentation
{
    void init(CurrentRequestEditor *);
    void retranslateUi();
    void applyMode(bool presentationMode);

    QComboBox *userBox;
    QComboBox *collectionBox;
    QLineEdit *rackBox;
    QSpinBox *shelfBox;
    QLineEdit *positionBox;
    QPlainTextEdit *docTitleBox;
    QComboBox *docTypeBox;
    QSpinBox *itemCountBox;
    QComboBox *statusBox;

    CurrentUserModel *userModel;
    CollectionTagModel *collectionTagModel;
};

void CurrentRequestEditorRepresentation::init(CurrentRequestEditor *w)
{
    // Creation
    userBox = new QComboBox;
    collectionBox = new QComboBox;
    rackBox = new QLineEdit;
    shelfBox = new QSpinBox;
    positionBox = new QLineEdit;
    docTitleBox = new QPlainTextEdit;
    docTypeBox = new QComboBox;
    itemCountBox = new QSpinBox;
    statusBox = new QComboBox;

    // Initialization
    shelfBox->setRange(ShelfNumberMinimum, ShelfNumberMaximum);
    itemCountBox->setRange(ItemCountMinimum, ItemCountMaximum);

    rackBox->setValidator(new QRegExpValidator(QRegExp(CallNumberRackRegExp), rackBox));
    positionBox->setValidator(new QRegExpValidator(QRegExp(CallNumberPositionRegExp), positionBox));

    docTitleBox->setMaximumHeight(docTitleBox->minimumSizeHint().height());

    docTitleBox->setReadOnly(false);
    docTitleBox->setTextInteractionFlags(Qt::TextEditorInteraction);
    docTitleBox->setWordWrapMode(QTextOption::WordWrap);

    userModel = new CurrentUserModel(w);
    collectionTagModel = new CollectionTagModel(w);

    userBox->setModel(userModel);
    collectionBox->setModel(collectionTagModel);

    // Layout
    QBoxLayout *userLayout = new QVBoxLayout;
    userLayout->addStretch();
    userLayout->addWidget(userBox);
    userLayout->addStretch();

    QBoxLayout *callNumberCollectionLayout = new QVBoxLayout;
    callNumberCollectionLayout->addStretch();
    callNumberCollectionLayout->addWidget(collectionBox);
    callNumberCollectionLayout->addStretch();

    QBoxLayout *callNumberNumeratorLayout = new QHBoxLayout;
    callNumberNumeratorLayout->addStretch();
    callNumberNumeratorLayout->addWidget(rackBox);
    callNumberNumeratorLayout->addStretch();

    QBoxLayout *callNumberDenominatorLayout = new QHBoxLayout;
    callNumberDenominatorLayout->addWidget(shelfBox);
    callNumberDenominatorLayout->addStretch();
    callNumberDenominatorLayout->addWidget(positionBox);

    QBoxLayout *callNumberLocationLayout = new QVBoxLayout;
    callNumberLocationLayout->addLayout(callNumberNumeratorLayout);
    callNumberLocationLayout->addLayout(callNumberDenominatorLayout);

    QBoxLayout *callNumberLayout = new QHBoxLayout;
    callNumberLayout->addLayout(callNumberCollectionLayout);
    callNumberLayout->addLayout(callNumberLocationLayout);

    QBoxLayout *docTitleLayout = new QVBoxLayout;
    docTitleLayout->addStretch();
    docTitleLayout->addWidget(docTitleBox);
    docTitleLayout->addStretch();

    QBoxLayout *docTypeLayout = new QVBoxLayout;
    docTypeLayout->addStretch();
    docTypeLayout->addWidget(docTypeBox);
    docTypeLayout->addStretch();

    QBoxLayout *itemCountLayout = new QVBoxLayout;
    itemCountLayout->addStretch();
    itemCountLayout->addWidget(itemCountBox);
    itemCountLayout->addStretch();

    QBoxLayout *statusLayout = new QVBoxLayout;
    statusLayout->addStretch();
    statusLayout->addWidget(statusBox);
    statusLayout->addStretch();

    QBoxLayout *editorLayout = new QHBoxLayout;
    editorLayout->addLayout(userLayout);
    editorLayout->addLayout(callNumberLayout);
    editorLayout->addLayout(docTitleLayout);
    editorLayout->addLayout(docTypeLayout);
    editorLayout->addLayout(itemCountLayout);
    editorLayout->addLayout(statusLayout);
    w->setLayout(editorLayout);

    w->setAutoFillBackground(true);
}

void CurrentRequestEditorRepresentation::retranslateUi()
{
    for (int i = DocumentType_MIN; i <= DocumentType_MAX; ++i)
        docTypeBox->addItem(toString(DocumentType(i)), i);

    for (int i = RequestStatus_MIN; i <= RequestStatus_MAX; ++i)
        statusBox->addItem(toString(RequestStatus(i)), i);
}

void CurrentRequestEditorRepresentation::applyMode(bool presentationMode)
{
    rackBox->setReadOnly(presentationMode);
    positionBox->setReadOnly(presentationMode);
    docTitleBox->setReadOnly(presentationMode);
}

} // namespace Impl

CurrentRequestEditor::CurrentRequestEditor(QWidget *parent)
    : ItemEditor(parent)
    , m_CurrentRequestEditor(new Impl::CurrentRequestEditorRepresentation)
{
    UNIQUE_REP(CurrentRequestEditor);
    m->init(this);
    m->retranslateUi();
}

CurrentRequestEditor::~CurrentRequestEditor()
{
}

int CurrentRequestEditor::userId() const
{
    CONST_UNIQUE_REP(CurrentRequestEditor);
    return m->userBox->currentData(CurrentUserModel::DataRole_Id).toInt();
}

void CurrentRequestEditor::setUserId(int id)
{
    UNIQUE_REP(CurrentRequestEditor);
    for (int i = 0; i < m->userBox->count(); ++i) {
        int itemData = m->userBox->itemData(i, CurrentUserModel::DataRole_Id).toInt();
        if (itemData == id) {
            m->userBox->setCurrentIndex(i);
            return;
        }
    }
}

CallNumber CurrentRequestEditor::callNumber() const
{
    CONST_UNIQUE_REP(CurrentRequestEditor);
    CallNumber callNumber;
    callNumber.setCollection(m->collectionBox->currentIndex());
    callNumber.setRack(m->rackBox->text());
    callNumber.setShelf(m->shelfBox->value());
    callNumber.setPosition(m->positionBox->text());

    return callNumber;
}

void CurrentRequestEditor::setCallNumber(const CallNumber &callNumber)
{
    UNIQUE_REP(CurrentRequestEditor);
    m->collectionBox->setCurrentIndex(callNumber.collection());
    m->rackBox->setText(callNumber.rack());
    m->shelfBox->setValue(callNumber.shelf());
    m->positionBox->setText(callNumber.position());
}

QString CurrentRequestEditor::docTitle() const
{
    CONST_UNIQUE_REP(CurrentRequestEditor);
    return m->docTitleBox->toPlainText();
}

void CurrentRequestEditor::setDocTitle(const QString &title)
{
    UNIQUE_REP(CurrentRequestEditor);
    m->docTitleBox->setPlainText(title);
}

int CurrentRequestEditor::docType() const
{
    CONST_UNIQUE_REP(CurrentRequestEditor);
    return m->docTypeBox->currentIndex();
}

void CurrentRequestEditor::setDocType(int type)
{
    UNIQUE_REP(CurrentRequestEditor);
    m->docTypeBox->setCurrentIndex(type);
}

int CurrentRequestEditor::itemCount() const
{
    CONST_UNIQUE_REP(CurrentRequestEditor);
    return m->itemCountBox->value();
}

void CurrentRequestEditor::setItemCount(int count)
{
    UNIQUE_REP(CurrentRequestEditor);
    m->itemCountBox->setValue(count);
}

int CurrentRequestEditor::status() const
{
    CONST_UNIQUE_REP(CurrentRequestEditor);
    return m->statusBox->currentIndex();
}

void CurrentRequestEditor::setStatus(int status)
{
    UNIQUE_REP(CurrentRequestEditor);
    m->statusBox->setCurrentIndex(status);
}

void CurrentRequestEditor::applyMode()
{
    UNIQUE_REP(CurrentRequestEditor);
    m->applyMode(isPresentationMode());
}

void CurrentRequestEditor::changeEvent(QEvent *e)
{
    UNIQUE_REP(CurrentRequestEditor);
    if (e->type() == QEvent::LanguageChange)
        m->retranslateUi();
    else
        QWidget::changeEvent(e);
}

} // namespace MapService
} // namespace Rsl
