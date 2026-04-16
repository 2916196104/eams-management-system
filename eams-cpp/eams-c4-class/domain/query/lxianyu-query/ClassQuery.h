#pragma once

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class MyClassPageQuery : public PageQuery
{
	DTO_INIT(MyClassPageQuery, PageQuery);

	DTO_FIELD(String, myclass);
	DTO_FIELD_INFO(myclass) {
		info->description = ZH_WORDS_GETTER("Class.myclass.myclass");
	}
	DTO_FIELD(String, teacher);
	DTO_FIELD_INFO(teacher) {
		info->description = ZH_WORDS_GETTER("Class.myclass.teacher");
	}
	DTO_FIELD(String, course);
	DTO_FIELD_INFO(course) {
		info->description = ZH_WORDS_GETTER("Class.myclass.course");
	}
	DTO_FIELD(String, number);
	DTO_FIELD_INFO(number) {
		info->description = ZH_WORDS_GETTER("Class.myclass.number");
	}

};

#include OATPP_CODEGEN_END(DTO)

