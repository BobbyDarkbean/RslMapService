#ifndef RMS_GLOBAL_H
#define RMS_GLOBAL_H

#include "rmscore_shared.h"

namespace Rsl {
namespace MapService {

extern RMS_CORE_SHARED const QString WrittenNameRegExp;

enum ReadingHall
{
    ReadingHall_Unspecified,
    ReadingHall_First,
    ReadingHall_Second,
    ReadingHall_Third,
    ReadingHall_Fourth,

    ReadingHall_MIN = ReadingHall_Unspecified,
    ReadingHall_MAX = ReadingHall_Fourth
};

enum {
    CardNumberMinimum = 0,
    CardNumberMaximum = 9999999
};

enum DocumentType
{
    DocumentType_Map,
    DocumentType_Atlas,
    DocumentType_Globe,
    DocumentType_Book,
    DocumentType_Bibliography,
    DocumentType_Periodical,
    DocumentType_OpticalDisc,

    DocumentType_MIN = DocumentType_Map,
    DocumentType_MAX = DocumentType_OpticalDisc
};

enum RequestStatus
{
    RequestStatus_Filling,
    RequestStatus_Pickup,
    RequestStatus_Delivered,
    RequestStatus_DenyDepartmentsOccupied,
    RequestStatus_DenyEmployeesOccupied,
    RequestStatus_DenyExhibitionOccupied,
    RequestStatus_DenyIlesOccupied,
    RequestStatus_DenyStock,
    RequestStatus_DenyNull,
    RequestStatus_Returned,
    RequestStatus_PutOnHold,

    RequestStatus_MIN = RequestStatus_Filling,
    RequestStatus_MAX = RequestStatus_PutOnHold
};

RMS_CORE_SHARED QString toString(DocumentType dt);
RMS_CORE_SHARED QString toString(RequestStatus rs);

} // namespace MapService
} // namespace Rsl

#endif // RMS_GLOBAL_H
