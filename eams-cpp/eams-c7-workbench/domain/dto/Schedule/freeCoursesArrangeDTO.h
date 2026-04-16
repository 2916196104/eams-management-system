#ifndef _FREECOURSESARRANGEDTO_H_
#define _FREECOURSESARRANGEDTO_H_

#include"../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class freeCoursesArrangeDTO :public oatpp::DTO
{

	DTO_INIT(freeCoursesArrangeDTO, DTO);

	//班级id
	API_DTO_FIELD_DEFAULT(Int64, class_id, ZH_WORDS_GETTER("freecourses.field.classid"));
	//课程id
	API_DTO_FIELD_DEFAULT(Int64, course_id, ZH_WORDS_GETTER("freecourses.field.courseid"));
	//老师id
	API_DTO_FIELD_DEFAULT(String, teacher_id, ZH_WORDS_GETTER("freecourses.field.teacherid"));
	//助教id
	API_DTO_FIELD_REQUIRE(String, assistant_id, ZH_WORDS_GETTER("freecourses.field.assistantid"), false);
	//教室id
	API_DTO_FIELD_REQUIRE(Int64, classroom_id, ZH_WORDS_GETTER("freecourses.field.classroomid"), false);

	//上课日期列表（多个日期）
	API_DTO_FIELD_DEFAULT(List<String>, dates, ZH_WORDS_GETTER("freecourses.field.dates"));
	//上课时间
	API_DTO_FIELD_DEFAULT(String, start_time, ZH_WORDS_GETTER("freecourses.field.starttime"));
	//下课时间
	API_DTO_FIELD_DEFAULT(String, end_time, ZH_WORDS_GETTER("freecourses.field.endtime"));
	//消课课时
	API_DTO_FIELD_REQUIRE(UInt32, dec_class_time, ZH_WORDS_GETTER("freecourses.field.decclasstime"), false);

	//限制人数
	API_DTO_FIELD_REQUIRE(String, limit_person_num, ZH_WORDS_GETTER("freecourses.field.limitpersonnum"), false);
	//开启预约
	API_DTO_FIELD_REQUIRE(Boolean, open_appointment, ZH_WORDS_GETTER("freecourses.field.openappointment"), false);
	//是否检查冲突
	API_DTO_FIELD_REQUIRE(Boolean, check_conflict, ZH_WORDS_GETTER("freecourses.field.checkconflict"), false);

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);

public:
	//检查字符串每个字符是否都为数字
	bool isAllDigit(const std::string& str)
	{
		if (str.empty()) return false;
		for (char c : str)
		{
			if (!isdigit(c))
				return false;
		}
		return true;
	}

	//开始时间段不能大于结束时间段
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

	std::string validate()
	{
		if (!class_id || class_id == 0)
			return ZH_WORDS_GETTER("freecourses.validate.classid_empty");
		if (!course_id || course_id == 0)
			return ZH_WORDS_GETTER("freecourses.validate.courseid_empty");

		if (!teacher_id || teacher_id->empty() || !isAllDigit(*teacher_id))
			return ZH_WORDS_GETTER("freecourses.validate.teacherid_invalid");
		if (!assistant_id || assistant_id->empty() || !isAllDigit(*assistant_id))
			return ZH_WORDS_GETTER("freecourses.validate.assistantid_invalid");

		if (!dates || dates->empty())
			return ZH_WORDS_GETTER("freecourses.validate.dates_empty");

		int dateIndex = 1;
		for (auto& date : *dates)
		{
			if (!date || date->empty() || *date == "string")
				return ZH_WORDS_GETTER("freecourses.validate.period_prefix") + std::to_string(dateIndex) + ZH_WORDS_GETTER("freecourses.validate.date_invalid");
			dateIndex++;
		}

		if (!start_time || start_time->empty() || *start_time == "string")
			return ZH_WORDS_GETTER("freecourses.validate.starttime_invalid");
		if (!end_time || end_time->empty() || *end_time == "string")
			return ZH_WORDS_GETTER("freecourses.validate.endtime_invalid");
		if (!compareTime(*start_time, *end_time))
			return ZH_WORDS_GETTER("freecourses.validate.starttime_after_endtime");

		int duration = calculateDurationMinutes(*start_time, *end_time);
		if (duration > 300)
			return ZH_WORDS_GETTER("freecourses.validate.duration_exceed_300");

		//限制人数格式判断
		if (limit_person_num && !limit_person_num->empty() && *limit_person_num != "string")
		{
			if (!isAllDigit(*limit_person_num))
				return ZH_WORDS_GETTER("freecourses.validate.limitpersonnum_invalid");
		}

		return "";
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif
