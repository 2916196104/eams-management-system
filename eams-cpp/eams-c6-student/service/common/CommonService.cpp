
#include "stdafx.h"
#include "CommonService.h"
#include "../../dao/common/CommonDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
void StudentService::ModifyStudentHeadImg(ModifyStudentHeadImgDTO::Wrapper dto) {
	uint64_t id = dto->id;
	std::string headImg = dto->picturePath;
	StudentDAO dao;
	dao.updateStudentHeadImg(id, headImg);
}
StudentDTO::Wrapper StudentService::GetStudentDetailById(uint64_t studentId) {
	StudentDAO dao;
	return dao.getStudentDetailById(studentId);
}
RegistrationPageDTO::Wrapper RegistrationRecordService::GetRegistrationRecordWithPage(RegistrationPageQuery::Wrapper query) {
	auto pages = RegistrationPageDTO::createShared();
	RegistrationRecordDAO dao;
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;
	uint64_t count = dao.count(query->id);
	if (count <= 0) {
		return pages;
	}
	pages->total = count;
	pages->calcPages();
	auto results = dao.selectRegistrationRecordWithPage(query);
	for (auto& result : results) {
		pages->addData(result);
	}
	return pages;

}
