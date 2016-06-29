#include <QStringList>
#include "xmldataloader.h"

#include "collectiontagdataadapter.h"

namespace Rsl {
namespace MapService {

namespace {
const QString TagAttribute("tag");
}

namespace Impl {

struct CollectionTagDataAdapterRepresentation
{
    QStringList data;
};

} // namespace Impl

CollectionTagDataAdapter::CollectionTagDataAdapter()
    : m(new Impl::CollectionTagDataAdapterRepresentation)
{
    XmlDataLoader loader(":/data/collections.xml");
    m->data = loader.load(TagAttribute);
}

CollectionTagDataAdapter::~CollectionTagDataAdapter()
{
}

QStringList CollectionTagDataAdapter::select() const
{
    return m->data;
}

} // namespace MapService
} // namespace Rsl
