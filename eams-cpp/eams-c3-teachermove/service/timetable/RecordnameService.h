#pragma once

#ifndef __RECORDNAME_SERVICE_H__
#define __RECORDNAME_SERVICE_H__

#include "domain/query/timetable/GetDetailCSQuery.h"
#include "domain/query/timetable/GetStuListQuery.h"
#include "domain/vo/timetable/GetDetailCSVO.h"
#include "domain/vo/timetable/GetStuListVO.h"

class RecordnameService
{
public:
	GetDetailCSJsonVO::Wrapper getDetailCS(const GetDetailCSQuery::Wrapper& query) const;
	GetStuListJsonVO::Wrapper getCSStuList(const GetStuListQuery::Wrapper& query) const;
};

#endif // __RECORDNAME_SERVICE_H__
