#include "stdafx.h"
#include "StudentService.h"
#include "../../../arch-skeleton/Macros.h"
#include <ctime>
#include <string>
#include <cstdint>

// 计算年龄
int StudentService::calculateAge(const std::string& birthday)
{
    if (birthday.empty()) return 0;
    int year = stoi(birthday.substr(0, 4));
    int month = stoi(birthday.substr(5, 2));
    int day = stoi(birthday.substr(8, 2));

    time_t now = time(0);
    tm* ltm = localtime(&now);
    int curYear = 1900 + ltm->tm_year;
    int curMonth = 1 + ltm->tm_mon;
    int curDay = ltm->tm_mday;

    int age = curYear - year;
    if (curMonth < month || (curMonth == month && curDay < day)) {
        age--;
    }
    return age;
}

// 转换性别编码
std::string StudentService::convertGender(int genderCode)
{
    switch (genderCode) {
    case 1:  return "MALE";
    case 2:  return "FEMALE";
    default: return "UNKNOWN";
    }
}

// 转换阶段编码
std::string StudentService::convertStage(int stageCode)
{
    switch (stageCode) {
    case 1:  return "GRADUATION";
    case 2:  return "INTENTION";
    default: return "STUDYING";
    }
}

// 分页查询学员列表
StudentPageDTO::Wrapper StudentService::listAll(const StudentQuery::Wrapper& query)
{
    auto page = StudentPageDTO::createShared();
    page->pageIndex = query->pageIndex;
    page->pageSize = query->pageSize;

    StudentDAO dao;
    auto count = dao.count(query);

    if (count <= 0)
        return page;

    page->total = count;
    page->calcPages();

    std::list<PtrStudentDO> list = dao.selectAll(query);

    for (PtrStudentDO& sub : list)
    {
        auto dto = StudentDTO::createShared();

        // DO转DTO字段映射
        ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, sub,
            name, Name,
            headImg, HeadImg,
            birthday, Birthday
        );

        // uint64_t转字符串
        dto->id = std::to_string(sub->getId()).c_str();
        dto->credit = sub->getCredit();
        // 计算/转换扩展字段
        dto->age = calculateAge(sub->getBirthday());
        dto->gender = convertGender(sub->getGender());
        dto->stage = convertStage(sub->getStage());

        page->addData(dto);
    }

    return page;
}

// 检查学员是否存在（切换学员）
bool StudentService::findById(uint64_t id)
{
    if (id <= 0) {
        return false;
    }
    StudentDAO dao;
    return dao.findById(id);
}

// 删除学员（软删除）
bool StudentService::deleteStudent(uint64_t id)
{
    if (id <= 0) {
        return false;
    }
    StudentDAO dao;
    return dao.deleteById(id);
}