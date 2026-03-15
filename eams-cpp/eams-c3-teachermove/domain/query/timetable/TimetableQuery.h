#ifndef __TIMETABLE_QUERY_H__
#define __TIMETABLE_QUERY_H__



#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"



#include OATPP_CODEGEN_BEGIN(DTO)

///*课表查询类*/
//
//
//class TimetableQuery : public
//{
//	DTO_INIT(TimetableQuery, )
//};
//


/* 课次点评查询 */

class EvaluationQuery : public PageQuery
{
	DTO_INIT(EvaluationQuery, PageQuery);
	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("evaluate.field.name");
	}
	// 分数
	DTO_FIELD(Int8, score);
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