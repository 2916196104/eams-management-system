#include "stdafx.h"
#include "RegisterService.h"
#include "dao/register/RegisterDAO.h"
#include "Macros.h"

RegisterDTO::Wrapper RegisterService::getById(std::string id)
{
	RegisterDAO dao;
	auto registerDO = dao.selectById(id);
	if (!registerDO) return nullptr;

	auto dto = RegisterDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, registerDO,
		id, Id, name, Name, telephoneNumber, TelephoneNumber, password, Password);
	return dto;
}