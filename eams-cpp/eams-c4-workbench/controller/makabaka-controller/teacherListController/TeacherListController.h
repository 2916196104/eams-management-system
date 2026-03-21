#pragma once
	
#include"domain/vo/makabaka-vo/teacher/teacherVO.h"
#include"domain/query/makabaka-query/teacher/teacherQuery.h"
#include"domain/vo/BaseJsonVO.h"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("teacher.tag")	

class TeacherListController :public oatpp::web::server::api::ApiController {
	//构造函数：继承父类的ObjectMapper（用于序列化/反序列化）
	API_ACCESS_DECLARE(TeacherListController);
public:
	//定义教师查询接口(条件+分页)
	//定义描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("teacher.query.summary"), getTeacherList, TeacherQuery, TeacherPageJsonVO::Wrapper, API_TAG);
	//定义教师查询端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c4/teacher/list", getTeacherList, TeacherQuery, executeGetTeacherList(query));
private:
	//查询教师列表
	TeacherPageJsonVO::Wrapper executeGetTeacherList(const TeacherQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)	