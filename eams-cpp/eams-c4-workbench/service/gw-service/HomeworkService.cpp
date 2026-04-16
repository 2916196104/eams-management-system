/*
 Copyright Zero One Star. All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
*/
#include "stdafx.h"

#include <chrono>
#include <cstdint>
#include <ctime>
#include <stdexcept>

#include "CustomerAuthorizeHandler.h"
#include "dao/gw-dao/HomeworkDAO.h"
#include "domain/dto/gw-dto/HomeworkRequestDTO.h"
#include "service/gw-service/HomeworkDtoMapper.h"
#include "service/gw-service/HomeworkService.h"

namespace {

std::string nowDateTimeString() {
	const auto now = std::chrono::system_clock::now();
	const std::time_t t = std::chrono::system_clock::to_time_t(now);
	std::tm local{};
#ifdef _WIN32
	localtime_s(&local, &t);
#else
	localtime_r(&t, &local);
#endif
	char buf[32]{};
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local);
	return std::string(buf);
}

bool parseInt64(const std::string& s, int64_t& out) {
	try {
		size_t pos = 0;
		const long long v = std::stoll(s, &pos, 10);
		if (pos != s.size()) {
			return false;
		}
		out = static_cast<int64_t>(v);
		return true;
	} catch (...) {
		return false;
	}
}

bool adminMatchesPayload(const std::string& adminId, const PayloadDTO& p) {
	return !adminId.empty() && adminId == p.getId();
}

int64_t userIdFromPayload(const PayloadDTO& p) {
	int64_t uid = 0;
	(void)parseInt64(p.getId(), uid);
	return uid;
}

} // namespace

HomeworkListPageJsonVO::Wrapper HomeworkService::getHomeworkList(const std::shared_ptr<CustomerAuthorizeObject>& auth,
	const std::string& adminId, const std::string& classId, int32_t page, int32_t size) {
	auto vo = HomeworkListPageJsonVO::createShared();
	if (!auth) {
		vo->code = 40100;
		vo->message = u8"\u672A\u6388\u6743";
		return vo;
	}
	const auto& payload = auth->getPayload();
	if (!adminMatchesPayload(adminId, payload)) {
		vo->code = 40300;
		vo->message = u8"\u6559\u5E08ID\u4E0E\u767B\u5F55\u7528\u6237\u4E0D\u5339\u914D";
		return vo;
	}
	if (classId.empty()) {
		vo->code = 40000;
		vo->message = u8"\u73ED\u7EA7ID\u4E0D\u80FD\u4E3A\u7A7A";
		return vo;
	}
	HomeworkDAO dao;
	if (!dao.isAdminManagingClass(classId, adminId)) {
		vo->code = 40301;
		vo->message = u8"\u65E0\u6743\u7BA1\u7406\u8BE5\u73ED\u7EA7";
		return vo;
	}
	const int32_t pageIndex = page > 0 ? page : 1;
	const int32_t pageSize = size > 0 ? size : 10;
	const int32_t safeSize = pageSize > 200 ? 200 : pageSize;
	const uint64_t total = dao.countHomeworkPublishedByClassFilter(classId);
	const int64_t pages = safeSize > 0 ? static_cast<int64_t>((total + static_cast<uint64_t>(safeSize) - 1) / static_cast<uint64_t>(safeSize)) : 0;
	const int offset = (pageIndex - 1) * safeSize;
	auto rows = dao.selectPublishedHomeworkPage(classId, offset, safeSize);

	auto pageDto = HomeworkListPageDTO::createShared();
	pageDto->pageIndex = static_cast<v_uint64>(pageIndex);
	pageDto->pageSize = static_cast<v_uint64>(safeSize);
	pageDto->total = static_cast<v_int64>(total);
	pageDto->pages = static_cast<v_int64>(pages);
	pageDto->rows = oatpp::List<oatpp::Object<HomeworkListRowDTO>>::createShared();
	for (const auto& r : rows) {
		const int32_t cnt = dao.countSubmitByHomeworkId(std::to_string(r.id));
		pageDto->rows->push_back(HomeworkDtoMapper::toListRow(r, cnt));
	}
	vo->code = 10000;
	vo->message = "success";
	vo->data = pageDto;
	return vo;
}

