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
//中文转码

static std::string urlDecode(const std::string& encoded) {
    std::string decoded;
    char ch;
    size_t i = 0;
    size_t len = encoded.length();
    while (i < len) {
        if (encoded[i] == '%' && i + 2 < len) {
            int hex = 0;
            sscanf(encoded.substr(i + 1, 2).c_str(), "%x", &hex);
            ch = static_cast<char>(hex);
            decoded += ch;
            i += 3;
        }
        else if (encoded[i] == '+') {
            decoded += ' ';
            i++;
        }
        else {
            decoded += encoded[i];
            i++;
        }
    }
    return decoded;
}

CourseDetailJsonVO::Wrapper CourseController::execQueryCourseDetail(const QueryParams& queryParams)
{
    auto jvo = CourseDetailJsonVO::createShared();
    // 1. 获取参数
    auto nameOpt = queryParams.get("name");
    if (!nameOpt) {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }
    std::string encodedName = nameOpt->c_str();
    std::string courseName = urlDecode(encodedName);
    // 3. 查询
    CourseService service;
    auto dto = service.getByName(courseName);
    // 4. 返回
    if (dto) {
        jvo->success(dto);
    }
    return jvo;
}