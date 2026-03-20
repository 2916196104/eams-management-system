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
	
};
	
#include OATPP_CODEGEN_END(DTO)

#endif