#include"stdafx.h"
#include"student_coursecontroller.h"
#include"../../service/StudentRecord/student_courseServeice.h"

CourseProgressPageJsonVO::Wrapper StudentRecord::CourseControllor::execCourseProgressPageQuery(StudentQuery::Wrapper userQuery) {
	if (!userQuery->id) {
		// 封装成VO返回（补充通用返回字段）
		auto vo = CourseProgressPageJsonVO::createShared();
		vo->code = 400;
		vo->message = "id can't be empty";
		return vo;
	}
	// 创建Service对象
	StudentCourseService service;
	// 调用Service查询数据
	auto pageDTO = service.listAllCourseProgress(userQuery);
	// 封装成VO返回（补充通用返回字段）
	auto vo = CourseProgressPageJsonVO::createShared();
	vo->data = pageDTO;
	vo->code = 200;
	vo->message = "seccesefully find through id";
	return vo;

}
CourseRecordPageJsonVO::Wrapper StudentRecord::CourseControllor::execCourseRecordPageQuery(StudentQuery::Wrapper userQuery) {

	if (!userQuery->id) {
		// 封装成VO返回（补充通用返回字段）
		auto vo = CourseRecordPageJsonVO::createShared();
		vo->code = 400;
		vo->message = "id can't be empty";
		return vo;
	}
	// 创建Service对象
	StudentCourseService service;
	// 调用Service查询数据
	auto pageDTO = service.listAllCourseRecord(userQuery);
	// 封装成VO返回（补充通用返回字段）
	auto vo = CourseRecordPageJsonVO::createShared();
	vo->data = pageDTO;
	vo->code = 200;
	vo->message = "seccesefully find through id";
	return vo;
}
StudentSighnUPPageJsonVO::Wrapper StudentRecord::CourseControllor::execStudentSighnUPPageQuery(StudentQuery::Wrapper userQuery) {

	if (!userQuery->id) {
		// 封装成VO返回（补充通用返回字段）
		auto vo = StudentSighnUPPageJsonVO::createShared();
		vo->code = 400;
		vo->message = "id can't be empty";
		return vo;
	}
	// 创建Service对象
	StudentCourseService service;
	// 调用Service查询数据
	auto pageDTO = service.listAllStudentSighnUP(userQuery);
	// 封装成VO返回（补充通用返回字段）
	auto vo = StudentSighnUPPageJsonVO::createShared();
	vo->data = pageDTO;
	vo->code = 200;
	vo->message = "seccesefully find through id";
	return vo;
}