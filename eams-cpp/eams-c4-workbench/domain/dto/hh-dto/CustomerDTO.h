#pragma once

#ifndef _CUSTOMER_DTO_
#define _CUSTOMER_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CustomerDTO : public oatpp::DTO {
	DTO_INIT(CustomerDTO, DTO);
	// 唯一ID
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("customer.field.id"));
	// 姓名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("customer.field.name"));
	// 手机号码
	API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("customer.field.phone"));
};

class CustomerDetailDTO : public oatpp::DTO {
	DTO_INIT(CustomerDetailDTO, DTO);
	// 唯一ID
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("customer.field.id"));
	// 姓名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("customer.field.name"));
	// 手机号码
	API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("customer.field.phone"));
	// 性别
	API_DTO_FIELD_DEFAULT(String, gender, ZH_WORDS_GETTER("customer.field.sex"));
	// 年龄
	API_DTO_FIELD_DEFAULT(Int16, age, ZH_WORDS_GETTER("customer.field.age"));
	// 生日
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("customer.field.birth"));
	// 类型
	API_DTO_FIELD_DEFAULT(String, stage, ZH_WORDS_GETTER("customer.field.type"));
	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("customer.field.note"));
};

class CustomerLessonDTO : public oatpp::DTO {
	DTO_INIT(CustomerLessonDTO, DTO);
	// 唯一ID
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("customer.field.courseid"));
	// 课程名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("customer.field.lessonName"));
	// 学习进度
	API_DTO_FIELD_DEFAULT(String, progress, ZH_WORDS_GETTER("customer.field.progress"));
	// 有效期
	API_DTO_FIELD_DEFAULT(String, deadline, ZH_WORDS_GETTER("customer.field.deadline"));
	// 剩余次数
	API_DTO_FIELD_DEFAULT(Int16, restTimes, ZH_WORDS_GETTER("customer.field.resttimes"));
};

class CustomerPageDTO : public PageDTO<CustomerDTO::Wrapper> {
	DTO_INIT(CustomerPageDTO, PageDTO<CustomerDTO::Wrapper>);
};

class CustomerLessonListDTO : public oatpp::DTO {
private:
	DTO_INIT(CustomerLessonListDTO, DTO);
	// 课程列表
	API_DTO_FIELD_DEFAULT(List<CustomerLessonDTO::Wrapper>, list, ZH_WORDS_GETTER("customer.field.list"));
public:
	CustomerLessonListDTO() {
		list = {};
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif