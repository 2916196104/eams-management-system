#include "stdafx.h"
#include "ClassStudentService.h"
#include "../../../dao/home/class/ClassStudentDAO.h"

oatpp::List<ClassStudentDTO::Wrapper> ClassStudentService::listAll(const ClassStudentQuery::Wrapper& query)
{
    auto dtoList = oatpp::List<ClassStudentDTO::Wrapper>::createShared();
    ClassStudentDAO dao;
    auto result = dao.selectAll(query);

    for (auto& sub : result)
    {
        auto dto = ClassStudentDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, name, Name);
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, gender, Gender);
        dtoList->push_back(dto);
    }

    return dtoList;
}