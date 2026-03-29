#pragma once

#ifndef __GET_COMMON_DATETIME_SERVICE_H__
#define __GET_COMMON_DATETIME_SERVICE_H__

#include "domain/query/timetable/GetCommonDatetimeQuery.h"
#include "domain/vo/timetable/CommonDatetimeVO.h"

class GetCommonDatetimeService
{
public:
	CommonDatetimeJsonVO::Wrapper getCommonDatetime(const GetCommonDatetimeQuery::Wrapper& query) const;
};

#endif // __GET_COMMON_DATETIME_SERVICE_H__
