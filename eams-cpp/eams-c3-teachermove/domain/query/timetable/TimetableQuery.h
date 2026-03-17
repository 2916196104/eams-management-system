#ifndef __TIMETABLE_QUERY_H__
#define __TIMETABLE_QUERY_H__

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/* 课表查询参数 */
class TimetableQuery : public oatpp::DTO 
{
	DTO_INIT(TimetableQuery, DTO)
};

// --- 1. 获取学员列表的 Query 参数 ---
// 继承自底层的 PageQuery，自带 pageIndex 和 pageSize
class StuListQuery : public PageQuery {
	DTO_INIT(StuListQuery, PageQuery)
	
	API_DTO_FIELD(String, keyword, "搜索关键字(姓名/学号)", false, "")
};

// --- 2. 获取学员课程列表 - 请求参数 Query ---
class StuClassQuery : public oatpp::DTO {
	DTO_INIT(StuClassQuery, DTO)

	API_DTO_FIELD(String, id, "学员ID", true, "10001")
};

#include OATPP_CODEGEN_END(DTO)

#endif