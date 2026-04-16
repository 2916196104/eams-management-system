#pragma once



#ifndef _REDEEMCREDIT_DO_
#define _REDEEMCREDIT_DO_
#include "../../../DoInclude.h"

class RedeemCreditDO : public BaseDO
{
    // 主键
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 积分商城礼品id
    MYSQL_SYNTHESIZE(uint64_t, creditMallId, CreditMallId);
    // 学校id
    MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId);
    // 创建人
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    // 编辑人
    MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
    // 添加时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 编辑时间
    MYSQL_SYNTHESIZE(string, editTime, EditTime);
    // 删除标记
    MYSQL_SYNTHESIZE(int, deleted, Deleted);
    // 学生id
    MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
    // 学生账号id
    MYSQL_SYNTHESIZE(uint64_t, userId, UserId);
    // 兑换数量
    MYSQL_SYNTHESIZE(int, num, Num);
    // 花费积分 
    MYSQL_SYNTHESIZE(string, credit, Credit);
    // 审核状态
    MYSQL_SYNTHESIZE(int, verifyState, VerifyState);
    // 审核人
    MYSQL_SYNTHESIZE(uint64_t, verifyStaff, VerifyStaff);
    // 审核时间
    MYSQL_SYNTHESIZE(string, verifyTime, VerifyTime);
    // 审核备注
    MYSQL_SYNTHESIZE(string, verifyRemark, VerifyRemark);
public:
    RedeemCreditDO() : BaseDO("credit_exchange")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);

        MYSQL_ADD_FIELD("credit_mall_id", "ull", creditMallId);
        MYSQL_ADD_FIELD("school_id", "ull", schoolId);
        MYSQL_ADD_FIELD("creator", "ull", creator);
        MYSQL_ADD_FIELD("editor", "l", editor);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("edit_time", "s", editTime);
        MYSQL_ADD_FIELD("deleted", "i", deleted);
        MYSQL_ADD_FIELD("student_id", "ull", studentId);
        MYSQL_ADD_FIELD("user_id", "ull", userId);
        MYSQL_ADD_FIELD("num", "i", num);
        MYSQL_ADD_FIELD("credit", "s", credit);
        MYSQL_ADD_FIELD("verify_state", "i", verifyState);
        MYSQL_ADD_FIELD("verify_staff", "l", verifyStaff);
        MYSQL_ADD_FIELD("verify_time", "s", verifyTime);
        MYSQL_ADD_FIELD("verify_remark", "s", verifyRemark);
    }
};

typedef std::shared_ptr<RedeemCreditDO> PtrRedeemCreditDO;


class StudentCreditDO: public BaseDO
{
    MYSQL_SYNTHESIZE(int, credit, Credit);
public:
    StudentCreditDO() :BaseDO("student")
    {
        MYSQL_ADD_FIELD("credit", "i", credit);
    }
    
};
typedef std::shared_ptr<StudentCreditDO> PtrStudentCreditDO;


class CreditMallDO : public BaseDO
{
    MYSQL_SYNTHESIZE(uint64_t, mairtal_id, MaritalId);
    MYSQL_SYNTHESIZE(int, credit, Credit);
    MYSQL_SYNTHESIZE(bool, state, State);
    MYSQL_SYNTHESIZE(string, name, Name);
public:
    CreditMallDO() :BaseDO("credit_mall")
    {

    }
};
typedef std::shared_ptr<CreditMallDO> PtrCreditMallDO;



class StudentCreditLogDO : public BaseDO
{
    // 主键
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 学生id
    MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
    // 学生账号id
    MYSQL_SYNTHESIZE(uint64_t, userId, UserId);
    // 变动数量
    MYSQL_SYNTHESIZE(int, credit, Credit);
    // 剩余积分数量
    MYSQL_SYNTHESIZE(int, currentCredit, CurrentCredit);
    // 变动类型
    MYSQL_SYNTHESIZE(int, changeType, ChangeType);
    // 变动时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 其他说明
    MYSQL_SYNTHESIZE(string, remark, Remark);
    // 记录来源id
    MYSQL_SYNTHESIZE(uint64_t, sourceId, SourceId);
    // 调整人
    MYSQL_SYNTHESIZE(uint64_t, staffId, StaffId);
    // 学生所属学校ID
    MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId);

public:
   
    StudentCreditLogDO() : BaseDO("student_credit_log")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);

        MYSQL_ADD_FIELD("student_id", "ull", studentId);
        MYSQL_ADD_FIELD("user_id", "ull", userId);
        MYSQL_ADD_FIELD("credit", "i", credit);
        MYSQL_ADD_FIELD("current_credit", "i", currentCredit);
        MYSQL_ADD_FIELD("change_type", "i", changeType);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("source_id", "ull", sourceId);
        MYSQL_ADD_FIELD("staff_id", "ull", staffId);
        MYSQL_ADD_FIELD("school_id", "ull", schoolId);
    }
};

// 给智能指针设定一个别名方便使用
typedef std::shared_ptr<StudentCreditLogDO> PtrStudentCreditLogDO;

class MaterialDO : public BaseDO
{
    MYSQL_SYNTHESIZE(uint64_t, school_id, SchoolId);
public:
     MaterialDO() :BaseDO("material")
    {

    }
};
typedef std::shared_ptr<MaterialDO> PtrMaterialDO;


class MaterialLogDO : public BaseDO
{
    // 主键
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 物料ID
    MYSQL_SYNTHESIZE(uint64_t, materialId, MaterialId);
    // 变动数量
    MYSQL_SYNTHESIZE(int, amount, Amount);
    // 变动原因说明
    MYSQL_SYNTHESIZE(string, reason, Reason);
    // 变动类型: 1入库 2出库 3积分商城出库
    MYSQL_SYNTHESIZE(int, changeType, ChangeType);
    // 变动对象id: 如积分商城里的商品id
    MYSQL_SYNTHESIZE(uint64_t, changeTargetId, ChangeTargetId);
    // 备注信息
    MYSQL_SYNTHESIZE(string, remark, Remark);
    // 创建人
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    // 编辑人
    MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
    // 变动时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 编辑时间
    MYSQL_SYNTHESIZE(string, editTime, EditTime);
    // 删除标记
    MYSQL_SYNTHESIZE(int, deleted, Deleted);
    // 涉及学生id
    MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
    // 涉及员工id
    MYSQL_SYNTHESIZE(uint64_t, staffId, StaffId);
    // 所属物料的组织ID
    MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);
    // 学校id
    MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId);

public:
    // 
    MaterialLogDO() : BaseDO("material_record")
    {
        MYSQL_ADD_FIELD_PK("id", "ull", id);

        MYSQL_ADD_FIELD("material_id", "ull", materialId);
        MYSQL_ADD_FIELD("amount", "i", amount);
        MYSQL_ADD_FIELD("reason", "s", reason);
        MYSQL_ADD_FIELD("change_type", "i", changeType);
        MYSQL_ADD_FIELD("change_target_id", "ull", changeTargetId);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("creator", "ull", creator);
        MYSQL_ADD_FIELD("editor", "ull", editor);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("edit_time", "s", editTime);
        MYSQL_ADD_FIELD("deleted", "i", deleted);
        MYSQL_ADD_FIELD("student_id", "ull", studentId);
        MYSQL_ADD_FIELD("staff_id", "ull", staffId);
        MYSQL_ADD_FIELD("org_id", "ull", orgId);
        MYSQL_ADD_FIELD("school_id", "ull", schoolId);
    }
};

// 给智能指针设定一个别名方便使用
typedef std::shared_ptr<MaterialLogDO> PtrMaterialLogDO;

#endif
