#ifndef DATASTORAGECONFIGURATOR_H
#define DATASTORAGECONFIGURATOR_H

#include "rmsdata_shared.h"

class QStringList;

namespace Rsl {
namespace MapService {

class RMS_DATA_SHARED DataStorageConfigurator
{
public:
    DataStorageConfigurator();
    bool init();
    bool configure();

private:
    QStringList sequence(const QString &pathToSql);
    bool execSequence(const QStringList &queries);
};

} // namespace MapService
} // namespace Rsl

#endif // DATASTORAGECONFIGURATOR_H
