#include "stdafx.h"
#include "EnrollCourseService.h"
#include "../../../dao/home/EnrollCourse/EnrollCourseDAO.h"



EnrollCoursePageDTO::Wrapper EnrollCourseService::listAll(const EnrollCourseQuery::Wrapper& query)
{
	auto pages = EnrollCoursePageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

    EnrollCourseDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	pages->total = count;
	pages->calcPages();
	list<EnrollCourseDO> result = dao.selectWithPage(query);

	for (EnrollCourseDO& sub : result)
	{
		auto dto = EnrollCourseDTO::createShared();
            ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,id,Id,
                student_id, StudentId,
                course_id, CourseId,
                subject_id, SubjectId,
                start_date, StartDate,
                expire_date, ExpireDate,
                remark, Remark,
                count_lesson_total, CountLessonTotal,
                count_lesson_complete, CountLessonComplete,
                count_lesson_refund, CountLessonRefund,
                course_amount, CourseAmount,
                discount_amount, DiscountAmount,
                amount, Amount,
                paid_amount, PaidAmount,
                unit_price, UnitPrice,
                pay_off, PayOff,
                deleted, Deleted,
                verify_state, VerifyState,
                warning_times, WarningTimes,
                priority, Priority,
                from_trial, FromTrial,
                operater, Operater,
                creator, Creator,
                add_time, AddTime,
                editor, Editor,
                edit_time, EditTime,
                org_id, OrgId,
                course_name, CourseName,
                subject_name, SubjectName
            );
		pages->addData(dto);
	}
	return pages;

}