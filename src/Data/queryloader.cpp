#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "queryloader.h"

namespace Rsl {
namespace MapService {

namespace {
const QChar SQL_SENTENCE_DELIM(';');
const QString SQL_COMMENT_SEQUENCE("--");
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
    if (m->queryFile.isOpen())
        return false;

    m->queryFile.setFileName(filename);
    if (!m->queryFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

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

        if (!queryString.isEmpty())
            queries << queryString;
    }

    return queries;
}

} // namespace MapService
} // namespace Rsl
