#pragma once
#ifndef _COURSERECORD_SERVICE_H_
#define _COURSERECORD_SERVICE_H_

#include "domain/vo/CourseRecord/CourseRecordVO.h"
#include "domain/query/CourseRecord/CourseRecordQuery.h"
#include "domain/dto/CourseRecord/CourseRecordDTO.h"

/**
 * 上课记录服务实现
 */
class CourseRecordService
{
public:
	// 分页查询上课记录
	CourseRecordPageDTO::Wrapper listAll(const CourseRecordQuery::Wrapper& query);
};

#endif // !_COURSERECORD_SERVICE_H_
