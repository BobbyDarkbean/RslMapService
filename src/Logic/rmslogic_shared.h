#ifndef RMSLOGIC_SHARED_H
#define RMSLOGIC_SHARED_H

#include <qobjectdefs.h>

#ifdef RMS_LOGIC_LIB
#define RMS_LOGIC_SHARED Q_DECL_EXPORT
#else
#define RMS_LOGIC_SHARED Q_DECL_IMPORT
#endif

#endif // RMSLOGIC_SHARED_H
