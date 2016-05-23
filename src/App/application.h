#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

namespace Rsl {
namespace MapService {

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char **argv);
    ~Application();

private:
    Q_DISABLE_COPY(Application)
};

} // namespace MapService
} // namespace Rsl

#endif // APPLICATION_H
