#pragma once
#ifndef _REPEATEDSCHEDULINGDTO_H_
#define _REPEATEDSCHEDULINGDTO_H_
#include"../../GlobalInclude.h"
#include"ServerInfo.h"
#include"Macros.h"
#include OATPP_CODEGEN_BEGIN(DTO)

// 周期内单条时间段
class PeriodDTO : public oatpp::DTO {
	DTO_INIT(PeriodDTO, DTO);
	// 周几：数组，使用 1..7 表示周一..周日
	API_DTO_FIELD_REQUIRE(List<UInt32>, weekDays, ZH_WORDS_GETTER("schedule.field.weekDays"), true);
	// 上课时间（如 "08:30")
	API_DTO_FIELD_REQUIRE(String, startTime, ZH_WORDS_GETTER("schedule.field.startTime"), true);
	// 下课时间（如 "10:00"）
	API_DTO_FIELD_REQUIRE(String, endTime, ZH_WORDS_GETTER("schedule.field.endTime"), true);
	// 消课课时
	API_DTO_FIELD_DEFAULT(UInt32, consumedHours, ZH_WORDS_GETTER("schedule.field.consumedHours"));
public:
	// 将周期内的周几转换为字符串，格式为 "123" 表示周一、周二、周三
	std::string weekDaysToString() const {
		std::string result;
		if (!this->weekDays || this->weekDays->empty());
		for (auto& weekDay : *this->weekDays) {
			result += std::to_string(weekDay);
		}
		return result;
	}
};

class RepeatedSchedulingDTO : public oatpp::DTO {
	DTO_INIT(RepeatedSchedulingDTO, DTO);
	//班级id
	API_DTO_FIELD_REQUIRE(String, classId, ZH_WORDS_GETTER("schedule.field.classId"),true);
	//课程id
	API_DTO_FIELD_REQUIRE(String, courseId, ZH_WORDS_GETTER("schedule.field.courseId"), true);
	//上课老师id
	API_DTO_FIELD_REQUIRE(String, teacherId, ZH_WORDS_GETTER("schedule.field.teacherId"), true);
	//助教老师id
	API_DTO_FIELD(String, assistantId, ZH_WORDS_GETTER("schedule.field.assistantId"),false,"");
	//教室id
	API_DTO_FIELD(String, classroomId, ZH_WORDS_GETTER("schedule.field.classroomId"),false,"");
	//开始日期
	API_DTO_FIELD_REQUIRE(String, startDate, ZH_WORDS_GETTER("schedule.field.startDate"), true);
	//结束日期
	API_DTO_FIELD_REQUIRE(String, endDate, ZH_WORDS_GETTER("schedule.field.endDate"), true);
	//限制人数
	API_DTO_FIELD_DEFAULT(Int32, limitNum, ZH_WORDS_GETTER("schedule.field.limitNum"));
	//跳过节假日默认不跳过
	API_DTO_FIELD(Boolean, skipHoliday, ZH_WORDS_GETTER("schedule.field.skipHolidays"),false,false);
	//开启预约
	API_DTO_FIELD_DEFAULT(Boolean, enableBooking, ZH_WORDS_GETTER("schedule.field.enableBooking"));
	//是否检查冲突默认检查
	API_DTO_FIELD(Boolean, checkConflict, ZH_WORDS_GETTER("schedule.field.checkConflict"),false,true);
	//周期内的时间段列表
	API_DTO_FIELD_DEFAULT(List<Object<PeriodDTO>>, periods, ZH_WORDS_GETTER("schedule.field.periods"));
	//关联负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	// 验证 DTO 数据的合法性，返回空字符串表示合法，否则返回错误信息
	std::string validate() {
		if(!classId || classId->empty()) return "classId invalidate.";
		if (!courseId || courseId->empty()) return "courseId invalidate.";
		if (!teacherId || teacherId->empty()) return "teacherId invalidate.";
		if (!startDate || startDate->empty()) return "startDate invalidate.";
		if (!endDate || endDate->empty()) return "endDate invalidate.";
		if (periods) {
			for (auto& period : *periods) {
				if (!period->weekDays || period->weekDays->empty()) return "weekDays invalidate.";
				if (!period->startTime || period->startTime->empty()) return "startTime invalidate.";
				if (!period->endTime || period->endTime->empty()) return "endTime invalidate.";
			}
		}
		return "";
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif