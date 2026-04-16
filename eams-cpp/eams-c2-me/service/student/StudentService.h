#pragma once
#ifndef _STUDENTSERVICE_H_
#define _STUDENTSERVICE_H_

#include "domain/query/student/StudentQuery.h"
#include "domain/dto/student/StudentDTO.h"
#include "dao/student/StudentDAO.h"
#include <cstdint>

class StudentService
{
private:
    // 计算年龄（根据生日）
    int calculateAge(const std::string& birthday);
    // 转换性别编码（int->字符串）
    std::string convertGender(int genderCode);
    // 转换阶段编码（int->字符串）
    std::string convertStage(int stageCode);

public:
    // 分页查询学员列表
    StudentPageDTO::Wrapper listAll(const StudentQuery::Wrapper& query);
    // 检查学员是否存在（切换学员）
    bool findById(uint64_t id);
    // 删除学员（软删除）
    bool deleteStudent(uint64_t id);
};

#endif