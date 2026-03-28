#pragma once

#include"../../../GlobalInclude.h"
#include"domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
定义一个老师信息的数据传输模型
*/
class TeacherDTO :public oatpp::DTO {
	//定义初始化	
	DTO_INIT(TeacherDTO, DTO);
	//教师id
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("teacher.field.id"),true);
	//教师姓名
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("teacher.field.name"), true);
	//教师职务id
	API_DTO_FIELD_REQUIRE(String, position_id, ZH_WORDS_GETTER("teacher.field.position"),false);
	//教师职务名称
	API_DTO_FIELD_REQUIRE(String, position_name, ZH_WORDS_GETTER("teacher.field.position_name"), false);
};

/*
定义一个老师列表分页传输对象
*/
class TeacherPageDTO :public PageDTO<TeacherDTO::Wrapper> {
	//定义初始化
	DTO_INIT(TeacherPageDTO, PageDTO<TeacherDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)