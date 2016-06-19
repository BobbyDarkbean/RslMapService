#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "rmsdata_module.h"

#include "queryloader.h"

namespace Rsl {
namespace MapService {

namespace {
const QChar SQL_SENTENCE_DELIM(';');
const QString SQL_COMMENT_SEQUENCE("--");

const QString LogContext("QueryLoader");
}

namespace Impl {

struct QueryLoaderRepresentation
{
    QFile queryFile;
};

} // namespace Impl

QueryLoader::QueryLoader()
    : m(new Impl::QueryLoaderRepresentation)
{
}

QueryLoader::QueryLoader(const QString &filename)
    : m(new Impl::QueryLoaderRepresentation)
{
    open(filename);
}

QueryLoader::~QueryLoader()
{
}

bool QueryLoader::isOpen() const
{
    return m->queryFile.isOpen();
}

bool QueryLoader::open(const QString &filename)
{
    if (m->queryFile.isOpen()) {
        logFileIO(LogContext, FileIOStatus_AlreadyOpen, &m->queryFile);
        return false;
    }

    m->queryFile.setFileName(filename);
    if (!m->queryFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        logFileIO(LogContext, FileIOStatus_OpenError, &m->queryFile);
        return false;
    }

    logFileIO(LogContext, FileIOStatus_OpenForReading, &m->queryFile);
    return true;
}

QStringList QueryLoader::load()
{
    QStringList queries;

    QTextStream queryStream(&m->queryFile);
    while (!queryStream.atEnd()) {
        QString queryString;

        while (!queryStream.atEnd()) {
            QString line = queryStream.readLine();
            if (line.isEmpty() || line.startsWith(SQL_COMMENT_SEQUENCE))
                continue;

            queryString += line.simplified();
            if (queryString.endsWith(SQL_SENTENCE_DELIM))
                break;

            queryString += QChar::Space;
        }

        if (!queryString.isEmpty()) {
            queries << queryString;
            logQueryReading(LogContext, queryString);
        }
    }

    logQueryReading(LogContext, queries.size());
    return queries;
}

} // namespace MapService
} // namespace Rsl
