#ifndef RMS_SHARED_H
#define RMS_SHARED_H

#include <qobjectdefs.h>

#ifdef RMS_CORE_LIB
#define RMS_CORE_SHARED Q_DECL_EXPORT
#else
#define RMS_CORE_SHARED Q_DECL_IMPORT
#endif

#endif // RMS_SHARED_H
