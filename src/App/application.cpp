#include <QSettings>
#include "workflow.h"
#include "application.h"

namespace Rsl {
namespace MapService {

namespace {
const QString SETTINGS_PATH("rms.ini");
}

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    WorkFlow wf;
    wf.connectDataStorage();

    QSettings settings(SETTINGS_PATH, QSettings::IniFormat);
    if (!settings.value("common/dbconfigured", false).toBool()) {
        if (wf.initDataStorage()) {
            settings.setValue("common/dbconfigured", true);
        }
    }

    wf.configureDataStorage();
    setApplicationName(tr("APP_NAME"));
}

Application::~Application()
{
}

} // namespace MapService
} // namespace Rsl
