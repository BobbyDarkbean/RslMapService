#include <QSize>
#include <QPalette>
#include <QStyleOptionViewItem>

#include "itemdelegatestyler.h"

namespace Rsl {
namespace MapService {

QPalette ItemDelegateStyler::palette(const QPalette &originalPalette, bool selected) const
{
    QPalette result(originalPalette);
    result.setBrush(QPalette::Active, QPalette::WindowText, selected ? originalPalette.highlightedText()
                                                                     : originalPalette.text());
    result.setBrush(QPalette::Active, QPalette::Text, selected ? originalPalette.highlightedText()
                                                               : originalPalette.text());
    result.setBrush(QPalette::Active, QPalette::Base, selected ? originalPalette.highlight()
                                                               : originalPalette.base());
    result.setBrush(QPalette::Active, QPalette::Window, selected ? originalPalette.highlight()
                                                                 : originalPalette.base());
    return result;
}

QSize ItemDelegateStyler::sizeHint(const QStyleOptionViewItem &option, const QWidget *widget) const
{
    return QSize(option.rect.width(), widget->sizeHint().height());
}

} // namespace MapService
} // namespace Rsl
