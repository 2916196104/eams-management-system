#pragma once

#ifndef _STUDENTDTO_H_
#define _STUDENTDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	学生数据传输对象
 */
class StudentDTO : public oatpp::DTO {
  DTO_INIT(StudentDTO, DTO);//初始化DTO

  API_DTO_FIELD(Int64, id, ZH_WORDS_GETTER("dto.student.id"), true,Int32(0));
  API_DTO_FIELD(String, name, ZH_WORDS_GETTER("dto.student.name"), true, "");
  API_DTO_FIELD_DEFAULT(String, headImg, ZH_WORDS_GETTER("dto.student.headImg"));
  API_DTO_FIELD(Int32, credit, ZH_WORDS_GETTER("dto.student.credit"), true, 0);
  API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("dto.student.birthday"));
  API_DTO_FIELD(Int32, age, ZH_WORDS_GETTER("dto.student.age"), true, 0);
  API_DTO_FIELD_DEFAULT(String, gender, ZH_WORDS_GETTER("dto.student.gender"));
  API_DTO_FIELD_DEFAULT(String, stage, ZH_WORDS_GETTER("dto.student.stage"));
  
};

// 分页 DTO：继承 PageDTO，包含 StudentDTO 列表和分页信息

class StudentPageDTO : public PageDTO<StudentDTO::Wrapper>
{
	DTO_INIT(StudentPageDTO, PageDTO<StudentDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _STUDENTDTO_H_
