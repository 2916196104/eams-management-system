#include "stdafx.h"
#include "CourseController.h"
#include "../../service/Course/CourseService.h"

// 分页查询
CoursePageJsonVO::Wrapper CourseController::execQueryPage(const CourseQuery::Wrapper& query)
{
    CourseService service;
    auto result = service.listAll(query);
    auto jvo = CoursePageJsonVO::createShared();
    jvo->success(result);
    return jvo;
}
CourseDetailJsonVO::Wrapper CourseController::execQueryCourseDetail(const QueryParams& queryParams)
{
    auto jvo = CourseDetailJsonVO::createShared();

    // 1. 获取参数 courseId
    auto courseIdOpt = queryParams.get("courseId");
    if (!courseIdOpt) {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }

    // 2. 定义变量 courseId
    oatpp::String courseId = courseIdOpt;

    // 3. 查询
    CourseService service;
    auto dto = service.getById(courseId);

    // 4. 返回
    if (dto) {
        jvo->success(dto);
    }
    return jvo;
}