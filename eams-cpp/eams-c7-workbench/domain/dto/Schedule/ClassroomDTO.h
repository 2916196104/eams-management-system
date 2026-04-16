#ifndef _CLASSROOM_H_
#define _CLASSROOM_H_

#include"../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//教室类
class ClassroomDTO :public oatpp::DTO
{
	DTO_INIT(ClassroomDTO, DTO);
	//教室id
	//API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("classroom.field.id"));
	//教室名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("classroom.field.name"));
	//教室地址
	API_DTO_FIELD_DEFAULT(String, address, ZH_WORDS_GETTER("classroom.field.address"));

};

/*
	教室分页类
*/
class ClassroomPageDTO :public PageDTO<ClassroomDTO::Wrapper>
{
	DTO_INIT(ClassroomPageDTO, PageDTO<ClassroomDTO::Wrapper>);

};

#include OATPP_CODEGEN_END(DTO)
#endif