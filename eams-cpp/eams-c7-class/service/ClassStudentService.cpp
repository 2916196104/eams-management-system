/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:13:11

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "ClassStudentService.h"
#include "../dao/ClassStudentDAO.h"
#include "SimpleDateTimeFormat.h"
#include <ctime>
#include <string>

using oatpp::UInt64;
using oatpp::Int32;
using oatpp::String;

// ==================== 辅助函数 ====================

static int calculateAge(const String& birthday) {
    if (!birthday || birthday->empty()) {
        return 0;
    }
    std::string birthStr = birthday.getValue("");
    if (birthStr.length() < 4) {
        return 0;
    }
    int birthYear = std::stoi(birthStr.substr(0, 4));
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;
    return currentYear - birthYear;
}

static String formatGender(Int32 gender) {
    switch (gender) {
    case 1: return String(ZH_WORDS_GETTER("student.gender.male"));
    case 2: return String(ZH_WORDS_GETTER("student.gender.female"));
    default: return String(ZH_WORDS_GETTER("student.gender.unknown"));
    }
}

static String formatStage(Int32 stage) {
    switch (stage) {
    case 0: return String(ZH_WORDS_GETTER("student.stage.intention"));
    case 1: return String(ZH_WORDS_GETTER("student.stage.studying"));
    case 2: return String(ZH_WORDS_GETTER("student.stage.graduated"));
    default: return String(ZH_WORDS_GETTER("student.stage.unknown"));
    }
}

// ==================== 获取班级学员列表（分页） ====================

ClassStudentPageDTO::Wrapper ClassStudentService::getClassStudentList(const ClassStudentListQuery::Wrapper& query)
{
    auto pages = ClassStudentPageDTO::createShared();
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    ClassStudentDAO dao;
    uint64_t count = dao.countClassStudentList(query);
    if (count <= 0) {
        return pages;
    }

    pages->total = count;
    pages->calcPages();

    std::list<PtrStudentDO> studentList = dao.selectClassStudentList(query);
    if (studentList.empty()) {
        return pages;
    }

    std::vector<UInt64> studentIds;
    for (auto& student : studentList) {
        studentIds.push_back(student->getId());
    }

    std::map<uint64_t, Int32> remainingMap = dao.selectRemainingLessonCountByStudentIds(studentIds);

    for (auto& student : studentList) {
        auto dto = ClassStudentItemDTO::createShared();

        dto->id = student->getId();
        dto->name = student->getName();
        dto->gender = formatGender(student->getGender());

        uint64_t studentIdVal = static_cast<uint64_t>(student->getId());
        auto it = remainingMap.find(studentIdVal);
        dto->remainingLessonCount = (it != remainingMap.end()) ? it->second : oatpp::Int32(0);

        pages->addData(dto);
    }

    return pages;
}

// ==================== 获取班级学员详情 ====================

StudentDetailDTO::Wrapper ClassStudentService::getStudentDetail(const UInt64& studentId)
{
    ClassStudentDAO dao;
    auto student = dao.selectStudentById(studentId);

    if (!student || student->getId() == 0) {
        return nullptr;
    }

    String mobile = dao.selectMobileByStudentId(studentId);

    auto dto = StudentDetailDTO::createShared();
    dto->id = student->getId();
    dto->name = student->getName();
    dto->mobile = mobile;
    dto->gender = formatGender(student->getGender());
    dto->age = calculateAge(student->getBirthday());
    dto->birthday = student->getBirthday();
    dto->stage = formatStage(student->getStage());
    dto->remark = student->getRemark();

    return dto;
}

// ==================== 获取班级学员课程列表（分页） ====================

StudentCoursePageDTO::Wrapper ClassStudentService::getStudentCourseList(const StudentCourseListQuery::Wrapper& query)
{
    auto pages = StudentCoursePageDTO::createShared();
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    ClassStudentDAO dao;
    uint64_t count = dao.countStudentCourseList(query);
    if (count <= 0) {
        return pages;
    }

    pages->total = count;
    pages->calcPages();

    std::list<PtrStudentCourseDO> courseList = dao.selectStudentCourseList(query);
    if (courseList.empty()) {
        return pages;
    }

    for (auto& course : courseList) {
        auto dto = StudentCourseItemDTO::createShared();

        dto->courseName = course->getCourseName();
        dto->countLessonTotal = course->getCountLessonTotal();
        dto->countLessonComplete = course->getCountLessonComplete();
        dto->countLessonRemaining = course->getRemainingLessonCount();
        dto->progressText = course->getProgressText();
        dto->expireDate = course->getExpireDate();

        Int32 remaining = course->getRemainingLessonCount();
        std::string remainingStr = ZH_WORDS_GETTER("student_course.remainingPrefix") +
            std::to_string(remaining) +
            ZH_WORDS_GETTER("student_course.remainingSuffix");
        dto->remainingText = String(remainingStr.c_str());

        String expireDate = course->getExpireDate();
        if (expireDate && !expireDate->empty()) {
            std::string expireStr = ZH_WORDS_GETTER("student_course.expirePrefix") + expireDate->c_str();
            dto->expireText = String(expireStr.c_str());
        }
        else {
            dto->expireText = String(ZH_WORDS_GETTER("student_course.expiredText").c_str());
        }

        pages->addData(dto);
    }

    return pages;
}