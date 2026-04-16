#ifndef _CLASSROOMCONTROLLER_H_
#define _CLASSROOMCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include"domain/vo/BaseJsonVO.h"
#include"domain/vo/Schedule/ClassroomVO.h"
#include"domain/dto/Schedule/ClassroomDTO.h"
#include"domain/query/Schedule/ClassroomQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("classroom.tag")

/**
	* 教室控制器（条件+分页）
	*/
class ClassroomController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
private:
	// 2 定义控制器访问入口
	API_ACCESS_DECLARE(ClassroomController);

public:
	// 3 定义接口
	// 
	// 3.1 定义获取教室列表(条件+分页）描述
	//	接口标题，端点函数名称，查询参数，响应参数,接口描述标签
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("classroom.query-page.summary"), queryPage, ClassroomQuery, ClassroomPageJsonVO::Wrapper, API_TAG);
	// 3.2 定义获取教室列表(条件+分页）处理
	//	HTTP请求格式，端点访问地址，端点函数名称，参数解析操作的宏，（可变：参数返回逻辑）
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7-workbench/classroom", queryPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, ClassroomQuery, queryParams); API_HANDLER_RESP_VO( execQueryPage(query) ); );

private:
	//3.3：定义获取班级列表（条件+分页）接口执行函数
	ClassroomPageJsonVO::Wrapper execQueryPage(const ClassroomQuery::Wrapper &query);
};


#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen


#endif