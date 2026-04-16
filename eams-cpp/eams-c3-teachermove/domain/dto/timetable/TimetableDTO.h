#ifndef __TIMETABLE_DTO_H__
#define __TIMETABLE_DTO_H__

#include "domain/vo/BaseJsonVO.h"
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// Timetable-related business DTO classes
class TimetableDTO : public oatpp::DTO
{
	DTO_INIT(TimetableDTO, DTO)
};


// --- 1. Student list (with conditions + pagination) - response list item DTO ---
class TimetableStudentDTO : public oatpp::DTO {
	DTO_INIT(TimetableStudentDTO, DTO)

		API_DTO_FIELD(String, id, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.studentId"), true, "10001")
		API_DTO_FIELD(String, name, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.studentName"), true, "111")
		API_DTO_FIELD(String, phone, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.phone"), false, "15865842975")
		API_DTO_FIELD(String, gender, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.gender"), false, "1")
		API_DTO_FIELD(Int32, rest_hour, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.restHour"), false, 108)
};

// Since the framework does not have a built-in PageJsonVO, we need to define a custom pagination VO for the current student list.
class TimetableStudentPageJsonVO : public JsonVO<PageDTO<TimetableStudentDTO::Wrapper>::Wrapper> {
	DTO_INIT(TimetableStudentPageJsonVO, JsonVO<PageDTO<TimetableStudentDTO::Wrapper>::Wrapper>)
};

// --- 2. Add student to lesson - request parameter DTO ---
class AddStudentToLessonDTO : public oatpp::DTO {
	DTO_INIT(AddStudentToLessonDTO, DTO)

		API_DTO_FIELD(String, course_id, ZH_WORDS_GETTER("timetable.dto.AddStudentToLessonDTO.courseId"), true, "c_001")
		API_DTO_FIELD_REQUIRE(List<String>, studentIds, ZH_WORDS_GETTER("timetable.dto.AddStudentToLessonDTO.studentIds"), true)
};

// --- 3. Get student course list - response list item DTO ---
class TimetableStudentCourseDTO : public oatpp::DTO {
	DTO_INIT(TimetableStudentCourseDTO, DTO)

		API_DTO_FIELD(String, course_id, ZH_WORDS_GETTER("timetable.dto.AddStudentToLessonDTO.courseId"), true, "c_001")
		API_DTO_FIELD(Int32, rest_hour, ZH_WORDS_GETTER("timetable.dto.TimetableStudentDTO.restHour"), true, 0)
		API_DTO_FIELD(String, title, ZH_WORDS_GETTER("timetable.dto.TimetableStudentCourseDTO.courseTitle"), true, "CollegePhysics")
		API_DTO_FIELD(String, teacher_id, ZH_WORDS_GETTER("timetable.dto.TimetableStudentCourseDTO.teacherId"), false, "TeacherWang")
		API_DTO_FIELD(String, sn, ZH_WORDS_GETTER("timetable.dto.TimetableStudentCourseDTO.sn"), false, "2")
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

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
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
	// 是否签到
	DTO_FIELD(String, sign_state);
	DTO_FIELD_INFO(sign_state) {
		info->description = ZH_WORDS_GETTER("evaluate.field.has_sign");
	}
	// 点评
	DTO_FIELD(String, evaluation);
	DTO_FIELD_INFO(evaluation) {
		info->description = ZH_WORDS_GETTER("evaluate.field.evaluation");
	}

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
		info->description = ZH_WORDS_GETTER("evaluate.field.evaluation");
	}
};


/* 设置点评某人的返回值 */
class EvaluateRspDTO : public oatpp::DTO {
	DTO_INIT(EvaluateRspDTO, oatpp::DTO);


	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("evaluate.field.id");
	}


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