#ifndef ITEMEDITOR_H
#define ITEMEDITOR_H

#include <QWidget>
#include <QScopedPointer>

namespace Rsl {
namespace MapService {

namespace Impl {
struct ItemEditorRepresentation;
}

class ItemEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ItemEditor(QWidget *parent = 0);
    ~ItemEditor();

    bool isPresentationMode() const;
    void setPresentationMode(bool);

protected:
    virtual void applyMode();

private:
    Q_DISABLE_COPY(ItemEditor)
    QScopedPointer<Impl::ItemEditorRepresentation> m_ItemEditor;
};

} // namespace MapService
} // namespace Rsl

#endif // ITEMEDITOR_H
