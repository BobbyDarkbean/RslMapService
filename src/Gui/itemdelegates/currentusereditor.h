#ifndef CURRENTUSEREDITOR_H
#define CURRENTUSEREDITOR_H

#include <QScopedPointer>
#include "itemeditor.h"

namespace Rsl {
namespace MapService {

namespace Impl {
struct CurrentUserEditorRepresentation;
}

class CurrentUserEditor : public ItemEditor
{
    Q_OBJECT

public:
    explicit CurrentUserEditor(QWidget *parent = 0);
    ~CurrentUserEditor();

    int hallNumber() const;
    void setHallNumber(int);

    int cardNumber() const;
    void setCardNumber(int);

    QString name() const;
    void setName(const QString &);

    bool isOff() const;
    void setOff(bool);

    void setId(int);

protected:
    void applyMode();
    void changeEvent(QEvent *);

private:
    Q_DISABLE_COPY(CurrentUserEditor)
    QScopedPointer<Impl::CurrentUserEditorRepresentation> m_CurrentUserEditor;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTUSEREDITOR_H
