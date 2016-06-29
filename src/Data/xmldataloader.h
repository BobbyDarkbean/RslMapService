#ifndef XMLDATALOADER_H
#define XMLDATALOADER_H

#include <QScopedPointer>

class QStringList;

namespace Rsl {
namespace MapService {

namespace Impl {
struct XmlDataLoaderRepresentation;
}

class XmlDataLoader
{
public:
    XmlDataLoader();
    explicit XmlDataLoader(const QString &filename);
    ~XmlDataLoader();

    bool isOpen() const;
    bool open(const QString &filename);
    QStringList load(const QString &dataAttribute);

private:
    Q_DISABLE_COPY(XmlDataLoader)
    QScopedPointer<Impl::XmlDataLoaderRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // XMLDATALOADER_H
