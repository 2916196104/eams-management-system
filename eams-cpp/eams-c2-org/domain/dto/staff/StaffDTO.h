#pragma once

#ifndef _STAFFDTO_H_
#define _STAFFDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	员工数据传输对象
 */
class StaffDTO : public oatpp::DTO {
	DTO_INIT(StaffDTO, DTO);




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

#include OATPP_CODEGEN_END(DTO)
#endif // _STAFFDTO_H_
