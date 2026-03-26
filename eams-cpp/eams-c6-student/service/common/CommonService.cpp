
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
std::list<RegistrationDTO::Wrapper> RegistrationRecordService::GetRegistrationRecordWithPage(RegistrationPageQuery::Wrapper query) {
	RegistrationRecordDAO dao;
	return dao.selectRegistrationRecordWithPage(query);
}

