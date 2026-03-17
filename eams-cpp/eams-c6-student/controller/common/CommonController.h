#pragma once
#ifndef COMMON_CONTROLLER_H
#define COMMON_CONTROLLER_H
#include "ApiHelper.h"
#include "../../Macros.h"
#include "ServerInfo.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/common/CommonVO.h"
#include "domain/query/common/CommonQuery.h"
#include "service/common/CommonService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("common.api-tag")
class CommonController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(CommonController);
public: 
	ENDPOINT_INFO(getStudentById) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.get-student-by-id"));//添加接口描述
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("common.field.student.id"), "123", true);//添加参数
		API_DEF_ADD_RSP_JSON_WRAPPER(StudentJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/c3/common/student/get-by-id/{id}", getStudentById, PATH(String, id), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeGetStudentById(id));
	}

	ENDPOINT_INFO(modifyStudentPicture) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.modify-student-picture"));//添加接口描述
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("common.field.student.id"), "123", true);//添加参数
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);//添加返回数据包装
	}
    ENDPOINT(API_M_POST, "/c3/common/student/modify-picture/{id}", modifyStudentPicture,PATH(String,id), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeModifyStudentPicture(id));
	}

	ENDPOINT_INFO(queryRegistrationRecordByPage) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.query-student-registration-record"));//添加接口描述
		API_DEF_ADD_PAGE_PARAMS();//添加分页参数
		API_DEF_ADD_RSP_JSON_WRAPPER(RegistrationPageJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/c3/common/registration-recordf/query-by-page", queryRegistrationRecordByPage, QUERIES(QueryParams, queryParams),API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, RegistrationPageQuery, queryParams);//获取参数
		API_HANDLER_RESP_VO(executeQueryRegistrationRecordByPage(query));
	}
private:
	StudentJsonVO::Wrapper executeGetStudentById(const String& id){
		return StudentJsonVO::createShared();
	}
    StringJsonVO::Wrapper executeModifyStudentPicture(const String& id){
		return StringJsonVO::createShared();
	}
	RegistrationPageJsonVO::Wrapper executeQueryRegistrationRecordByPage(const RegistrationPageQuery::Wrapper& query){
		return RegistrationPageJsonVO::createShared();
	}
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) 
#endif