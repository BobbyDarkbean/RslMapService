#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "rmscore_module.h"

#include "log.h"

namespace Rsl {
namespace MapService {

namespace {
const QString ThisDirectory(".");
const QString LogHeader(" ------ RSL Map Service Application Log ------");
const QString SessionStart("Session started.");
const QString SessionFinish("Session finished.");
const QString DateFormat("yyyyMMdd");
const QString TimeFormat("HH:mm:ss");
}

namespace Impl {

inline QString timeText()
{ return QDateTime::currentDateTime().time().toString(TimeFormat); }

inline QString dateText()
{ return QDateTime::currentDateTime().date().toString(DateFormat); }

inline QString logFileName()
{ return QString("%1.log").arg(dateText()); }

struct LogRepresentation
{
    ~LogRepresentation();

    void initPath(const QString &path);
    void write(const QString &tag, const QString &context, const QString &text, const QString &data);

private:
    void write(const QString &text);
    QString filePath;
};

LogRepresentation::~LogRepresentation()
{
    write(QString());
    write(QString("%1 [%2] %3%4").arg(timeText(), RmsCoreTag, SessionFinish, QChar(QChar::LineFeed)));
}

void LogRepresentation::initPath(const QString &path)
{
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(ThisDirectory);

    filePath = dir.absoluteFilePath(logFileName());

    write(QString("%1%2").arg(LogHeader, QChar(QChar::LineFeed)));
    write(QString("%1 [%2] %3%4").arg(timeText(), RmsCoreTag, SessionStart, QChar(QChar::LineFeed)));
}

inline void LogRepresentation::write(const QString &tag, const QString &context, const QString &text, const QString &data)
{
    write(QString("%1 [%2] %3: %4 %5").arg(timeText(), tag, context, text, data).simplified());
}

void LogRepresentation::write(const QString &text)
{
    QFile outputFile(filePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream output(&outputFile);
    output << text;
    endl(output);
}

LogRepresentation &logInstance()
{
    static LogRepresentation logRepresentation;
    return logRepresentation;
}

} // namespace Impl

void Log::initPath(const QString &path)
{ Impl::logInstance().initPath(path); }

void Log::write(const QString &tag, const QString &context, const QString &text, const QString &data)
{ Impl::logInstance().write(tag, context, text, data); }

} // namespace MapService
} // namespace Rsl
