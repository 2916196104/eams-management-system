#pragma once
#ifndef _SAMPLE_SERVICE_
#define _SAMPLE_SERVICE_
#include "../../domain/dto/common/CommonDTO.h"
#include "../../dao/common/CommonDAO.h"
class StudentService {
public:
	void ModifyStudentHeadImg(ModifyStudentHeadImgDTO::Wrapper dto);
};
class RegistrationRecordService {
public:
	std::list<RegistrationDTO::Wrapper> GetRegistrationRecordWithPage(RegistrationPageQuery::Wrapper query);
};







#endif // !_SAMPLE_SERVICE_


