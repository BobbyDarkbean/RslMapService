#include <QSettings>
#include <QTranslator>
#include "log.h"
#include "workflow.h"

#include "application.h"

namespace Rsl {
namespace MapService {

namespace {
const QString SETTINGS_PATH("rms.ini");
const QString TR_DIR("translations");
const QString LOG_DIR("log");
}

namespace Impl {

struct ApplicationRepresentation
{
    void setupLanguage();

    QTranslator qtTranslator;
    QTranslator appTranslator;

    QString localeName;
};

void ApplicationRepresentation::setupLanguage()
{
    QLocale locale(localeName);

    if (qtTranslator.load(locale, "qtbase", "_", TR_DIR))
        QApplication::installTranslator(&qtTranslator);

    if (appTranslator.load(locale, "rms", ".", TR_DIR))
        QApplication::installTranslator(&appTranslator);
}

} // namespace Impl

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
    , m(new Impl::ApplicationRepresentation)
{
    Log::initPath(LOG_DIR);

    WorkFlow wf;
    wf.connectDataStorage();

    QSettings settings(SETTINGS_PATH, QSettings::IniFormat);
    if (!settings.value("common/dbconfigured", false).toBool()) {
        if (wf.initDataStorage()) {
            settings.setValue("common/dbconfigured", true);
        }
    }

    wf.configureDataStorage();

    m->localeName = settings.value("common/locale", QLocale::system().name()).toString();
    m->setupLanguage();
    setApplicationName(tr("APP_NAME"));
}

Application::~Application()
{
    QSettings settings(SETTINGS_PATH, QSettings::IniFormat);
    settings.setValue("common/locale", m->localeName);
}

} // namespace MapService
} // namespace Rsl
