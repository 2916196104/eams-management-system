#pragma once
#ifndef COMMON_CONTROLLER_H
#define COMMON_CONTROLLER_H
#include "ApiHelper.h"
#include "../../Macros.h"
#include "ServerInfo.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/common/CommonVO.h"
#include "domain/dto/common/CommonDTO.h"
#include "domain/query/common/CommonQuery.h"
#include "service/common/CommonService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("common.api-tag")
class CommonController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(CommonController);
public:
	ENDPOINT_INFO(getCourseCountData) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.get-student-course-count"));//添加接口描述
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("common.field.student.id"), "123", true);//添加参数
		API_DEF_ADD_RSP_JSON_WRAPPER(CourseCountJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/c3/common/interface/get-student-course-count", getCourseCountData, PATH(String,id), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeGetCourseCountData(id));
	}

	ENDPOINT_INFO(SaveStudent) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.save-student"));//添加接口描述
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("common.field.student.id"), "123", true);//添加参数
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/c3/common/interface/save-student", SaveStudent, PATH(String, id), BODY_DTO(SaveStudentDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeSaveStudent(id));
	}
private:
	CourseCountJsonVO::Wrapper executeGetCourseCountData(const String& id) {
		return CourseCountJsonVO::createShared();
	}

	StringJsonVO::Wrapper executeSaveStudent(const String& id) {
		return StringJsonVO::createShared();
	}
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) 
#endif