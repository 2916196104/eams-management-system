#include"ClassDetailService.h"
#include"../../dao/class/ClassDetailDAO.h"
#include"../../domain/dto/classDTO/classDetailDTO.h"
#include"stdafx.h"

ClassDetailDTO::Wrapper ClassDetailService::getClassDetail(const std::string &id)
{
	ClassDetailDAO dao;
	auto detail = dao.selectClassDetailById(id);
		if (!detail)
		{
			return nullptr;
		}
	auto dto = ClassDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, detail, class_name, ClassName,staff_name, StaffName, room_name, RoomName, start_date, StartDate, end_date, EndDate, course_lessons, CourseLessons, planed_student_count, PlanedStudentCount, remark, Remark, be_over, BeOver);
	return dto;
}