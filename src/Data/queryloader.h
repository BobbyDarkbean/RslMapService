#ifndef QUERYLOADER_H
#define QUERYLOADER_H

#include <QScopedPointer>

class QStringList;

namespace Rsl {
namespace MapService {

namespace Impl {
struct QueryLoaderRepresentation;
}

class QueryLoader
{
public:
    QueryLoader();
    explicit QueryLoader(const QString &filename);
    ~QueryLoader();

    bool isOpen() const;
    bool open(const QString &filename);
    QStringList load();

private:
    Q_DISABLE_COPY(QueryLoader)
    QScopedPointer<Impl::QueryLoaderRepresentation> m;
};

} // namespace MapService
} // namespace Rsl

#endif // QUERYLOADER_H
