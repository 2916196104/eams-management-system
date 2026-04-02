#ifndef _CLASSROOMQUERY_H_
#define _CLASSROOMQUERY_H_

#include"../../GlobalInclude.h"
#include"domain/query/PageQuery.h"


#include OATPP_CODEGEN_BEGIN(DTO)

class ClassroomQuery:public PageQuery
{
	DTO_INIT(ClassroomQuery, PageQuery);
	//教室名
	//教室id
	//API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("classroom.field.id"));
	//教室名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("classroom.field.name"));
	//教室地址
	//API_DTO_FIELD_DEFAULT(String, address, ZH_WORDS_GETTER("classroom.field.address"));

};



#include OATPP_CODEGEN_END(DTO)
#endif