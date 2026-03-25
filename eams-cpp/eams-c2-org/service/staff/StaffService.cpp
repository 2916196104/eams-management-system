#include "StaffService.h"
#include "dao/staff/StaffDAO.h"
#include "Macros.h"     // ZO_STAR_DOMAIN_DO_TO_DTO_1宏

StaffDetailDTO::Wrapper StaffService::getStaffDetail(const oatpp::String& id)
{
	// 1. 获取员工主数据
	StaffDAO ud;
	auto data = ud.selectById(id.getValue(""));
	if (!data)
		return nullptr;

	// 2. DO转DTO（映射所有真实存在的字段，保证数据完整）
	auto dto = StaffDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, data,
		// 核心基础字段
		id, Id,
		name, Name,
		idCard, IdCard,
		headImg, HeadImg,
		deleted, Deleted,
		mobile, Mobile,
		wxAccessId, WxAccessId,
		email, Email,
		birthday, Birthday,
		gender, Gender,
		school, School,
		degree, Degree,
		remark, Remark,
		state, State,
		isManager, IsManager,
		hireDate, HireDate,
		fireDate, FireDate,
		intro, Intro,
		// 系统审计字段
		addTime, AddTime,
		editTime, EditTime,
		creator, Creator,
		editor, Editor,
		// 其他字段
		password, Password,
		classFee, ClassFee,
		assistantFee, AssistantFee,
		orgId, OrgId,
		isInner, IsInner);

	return dto;
}

// 批量删除员工（补充的核心删除函数）
bool StaffService::batchDeleteStaff(const oatpp::List<oatpp::String>& ids)
{
	// 1. 空列表校验（避免无效操作）
	if (ids == nullptr || ids->empty()) {
		return false;
	}

	// 2. 转换oatpp::List为DAO层需要的std::list<std::string>
	std::list<std::string> idList;
	for (const auto& id : *ids) {
		// 兼容空ID，避免数据库报错
		if (id != nullptr && !id->empty()) {
			idList.push_back(id.getValue(""));
		}
	}

	// 3. 调用DAO执行批量删除
	StaffDAO dao;
	int deleteCount = dao.batchDeleteByIds(idList);

	// 4. 删除条数>0则返回成功（表示至少有1条数据被删除）
	return deleteCount > 0;
}