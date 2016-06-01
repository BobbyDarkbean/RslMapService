#include "application.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Rsl::MapService::Application app(argc, argv);
    Rsl::MapService::MainWindow w;

    w.showMaximized();
    return app.exec();
}
