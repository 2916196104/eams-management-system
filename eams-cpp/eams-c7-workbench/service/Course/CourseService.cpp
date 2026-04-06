#include "stdafx.h"
#include "CourseService.h"
#include "../../dao/Course/CourseDAO.h"
#include "../../domain/do/Course/CourseDO.h"

CoursePageDTO::Wrapper CourseService::listAll(const CourseQuery::Wrapper& query)
{
    auto pages = CoursePageDTO::createShared();
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    CourseDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0) return pages;

    pages->total = count;
    pages->calcPages();
    auto result = dao.selectWithPage(query);

    for (CourseDO& sub : result)
    {
        auto dto = CourseDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
            courseName, CourseName,
            subjectName, SubjectName,
            lessonType, LessonType,
            courseNum, CourseNum,
            expireMonths, ExpireMonths,
            coursePrice, CoursePrice,
            tip, Tip
        );
        if (dto->lessonType == "1") {
            dto->lessonType = ZH_WORDS_GETTER("course.type.1");
        }
        else if (dto->lessonType == "2") {
            dto->lessonType = ZH_WORDS_GETTER("course.type.2");
        }
        else if (dto->lessonType == "3") {
            dto->lessonType = ZH_WORDS_GETTER("course.type.3");
        }
        pages->addData(dto);
    }
    return pages;
}

CourseDTO::Wrapper CourseService::getById(std::string courseId)
{
    CourseDAO dao;
    auto dataList = dao.selectById(courseId);

    if (dataList.empty()) return nullptr;

    auto& sub = dataList.front();
    auto dto = CourseDTO::createShared();

    ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
        courseName, CourseName,
        subjectName, SubjectName,
        lessonType, LessonType,
        courseNum, CourseNum,
        coursePrice, CoursePrice,
        expireMonths, ExpireMonths,
        startTime, StartTime,
        endTime, EndTime,
        tip, Tip
    );
    if (dto->lessonType == "1") {
        dto->lessonType = ZH_WORDS_GETTER("course.type.1");
    }
    else if (dto->lessonType == "2") {
        dto->lessonType = ZH_WORDS_GETTER("course.type.2");
    }
    else if (dto->lessonType == "3") {
        dto->lessonType = ZH_WORDS_GETTER("course.type.3");
    }

    dto->discountPrice = 0;
    dto->actualPayment = dto->coursePrice;

    return dto;
}