#ifndef __TIMETABLE_DTO_H__
#define __TIMETABLE_DTO_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业DTO类*/


class TimetableDTO: public oatpp::DTO
{
	DTO_INIT(TimetableDTO, DTO)
};

/* 设置设置上课状态的传入值 */
class SetStudyStatusDTO : public oatpp::DTO {
	DTO_INIT(SetStudyStatusDTO, DTO);


	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("set_status.id");
	}
	DTO_FIELD(Int32, count);
	DTO_FIELD_INFO(count) {
		info->description = ZH_WORDS_GETTER("set_status.count");
	}
	DTO_FIELD(Int8, type);
	DTO_FIELD_INFO(type) {
		info->description = ZH_WORDS_GETTER("set_status.sign_type");
	}
	DTO_FIELD(Int8, state);
	DTO_FIELD_INFO(state) {
		info->description = ZH_WORDS_GETTER("set_status.sign_type");
	}
};

/* 设置设置上课状态的返回值 */
class SetStudyStatusRspDTO : public oatpp::DTO {
	DTO_INIT(SetStudyStatusRspDTO, DTO);

	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("set_status.id");
	}

	DTO_FIELD(Int8, resp_code);
	DTO_FIELD_INFO(resp_code) {
		info->description = ZH_WORDS_GETTER("set_status.response.code");
	}

	DTO_FIELD(String, resp_message);
	DTO_FIELD_INFO(resp_message) {
		info->description = ZH_WORDS_GETTER("set_status.response.message");
	}
};


/* 课次状态的返回值 */
class EvaluateDTO : public oatpp::DTO
{
	DTO_INIT(EvaluateDTO, oatpp::DTO);
	// 编号
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("evaluate.field.id");
	}
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
	// 点评
	DTO_FIELD(String, evaluation);
	DTO_FIELD_INFO(evaluation) {
		info->description = ZH_WORDS_GETTER("evaluate.field.evaluation");
	}
	// 点评人
	DTO_FIELD(String, Operator);
	DTO_FIELD_INFO(Operator) {
		info->description = ZH_WORDS_GETTER("evaluate.field.operator");
	}
	// 操作时间
	DTO_FIELD(String, operationTime);
	DTO_FIELD_INFO(operationTime) {
		info->description = ZH_WORDS_GETTER("evaluate.field.operation_time");
	}
};


/* 设置课次状态的分页返回值 */
class EvaluatePageDTO : public PageDTO<EvaluateDTO::Wrapper>
{
	DTO_INIT(EvaluatePageDTO, PageDTO<EvaluateDTO::Wrapper>);
};



/* 设置 添加评语的DTO */
class EvaluationDTO : public oatpp::DTO {
	DTO_INIT(EvaluationDTO, oatpp::DTO);

	// 信息的id
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("evaluate.field.id");
	}

	// 评分
	DTO_FIELD(Int8, score);
	DTO_FIELD_INFO(score) {
		info->description = ZH_WORDS_GETTER("evaluate.field.score");
	}

	// 评语
	DTO_FIELD(String, evaluation);
	DTO_FIELD_INFO(evaluation) {
		info->description = ZH_WORDS_GETTER("evaluate.field.evalution");
	}
};


/* 设置点评某人的返回值 */
class EvaluateRspDTO : public oatpp::DTO {
	DTO_INIT(EvaluateRspDTO, oatpp::DTO);


	// 定义信息的唯一id号
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("evaluate.field.id");
	}

	// 定义错误码
	DTO_FIELD(Int8, code);
	DTO_FIELD_INFO(code) {
		info->description = ZH_WORDS_GETTER("evaluate.response.code");
	}

	// 定义错误信息
	DTO_FIELD(String, message);
	DTO_FIELD_INFO(message) {
		info->description = ZH_WORDS_GETTER("evaluate.response.message");
	}


};


#include OATPP_CODEGEN_END(DTO)

#endif