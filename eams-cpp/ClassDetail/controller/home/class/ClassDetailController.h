#ifndef _CLASSDETAILCONTROLLER_H_
#define _CLASSDETAILCONTROLLER_H_


#include "ApiHelper.h"
#include "Macros.h"
#include "ServerInfo.h"

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"

#include "domain/query/home/class/ClassDetailQuery.h"
#include "domain/dto/home/class/ClassDetailDTO.h"
#include "domain/vo/home/class/ClassDetailVO.h"

// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("ClassDetail.tag")


class ClassDetailController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
	// 2 定义控制器访问入口
	API_ACCESS_DECLARE(ClassDetailController);
	// 3 定义接口
public:
	
	// 3.1 定义ID查询接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("ClassDetail.summary"), GetClassDetailById, ClassDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("ClassDetail.id"), "d934050a8bb373e8f8eed0bf7507ec17", true);
	);
	// 3.2 定义ID查询接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/home/class/classdetail", GetClassDetailById, QUERY(String, id), execQueryById(id));
private:
	// 3.3 演示ID查询数据
	ClassDetailJsonVO::Wrapper execQueryById(const String& id);
};


// 0 取消API控制器使用宏
#include OATPP_CODEGEN_END(ApiController) 

#endif
