#pragma once
#ifndef _MyCustomersVO_H_
#define _MyCustomersVO_H_

#include "../../GlobalInclude.h"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "domain/dto/MyCustomers/MyCustomersDTO.h"
#include "../lib-oatpp/include/domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 学生分页列表VO
class MyCustomersPageJsonVO : public JsonVO<MyCustomersPageDTO::Wrapper> {
	DTO_INIT(MyCustomersPageJsonVO, JsonVO<MyCustomersPageDTO::Wrapper>);
	API_DTO_FIELD_DEFAULT(MyCustomersPageDTO::Wrapper, data, u8"学生分页数据");
public:
	static MyCustomersPageJsonVO::Wrapper createPageResult(MyCustomersPageDTO::Wrapper dto) {
		auto vo = MyCustomersPageJsonVO::createShared();
		vo->data = dto;
		vo->success(vo->data);
		return vo;
	}
};

// 学生详情VO
class MyCustomerDetailJsonVO : public JsonVO<MyCustomerDetailDTO::Wrapper> {
	DTO_INIT(MyCustomerDetailJsonVO, JsonVO<MyCustomerDetailDTO::Wrapper>);
	API_DTO_FIELD_DEFAULT(MyCustomerDetailDTO::Wrapper, data, u8"学生详情");
public:
	static MyCustomerDetailJsonVO::Wrapper createDetailResult(MyCustomerDetailDTO::Wrapper dto) {
		auto vo = MyCustomerDetailJsonVO::createShared();
		vo->data = dto;
		vo->success(vo->data);
		return vo;
	}
};

// 学生课程分页VO
class StudentCoursesPageJsonVO : public JsonVO<StudentCoursesPageDTO::Wrapper> {
	DTO_INIT(StudentCoursesPageJsonVO, JsonVO<StudentCoursesPageDTO::Wrapper>);
	API_DTO_FIELD_DEFAULT(StudentCoursesPageDTO::Wrapper, data, u8"学生课程分页");
public:
	static StudentCoursesPageJsonVO::Wrapper createCourseResult(StudentCoursesPageDTO::Wrapper dto) {
		auto vo = StudentCoursesPageJsonVO::createShared();
		vo->data = dto;
		vo->success(vo->data);
		return vo;
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_MyCustomersVO_H_