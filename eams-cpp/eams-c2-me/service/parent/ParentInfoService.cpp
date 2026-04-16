#include "stdafx.h"
#include "Macros.h"
#include "ParentInfoService.h"
#include "domain/do/parent/ParentInfoDO.h"
#include "domain/dto/parent/ParentInfoDTO.h"
#include "dao/parent/ParentInfoDAO.h"

ParentInfoDTO::Wrapper ParentInfoService::getParentInfo(const ParentInfoDTO::Wrapper& dto)
{
	// 执行数据获取  从dao层获取数据库信息，再用DTO返回给controller层
	//ParentInfoDAO dao;
	//auto res = dao.selectParentInfoById(dto->id);
	//// 没有查询到数据
	//if (!res)
	//	return nullptr;

	//// 
	//ParentInfoDTO pidto;
	//ZO_STAR_DOMAIN_DO_TO_DTO(pidto, res, name, Name, mobile, Mobile, datetime, Datetime);
	//return pidto;
	return nullptr;
}
