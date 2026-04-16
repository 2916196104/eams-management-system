#pragma once

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)


//查询DTO
class StprofileDetailsDTO :public oatpp::DTO
{
	DTO_INIT(StprofileDetailsDTO, DTO);

	// 学生姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.name");
	}
	// 手机号
	DTO_FIELD(String, mobile);
	DTO_FIELD_INFO(mobile) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.mobile");
	}
	// 剩余课时
	DTO_FIELD(Int32, closeTime);
	DTO_FIELD_INFO(closeTime) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.closeTime");
	}
	// 积分
	DTO_FIELD(Int32, credit);
	DTO_FIELD_INFO(credit) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.credit");
	}
	// 体验卡
	DTO_FIELD(Int32, lessonCount);
	DTO_FIELD_INFO(lessonCount) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.lessonCount");
	}
	// 学习阶段
	DTO_FIELD(Int32, stage);
	DTO_FIELD_INFO(stage) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.stage");
	}
	// 家长姓名
	DTO_FIELD(String, familyName);
	DTO_FIELD_INFO(familyName) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.familyName");
	}
	// 亲属关系
	DTO_FIELD(Int32, familyRel);
	DTO_FIELD_INFO(familyRel) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.familyRel");
	}
	// 年级
	DTO_FIELD(String, className);
	DTO_FIELD_INFO(className) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.className");
	}
	// 性别
	DTO_FIELD(Int32, gender);
	DTO_FIELD_INFO(gender) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.gender");
	}
	// 生日
	DTO_FIELD(String, birthday);
	DTO_FIELD_INFO(birthday) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.birthday");
	}
	// 身份证号码
	DTO_FIELD(String, idcard);
	DTO_FIELD_INFO(idcard) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.idcard");
	}
	//入学年份
	DTO_FIELD(Int32, grade);
	DTO_FIELD_INFO(grade) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.grade");
	}
	// 入学日期
	DTO_FIELD(String, joinDate);
	DTO_FIELD_INFO(joinDate) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.joinDate");
	}
	// 加入时间
	DTO_FIELD(String, addTime);
	DTO_FIELD_INFO(addTime) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.addTime");
	}
};

//分页DTO
class StprofileDetailsPageDTO :public PageDTO<StprofileDetailsDTO::Wrapper>
{
	DTO_INIT(StprofileDetailsPageDTO, PageDTO<StprofileDetailsDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO) 