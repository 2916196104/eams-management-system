#include "stdafx.h"
#include "RegisterService.h"
#include "../../../lib-common/include/SimpleDateTimeFormat.h"
#include "../../domain/do/Course/RegisterDO.h"
#include "../../dao/Course/RegisterDAO.h"
#include "../../../eams-c7-class/Macros.h"
#include "../../../lib-common/include/id/UuidFacade.h"

std::string RegisterService::saveReg(const RegisterAddDTO::Wrapper& dto)
{
	try {
		if (!dto || !dto->getPayload()) {
			return "";
		}

		RegisterDO data;
		auto now = std::chrono::system_clock::now();
		int64_t id = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
		data.setId(id);

		RegisterDAO dao;
		int64_t student_id = 0;
		int64_t course_id = 0;

		if (dto->stuName && dto->stuName->c_str() && *(dto->stuName->c_str())) {
			student_id = dao.selectStudentIdByName(dto->stuName->c_str());
		}
		if (dto->courseName && dto->courseName->c_str() && *(dto->courseName->c_str())) {
			course_id = dao.selectCourseIdByName(dto->courseName->c_str());
		}

		int64_t subject_id = dto->subjectId;

		data.setStudentId(student_id);
		data.setCourseId(course_id);
		data.setSubjectId(subject_id);

		const char* startDate = dto->startDate ? dto->startDate->c_str() : "";
		if (startDate && strlen(startDate) > 10) {
			char buf[11] = { 0 };
			strncpy(buf, startDate, 10);
			data.setStartDate(buf);
		}
		else {
			data.setStartDate(startDate ? startDate : "");
		}

		const char* expireDate = dto->expireDate ? dto->expireDate->c_str() : "";
		if (expireDate && strlen(expireDate) > 10) {
			char buf[11] = { 0 };
			strncpy(buf, expireDate, 10);
			data.setExpireDate(buf);
		}
		else {
			data.setExpireDate(expireDate ? expireDate : "");
		}

		data.setCountLessonTotal(dto->courseNum);
		data.setAmount(dto->coursePrice);
		data.setDiscountAmount(dto->discountPrice);
		data.setPaidAmount(dto->actualPayment);

		const char* tip = dto->tip ? dto->tip->c_str() : "";
		if (tip && strlen(tip) > 255) {
			char buf[256] = { 0 };
			strncpy(buf, tip, 255);
			data.setRemark(buf);
		}
		else {
			data.setRemark(tip ? tip : "");
		}

		int64_t userId = 0;
		try {
			if (dto->getPayload() && dto->getPayload()->getId().c_str() && *(dto->getPayload()->getId().c_str())) {
				userId = stoll(dto->getPayload()->getId().c_str());
			}
		}
		catch (...) {}
		data.setCreator(userId);

		std::string addTime = SimpleDateTimeFormat::format();
		data.setAddTime(addTime.length() > 19 ? addTime.substr(0, 19) : addTime);

		data.setDeleted(0);
		data.setVerifyState(1);

		uint64_t newId = dao.insert(data);
		return newId > 0 ? std::to_string(newId) : "";
	}
	catch (const std::exception& e) {
		printf("Save error: %s\n", e.what());
		return "";
	}
}