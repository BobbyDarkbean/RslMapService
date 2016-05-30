#include <QSettings>
#include "workflow.h"
#include "application.h"

namespace Rsl {
namespace MapService {

namespace {
const QString APP_NAME("Map department service");
const QString SETTINGS_PATH("rms.ini");
}

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setApplicationName(APP_NAME);

    WorkFlow wf;
    wf.connectDataStorage();

    QSettings settings(SETTINGS_PATH, QSettings::IniFormat);
    if (!settings.value("common/dbconfigured", false).toBool()) {
        if (wf.initDataStorage()) {
            settings.setValue("common/dbconfigured", true);
        }
    }

    wf.configureDataStorage();
}

Application::~Application()
{
}

} // namespace MapService
} // namespace Rsl
