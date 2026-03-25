#pragma once

#ifndef _STAFFDTO_H_
#define _STAFFDTO_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 员工核心DTO（基类，包含所有基础通用字段）
 * 对齐数据库staff表核心字段，无无效字段
 */
class StaffDTO : public oatpp::DTO {
    DTO_INIT(StaffDTO, DTO);

    // 1. 主键&基础标识字段
    API_DTO_FIELD_DEFAULT(String, id, "field.id");                // 对应数据库：id (bigint)
    API_DTO_FIELD_DEFAULT(String, orgId, "field.orgId");         // 对应数据库：org_id (bigint)
    API_DTO_FIELD_DEFAULT(Int32, deleted, "field.deleted"); // 对应数据库：deleted (tinyint)
    API_DTO_FIELD_DEFAULT(Int32, isInner, "field.isInner"); // 对应数据库：is_inner (tinyint)

    // 2. 核心业务字段（必展示）
    API_DTO_FIELD_DEFAULT(String, name, "field.name");                // 对应数据库：name (varchar)
    API_DTO_FIELD_DEFAULT(String, mobile, "field.mobile");            // 对应数据库：mobile (varchar)
    API_DTO_FIELD_DEFAULT(String, idCard, "field.idCard");          // 对应数据库：id_card (varchar)
    API_DTO_FIELD_DEFAULT(String, headImg, "field.headImg");          // 对应数据库：head_img (varchar)
    API_DTO_FIELD_DEFAULT(Int32, state, "field.state"); // 对应数据库：state (tinyint)

    // 3. 基础信息字段（可选展示）
    API_DTO_FIELD_DEFAULT(String, wxAccessId, "field.wxAccessId");    // 对应数据库：wx_access_id (bigint)
    API_DTO_FIELD_DEFAULT(String, email, "field.email");              // 对应数据库：email (varchar)
    API_DTO_FIELD_DEFAULT(String, birthday, "field.birthday");            // 对应数据库：birthday (date)
    API_DTO_FIELD_DEFAULT(Int32, gender, "field.gender"); // 对应数据库：gender (tinyint)
    API_DTO_FIELD_DEFAULT(String, school, "field.school");          // 对应数据库：school (varchar)
    API_DTO_FIELD_DEFAULT(Int32, degree, "field.degree"); // 对应数据库：degree (tinyint)
    API_DTO_FIELD_DEFAULT(String, remark, "field.remark");              // 对应数据库：remark (varchar)
    API_DTO_FIELD_DEFAULT(Int32, isManager, "field.isManager"); // 对应数据库：is_manager (tinyint)
    API_DTO_FIELD_DEFAULT(String, hireDate, "field.hireDate");        // 对应数据库：hire_date (date)
    API_DTO_FIELD_DEFAULT(String, fireDate, "field.fireDate");        // 对应数据库：fire_date (date)
    API_DTO_FIELD_DEFAULT(String, intro, "field.intro");           // 对应数据库：intro (varchar)

    // 4. 薪资相关字段
    API_DTO_FIELD_DEFAULT(Float64, classFee, "field.classFee");         // 对应数据库：class_fee (decimal)
    API_DTO_FIELD_DEFAULT(Float64, assistantFee, "field.assistantFee");     // 对应数据库：assistant_fee (decimal)

    // 5. 系统审计字段（后台用，前端可选展示）
    API_DTO_FIELD_DEFAULT(String, addTime, "field.addTime");         // 对应数据库：add_time (datetime)
    API_DTO_FIELD_DEFAULT(String, editTime, "field.editTime");        // 对应数据库：edit_time (datetime)
    API_DTO_FIELD_DEFAULT(String, creator, "field.creator");         // 对应数据库：creator (bigint)
    API_DTO_FIELD_DEFAULT(String, editor, "field.editor");          // 对应数据库：editor (bigint)
};

/**
 * 员工基础DTO（列表展示用）
 * 仅保留列表页需要的核心字段，减少数据传输
 */
class StaffBaseDTO : public StaffDTO
{
    DTO_INIT(StaffBaseDTO, StaffDTO);

    // 继承StaffDTO，但前端展示时仅返回以下核心字段（通过接口控制，代码无需修改）
    // id / name / mobile / headImg / state / isInner / orgId
};

/**
 * 员工详情DTO（详情页/编辑页用）
 * 包含所有字段，满足详情展示和编辑需求
 */
class StaffDetailDTO : public StaffBaseDTO
{
    DTO_INIT(StaffDetailDTO, StaffBaseDTO);

    // 继承所有字段，额外补充敏感字段（按需开放）
    API_DTO_FIELD_DEFAULT(String, password, "field.password"); // 对应数据库：password (varchar)

};


/**
 * 保存员工参数对象
 */
class StaffSaveDTO : public StaffDTO
{
	DTO_INIT(StaffSaveDTO, StaffDTO);

