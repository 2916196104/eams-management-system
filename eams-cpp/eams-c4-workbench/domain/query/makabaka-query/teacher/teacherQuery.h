#pragma once

#include"../../../GlobalInclude.h"
#include"domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
定义一个查询老师信息的数据传输模型
*/
class TeacherQuery :public PageQuery {
	//定义初始化
	DTO_INIT(TeacherQuery, PageQuery);
	//教师名字
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("teacher.field.name"));
};

#include OATPP_CODEGEN_END(DTO)