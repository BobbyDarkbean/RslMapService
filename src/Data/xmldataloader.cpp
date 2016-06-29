#include <QFile>
#include <QXmlStreamReader>
#include <QStringList>
#include "rmsdata_module.h"

#include "xmldataloader.h"

namespace Rsl {
namespace MapService {

namespace {
const QString LogContext("XmlDataLoader");
}

namespace Impl {

struct XmlDataLoaderRepresentation
{
    QFile xmlDataFile;
};

} // namespace Impl

XmlDataLoader::XmlDataLoader()
    : m(new Impl::XmlDataLoaderRepresentation)
{
}

XmlDataLoader::XmlDataLoader(const QString &filename)
    : m(new Impl::XmlDataLoaderRepresentation)
{
    open(filename);
}

XmlDataLoader::~XmlDataLoader()
{
}

bool XmlDataLoader::isOpen() const
{
    return m->xmlDataFile.isOpen();
}

bool XmlDataLoader::open(const QString &filename)
{
    if (m->xmlDataFile.isOpen()) {
        logFileIO(LogContext, FileIOStatus_AlreadyOpen, &m->xmlDataFile);
        return false;
    }

    m->xmlDataFile.setFileName(filename);
    if (!m->xmlDataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        logFileIO(LogContext, FileIOStatus_OpenError, &m->xmlDataFile);
        return false;
    }

    logFileIO(LogContext, FileIOStatus_OpenForReading, &m->xmlDataFile);
    return true;
}

QStringList XmlDataLoader::load(const QString &dataAttribute)
{
    QStringList result;

    QXmlStreamReader xsr(&m->xmlDataFile);

    while (!xsr.atEnd()) {
        xsr.readNext();
        if (xsr.isStartElement())   // root
            break;
    }

    int entriesRead = 0;
    while (!xsr.atEnd()) {
        xsr.readNext();
        if (xsr.isStartElement()) {
            QXmlStreamAttributes atts = xsr.attributes();
            result << atts.value(dataAttribute).toString();
            ++entriesRead;
        }
    }

    logXmlDataReading(LogContext, entriesRead);
    return result;
}

} // namespace MapService
} // namespace Rsl
