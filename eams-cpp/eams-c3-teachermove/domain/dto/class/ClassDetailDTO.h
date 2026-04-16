#ifndef __CLASS_JOIN_DTO_H__
#define __CLASS_JOIN_DTO_H__

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 班级联表查询结果 DTO（class + classroom + course + staff + ?）
 * 仅暴露：课程主键、班级名、班主任名称、教室名称、课程名称、
 * 起始/结束日期、课程进度、招生进度、排课备注、班级状态
 */
class ClassDetailDTO : public oatpp::DTO
{
	DTO_INIT(ClassDetailDTO, DTO)

	/** 班级主键 */
	DTO_FIELD(Int64, classId);
	/** 班级名 */
	DTO_FIELD(String, className);
	/** 班主任名称（teacher_id 关联 staff） */
	DTO_FIELD(String, teacherName);
	/** 教室名称（classroom_id 关联 classroom） */
	DTO_FIELD(String, classroomName);
	/** 课程名称 */
	DTO_FIELD(String, courseName);
	/** 起始日期（计划开班日期） */
	DTO_FIELD(String, startDate);
	/** 结束日期（计划结业日期） */
	DTO_FIELD(String, endDate);
	/** 课程进度（DO 无，用 String） */
	DTO_FIELD(String, courseProgress);
	/** 招生进度（DO 无，用 String） */
	DTO_FIELD(String, enrollmentProgress);
	/** 排课备注 */
	DTO_FIELD(String, remark);
	/** 班级状态（DO 无，用 String） */
	DTO_FIELD(String, classStatus);
};
class ClassDetailPageDTO : public PageDTO<ClassDetailDTO::Wrapper>
{
	DTO_INIT(ClassDetailPageDTO, PageDTO<ClassDetailDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif
