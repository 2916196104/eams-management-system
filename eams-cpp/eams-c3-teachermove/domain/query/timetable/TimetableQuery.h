#ifndef __TIMETABLE_QUERY_H__
#define __TIMETABLE_QUERY_H__

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"


#include OATPP_CODEGEN_BEGIN(DTO)

// Timetable query parameters
class TimetableQuery : public oatpp::DTO
{
	DTO_INIT(TimetableQuery, DTO)
};

// --- 1. Query parameters for getting student list ---
// Inherits from base PageQuery, which provides pageIndex and pageSize fields.
class StuListQuery : public PageQuery {
	DTO_INIT(StuListQuery, PageQuery)

		API_DTO_FIELD(String, keyword, ZH_WORDS_GETTER("timetable.query.keyword"), false, "")
};

// --- 2. Query parameters for getting student class list ---
class StuClassQuery : public oatpp::DTO {
	DTO_INIT(StuClassQuery, DTO);
	API_DTO_FIELD(String, id, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.studentId"), true, "10001");
};

/* 课次点评查询 */

class EvaluationQuery : public PageQuery
{
	DTO_INIT(EvaluationQuery, PageQuery);

	// 课程id
	DTO_FIELD(Int32, lesson_id);
	DTO_FIELD_INFO(lesson_id) {
		info->description = ZH_WORDS_GETTER("evaluate.field.lesson_id");
	}

	// 学生姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("evaluate.field.name");
	}

	// 评分
	DTO_FIELD(Int32, score);
	DTO_FIELD_INFO(score) {
		info->description = ZH_WORDS_GETTER("evaluate.field.score");
	}

	// 是否签到
	DTO_FIELD(Boolean, isSign);
	DTO_FIELD_INFO(isSign) {
		info->description = ZH_WORDS_GETTER("evaluate.field.has_sign");
	}

	// 是否点评
	DTO_FIELD(Boolean, isEvaluate);
	DTO_FIELD_INFO(isEvaluate) {
		info->description = ZH_WORDS_GETTER("evaluate.field.has_evaluation");
	}

};




#include OATPP_CODEGEN_END(DTO)

#endif