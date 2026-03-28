#include "stdafx.h"
#include "OnlineStudentService.h"
#include "../../dao/onlinestudent/OnlineStudentDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

std::list<OnlineExportDTO::Wrapper> OnlineService::listByIds(const std::vector<std::string>& ids)
{
	OnlineExportDAO dao;
	std::list<PtrStudentDetail> details = dao.selectByIds(ids);

	// 转换为导出DTO
	std::list<OnlineExportDTO::Wrapper> result;
	for (PtrStudentDetail& detail : details)
	{
		auto dto = OnlineExportDTO::createShared();

		// id 单独处理：string 转 UInt64
		dto->id = std::stoull(detail->student.getId());

		// student 部分
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->student,
			name, Name,
			gender, Gender,
			familyRel, FamilyRel,
			birthday, Birthday
		);

		// user 部分
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->user,
			mobile, Mobile,
			parentName, Name
		);

		// org 部分
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->org,
			schoolName, Name
		);

		// class_grade 部分
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->classGrade,
			gradeName, Name
		);

		// staff 部分
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->staff,
			counselorName, Name
		);

		result.push_back(dto);
	}
	return result;
}