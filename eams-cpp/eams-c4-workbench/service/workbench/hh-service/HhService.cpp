#include "HhService.h"
#include "../../../dao/hh-dao/HhDAO.h"

CustomerPageDTO::Wrapper HhService::listAllStudent(const CustomerQuery::Wrapper& query, std::string creator_id) {
	// 构建返回对象
	auto pages = CustomerPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	HhDAO dao;
	uint64_t count = dao.countCustomer(query, creator_id);
	if (count <= 0) {
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	auto result = dao.selectCustomerWithPage(query, creator_id);
	for (HhStudentViewDO& sub : result) {
		auto dto = CustomerDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id,
			name, Name,
			mobile, Mobile);
		pages->addData(dto);
	}
	return pages;
}

CustomerDetailDTO::Wrapper HhService::getDetailById(std::string id) {
	HhDAO dao;
	auto res = dao.selectCustomerDetailWithId(id);

	if (!res) {
		return nullptr;
	}

	auto dto = CustomerDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res,
		id, Id,
		name, Name,
		mobile, Mobile,
		age, Age,
		birthday, Birthday,
		remark, Remark);

	// 性别是女二，男一，0未知
	switch (res->getGender()) {
	case 0:
		dto->gender = ZH_WORDS_GETTER("customer.enum.gender.unknown");
		break;
	case 1:
		dto->gender = ZH_WORDS_GETTER("customer.enum.gender.male");
		break;
	case 2:
		dto->gender = ZH_WORDS_GETTER("customer.enum.gender.female");
		break;
	default:
		dto->gender = ZH_WORDS_GETTER("customer.enum.gender.unknown");
		break;
	}

	std::cout << "第一行：" << ZH_WORDS_GETTER("customer.enum.stage.studying") << std::endl;
	dto->stage = res->getStage() == 2 ? ZH_WORDS_GETTER("customer.enum.stage.studying") : ZH_WORDS_GETTER("customer.enum.stage.intention");
	return dto;
}

CustomerLessonListDTO::Wrapper HhService::getLessonListById(std::string id) {
	// 构建返回对象
	auto result = CustomerLessonListDTO::createShared();

	// 进行查询
	HhDAO dao;
	std::list<HhCourseViewDO> dtolist = dao.selectCourseWithId(id);
	for (HhCourseViewDO& sub : dtolist) {
		auto dto = CustomerLessonDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
			name, Name,
			progress, Progress,
			deadline, DeadLine,
			restTimes, RestTimes
		);
		dto->id = stoi(sub.getId());
		result->list->push_back(dto);
	}

	return result;
}

ClassroomPageDTO::Wrapper HhService::listAllClassroom(const ClassroomQuery::Wrapper& query) {
	// 构建返回对象
	auto pages = ClassroomPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	HhDAO dao;
	uint64_t count = dao.countClassroom(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	auto result = dao.selectClassroomWithPage(query);
	// 将DO转换成DTO
	for (auto& sub : result)
	{
		auto dto = ClassroomDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, name, Name, address, Address);
		pages->addData(dto);
	}
	return pages;
}