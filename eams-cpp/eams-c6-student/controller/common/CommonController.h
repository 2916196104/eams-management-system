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
	//获取学员详情
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("common.interface.get-student-by-id"),
		getStudentById, StudentJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(
			String, "id", ZH_WORDS_GETTER("common.field.student.id"),
			"d934050a8bb373e8f8eed0bf7507ec17", true
		);
	)
		API_HANDLER_ENDPOINT_AUTH(
			API_M_GET,
			"/c3/common/student/get-by-id",
			getStudentById,
			QUERY(String, id),
			executeGetStudentById(id)
		);

	//下载学员头像
	API_DEF_ENDPOINT_INFO(
		ZH_WORDS_GETTER("common.interface.download-student-picture"), loadStudentPicturebyPicturePath, Void, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "picturePath", ZH_WORDS_GETTER("common.field.student.picture-path"), "file/test.jpg", true);
	);
	API_HANDLER_ENDPOINT_OPTION(
		API_M_GET,
		"/c3/common/student/download-student-picture",
		loadStudentPicturebyPicturePath,
		QUERY(String, picturePath),
		return executeLoadStudentPicturebyPicturePath(picturePath);
	);

	//修改学员头像
	ENDPOINT_INFO(modifyStudentPicture) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.modify-student-picture"));//添加接口描述
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("common.field.student.id"), "123", true);//添加参数
		API_DEF_ADD_FILE_FORM(FileOnlyDTO::Wrapper);
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_POST, "/c3/common/student/modify-picture/{id}", modifyStudentPicture, PATH(String, id), REQUEST(std::shared_ptr<IncomingRequest>, request), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeModifyStudentPicture(id, request));
	}

	//查询学员报名记录
	ENDPOINT_INFO(queryRegistrationRecordByPage) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.query-student-registration-record"));//添加接口描述
		API_DEF_ADD_PAGE_PARAMS();//添加分页参数
		API_DEF_ADD_RSP_JSON_WRAPPER(RegistrationPageJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/c3/common/registration-recordf/query-by-page", queryRegistrationRecordByPage, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, RegistrationPageQuery, queryParams);//获取参数
		API_HANDLER_RESP_VO(executeQueryRegistrationRecordByPage(query));
	}
private:
	StudentJsonVO::Wrapper executeGetStudentById(const String& id) {
		return StudentJsonVO::createShared();
	}
	StringJsonVO::Wrapper executeModifyStudentPicture(const String& id, std::shared_ptr<IncomingRequest>request) {
		return StringJsonVO::createShared();
	}
	RegistrationPageJsonVO::Wrapper executeQueryRegistrationRecordByPage(const RegistrationPageQuery::Wrapper& query) {
		return RegistrationPageJsonVO::createShared();
	}
	std::shared_ptr<OutgoingResponse> executeLoadStudentPicturebyPicturePath(const String& picturePath) {
		return nullptr;
	}
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) 
#endif