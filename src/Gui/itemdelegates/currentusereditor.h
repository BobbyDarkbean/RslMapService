#ifndef CURRENTUSEREDITOR_H
#define CURRENTUSEREDITOR_H

#include <QWidget>
#include <QScopedPointer>

namespace Rsl {
namespace MapService {

namespace Impl {
struct CurrentUserEditorRepresentation;
}

class CurrentUserEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentUserEditor(QWidget *parent = 0);
    ~CurrentUserEditor();

    bool isPresentationMode() const;
    void setPresentationMode(bool);

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
    void changeEvent(QEvent *);

private:
    Q_DISABLE_COPY(CurrentUserEditor)
    QScopedPointer<Impl::CurrentUserEditorRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // CURRENTUSEREDITOR_H
