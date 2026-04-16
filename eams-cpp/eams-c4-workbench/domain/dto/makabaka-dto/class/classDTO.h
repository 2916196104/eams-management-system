#pragma once

#include"../../../GlobalInclude.h"
#include"domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
定义一个班级信息的数据传输模型
*/
class ClassDTO :public oatpp::DTO {
	//定义初始化
	DTO_INIT(ClassDTO, DTO);
	//班级id
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("class.field.id"), true);
	//班级名
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("class.field.name"), true);
	//班级年级id
	API_DTO_FIELD_REQUIRE(Int32, grade_id, ZH_WORDS_GETTER("class.field.grade"), false);
};

/*
定义一个班级列表分页传输对象
*/
class ClassPageDTO :public PageDTO<ClassDTO::Wrapper> {
	//定义初始化
	DTO_INIT(ClassPageDTO, PageDTO<ClassDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)