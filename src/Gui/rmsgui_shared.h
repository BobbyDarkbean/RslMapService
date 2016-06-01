#ifndef RMSGUI_SHARED_H
#define RMSGUI_SHARED_H

#include <qobjectdefs.h>

#ifdef RMS_GUI_LIB
#define RMS_GUI_SHARED Q_DECL_EXPORT
#else
#define RMS_GUI_SHARED Q_DECL_IMPORT
#endif

#endif // RMSGUI_SHARED_H
