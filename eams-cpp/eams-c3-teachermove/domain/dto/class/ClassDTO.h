#ifndef __CLASS_DTO_H__
#define __CLASS_DTO_H__

#include "domain/GlobalInclude.h"
#include "Macros.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 班级 DTO（与 class 表字段对应）
 */
class ClassDTO : public oatpp::DTO
{
	DTO_INIT(ClassDTO, DTO)

	DTO_FIELD(UInt64, id);
	DTO_FIELD(String, name);
	DTO_FIELD(Int64, courseId);
	DTO_FIELD(Int64, classroomId);
	DTO_FIELD(Int64, creator);
	DTO_FIELD(Int64, editor);
	DTO_FIELD(String, addTime);
	DTO_FIELD(String, editTime);
	DTO_FIELD(Boolean, deleted);
	DTO_FIELD(Int64, teacherId);
	DTO_FIELD(String, remark);
	DTO_FIELD(Boolean, beOver);
	DTO_FIELD(String, overTime);
	DTO_FIELD(Int64, overOperator);
	DTO_FIELD(String, startDate);
	DTO_FIELD(String, endDate);
	DTO_FIELD(Int32, plannedStudentCount);
	DTO_FIELD(Int32, plannedLessonCount);
	DTO_FIELD(Int64, schoolId);
	DTO_FIELD(Int64, orgId);
	DTO_FIELD(Int32, gradeId);
};
/**
 * 班级分页 DTO
 */
class ClassPageDTO : public PageDTO<ClassDTO::Wrapper>
{
	DTO_INIT(ClassPageDTO, PageDTO<ClassDTO::Wrapper>);
};

// 学生详情DTO
class StudentDetailDTO : public oatpp::DTO
{
	DTO_INIT(StudentDetailDTO, DTO);
	// 姓名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.name"));
	// 电话号码
	API_DTO_FIELD_DEFAULT(String, phone, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.phone"));
	// 性别
	API_DTO_FIELD_DEFAULT(String, gender, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.gender"));
	// 年龄
	API_DTO_FIELD_DEFAULT(Int32, age, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.age"));
	// 出生日期
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.birthday"));
	// 学生类型
	API_DTO_FIELD_DEFAULT(String, studentType, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.studentType"));
	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("class.dto.StudentDetailDTO.remark"));
};

// 课程信息DTO
class CourseInfoDTO : public oatpp::DTO
{
	DTO_INIT(CourseInfoDTO, DTO);
	// 课程名称
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("class.dto.CourseInfoDTO.courseName"));
	// 学习进度
	API_DTO_FIELD_DEFAULT(String, progress, ZH_WORDS_GETTER("class.dto.CourseInfoDTO.progress"));
	// 有效期
	API_DTO_FIELD_DEFAULT(String, validityPeriod, ZH_WORDS_GETTER("class.dto.CourseInfoDTO.validityPeriod"));
	// 剩余次数
	API_DTO_FIELD_DEFAULT(Int32, remainingCount, ZH_WORDS_GETTER("class.dto.CourseInfoDTO.remainingCount"));
};

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
