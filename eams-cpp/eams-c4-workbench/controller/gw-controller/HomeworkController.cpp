#include "stdafx.h"
#include <climits>
#include <string>
#include "HomeworkController.h"
#include "service/gw-service/HomeworkService.h"

namespace {

	std::string toStd(const oatpp::String& s) {
		return s ? std::string(s->c_str()) : std::string();
	}

	std::string teacherIdFromListQuery(const HomeworkListQueryDTO::Wrapper& query) {
		if (!query) {
			return {};
		}
		const std::string t = toStd(query->teacher_id);
		if (!t.empty()) {
			return t;
		}
		return toStd(query->admin_id);
	}

	int32_t queryPageIndex(const HomeworkListQueryDTO::Wrapper& query) {
		if (query && query->pageIndex && *query->pageIndex > 0) {
			const auto v = *query->pageIndex;
			return v > static_cast<v_uint64>(INT32_MAX) ? 1 : static_cast<int32_t>(v);
		}
		if (query && query->page && *query->page > 0) {
			return *query->page;
		}
		return 1;
	}

	int32_t queryPageSize(const HomeworkListQueryDTO::Wrapper& query) {
		if (query && query->pageSize && *query->pageSize > 0) {
			const auto v = *query->pageSize;
			return v > static_cast<v_uint64>(INT32_MAX) ? 10 : static_cast<int32_t>(v);
		}
		if (query && query->size && *query->size > 0) {
			return *query->size;
		}
		return 10;
	}

} // namespace

HomeworkListPageJsonVO::Wrapper HomeworkController::executeGetHomeworkList(
	const std::shared_ptr<CustomerAuthorizeObject>& authObject,
	const HomeworkListQueryDTO::Wrapper& query) {
	HomeworkService service;
	return service.getHomeworkList(authObject, teacherIdFromListQuery(query), toStd(query->class_id),
		queryPageIndex(query), queryPageSize(query));
}

HomeworkDetailJsonVO::Wrapper HomeworkController::executeGetHomeworkDetail(
	const std::shared_ptr<CustomerAuthorizeObject>& authObject,
	const HomeworkDetailQueryDTO::Wrapper& query) {
	HomeworkService service;
	std::string teacherId = toStd(query->teacher_id);
	if (teacherId.empty()) {
		teacherId = toStd(query->admin_id);
	}
	return service.getHomeworkDetail(authObject, toStd(query->homework_id), teacherId);
}

HomeworkAddJsonVO::Wrapper HomeworkController::executeAddHomework(
	const std::shared_ptr<CustomerAuthorizeObject>& authObject,
	const HomeworkAddBodyDTO::Wrapper& body) {
	HomeworkService service;
	return service.addHomework(authObject, body);
}

HomeworkCommentJsonVO::Wrapper HomeworkController::executeCommentHomework(
	const std::shared_ptr<CustomerAuthorizeObject>& authObject,
	const HomeworkCommentBodyDTO::Wrapper& body) {
	HomeworkService service;
	return service.commentHomework(authObject, body);
}