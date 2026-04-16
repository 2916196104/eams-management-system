#ifndef _PERIODDTO_
#define _PERIODDTO_

#include"../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//教室类
class periodDTO :public oatpp::DTO
{
	DTO_INIT(periodDTO, DTO);

	//周几上课，上课时间，下课时间，消课课时
	API_DTO_FIELD_DEFAULT(String, weeks, ZH_WORDS_GETTER("repeatcourses.field.weeks"));
	API_DTO_FIELD_DEFAULT(String, start_time, ZH_WORDS_GETTER("repeatcourses.field.starttime"));
	API_DTO_FIELD_DEFAULT(String, end_time, ZH_WORDS_GETTER("repeatcourses.field.endtime"));
	API_DTO_FIELD_REQUIRE(UInt32, dec_class_time, ZH_WORDS_GETTER("repeatcourses.field.decclasstime"), false);

};


#include OATPP_CODEGEN_END(DTO)
#endif