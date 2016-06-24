#ifndef ITEMDELEGATESTYLER_H
#define ITEMDELEGATESTYLER_H

class QSize;
class QPalette;
class QWidget;
class QStyleOptionViewItem;

namespace Rsl {
namespace MapService {

class ItemDelegateStyler
{
public:
    QPalette palette(const QPalette &originalPalette, bool selected) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QWidget *widget) const;
};

} // namespace MapService
} // namespace Rsl

#endif // ITEMDELEGATESTYLER_H
