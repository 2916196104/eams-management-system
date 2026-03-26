#include "stdafx.h"
#include"student_courseServeice.h"
#include<string>
#define deBug 1
CourseProgressPageDTO::Wrapper StudentCourseService::listAllCourseProgress(const StudentQuery::Wrapper& query) {
	//创建返回对象
    auto pages = CourseProgressPageDTO::createShared();
    // 第一步：检查query是否为空
    if (!query) {
        
        pages->pageIndex = 1;
        pages->pageSize = 10;
        return pages;
    }
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;
    // 获取学生ID
    string studentId = query->id.getValue("");
#if deBug
    OATPP_LOGD("StudentCourseService", "查询学生ID: %s", studentId.c_str());
#endif // deBug
    // 查询数据总条数
    StudentCourseDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0) {
        return pages;
    }

    // 分页查询数据（补回总条数赋值）
    pages->total = count;
    list<CourseProgressViewDO> result = dao.selectWithPageCourseProgress(query);

    // 将DO转换成DTO
    for (CourseProgressViewDO& sub : result) {
        auto dto = CourseProgressDTO::createShared();
		dto->class_name = sub.getCourseName();
		dto->status = sub.getCourseStatus();
		dto->coursesum = sub.getCourseSum();
        dto->finishedsum = sub.getFinishedSum();
        dto->unfinishedsum = dto->coursesum- dto->finishedsum;
        pages->addData(dto);
    }
    return pages;
}

StudentSighnUPPageDTO::Wrapper StudentCourseService::listAllStudentSighnUP(const StudentQuery::Wrapper& query) {
    //创建返回对象
    auto pages = StudentSighnUPPageDTO::createShared();
    // 第一步：检查query是否为空
    if (!query) {

        pages->pageIndex = 1;
        pages->pageSize = 10;
        return pages;
    }
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;
    // 获取学生ID
    string studentId = query->id.getValue("");

    // 查询数据总条数
    StudentCourseDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0) {
        return pages;
    }

    // 分页查询数据（补回总条数赋值）
    pages->total = count;
    list<StudentSignUpViewDO> result = dao.selectWithPageStudentSighnUP(query);

    // 将DO转换成DTO
    for (StudentSignUpViewDO& sub : result) {
        auto dto = StudentSighnUPDTO::createShared();
        dto->class_name = sub.getCourseName();
        //dto->class_name = "";
		dto->buycoursesum = sub.getBuyCourseSum();
		dto->time = sub.getSignUpTime();
		dto->pay = int(sub.getPayAmount());
        pages->addData(dto);
    }
    return pages;
}

CourseRecordPageDTO::Wrapper StudentCourseService::listAllCourseRecord(const StudentQuery::Wrapper& query) {
    //创建返回对象
    auto pages = CourseRecordPageDTO::createShared();
    // 第一步：检查query是否为空
    if (!query) {

        pages->pageIndex = 1;
        pages->pageSize = 10;
        return pages;
    }
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;
    // 获取学生ID
    string studentId = query->id.getValue("");

    // 查询数据总条数
    StudentCourseDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0) {
        return pages;
    }

    // 分页查询数据（补回总条数赋值）
    pages->total = count;
    list<CourseRecordViewDO> result = dao.selectWithPageCourseRecord(query);

    // 将DO转换成DTO
    for (CourseRecordViewDO& sub : result) {
        auto dto = CourseRecordDTO::createShared();
		dto->class_name = sub.getCourseName();
		dto->status = sub.getCourseStatus();
		dto->consume_course_num = sub.getConsumeCourseNum();
		dto->course_balance = sub.getCourseBalance();
        pages->addData(dto);
    }
    return pages;
}
/**
 * 学员课时记录数据传输对象
 * name: 课程名称
  status: 课程状态
  finishedsum: 消课数
  unfinishedsum: 剩余课程数
 */