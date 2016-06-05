#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QScopedPointer>

namespace Rsl {
namespace MapService {

namespace Impl {
struct ApplicationRepresentation;
}

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char **argv);
    ~Application();

private:
    Q_DISABLE_COPY(Application)
    QScopedPointer<Impl::ApplicationRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // APPLICATION_H
