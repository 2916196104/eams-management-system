#pragma once
#ifndef _FREESCHEDULINGDTO_H_
#define _FREESCHEDULINGDTO_H_

#include"../../GlobalInclude.h"
#include"ServerInfo.h"
#include"Macros.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class FreeSchedulingDTO : public oatpp::DTO {
	DTO_INIT(FreeSchedulingDTO, DTO);
	//班级id
	API_DTO_FIELD_REQUIRE(String, classId, ZH_WORDS_GETTER("schedule.field.classId"), true);
	//课程id
	API_DTO_FIELD_REQUIRE(String, courseId, ZH_WORDS_GETTER("schedule.field.courseId"), true);
	//上课老师id
	API_DTO_FIELD_REQUIRE(String, teacherId, ZH_WORDS_GETTER("schedule.field.teacherId"), true);
	//助教老师id
	API_DTO_FIELD_DEFAULT(String, assistantId, ZH_WORDS_GETTER("schedule.field.assistantId"));
	//教室id
	API_DTO_FIELD_DEFAULT(String, classroomId, ZH_WORDS_GETTER("schedule.field.classroomId"));
	//开始日期
	API_DTO_FIELD_REQUIRE(List<String>, startDate, ZH_WORDS_GETTER("schedule.field.startDate"), true);
	// 上课时间（如 "08:30"）
	API_DTO_FIELD_REQUIRE(String, startTime, ZH_WORDS_GETTER("schedule.field.startTime"), true);
	// 下课时间（如 "10:00"）
	API_DTO_FIELD_REQUIRE(String, endTime, ZH_WORDS_GETTER("schedule.field.endTime"), false);
	// 消课课时
	API_DTO_FIELD_DEFAULT(UInt32, consumedHours, ZH_WORDS_GETTER("schedule.field.consumedHours"));
	//限制人数
	API_DTO_FIELD_DEFAULT(Int32, limitNum, ZH_WORDS_GETTER("schedule.field.limitNum"));
	//开启预约
	API_DTO_FIELD_DEFAULT(Boolean, enableBooking, ZH_WORDS_GETTER("schedule.field.enableBooking"));
	//是否检查冲突
	API_DTO_FIELD(Boolean, checkConflict, ZH_WORDS_GETTER("schedule.field.checkConflict"), false, false);
	//星期几
	API_DTO_FIELD_DEFAULT(List<String>, weeks, ZH_WORDS_GETTER("schedule.field.weeks"))
	//关联负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	std::string validate() {
		if (!classId || classId->empty()) return "classId invalidate.";
		if (!courseId || courseId->empty()) return "courseId invalidate.";
		if (!teacherId || teacherId->empty()) return "teacherId invalidate.";
		if (!startDate || startDate->empty()) return "startDate invalidate.";
		if (!startTime || startTime->empty()) return "startTime invalidate.";
		if (!endTime || endTime->empty()) return "endTime invalidate.";
		if (!startDate || !weeks || startDate->size() != weeks->size()) return "startDate and weeks invalidate";
		return "";
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_FREESCHEDULINGDTO_H_