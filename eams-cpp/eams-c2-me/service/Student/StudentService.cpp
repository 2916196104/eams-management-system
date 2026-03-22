

#include "stdafx.h"
#include "StudentService.h"
#include "../../../arch-skeleton/Macros.h"
#include <ctime>
#include <string>
#include "domain/do/Student/StudentDO.h"

int StudentService::calculateAge(const std::string& birthday)
{
	if (birthday.empty()) return 0;

	// 解析年月日
	int year = stoi(birthday.substr(0, 4));
	int month = stoi(birthday.substr(5, 2));
	int day = stoi(birthday.substr(8, 2));

	// 获取当前时间
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int curYear = 1900 + ltm->tm_year;
	int curMonth = 1 + ltm->tm_mon;
	int curDay = ltm->tm_mday;

	// 计算年龄
	int age = curYear - year;
	if (curMonth < month || (curMonth == month && curDay < day)) {
		age--;
	}
	return age;
}

std::string StudentService::convertGender(int genderCode)
{
       switch (genderCode) {
        case 1:  return "MALE";
        case 2:  return "FEMALE";
        default: return "UNKNOWN"; // 0/其他值
    }
}

std::string StudentService::convertStage(int stageCode)
{
	switch (stageCode) {
	case 1:  return "GRADUATION";
	case 2:  return "INTENTION";
	default: return "STUDYING"; // 0/其他值
	}
}


//查询学生列表
StudentPageDTO::Wrapper StudentService::listAll(const StudentQuery::Wrapper& query)
{
	// 定义一个分页对象
	auto page = StudentPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	// 调用DAO获取数据总条数
	StudentDAO dao;
	auto count = dao.count(query);

	//std::cout << "===== 统计学生总数：" << count << std::endl;

	if (count <= 0)
		return page;//无数据直接返回空分页
	
	page->total = count;//计算分页信息(总条数，总页数)
	page->calcPages();

	// 调用DAO分页查询学生数据(DO列表) 获取分页数据
	std::list<PtrStudentDO>  list = dao.selectAll(query);

	//DO->DTO
	for (PtrStudentDO& sub : list)
	{
		auto dto = StudentDTO::createShared();
/*
		dto->name = sub->getName();
		dto->headImg = sub->getHead_img();
		dto->birthday = sub->getBirthday();

		dto->id = sub->getId();
		dto->credit = sub->getCredit();
*/

		ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, sub,
			id, Id,
			name, Name, 
			headImg,Head_img,
			birthday,Birthday,
			credit,Credit
			 
		);

		//年龄需要计算
		dto->age = calculateAge(sub->getBirthday());
		//性别需要数字转为字符串
		dto->gender = convertGender(sub->getGender());
		//学习阶段需要数字转为字符串
		dto->stage = convertStage(sub->getStage());
		//将转换后的DTO加入分页数据列表
		page->addData(dto);
	}
	//返回完整分页DTO
	return page;


}
