#ifndef __CLASS_DTO_H__
#define __CLASS_DTO_H__

#include "domain/GlobalInclude.h"
#include "Macros.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)



// 课程信息DTO
class CourseInfoDTO : public oatpp::DTO {
	DTO_INIT(CourseInfoDTO, DTO);
	// 课程名称
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("class.dto.CourseInfoDTO.courseName"));
	// 学习进度
	API_DTO_FIELD_DEFAULT(String, progress, ZH_WORDS_GETTER("class.dto.CourseInfoDTO.progress"));
	// 有效期限
	API_DTO_FIELD_DEFAULT(String, validityPeriod, ZH_WORDS_GETTER("class.dto.CourseInfoDTO.validityPeriod"));
	// 剩余次数
	API_DTO_FIELD_DEFAULT(Int32, remainingCount, ZH_WORDS_GETTER("class.dto.CourseInfoDTO.remainingCount"));
};

// 学员详情DTO
class StudentDetailDTO : public oatpp::DTO {
	DTO_INIT(StudentDetailDTO, DTO);
	// 姓名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.name"));
	// 手机号码
	API_DTO_FIELD_DEFAULT(String, phone, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.phone"));
	// 性别
	API_DTO_FIELD_DEFAULT(String, gender, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.gender"));
	// 年龄
	API_DTO_FIELD_DEFAULT(Int32, age, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.age"));
	// 生日
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.birthday"));
	// 学员类型
	API_DTO_FIELD_DEFAULT(String, studentType, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.studentType"));
	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.remark"));
};

// 班级DTO
class ClassDTO : public oatpp::DTO {
	DTO_INIT(ClassDTO, DTO);
	// 班级编号
	API_DTO_FIELD_DEFAULT(String, classNo, ZH_WORDS_GETTER("class.dto.ClassDTO.classNo"));
	// 班级名称
	API_DTO_FIELD_DEFAULT(String, className, ZH_WORDS_GETTER("class.dto.ClassDTO.className"));
	// 老师名称
	API_DTO_FIELD_DEFAULT(String, teacherName, ZH_WORDS_GETTER("class.dto.ClassDTO.teacherName"));
	// 课程名称
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("class.dto.ClassDTO.courseName"));
	// 开始时间
	API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("class.dto.ClassDTO.startTime"));
	// 结束时间
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("class.dto.ClassDTO.endTime"));
	// 参与人数（已参与/预估人数）
	API_DTO_FIELD_DEFAULT(String, participantCount, ZH_WORDS_GETTER("class.dto.ClassDTO.participantCount"));
};

// 班级分页DTO
class ClassPageDTO : public PageDTO<oatpp::Object<ClassDTO>> {
	DTO_INIT(ClassPageDTO, PageDTO<oatpp::Object<ClassDTO>>);
};

// 课程分页DTO
class CoursePageDTO : public PageDTO<oatpp::Object<CourseInfoDTO>> {
	DTO_INIT(CoursePageDTO, PageDTO<oatpp::Object<CourseInfoDTO>>);
};

// 课程列表查询DTO已在ClassQuery.h中定义

// 课程列表响应DTO
class CourseListResponseDTO : public oatpp::DTO {
	DTO_INIT(CourseListResponseDTO, DTO);
	// 课程列表
	API_DTO_FIELD_DEFAULT(Vector<oatpp::Object<CourseInfoDTO>>, items, ZH_WORDS_GETTER("class.dto.CourseListResponseDTO.items"));
	// 总记录数
	API_DTO_FIELD_DEFAULT(Int32, total, ZH_WORDS_GETTER("class.dto.CourseListResponseDTO.total"));
	// 当前页码
	API_DTO_FIELD_DEFAULT(Int32, page, ZH_WORDS_GETTER("class.dto.CourseListResponseDTO.page"));
	// 每页大小
	API_DTO_FIELD_DEFAULT(Int32, size, ZH_WORDS_GETTER("class.dto.CourseListResponseDTO.size"));
};

#include OATPP_CODEGEN_END(DTO)

#endif