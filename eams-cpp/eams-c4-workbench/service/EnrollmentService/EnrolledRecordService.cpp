#include"EnrolledRecordService.h"
#include"stdafx.h"
#include"../../dao/EnrollmentDAO/EnrollmentDAO.h"
#include"../../domain/query/EnrollmentQuery/EnrolledRecordQuery.h"
#include"../../domain/do/ViewDO/EnrolledRecordDO.h"
EnrolledRecordPageDTO::Wrapper EnrolledRecordService::getEnrolledRecordList(const EnrolledQuery::Wrapper& query)
{
	auto pages = EnrolledRecordPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	EnrollmentDAO dao;

	uint64_t totalCount = dao.countByQuery(query);
	if(totalCount == 0)
	{
		return pages;
	}
	pages->total= totalCount;
	pages->calcPages();
	list<EnrolledRecordDO> result = dao.selectEnrolledRecordListByQuery(query);

	for(EnrolledRecordDO& item: result)
	{
		auto dto = EnrolledRecordListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, item, studentName, StudentName, courseName, CourseName,startCourseTime,StartDate,endCourseTime,ExpireDate,courseAmount,Amount);
		pages->addData(dto);
	}
	return pages;
}
EnrolledRecordDTO::Wrapper EnrolledRecordService::getEnrolledRecordDetail(const Int32 id)
{
	EnrollmentDAO dao;
	auto enrollDO = dao.selectDetailById(id);
	if(!enrollDO)
	{
		return nullptr;
	}
	auto dto = EnrolledRecordDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, enrollDO, studentName, StudentName, courseName, CourseName, subjectName, SubjectName,
		startDate, StartDate, expireDate, ExpireDate, courseAmount, CourseAmount, discountCourseAmount, DiscountAmount, paidCourseAmount, PaidAmount);
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, enrollDO,owedCourseAmount, OwedAmount, submitTime, SubmitTime, remark, Remark, totalLessons, TotalLessons, completedLessons, CompletedLessons,
		remainingLessons,RemainingLessons, refundInfo, RefundInfo);

	return dto;
}