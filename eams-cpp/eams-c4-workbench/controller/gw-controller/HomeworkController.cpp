#include "stdafx.h"
#include <string>
#include "HomeworkController.h"
#include "service/gw-service/HomeworkService.h"

namespace {

std::string toStd(const oatpp::String& s) {
	return s ? std::string(s->c_str()) : std::string();
}

} // namespace

HomeworkListPageJsonVO::Wrapper HomeworkController::executeGetHomeworkList(
	const std::shared_ptr<CustomerAuthorizeObject>& authObject,
	const String& adminId, const String& classId, const Int32& page, const Int32& size) {
	HomeworkService service;
	return service.getHomeworkList(authObject, toStd(adminId), toStd(classId),
		page && *page > 0 ? *page : 1, size && *size > 0 ? *size : 10);
}

HomeworkDetailJsonVO::Wrapper HomeworkController::executeGetHomeworkDetail(
	const std::shared_ptr<CustomerAuthorizeObject>& authObject,
	const String& homeworkId, const String& adminId) {
	HomeworkService service;
	return service.getHomeworkDetail(authObject, toStd(homeworkId), toStd(adminId));
}

HomeworkAddJsonVO::Wrapper HomeworkController::executeAddHomework(
	const std::shared_ptr<CustomerAuthorizeObject>& authObject, const String& body) {
	HomeworkService service;
	return service.addHomework(authObject, toStd(body));
}

HomeworkCommentJsonVO::Wrapper HomeworkController::executeCommentHomework(
	const std::shared_ptr<CustomerAuthorizeObject>& authObject, const String& body) {
	HomeworkService service;
	return service.commentHomework(authObject, toStd(body));
}
