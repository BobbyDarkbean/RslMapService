#ifndef CURRENTREQUESTEDITOR_H
#define CURRENTREQUESTEDITOR_H

#include <QScopedPointer>
#include "itemeditor.h"

namespace Rsl {
namespace MapService {

class CallNumber;

namespace Impl {
struct CurrentRequestEditorRepresentation;
}

class CurrentRequestEditor : public ItemEditor
{
    Q_OBJECT

public:
    explicit CurrentRequestEditor(QWidget *parent = 0);
    ~CurrentRequestEditor();

    int userId() const;
    void setUserId(int);

    CallNumber callNumber() const;
    void setCallNumber(const CallNumber &);

    QString docTitle() const;
    void setDocTitle(const QString &);

    int docType() const;
    void setDocType(int);

    int itemCount() const;
    void setItemCount(int);

    int status() const;
    void setStatus(int);

protected:
    void applyMode();
    void changeEvent(QEvent *);

private:
    Q_DISABLE_COPY(CurrentRequestEditor)
    QScopedPointer<Impl::CurrentRequestEditorRepresentation> m_CurrentRequestEditor;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTREQUESTEDITOR_H
