#ifndef LOG_H
#define LOG_H

#include <QScopedPointer>
#include "rmscore_shared.h"

namespace Rsl {
namespace MapService {

class RMS_CORE_SHARED Log
{
public:
    static void initPath(const QString &);
    static void write(const QString &tag, const QString &context, const QString &text, const QString &data = QString());
};

} // namespace MapService
} // namespace Rsl

#endif // LOG_H