	//// 添加成员变量:id
	//DTO_FIELD(UInt64, id);
	//DTO_FIELD_INFO(id) {
	//	info->description = ZH_WORDS_GETTER("saveEmp.dto.id");
	//}
	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("saveEmp.dto.id"), false);         // 可选，新增不用传


	// 姓名
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("saveEmp.dto.name"), true);
	// 电话/登录账号
	API_DTO_FIELD_REQUIRE(String, mobile, ZH_WORDS_GETTER("saveEmp.dto.mobile"), true);
	// 所属机构
	API_DTO_FIELD_REQUIRE(Int64, orgId, ZH_WORDS_GETTER("saveEmp.dto.orgId"), true);
	// 所属职位
	API_DTO_FIELD_REQUIRE(Int64, positionId, ZH_WORDS_GETTER("saveEmp.dto.positionId"), true);
	// 性别
	API_DTO_FIELD_REQUIRE(Int32, gender, ZH_WORDS_GETTER("saveEmp.dto.gender"), false);
	// 学历
	API_DTO_FIELD_REQUIRE(Int32, degree, ZH_WORDS_GETTER("saveEmp.dto.degree"), false);
	// 生日
	API_DTO_FIELD_REQUIRE(String, birthday, ZH_WORDS_GETTER("saveEmp.dto.birthday"), false);
	// 毕业学校
	API_DTO_FIELD_REQUIRE(String, school, ZH_WORDS_GETTER("saveEmp.dto.school"), false);
	// 入职日期
	API_DTO_FIELD_REQUIRE(String, hireDate, ZH_WORDS_GETTER("saveEmp.dto.hireDate"), false);
	// 上课费
	API_DTO_FIELD_REQUIRE(Float64, classFee, ZH_WORDS_GETTER("saveEmp.dto.classFee"), false);
	// 助教费
	API_DTO_FIELD_REQUIRE(Float64, assistantFee, ZH_WORDS_GETTER("saveEmp.dto.assistantFee"), false);
	// 简介
	API_DTO_FIELD_REQUIRE(String, intro, ZH_WORDS_GETTER("saveEmp.dto.intro"), false);
	// 是否是内部人员
	API_DTO_FIELD_REQUIRE(Boolean, isInner, ZH_WORDS_GETTER("saveEmp.dto.isInner"), false);
	// 是否是管理者
	API_DTO_FIELD_REQUIRE(Boolean, isManager, ZH_WORDS_GETTER("saveEmp.dto.isManager"), false);

public:

};






/**
 * 员工列表分页传输对象
 */
class StaffPageDTO : public PageDTO<StaffDTO::Wrapper>
{
	DTO_INIT(StaffPageDTO, PageDTO<StaffDTO::Wrapper>);


};


/**
 * 员工列表查询参数对象
 */
class StaffPageQuery : public oatpp::DTO {
	DTO_INIT(StaffPageQuery, DTO);


	
	//API_DTO_FIELD_REQUIRE(UInt64, pageIndex, ZH_WORDS_GETTER("getEmpList.dto.pageIndex"), true);
	API_DTO_FIELD(UInt64, pageIndex, ZH_WORDS_GETTER("getEmpList.dto.pageIndex"), true, 1);

	
	//API_DTO_FIELD_REQUIRE(UInt64, pageSize, ZH_WORDS_GETTER("getEmpList.dto.pageSize"), true);
	API_DTO_FIELD(UInt64, pageSize, ZH_WORDS_GETTER("getEmpList.dto.pageSize"), true, 10);


	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("getEmpList.dto.name"), false);

	
	API_DTO_FIELD_REQUIRE(String, phone, ZH_WORDS_GETTER("getEmpList.dto.phone"), false);
	
	
	API_DTO_FIELD_REQUIRE(Int32, status, ZH_WORDS_GETTER("getEmpList.dto.status"), false);
};




//头像上传表单DTO
class AvatarUploadDTO : public oatpp::DTO {
    DTO_INIT(AvatarUploadDTO, DTO);

    // 员工ID
    DTO_FIELD(UInt64, employeeId, "employeeId");
    DTO_FIELD_INFO(employeeId) {
        info->description = ZH_WORDS_GETTER("modifyAvatar.param1");
        info->required = true;
    }

    // 头像文件
    DTO_FIELD(oatpp::String, avatarFile, "avatarFile");
    DTO_FIELD_INFO(avatarFile) {
        info->description = ZH_WORDS_GETTER("modifyAvatar.param2");
        info->required = true;
    }
};
class   StaffChangePasswordDTO :public oatpp::DTO {
	DTO_INIT(StaffChangePasswordDTO, DTO);
	API_DTO_FIELD_REQUIRE(Int64, id, ZH_WORDS_GETTER("staff.field.id"),true);
	API_DTO_FIELD_REQUIRE(String, password, ZH_WORDS_GETTER("staff.field.new-password"),true);

};

class StaffExportQueryDto :public oatpp::DTO {
	DTO_INIT(StaffExportQueryDto, DTO);
	DTO_FIELD(Boolean, exportFlag, "export");
	DTO_FIELD_INFO(exportFlag) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("staff.export-list.export");
	}
	//API_DTO_FIELD_REQUIRE(Boolean, exportFlag, ZH_WORDS_GETTER("staff.export-list.export"), true);
	API_DTO_FIELD_DEFAULT(String, keyword, ZH_WORDS_GETTER("staff.export-list.keyword"));
	API_DTO_FIELD_DEFAULT(String, state, ZH_WORDS_GETTER("staff.field.state"));
	
};

// 带班记录查询 DTO
class DutyRecordQueryDTO : public PageQuery {
    DTO_INIT(DutyRecordQueryDTO, PageQuery);

    // 员工ID
    DTO_FIELD(UInt64, employeeId, "employeeId");
    DTO_FIELD_INFO(employeeId) {
        info->description = ZH_WORDS_GETTER("getDutyRecord.param1");
        info->required = false;
    }

    // 带班日期
    DTO_FIELD(oatpp::String, dutyDate, "dutyDate");
    DTO_FIELD_INFO(dutyDate) {
        info->description = ZH_WORDS_GETTER("getDutyRecord.param2");
        info->required = false;
    }
};
#include OATPP_CODEGEN_END(DTO)

#endif // STAFF_DTO_H