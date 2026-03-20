#ifndef _FREECOURSESARRANGECONTROLLER_H_
#define _FREECOURSESARRANGECONTROLLER_H_

#include"domain/vo/BaseJsonVO.h"
#include"domain/vo/Schedule/freeCoursesArrangeVO.h"
#include"domain/dto/Schedule/freeCoursesArrangeDTO.h"


#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("freecourses.tag")

/**
	* 自由排课控制器
	*/
class freeCoursesArrangeController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
private:
	// 2 定义控制器访问入口
	API_ACCESS_DECLARE(freeCoursesArrangeController);

public:
	// 3 定义接口
	
	// 3.1 定义新增接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("freecourses.post.summary"), addFreeCoursesArrange, freeCoursesArrangeJsonVO::Wrapper, API_TAG);
	// 3.2 定义新增接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/lesson_schedule/free", addFreeCoursesArrange, BODY_DTO(freeCoursesArrangeDTO::Wrapper, dto), execAddSample(dto));

private:
	// 3.3 演示新增数据
	freeCoursesArrangeJsonVO::Wrapper execAddSample(const freeCoursesArrangeDTO::Wrapper& dto);
};


#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen


#endif