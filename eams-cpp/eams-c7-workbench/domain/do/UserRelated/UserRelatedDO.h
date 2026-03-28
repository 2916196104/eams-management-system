#pragma once

#ifndef _USERRELATEDDO_H_
#define _USERRELATEDDO_H_
#include "../DoInclude.h"

/*
* 用户相关的DO，主要对应表staff，教师表，主要用途，获取当前用户信息，获取用户资料以及获取头像地址
*/

class UserRelatedDO : public BaseDO
{
    // 主键ID
    MYSQL_SYNTHESIZE(long long, id, Id);

    // 姓名
    MYSQL_SYNTHESIZE(string, name, Name);

    // 手机号
    MYSQL_SYNTHESIZE(string, mobile, Mobile);

    // 微信登录id
    MYSQL_SYNTHESIZE(long long, wxAccessId, WxAccessId);

    // 邮箱
    MYSQL_SYNTHESIZE(string, email, Email);

    // 生日
    MYSQL_SYNTHESIZE(string, birthday, Birthday);

    // 性别
    MYSQL_SYNTHESIZE(int, gender, Gender);

    // 身份证
    MYSQL_SYNTHESIZE(string, idCard, IdCard);

    // 毕业学校
    MYSQL_SYNTHESIZE(string, school, School);

    // 学历
    MYSQL_SYNTHESIZE(int, degree, Degree);

    // 备注
    MYSQL_SYNTHESIZE(string, remark, Remark);

    // 在职状态
    MYSQL_SYNTHESIZE(int, state, State);

    // 是否管理者
    MYSQL_SYNTHESIZE(int, isManager, IsManager);

    // 头像
    MYSQL_SYNTHESIZE(string, headImg, HeadImg);

    // 入职日期
    MYSQL_SYNTHESIZE(string, hireDate, HireDate);

    // 离职日期
    MYSQL_SYNTHESIZE(string, fireDate, FireDate);

    // 介绍
    MYSQL_SYNTHESIZE(string, intro, Intro);

    // 创建时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);

    // 编辑时间
    MYSQL_SYNTHESIZE(string, editTime, EditTime);

    // 创建人
    MYSQL_SYNTHESIZE(long long, creator, Creator);

    // 编辑人
    MYSQL_SYNTHESIZE(long long, editor, Editor);

    // 是否删除
    MYSQL_SYNTHESIZE(int, deleted, Deleted);

    // 密码，接口返回时不可以返回到前端
    MYSQL_SYNTHESIZE(string, password, Password);

    // 课时费
    MYSQL_SYNTHESIZE(double, classFee, ClassFee);

    // 助教费
    MYSQL_SYNTHESIZE(double, assistantFee, AssistantFee);

    // 组织ID
    MYSQL_SYNTHESIZE(long long, orgId, OrgId);

    // 是否内部人员
    MYSQL_SYNTHESIZE(int, isInner, IsInner);

public:
	//绑定表名staff，构造函数中添加字段域
    UserRelatedDO() : BaseDO("staff")
    {
        MYSQL_ADD_FIELD_PK("id", "i", id);

        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("mobile", "s", mobile);
        MYSQL_ADD_FIELD("wx_access_id", "i", wxAccessId);
        MYSQL_ADD_FIELD("email", "s", email);
        MYSQL_ADD_FIELD("birthday", "s", birthday);
        MYSQL_ADD_FIELD("gender", "i", gender);
        MYSQL_ADD_FIELD("id_card", "s", idCard);
        MYSQL_ADD_FIELD("school", "s", school);
        MYSQL_ADD_FIELD("degree", "i", degree);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("state", "i", state);
        MYSQL_ADD_FIELD("is_manager", "i", isManager);
        MYSQL_ADD_FIELD("head_img", "s", headImg);
        MYSQL_ADD_FIELD("hire_date", "s", hireDate);
        MYSQL_ADD_FIELD("fire_date", "s", fireDate);
        MYSQL_ADD_FIELD("intro", "s", intro);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("edit_time", "s", editTime);
        MYSQL_ADD_FIELD("creator", "i", creator);
        MYSQL_ADD_FIELD("editor", "i", editor);
        MYSQL_ADD_FIELD("deleted", "i", deleted);
        MYSQL_ADD_FIELD("password", "s", password);
        MYSQL_ADD_FIELD("class_fee", "d", classFee);
        MYSQL_ADD_FIELD("assistant_fee", "d", assistantFee);
        MYSQL_ADD_FIELD("org_id", "i", orgId);
        MYSQL_ADD_FIELD("is_inner", "i", isInner);
    }


};

//给UserReleatedDO定义一个智能指针类型，方便使用
typedef std::shared_ptr<UserRelatedDO> PtrUserRelatedDO;


#endif // !_USERRELEATEDDO_H_
