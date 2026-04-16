#pragma once
#ifndef _INSTITUTION_DTO_
#define _INSTITUTION_DTO_

#include "../../GlobalInclude.h"
#include "../../lib-oatpp/include/ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class InstitutionDTO : public oatpp::DTO {
    DTO_INIT(InstitutionDTO, DTO);

    API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("institution.field.id"));
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("institution.field.name"));
    API_DTO_FIELD_DEFAULT(UInt64, parentId, ZH_WORDS_GETTER("institution.field.parentId"));
    API_DTO_FIELD_DEFAULT(List<Object<InstitutionDTO>>, children, ZH_WORDS_GETTER("institution.field.children"));
    API_DTO_FIELD_DEFAULT(Int32, level, ZH_WORDS_GETTER("institution.field.level"));       // 级别
    API_DTO_FIELD_DEFAULT(String, shortname, ZH_WORDS_GETTER("institution.field.shortname")); // 简称
    API_DTO_FIELD_DEFAULT(String, contactName, ZH_WORDS_GETTER("institution.field.contactName"));     // 联系人
    API_DTO_FIELD_DEFAULT(String, phone, ZH_WORDS_GETTER("institution.field.phone"));         // 电话
    API_DTO_FIELD_DEFAULT(String, fax, ZH_WORDS_GETTER("institution.field.fax"));             // 传真
    API_DTO_FIELD_DEFAULT(String, email, ZH_WORDS_GETTER("institution.field.email"));         // 邮箱
    API_DTO_FIELD_DEFAULT(Int32, sortNum, ZH_WORDS_GETTER("institution.field.sortNum"));             // 排序
    API_DTO_FIELD_DEFAULT(Int32, state, ZH_WORDS_GETTER("institution.field.state"));       // 状态
    API_DTO_FIELD_DEFAULT(String, info, ZH_WORDS_GETTER("institution.field.info")); // 说明
};

#include OATPP_CODEGEN_END(DTO)
#endif // _INSTITUTION_DTO_