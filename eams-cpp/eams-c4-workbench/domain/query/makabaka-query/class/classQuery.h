#pragma once

#include"../../../GlobalInclude.h"
#include"domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
定义一个查询老师信息的数据传输模型
*/
class ClassQuery :public PageQuery {
	//定义初始化
	DTO_INIT(ClassQuery, PageQuery);
	//班级名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("class.field.name"));
	//班级年级id
	API_DTO_FIELD_DEFAULT(Int32, grade, ZH_WORDS_GETTER("class.field.grade"));
	//班级id
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("class.field.id"));
};

#include OATPP_CODEGEN_END(DTO)