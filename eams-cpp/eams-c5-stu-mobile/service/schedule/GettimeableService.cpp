#include "stdafx.h"
#include "GettimeableService.h"
#include "../../dao/schedule/GetTimeableDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

//GetTimeablePageDTO::Wrapper GettimeableService::listAll(const GetTimeableQuery::Wrapper& query)
//{
//	if (!query) {
//		// 直接返回一个空的分页对象，避免后续访问空指针
//		auto emptyPages = GetTimeablePageDTO::createShared();
//		emptyPages->pageIndex = 1;  // 给默认值
//		emptyPages->pageSize = 10;  // 直接赋值0，不再用reset或列表初始化
//		return emptyPages;
//	}
//
//	// 构建返回对象
//	auto pages = GetTimeablePageDTO::createShared();
//	pages->pageIndex = query->pageIndex;
//	pages->pageSize = query->pageSize;
//
//	// 查询数据总条数
//	GetTimeableDAO dao;
//	uint64_t count = dao.count(query);
//	if (count <= 0)
//	{
//		return pages;
//	}
//
//	// 分页查询数据
//	pages->total = count;
//	pages->calcPages();
//	list<GetTimeableDO> result = dao.selectWithPage(query);
//
//	if (result.empty()) {
//		// 日志提示（可选）
//		std::cout << "警告：数据总条数为" << count << "，但分页查询结果为空" << std::endl;
//		return pages;
//	}
//
//	// 将DO转换成DTO
//	for (GetTimeableDO& sub : result)
//	{	
//		if (sub.getDate().empty()) { // 假设date是字符串类型，根据实际类型调整判断逻辑
//			std::cout << "警告：发现空日期的时间表记录，跳过该条数据" << std::endl;
//			continue; // 跳过空数据，避免DTO赋值时的异常
//		}
//
//
//		auto dto = GetTimeableDTO::createShared();
//		if (!dto) {
//			throw std::runtime_error("创建GetTimeableDTO对象失败，内存不足或对象初始化异常");
//		}
//		//DO转换成DTO后面加的是查询需要的参数
//		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, date, Date);
//		pages->addData(dto);
//	}
//	return pages;
//}
GetTimeablePageDTO::Wrapper GettimeableService::listAll(const GetTimeableQuery::Wrapper& query)
{
	if (!query) {
		// 直接返回一个空的分页对象，避免后续访问空指针
		auto emptyPages = GetTimeablePageDTO::createShared();
		emptyPages->pageIndex = 1;  // 给默认值
		emptyPages->pageSize = 10; // 补充：无数据时total显式置0，避免默认值异常
		return emptyPages;
	}

	// 构建返回对象
	auto pages = GetTimeablePageDTO::createShared();
	if (!pages) { // 补充：防护pages创建失败（内存不足等极端场景）
		throw std::runtime_error("创建GetTimeablePageDTO分页对象失败");
	}
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;// 初始化total为0，避免无数据时total为随机值

	// 查询数据总条数
	GetTimeableDAO dao;
	uint64_t count = 0;
	try { // 补充：捕获DAO查询异常，避免数据库错误导致崩溃
		count = dao.count(query);
	}
	catch (const std::exception& e) {
		std::cerr << "查询数据总条数异常：" << e.what() << std::endl;
		return pages;
	}

	if (count <= 0)
	{
		return pages; // 数据库无数据，直接返回空分页
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();

	list<GetTimeableDO> result;
	try { // 补充：捕获分页查询异常
		result = dao.selectWithPage(query);
	}
	catch (const std::exception& e) {
		std::cerr << "分页查询数据异常：" << e.what() << std::endl;
		return pages;
	}

	if (result.empty()) {
		// 日志提示（可选）
		std::cout << "警告：数据总条数为" << count << "，但分页查询结果为空" << std::endl;
		return pages;
	}

	// 将DO转换成DTO
	for (GetTimeableDO& sub : result)
	{
		if (sub.getDate().empty()) { // 假设date是字符串类型，根据实际类型调整判断逻辑
			std::cout << "警告：发现空日期的时间表记录，跳过该条数据" << std::endl;
			continue; // 跳过空数据，避免DTO赋值时的异常
		}

		auto dto = GetTimeableDTO::createShared();
		if (!dto) {
			std::cerr << "创建GetTimeableDTO对象失败，跳过该条数据" << std::endl;
			continue; // 优化：抛异常改为跳过，避免单条数据错误导致整体查询失败
		}
		//DO转换成DTO后面加的是查询需要的参数
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id);                // 课程ID
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, title, Title);          // 课程标题
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, sn, Sn);                // 课程序号
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, date, Date);            // 上课日期
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, start_time, Start_time);// 开始时间
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, end_time, End_time);    // 结束时间
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, teacher_id, Teacher_id);// 教师ID
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, schedule_id, Schedule_id);// 排课ID
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, teacher_name, TeacherName); // 教师姓名
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, sign_state, SignState); // 签到状态
		pages->addData(dto);
	}
	return pages;
}
//GetTimeableDTO::Wrapper GettimeableService::getById(std::string id)
//{
//	// 查询数据
//	GetTimeableDAO dao;
//	auto res = dao.selectById(id);
//
//	// 没有查询到数据
//	if (!res)
//		return nullptr;
//
//	// 查询到数据转换成DTO
//	auto dto = GetTimeableDTO::createShared();
//	ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, date, Date);
//	return dto;
//}