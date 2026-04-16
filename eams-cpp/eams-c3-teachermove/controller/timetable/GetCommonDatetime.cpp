#include "GetCommonDatetime.h"
#include "stdafx.h"
#include "service/timetable/GetCommonDatetimeService.h"

CommonDatetimeJsonVO::Wrapper GetCommonDatetime::execGetCommonDatetime(const GetCommonDatetimeQuery::Wrapper& query)
{
	GetCommonDatetimeService service;
	return service.getCommonDatetime(query);
}