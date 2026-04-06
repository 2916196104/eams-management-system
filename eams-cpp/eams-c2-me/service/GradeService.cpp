#include "stdafx.h"
#include "GradeService.h"
#include "id/UuidFacade.h"
#include "dao/GradeDAO.h"
#include "domain/do/GradeDO.h"
#include "domain/dto/student/GradeDTO.h"
#include "domain/dto/student/GradeListDTO.h"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
// 放到最后导入防止编译冲突
#include "NacosClient.h"

GradeListDTO::Wrapper GradeService::listAllGrade()
{

	auto res = GradeListDTO::createShared();
	res->list = oatpp::List<oatpp::Object<GradeDTO>>::createShared();
	// 获取数据总条数
	GradeDAO ud;

	auto list = ud.selectWithPage();
	for (auto& one : list)
	{
		auto grade = GradeDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(grade, one, name,Name);

		res->list->push_back(grade);
	}
	return res;
}