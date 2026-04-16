#include "stdafx.h"
#include "CommonService.h"
#include "../../dao/common/CommonDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
void StudentService::ModifyStudentHeadImg(ModifyStudentHeadImgDTO::Wrapper dto) {
	uint64_t id = dto->id;
	std::string headImg = dto->picturePath;
	StudentDAO dao;
	dao.updateStudentHeadImg(id, headImg);
}
StudentDTO::Wrapper StudentService::GetStudentDetailById(uint64_t studentId) {
	StudentDAO dao;
	return dao.getStudentDetailById(studentId);
}
RegistrationPageDTO::Wrapper RegistrationRecordService::GetRegistrationRecordWithPage(RegistrationPageQuery::Wrapper query) {
	auto pages = RegistrationPageDTO::createShared();
	RegistrationRecordDAO dao;
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;
	uint64_t count = dao.count(query->id);
	if (count <= 0) {
		return pages;
	}
	pages->total = count;
	pages->calcPages();
	auto results = dao.selectRegistrationRecordWithPage(query);
	for (auto& result : results) {
		pages->addData(result);
	}
	return pages;
}
//班级列表服务
getClassListPageDTO::Wrapper getClassListService::listAll(const getClassListQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = getClassListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	getClassListDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	std::list<getClassListDO> result = dao.selectWithPage(query);

	// 将DO转换成DTO
	for (getClassListDO& sub : result)
	{
		auto dto = getClassListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
			id, Id,
			className, ClassName,
			subject, Subject,
			classroom, Classroom,
			studentCount, StudentCount,
			maxStudentCount, MaxStudentCount);
		pages->addData(dto);
	}
	return pages;
}

//课程统计服务
getCourseStatisticsPageDTO::Wrapper getCourseStatisticsService::listAll(const getCourseStatisticsQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = getCourseStatisticsPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	getCourseStatisticsDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	std::list<getCourseStatisticsDO> result = dao.selectWithPage(query);

	// 将DO转换成DTO
	for (getCourseStatisticsDO& sub : result)
	{
		auto dto = getCourseStatisticsDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
			course, Course,
			totalHours, TotalHours,
			remainingHours, RemainingHours,
			attendedHours, AttendedHours,
			expireDate, ExpireDate,
			cancelPriority, CancelPriority);
		pages->addData(dto);
	}
	return pages;
}

// 分页查询可加入的班级列表
JoinclassPageDTO::Wrapper JoinclassService::listAll(const JoinclassQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = JoinclassPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	JoinclassDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	std::list<JoinclassDO> result = dao.selectWithPage(query);

	// 将DO转换成DTO
	for (JoinclassDO& sub : result)
	{
		auto dto = JoinclassDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
			className, ClassName,
			school, School);
		pages->addData(dto);
	}
	return pages;
}

// 学生加入班级的实现
bool JoinclassService::joinClass(const oatpp::String& studentId, const oatpp::String& className)
{

	// 创建学生班级关系记录
	ClassStudentDO classStudent;
	UuidFacade uf;
	classStudent.setId(uf.genUuid());
	classStudent.setClassId(className);
	classStudent.setStudentId(studentId);
	classStudent.setAddTime(SimpleDateTimeFormat::format());
	classStudent.setDeleted(0);  // 未删除
	classStudent.setReason(0);    // 默认原因

	// 设置创建人
	// 这里需要获取当前登录用户信息

	// 保存到数据库
	// 这里需要实现ClassStudentDAO的插入方法

	return true;  // 暂时返回true，实际需要实现
}

// 删除跟进记录的实现
StringJsonVO::Wrapper ContactRecordService::deleteContactRecord(const DeleteContactRecordDTO::Wrapper& dto)
{
	// 验证参数
	if (!dto || !dto->ids || dto->ids->empty()) {
		auto vo = StringJsonVO::createShared();
		vo->code = 400;
		vo->message = "跟进记录ID不能为空";
		return vo;
	}
	
	// 只允许删除一条记录
	if (dto->ids->size() > 1) {
		auto vo = StringJsonVO::createShared();
		vo->code = 400;
		vo->message = "只允许删除一条跟进记录";
		return vo;
	}
	
	// 执行删除操作
	ContactRecordDAO dao;
	int result = dao.deleteContactRecord(static_cast<uint64_t>(*dto->ids->front()));
	
	// 检查删除结果
	if (result <= 0) {
		auto vo = StringJsonVO::createShared();
		vo->code = 500;
		vo->message = "删除失败";
		return vo;
	}
	
	// 删除成功
	auto vo = StringJsonVO::createShared();
	vo->code = 200;
	vo->message = "删除成功";
	vo->data = "删除了 1 条跟进记录";
	return vo;
}

