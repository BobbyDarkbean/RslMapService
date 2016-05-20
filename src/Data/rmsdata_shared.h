#ifndef RMSDATA_SHARED_H
#define RMSDATA_SHARED_H

#include <qobjectdefs.h>

#ifdef RMS_DATA_LIB
#define RMS_DATA_SHARED Q_DECL_EXPORT
#else
#define RMS_DATA_SHARED Q_DECL_IMPORT
#endif

#endif // RMSDATA_SHARED_H
