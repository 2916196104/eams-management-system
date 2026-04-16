#ifndef _REPEATCOURSESARRANGECONTROLLER_H_
#define _REPEATCOURSESARRANGECONTROLLER_H_

#include"domain/vo/BaseJsonVO.h"
#include"domain/vo/Schedule/repeatCoursesArrangeVO.h"
#include"domain/dto/Schedule/repeatCoursesArrangeDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("repeatcourses.tag")

/**
	* 重复排课控制器
	*/
class repeatCoursesArrangeController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
private:
	// 2 定义控制器访问入口
	API_ACCESS_DECLARE(repeatCoursesArrangeController);

public:
	// 3 定义接口

	// 3.1 定义新增接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("repeatcourses.post.summary"), addRepeatCoursesArrange, StringJsonVO::Wrapper, API_TAG);
	// 3.2 定义新增接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c7-workbench/RepeatCoursesArrange", addRepeatCoursesArrange, BODY_DTO(repeatCoursesArrangeDTO::Wrapper, dto), execAddSample(dto, authObject->getPayload()));

private:
	// 3.3 演示新增数据
	StringJsonVO::Wrapper execAddSample(const repeatCoursesArrangeDTO::Wrapper& dto, const PayloadDTO& payload);
};


#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen


#endif