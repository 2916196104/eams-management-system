#pragma once
// UserQuery.h
#include "domain/query/PageQuery.h"
#include "../GlobalInclude.h"

class UserQuery : public PageQuery {
    DTO_INIT(UserQuery, PageQuery);
    API_DTO_FIELD_DEFAULT(String, username, "用户名");
    API_DTO_FIELD_DEFAULT(String, nickname, "昵称");
    API_DTO_FIELD_DEFAULT(String, sex, "性别");
    API_DTO_FIELD_DEFAULT(Int32, minAge, "最小年龄");
    API_DTO_FIELD_DEFAULT(Int32, maxAge, "最大年龄");
    API_DTO_FIELD_DEFAULT(Int32, status, "状态");
};