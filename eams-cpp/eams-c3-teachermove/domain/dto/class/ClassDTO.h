#ifndef __CLASS_DTO_H__
#define __CLASS_DTO_H__

#include "../../GlobalInclude.h"
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

#include OATPP_CODEGEN_END(DTO)

#endif
