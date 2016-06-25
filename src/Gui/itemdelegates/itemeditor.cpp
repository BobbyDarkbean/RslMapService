#include "rms_global.h"
#include "itemeditor.h"

namespace Rsl {
namespace MapService {

namespace Impl {

struct ItemEditorRepresentation
{
    void init();

    bool presentationMode;
};

void ItemEditorRepresentation::init()
{
    presentationMode = false;
}

} // namespace Impl

ItemEditor::ItemEditor(QWidget *parent)
    : QWidget(parent)
    , m_ItemEditor(new Impl::ItemEditorRepresentation)
{
    UNIQUE_REP(ItemEditor);
    m->init();
}

ItemEditor::~ItemEditor()
{
}

bool ItemEditor::isPresentationMode() const
{
    CONST_UNIQUE_REP(ItemEditor);
    return m->presentationMode;
}

void ItemEditor::setPresentationMode(bool presentationMode)
{
    UNIQUE_REP(ItemEditor);
    m->presentationMode = presentationMode;
    applyMode();
}

void ItemEditor::applyMode()
{
}

} // namespace MapService
} // namespace Rsl
