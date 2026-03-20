#ifndef _FREECOURSESARRANGEDTO_H_
#define _FREECOURSESARRANGEDTO_H_

#include"../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 教室类
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


	// 上课日期
	API_DTO_FIELD_DEFAULT(String, classdate, ZH_WORDS_GETTER("freecourses.field.classdate"));

	//上课时间，下课时间，消课课时
	API_DTO_FIELD_DEFAULT(String, start_time, ZH_WORDS_GETTER("freecourses.field.starttime"));
	API_DTO_FIELD_DEFAULT(String, end_time, ZH_WORDS_GETTER("freecourses.field.endtime"));
	API_DTO_FIELD_REQUIRE(UInt32, dec_class_time, ZH_WORDS_GETTER("freecourses.field.decclasstime"), false);


	//限制人数
	API_DTO_FIELD_REQUIRE(String, limit_person_num, ZH_WORDS_GETTER("freecourses.field.limitpersonnum"), false);
	//开启预约
	API_DTO_FIELD_REQUIRE(Boolean, open_appointment, ZH_WORDS_GETTER("freecourses.field.openappointment"), false);
	//是否检查冲突
	API_DTO_FIELD_REQUIRE(Boolean, check_conflict, ZH_WORDS_GETTER("freecourses.field.checkconflict"), false);

};

#include OATPP_CODEGEN_END(DTO)
#endif