HomeworkDetailJsonVO::Wrapper HomeworkService::getHomeworkDetail(const std::shared_ptr<CustomerAuthorizeObject>& auth,
	const std::string& homeworkId, const std::string& adminId) {
	auto vo = HomeworkDetailJsonVO::createShared();
	if (!auth) {
		vo->code = 40100;
		vo->message = u8"\u672A\u6388\u6743";
		return vo;
	}
	const auto& payload = auth->getPayload();
	if (!adminMatchesPayload(adminId, payload)) {
		vo->code = 40300;
		vo->message = u8"\u6559\u5E08ID\u4E0E\u767B\u5F55\u7528\u6237\u4E0D\u5339\u914D";
		return vo;
	}
	int64_t pk = 0;
	if (!parseInt64(homeworkId, pk)) {
		vo->code = 40001;
		vo->message = u8"\u4F5C\u4E1AID\u683C\u5F0F\u65E0\u6548";
		return vo;
	}
	HomeworkDAO dao;
	bool ok = false;
	const auto row = dao.selectHomeworkById(pk, ok);
	if (!ok) {
		vo->code = 40400;
		vo->message = u8"\u4F5C\u4E1A\u4E0D\u5B58\u5728";
		return vo;
	}
	const std::string classKey = !row.classKey.empty() ? row.classKey : std::to_string(row.classId);
	if (!dao.isAdminManagingClass(classKey, adminId)) {
		vo->code = 40301;
		vo->message = u8"\u65E0\u6743\u67E5\u770B\u8BE5\u4F5C\u4E1A";
		return vo;
	}
	const auto records = dao.selectRecordsByHomeworkId(homeworkId);
	auto data = HomeworkDetailDataDTO::createShared();
	HomeworkDtoMapper::fillDetail(data, row, records, "");
	vo->code = 10000;
	vo->message = "success";
	vo->data = data;
	return vo;
}

HomeworkAddJsonVO::Wrapper HomeworkService::addHomework(const std::shared_ptr<CustomerAuthorizeObject>& auth,
	const HomeworkAddBodyDTO::Wrapper& body) {
	auto vo = HomeworkAddJsonVO::createShared();
	if (!auth) {
		vo->code = 40100;
		vo->message = u8"\u672A\u6388\u6743";
		return vo;
	}
	if (!body) {
		vo->code = 40002;
		vo->message = u8"\u8BF7\u6C42\u4F53\u4E0D\u80FD\u4E3A\u7A7A";
		return vo;
	}
	const auto& payload = auth->getPayload();
	std::string adminId = body->teacher_id ? body->teacher_id->c_str() : "";
	if (adminId.empty()) {
		adminId = body->admin_id ? body->admin_id->c_str() : "";
	}
	if (!adminMatchesPayload(adminId, payload)) {
		vo->code = 40300;
		vo->message = u8"\u6559\u5E08ID\u4E0E\u767B\u5F55\u7528\u6237\u4E0D\u5339\u914D";
		return vo;
	}
	const std::string classIdStr = body->class_id ? body->class_id->c_str() : "";
	const std::string title = body->title ? body->title->c_str() : "";
	const std::string content = body->content ? body->content->c_str() : "";
	if (classIdStr.empty() || title.empty()) {
		vo->code = 40003;
		vo->message = u8"\u73ED\u7EA7ID\u6216\u6807\u9898\u4E0D\u80FD\u4E3A\u7A7A";
		return vo;
	}
	HomeworkDAO dao;
	if (!dao.isAdminManagingClass(classIdStr, adminId)) {
		vo->code = 40301;
		vo->message = u8"\u65E0\u6743\u5728\u8BE5\u73ED\u7EA7\u53D1\u5E03\u4F5C\u4E1A";
		return vo;
	}
	int64_t classPk = 0;
	if (!parseInt64(classIdStr, classPk)) {
		vo->code = 40004;
		vo->message = u8"\u73ED\u7EA7ID\u683C\u5F0F\u65E0\u6548";
		return vo;
	}
	const int64_t creator = userIdFromPayload(payload);
	const std::string ts = nowDateTimeString();
	const uint64_t newId = dao.insertHomework(classPk, title, content, creator, 0, ts, ts);
	auto data = HomeworkAddDataDTO::createShared();
	data->homework_id = oatpp::String(std::to_string(newId).c_str());
	data->title = oatpp::String(title.c_str());
	vo->code = 10000;
	vo->message = "success";
	vo->data = data;
	return vo;
}

