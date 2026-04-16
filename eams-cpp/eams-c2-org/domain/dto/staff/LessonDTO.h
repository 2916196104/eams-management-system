#pragma once

#ifndef _LESSONDTO_H_
#define _LESSONDTO_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
	授课记录数据传输对象
 */

class LessonQuery : public PageQuery {
  API_DTO_FIELD_REQUIRE(Int64, id, ZH_WORDS_GETTER("staff.field.id"), true);
DTO_INIT(LessonQuery, PageQuery); 
  API_DTO_FIELD_DEFAULT(String, startDate, ZH_WORDS_GETTER("staff.get-lesson-record.start-date"));
  API_DTO_FIELD_DEFAULT(String, endDate, ZH_WORDS_GETTER("staff.get-lesson-record.end-date"));

};

#include OATPP_CODEGEN_END(DTO)
#endif // _LESSONDTO_H_
