#include"EnrolledRecordController.h"
#include"../../service/EnrollmentService/EnrolledRecordService.h"
#include"stdafx.h"

EnrolledRecordListJsonVO::Wrapper EnrolledRecordController:: execQueryNameList(const EnrolledQuery::Wrapper& name)
{
	auto result = EnrolledRecordService().getEnrolledRecordList(name);
	auto Jvo = EnrolledRecordListJsonVO::createShared();
	Jvo->success(result);

	return Jvo;
}
EnrolledRecordDetailJsonVO::Wrapper EnrolledRecordController::execEnrolledDetail(const Int32 &id)
{
	auto result = EnrolledRecordService().getEnrolledRecordDetail(id);
	auto Jvo = EnrolledRecordDetailJsonVO::createShared();
	Jvo->success(result);
	return Jvo;
}