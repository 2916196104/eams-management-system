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
	DTO_FIELD(String, telephone);
	DTO_FIELD_INFO(telephone) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.telephone");
	}
	// 剩余课时
	DTO_FIELD(Int32, lesson_count);
	DTO_FIELD_INFO(lesson_count) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.lesson_count");
	}
	// 积分
	DTO_FIELD(Int32, credit);
	DTO_FIELD_INFO(credit) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.credit");
	}
	// 体验卡
	DTO_FIELD(Int32, remaining_quantity);
	DTO_FIELD_INFO(remaining_quantity) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.remaining_quantity");
	}
	// 学习阶段
	DTO_FIELD(Int32, stage);
	DTO_FIELD_INFO(stage) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.stage");
	}
	// 家长姓名
	DTO_FIELD(String, family_name);
	DTO_FIELD_INFO(family_name) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.family_name");
	}
	// 亲属关系
	DTO_FIELD(Int32, family_rel);
	DTO_FIELD_INFO(family_rel) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.family_rel");
	}
	// 年级
	DTO_FIELD(String, grade_names);
	DTO_FIELD_INFO(grade_names) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.grade_names");
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
	// 入学时间
	DTO_FIELD(String, join_date);
	DTO_FIELD_INFO(join_date) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.join_date");
	}
	// 加入时间
	DTO_FIELD(String, add_time);
	DTO_FIELD_INFO(add_time) {
		info->description = ZH_WORDS_GETTER("stprofiledetails.dto.add_time");
	}
};

//分页DTO
class StprofileDetailPageDTO :public PageDTO<StprofileDetailsDTO::Wrapper>
{
	DTO_INIT(StprofileDetailPageDTO, PageDTO<StprofileDetailsDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO) 