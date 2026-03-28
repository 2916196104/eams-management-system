#pragma once
#ifndef _REGISTERVTO_H_
#define _REGISTERVTO_H_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class RegisterDTO : public oatpp::DTO
{
	DTO_INIT(RegisterDTO, DTO);
	API_DTO_FIELD_DEFAULT(Int32, reportType, ZH_WORDS_GETTER("register.field.reportType"));  // 报名类型
	API_DTO_FIELD_DEFAULT(String, stuName, ZH_WORDS_GETTER("register.field.stuName"));        // 学生姓名
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("register.field.courseName"));  // 课程名称
	API_DTO_FIELD_DEFAULT(String, subjectName, ZH_WORDS_GETTER("register.field.subjectName"));// 所属科目名称
	API_DTO_FIELD_DEFAULT(Int32, subjectId, ZH_WORDS_GETTER("register.field.subjectId"));    // 所属科目 ID
	API_DTO_FIELD_DEFAULT(String, startDate, ZH_WORDS_GETTER("register.field.startDate"));   // 课程开始时间
	API_DTO_FIELD_DEFAULT(String, expireDate, ZH_WORDS_GETTER("register.field.expireDate")); // 课程过期时间
	API_DTO_FIELD_DEFAULT(Int32, courseNum, ZH_WORDS_GETTER("register.field.courseNum"));    // 课程总课时数
	API_DTO_FIELD_DEFAULT(Float64, coursePrice, ZH_WORDS_GETTER("register.field.coursePrice"));    // 课程原价
	API_DTO_FIELD_DEFAULT(Float64, discountPrice, ZH_WORDS_GETTER("register.field.discountPrice"));// 优惠金额
	API_DTO_FIELD_DEFAULT(Float64, actualPayment, ZH_WORDS_GETTER("register.field.actualPayment"));// 实际支付金额
	API_DTO_FIELD_DEFAULT(String, tip, ZH_WORDS_GETTER("register.field.tip"));                // 备注信息

	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

class RegisterAddDTO : public RegisterDTO
{
	DTO_INIT(RegisterAddDTO, RegisterDTO);
};

#include OATPP_CODEGEN_END(DTO)
#endif