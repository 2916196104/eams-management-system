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
    API_DTO_FIELD_DEFAULT(UInt64, id, "field.id");                // bigint → 不动
    API_DTO_FIELD_DEFAULT(UInt64, orgId, "field.orgId");         // bigint → 不动
    API_DTO_FIELD_DEFAULT(Int32, deleted, "field.deleted");       // tinyint Int32 → Int8
    API_DTO_FIELD_DEFAULT(Int32, isInner, "field.isInner");       // tinyint Int32 → Int8

    // 2. 核心业务字段（必展示）
    API_DTO_FIELD_DEFAULT(String, name, "field.name");
    API_DTO_FIELD_DEFAULT(String, mobile, "field.mobile");
    API_DTO_FIELD_DEFAULT(String, idCard, "field.idCard");
    API_DTO_FIELD_DEFAULT(String, headImg, "field.headImg");
    API_DTO_FIELD_DEFAULT(Int32, state, "field.state");           // tinyint Int32 → Int8

    // 3. 基础信息字段（可选展示）
    API_DTO_FIELD_DEFAULT(UInt64, wxAccessId, "field.wxAccessId");// bigint → 不动
    API_DTO_FIELD_DEFAULT(String, email, "field.email");
    API_DTO_FIELD_DEFAULT(String, birthday, "field.birthday");
    API_DTO_FIELD_DEFAULT(Int32, gender, "field.gender");         // tinyint Int32 → Int8
    API_DTO_FIELD_DEFAULT(String, school, "field.school");
    API_DTO_FIELD_DEFAULT(Int32, degree, "field.degree");         // tinyint Int32 → Int8
    API_DTO_FIELD_DEFAULT(String, remark, "field.remark");
    API_DTO_FIELD_DEFAULT(Int32, isManager, "field.isManager");   // tinyint Int32 → Int8
    API_DTO_FIELD_DEFAULT(String, hireDate, "field.hireDate");
    API_DTO_FIELD_DEFAULT(String, fireDate, "field.fireDate");
    API_DTO_FIELD_DEFAULT(String, intro, "field.intro");

    // 4. 薪资相关字段
    API_DTO_FIELD_DEFAULT(Float64, classFee, "field.classFee");
    API_DTO_FIELD_DEFAULT(Float64, assistantFee, "field.assistantFee");

    // 5. 系统审计字段（后台用，前端可选展示）
    API_DTO_FIELD_DEFAULT(String, addTime, "field.addTime");
    API_DTO_FIELD_DEFAULT(String, editTime, "field.editTime");
    API_DTO_FIELD_DEFAULT(UInt64, creator, "field.creator");     // bigint → 不动
    API_DTO_FIELD_DEFAULT(UInt64, editor, "field.editor");       // bigint → 不动
};

/**
 * 员工基础DTO（列表展示用）
 */
class StaffBaseDTO : public StaffDTO
{
    DTO_INIT(StaffBaseDTO, StaffDTO);
};

/**
 * 员工详情DTO（详情页/编辑页用）
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