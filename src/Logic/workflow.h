#ifndef WORKFLOW_H
#define WORKFLOW_H

#include "rmslogic_shared.h"

namespace Rsl {
namespace MapService {

class RMS_LOGIC_SHARED WorkFlow
{
public:
    WorkFlow();
    ~WorkFlow();

    bool connectDataStorage();
    bool initDataStorage();
    bool configureDataStorage();

private:
    Q_DISABLE_COPY(WorkFlow)
};

} // namespace MapService
} // namespace Rsl

#endif // WORKFLOW_H