HomeworkCommentJsonVO::Wrapper HomeworkService::commentHomework(const std::shared_ptr<CustomerAuthorizeObject>& auth,
	const HomeworkCommentBodyDTO::Wrapper& body) {
	auto vo = HomeworkCommentJsonVO::createShared();
	if (!auth) {
		vo->code = 40100;
		vo->message = u8"\u672A\u6388\u6743";
		return vo;
	}
	if (!body) {
		vo->code = 40002;
		vo->message = u8"\u8BF7\u6C42\u4F53\u4E0D\u80FD\u4E3A\u7A7A";
		return vo;
	}
	const auto& payload = auth->getPayload();
	std::string adminId = body->teacher_id ? body->teacher_id->c_str() : "";
	if (adminId.empty()) {
		adminId = body->admin_id ? body->admin_id->c_str() : "";
	}
	if (!adminMatchesPayload(adminId, payload)) {
		vo->code = 40300;
		vo->message = u8"\u6559\u5E08ID\u4E0E\u767B\u5F55\u7528\u6237\u4E0D\u5339\u914D";
		return vo;
	}
	const std::string recordId = body->submit_id ? body->submit_id->c_str() : "";
	int32_t score = 0;
	std::string commentText;
	if (body->review) {
		score = body->review->score;
		commentText = body->review->content ? body->review->content->c_str() : "";
	} else {
		score = body->score;
		commentText = body->content ? body->content->c_str() : "";
	}
	if (recordId.empty()) {
		vo->code = 40005;
		vo->message = u8"\u63D0\u4EA4\u8BB0\u5F55ID\u4E0D\u80FD\u4E3A\u7A7A";
		return vo;
	}
	if (score < 0 || score > 100) {
		vo->code = 40006;
		vo->message = u8"\u5206\u6570\u5E94\u57280-100\u4E4B\u95F4";
		return vo;
	}
	HomeworkDAO dao;
	bool recOk = false;
	const auto rec = dao.selectRecordById(recordId, recOk);
	if (!recOk) {
		vo->code = 40401;
		vo->message = u8"\u63D0\u4EA4\u8BB0\u5F55\u4E0D\u5B58\u5728";
		return vo;
	}
	int64_t hwPk = 0;
	if (!parseInt64(rec.homeworkId, hwPk)) {
		vo->code = 40007;
		vo->message = u8"\u4F5C\u4E1AID\u6570\u636E\u5F02\u5E38";
		return vo;
	}
	bool hwOk = false;
	const auto hw = dao.selectHomeworkById(hwPk, hwOk);
	if (!hwOk) {
		vo->code = 40400;
		vo->message = u8"\u4F5C\u4E1A\u4E0D\u5B58\u5728";
		return vo;
	}
	const std::string classKey = !hw.classKey.empty() ? hw.classKey : std::to_string(hw.classId);
	if (!dao.isAdminManagingClass(classKey, adminId)) {
		vo->code = 40301;
		vo->message = u8"\u65E0\u6743\u70B9\u8BC4\u8BE5\u63D0\u4EA4";
		return vo;
	}
	const std::string ts = nowDateTimeString();
	const int n = dao.updateRecordComment(recordId, static_cast<int>(score), commentText, ts, adminId);
	if (n <= 0) {
		vo->code = 50000;
		vo->message = u8"\u70B9\u8BC4\u66F4\u65B0\u5931\u8D25";
		return vo;
	}
	auto data = HomeworkCommentDataDTO::createShared();
	data->comment_id = oatpp::String(recordId.c_str());
	data->score = score;
	data->content = oatpp::String(commentText.c_str());
	vo->code = 10000;
	vo->message = "success";
	vo->data = data;
	return vo;
}
