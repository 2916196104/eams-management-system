#ifndef __CLASS_STUDENT_DTO_H__
#define __CLASS_STUDENT_DTO_H__

#include "domain/GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 班级学员列表项 DTO（class_student 关联 student 展示字段）
 */

class ClassStudentDTO : public oatpp::DTO
{
	DTO_INIT(ClassStudentDTO, DTO);

	// class_student 主键
	DTO_FIELD(UInt64, id);
	DTO_FIELD(UInt64, classId);
	DTO_FIELD(UInt64, studentId);
	DTO_FIELD(String, addTime);
	DTO_FIELD(Int64, creator);
	DTO_FIELD(Int32, reason);
	DTO_FIELD(Boolean, deleted);
	DTO_FIELD(String, remark);
	DTO_FIELD(Int64, consumeCourseId);

	// student 展示字段
	DTO_FIELD(String, studentName);
	DTO_FIELD(Int32, gender);
	DTO_FIELD(String, headImg);
	DTO_FIELD(String, birthday);
};

class ClassStudentListDTO : public oatpp::DTO {
	DTO_INIT(ClassStudentListDTO, DTO);
	DTO_FIELD(UInt64, studentId);
	DTO_FIELD(String, studentName);
	DTO_FIELD(Int32, gender);
	DTO_FIELD(Int32, remaining);
};

/**
 * 班级学员分页 DTO
 */
class ClassStudentPageDTO : public PageDTO<ClassStudentDTO::Wrapper>
{
	DTO_INIT(ClassStudentPageDTO, PageDTO<ClassStudentDTO::Wrapper>);
};

class ClassStudentListPageDTO : public PageDTO<ClassStudentListDTO::Wrapper> {
	DTO_INIT(ClassStudentListPageDTO, PageDTO<ClassStudentListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif