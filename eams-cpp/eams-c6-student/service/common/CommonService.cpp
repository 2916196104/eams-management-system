
#include "stdafx.h"
#include "CommonService.h"
#include "../../dao/common/CommonDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"



/**
 * 调整积分执行函数
 */
bool AdjustPointsService::updateData(const ModifyPointsDTO::Wrapper& dto)
{
	// 组装DO数据
	//ModifyPointsDO data;
	//ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Name, name, Sex, sex, Age, age, Id, id);
	// 设置修改人
	//data.setUpdateBy(dto->getPayload()->getUsername());
	// 设置修改时间
	//data.setUpdateTime(SimpleDateTimeFormat::format());
	// 执行数据修改
	//ModifyPointsDAO dao;
	//return dao.update(data) == 1;
	return true;
}








/**
 * 示例表数据库操作实现
 */
bool AddFollowUpRecordService::updateData(const AddFollowUpRecordDTO::Wrapper& dto)
{
	// 组装DO数据
	//AddFollowUpRecordDO data;
	//ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Name, name, Sex, sex, Age, age, Id, id);
	// 设置修改人
	//data.setUpdateBy(dto->getPayload()->getUsername());
	// 设置修改时间
	//data.setUpdateTime(SimpleDateTimeFormat::format());
	// 执行数据修改
	//AddFollowUpRecordDAO dao;
	//return dao.update(data) == 1;
	return true;
}
