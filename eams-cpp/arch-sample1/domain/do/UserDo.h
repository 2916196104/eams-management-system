#pragma once

#include"Dolnclude.h"
class UserDO : public BaseDO {
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, username, Username);
    MYSQL_SYNTHESIZE(string, password, Password);
    MYSQL_SYNTHESIZE(string, nickname, Nickname);
    MYSQL_SYNTHESIZE(string, avatar, Avatar);
    MYSQL_SYNTHESIZE(string, email, Email);
    MYSQL_SYNTHESIZE(string, phone, Phone);
    MYSQL_SYNTHESIZE(string, sex, Sex);
    MYSQL_SYNTHESIZE(int, age, Age);
    MYSQL_SYNTHESIZE(int, status, Status);
    MYSQL_SYNTHESIZE(string, createBy, CreateBy);
    MYSQL_SYNTHESIZE(string, createTime, CreateTime);
    MYSQL_SYNTHESIZE(string, updateBy, UpdateBy);
    MYSQL_SYNTHESIZE(string, updateTime, UpdateTime);

public:
    UserDO() : BaseDO("sys_user") {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("username", "s", username);
        MYSQL_ADD_FIELD("password", "s", password);
        MYSQL_ADD_FIELD("nickname", "s", nickname);
        MYSQL_ADD_FIELD("avatar", "s", avatar);
        MYSQL_ADD_FIELD("email", "s", email);
        MYSQL_ADD_FIELD("phone", "s", phone);
        MYSQL_ADD_FIELD("sex", "s", sex);
        MYSQL_ADD_FIELD("age", "i", age);
        MYSQL_ADD_FIELD("status", "i", status);
        MYSQL_ADD_FIELD("create_by", "s", createBy);
        MYSQL_ADD_FIELD("create_time", "s", createTime);
        MYSQL_ADD_FIELD("update_by", "s", updateBy);
        MYSQL_ADD_FIELD("update_time", "s", updateTime);
    }
};









