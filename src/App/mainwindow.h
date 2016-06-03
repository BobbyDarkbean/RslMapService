#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Rsl {
namespace MapService {

namespace Impl {
struct MainWindowRepresentation;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *);

private slots:
    void reportEmployeeEdited(bool success);
    void reportEmployeeAppending(bool success);
    void reportEmployeeRemoval(int count);

private:
    Q_DISABLE_COPY(MainWindow)

    friend class Impl::MainWindowRepresentation;
    QScopedPointer<Impl::MainWindowRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // MAINWINDOW_H
