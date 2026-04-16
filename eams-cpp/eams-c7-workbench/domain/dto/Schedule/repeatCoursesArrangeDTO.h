#ifndef _REPEATCOURSESARRANGEDTO_H_
#define _REPEATCOURSESARRANGEDTO_H_

#include"../../GlobalInclude.h"
#include"periodDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 教室类
class repeatCoursesArrangeDTO :public oatpp::DTO
{

	DTO_INIT(repeatCoursesArrangeDTO, DTO);
	////编排计划id（由服务端生成，与客户端无关）
	//API_DTO_FIELD_DEFAULT(Int64,id, ZH_WORDS_GETTER("classroom.field.id"));
	//班级id
	API_DTO_FIELD_DEFAULT(Int64, class_id, ZH_WORDS_GETTER("repeatcourses.field.classid"));
	//课程id
	API_DTO_FIELD_DEFAULT(Int64, course_id, ZH_WORDS_GETTER("repeatcourses.field.courseid"));
	//老师id
	API_DTO_FIELD_DEFAULT(String, teacher_id, ZH_WORDS_GETTER("repeatcourses.field.teacherid"));
	//助教id
	API_DTO_FIELD_REQUIRE(String, assistant_id, ZH_WORDS_GETTER("repeatcourses.field.assistantid"), false);
	//教室id
	API_DTO_FIELD_REQUIRE(Int64, classroom_id, ZH_WORDS_GETTER("repeatcourses.field.classroomid"), false);


	// 开始日期
	API_DTO_FIELD_DEFAULT(String, start_date, ZH_WORDS_GETTER("repeatcourses.field.startdate"));
	// 结束日期
	API_DTO_FIELD_DEFAULT(String, end_date, ZH_WORDS_GETTER("repeatcourses.field.enddate"));


	//周几上课，上课时间，下课时间，消课课时
	API_DTO_FIELD_DEFAULT(List<periodDTO::Wrapper>, class_period, ZH_WORDS_GETTER("repeatcourses.field.classperiod"));


	//限制人数
	API_DTO_FIELD_REQUIRE(String, limit_person_num, ZH_WORDS_GETTER("repeatcourses.field.limitpersonnum"), false);
	//跳过节假日
	API_DTO_FIELD_REQUIRE(Boolean, skip_holiday, ZH_WORDS_GETTER("repeatcourses.field.skipholiday"), false);
	//开启预约
	API_DTO_FIELD_REQUIRE(Boolean, open_appointment, ZH_WORDS_GETTER("repeatcourses.field.openappointment"), false);
	//是否检查冲突
	API_DTO_FIELD_REQUIRE(Boolean, check_confilct, ZH_WORDS_GETTER("repeatcourses.field.checkconflict"), false);

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);

public:
	bool isAllDigit(const std::string& str)
	{
		for (char c : str)
		{
			if (!isdigit(c))
				return false;
		}
		return true;
	}

	bool compareTime(const std::string& time1, const std::string& time2)
	{
		int h1, m1, h2, m2;
		if (sscanf(time1.c_str(), "%d:%d", &h1, &m1) != 2) return false;
		if (sscanf(time2.c_str(), "%d:%d", &h2, &m2) != 2) return false;
		if (h1 < h2) return true;
		if (h1 > h2) return false;
		return m1 <= m2;
	}

	int calculateDurationMinutes(const std::string& startTime, const std::string& endTime)
	{
		int h1, m1, h2, m2;
		if (sscanf(startTime.c_str(), "%d:%d", &h1, &m1) != 2) return -1;
		if (sscanf(endTime.c_str(), "%d:%d", &h2, &m2) != 2) return -1;
		return (h2 * 60 + m2) - (h1 * 60 + m1);
	}

	bool compareDate(const std::string& date1, const std::string& date2)
	{
		int y1, m1, d1, y2, m2, d2;
		if (sscanf(date1.c_str(), "%d-%d-%d", &y1, &m1, &d1) != 3) return false;
		if (sscanf(date2.c_str(), "%d-%d-%d", &y2, &m2, &d2) != 3) return false;
		if (y1 < y2) return true;
		if (y1 > y2) return false;
		if (m1 < m2) return true;
		if (m1 > m2) return false;
		return d1 <= d2;
	}

	std::string validate()
	{
		//班级和课程id，为int类型
		if (!class_id || class_id == 0)
			return ZH_WORDS_GETTER("repeatcourses.validate.classid_empty");
		if (!course_id || course_id == 0)
			return ZH_WORDS_GETTER("repeatcourses.validate.courseid_empty");

		//老师id和助教id为string类型，需要确保全部为数字
		if (!teacher_id || teacher_id->empty() || !isAllDigit(*teacher_id))
			return ZH_WORDS_GETTER("repeatcourses.validate.teacherid_invalid");
		if (!assistant_id || assistant_id->empty() || !isAllDigit(*assistant_id))
			return ZH_WORDS_GETTER("repeatcourses.validate.assistantid_invalid");

		//日期格式判断：
		if (!start_date || start_date->empty() || *start_date == "string")
			return ZH_WORDS_GETTER("repeatcourses.validate.startdate_invalid");
		if (!end_date || end_date->empty() || *end_date == "string")
			return ZH_WORDS_GETTER("repeatcourses.validate.enddate_invalid");
		if (!compareDate(*start_date, *end_date))
			return ZH_WORDS_GETTER("repeatcourses.validate.startdate_after_enddate");

		//课程周期判断
		if (!class_period || class_period->empty())
			return ZH_WORDS_GETTER("repeatcourses.validate.classperiod_empty");
		int periodIndex = 1;
		for (auto& period : *class_period)
		{
			if (!period->weeks || period->weeks->empty() || *period->weeks == "string")
				return ZH_WORDS_GETTER("repeatcourses.validate.period_prefix") + std::to_string(periodIndex) + ZH_WORDS_GETTER("repeatcourses.validate.period_weeks_invalid");
			if (!period->start_time || period->start_time->empty() || *period->start_time == "string")
				return ZH_WORDS_GETTER("repeatcourses.validate.period_prefix") + std::to_string(periodIndex) + ZH_WORDS_GETTER("repeatcourses.validate.period_starttime_invalid");
			if (!period->end_time || period->end_time->empty() || *period->end_time == "string")
				return ZH_WORDS_GETTER("repeatcourses.validate.period_prefix") + std::to_string(periodIndex) + ZH_WORDS_GETTER("repeatcourses.validate.period_endtime_invalid");
			if (!compareTime(*period->start_time, *period->end_time))
				return ZH_WORDS_GETTER("repeatcourses.validate.period_prefix") + std::to_string(periodIndex) + ZH_WORDS_GETTER("repeatcourses.validate.period_starttime_after_endtime");
			int duration = calculateDurationMinutes(*period->start_time, *period->end_time);
			if (duration > 300)
				return ZH_WORDS_GETTER("repeatcourses.validate.period_duration_exceed_300");
			if (duration < 0)
				return ZH_WORDS_GETTER("repeatcourses.validate.period_duration_invalid");
			periodIndex++;
		}

		//限制人数格式判断
		if (limit_person_num && !limit_person_num->empty() && *limit_person_num != "string")
		{
			if (!isAllDigit(*limit_person_num))
				return ZH_WORDS_GETTER("repeatcourses.validate.limitpersonnum_invalid");
		}
		return "";
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif