#pragma once

#ifndef _CLASSROOM_CONTROLLER_
#define _CLASSROOM_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/hh-dto/ClassroomDTO.h"
#include "domain/query/hh-query/ClassroomQuery.h"
#include "domain/vo/hh-vo/ClassroomVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController) // 开始代码生成

#define API_TAG2 ZH_WORDS_GETTER("classroom.tag")

class ClassroomController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(ClassroomController);
public:
	// 教室列表查询接口信息
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("classroom.get.summary"), queryClassroom, ClassroomQuery, ClassroomPageJsonVO::Wrapper, API_TAG2
	);
	// 教室列表查询接口处理
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c4-workbench/classroom", queryClassroom, ClassroomQuery,
		execQueryClassroom(query));
private:
	ClassroomPageJsonVO::Wrapper execQueryClassroom(const ClassroomQuery::Wrapper& query);
};

#undef API_TAG2

#include OATPP_CODEGEN_END(ApiController) // 结束代码生成

#endif