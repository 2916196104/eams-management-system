#pragma once
#ifndef _HOMEWORK_CONTROLLER_
#define _HOMEWORK_CONTROLLER_

#include "ServerInfo.h" // 中文字典需要引入的头文件
#include "Macros.h"     // 中文字典需要引入的头文件
#include "ApiHelper.h"
#include "domain/dto/gw-dto/CommonResponseDTO.h"

using namespace oatpp;

#define API_TAG ZH_WORDS_GETTER("homework.tag")

#include OATPP_CODEGEN_BEGIN(ApiController)

class HomeworkController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(HomeworkController);
public:
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.list.summary"), getHomeworkList, HomeworkListPageJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "admin_id", ZH_WORDS_GETTER("homework.query.admin_id"), "admin001", true);
		API_DEF_ADD_QUERY_PARAMS(String, "class_id", ZH_WORDS_GETTER("homework.query.class_id"), "class001", true);
		API_DEF_ADD_QUERY_PARAMS(Int32, "page", ZH_WORDS_GETTER("homework.query.page"), 1, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "size", ZH_WORDS_GETTER("homework.query.size"), 10, false);
	);
	ENDPOINT(API_M_GET, "/c4/homework/list", getHomeworkList,
		QUERY(String, admin_id),
		QUERY(String, class_id),
		QUERY(Int32, page),
		QUERY(Int32, size),
		API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeGetHomeworkList(authObject, admin_id, class_id, page, size));
	}

	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.detail.summary"), getHomeworkDetail, HomeworkDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "homework_id", ZH_WORDS_GETTER("homework.query.homework_id"), "hw001", true);
		API_DEF_ADD_QUERY_PARAMS(String, "admin_id", ZH_WORDS_GETTER("homework.query.admin_id"), "admin001", true);
	);
	ENDPOINT(API_M_GET, "/c4/homework/detail", getHomeworkDetail,
		QUERY(String, homework_id),
		QUERY(String, admin_id),
		API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeGetHomeworkDetail(authObject, homework_id, admin_id));
	}

	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.add.summary"), addHomework, HomeworkAddJsonVO::Wrapper, API_TAG);
	ENDPOINT(API_M_POST, "/c4/homework/add", addHomework,
		BODY_STRING(String, body),
		API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeAddHomework(authObject, body));
	}

	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.comment.summary"), commentHomework, HomeworkCommentJsonVO::Wrapper, API_TAG);
	ENDPOINT(API_M_POST, "/c4/homework/comment", commentHomework,
		BODY_STRING(String, body),
		API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeCommentHomework(authObject, body));
	}

private:
	HomeworkListPageJsonVO::Wrapper executeGetHomeworkList(const std::shared_ptr<CustomerAuthorizeObject>& authObject,
		const String& adminId, const String& classId, const Int32& page, const Int32& size);
	HomeworkDetailJsonVO::Wrapper executeGetHomeworkDetail(const std::shared_ptr<CustomerAuthorizeObject>& authObject,
		const String& homeworkId, const String& adminId);
	HomeworkAddJsonVO::Wrapper executeAddHomework(const std::shared_ptr<CustomerAuthorizeObject>& authObject, const String& body);
	HomeworkCommentJsonVO::Wrapper executeCommentHomework(const std::shared_ptr<CustomerAuthorizeObject>& authObject, const String& body);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // _HOMEWORK_CONTROLLER_
