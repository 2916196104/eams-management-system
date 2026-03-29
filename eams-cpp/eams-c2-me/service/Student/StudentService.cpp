#include "stdafx.h"
#include "StudentService.h"
#include "../../../arch-skeleton/Macros.h"
#include <ctime>
#include <string>
#include "domain/do/Student/StudentDO.h"
#include <cstdint>

// 计算年龄（无需修改）
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

// 【修改】参数类型：int -> char
std::string StudentService::convertGender(char genderCode)
{
	switch (genderCode) {
	case 1:  return "MALE";
	case 2:  return "FEMALE";
	default: return "UNKNOWN";
	}
}

// 【修改】参数类型：int -> char
std::string StudentService::convertStage(char stageCode)
{
	switch (stageCode) {
	case 1:  return "GRADUATION";
	case 2:  return "INTENTION";
	default: return "STUDYING";
	}
}

// 查询学生列表（核心类型适配）
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

	// DO -> DTO 类型完全适配新DO
	for (PtrStudentDO& sub : list)
	{
		auto dto = StudentDTO::createShared();

		// 宏转换基础字段（自动匹配新DO的get方法）
		ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, sub,
			name, Name,
			headImg, HeadImg,
			birthday, Birthday
		);

		// 【关键1】uint64_t 类型的 id 转字符串，赋值给DTO
		dto->id = std::to_string(sub->getId()).c_str();

		// 【关键2】char 类型的 credit 转 int32，赋值给DTO
		dto->credit = (int32_t)sub->getCredit();

		// 【关键3】char 类型的 gender/stage 转换
		dto->age = calculateAge(sub->getBirthday());
		dto->gender = convertGender(sub->getGender());
		dto->stage = convertStage(sub->getStage());

		page->addData(dto);
	}

	return page;
}