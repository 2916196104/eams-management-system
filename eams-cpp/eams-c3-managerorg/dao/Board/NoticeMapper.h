#ifndef _NOTICE_MAPPER_
#define _NOTICE_MAPPER_

#include "Mapper.h"
#include "../../domain/do/Board/NoticeDO.h"

/**
 * 通知设置表字段匹配映射
 */
class NoticeMapper : public Mapper<NoticeDO>
{
public:
	NoticeDO mapper(ResultSet* resultSet) const override
	{
		NoticeDO data;
		data.setId(resultSet->getInt(1));                // id
		data.setName(resultSet->getString(2));           // name
		data.setCode(resultSet->getString(3));           // code
		data.setEnabled(resultSet->getInt(4));           // enabled
		data.setWxTemplateId(resultSet->getString(5));   // wx_template_id
		data.setSmsEnabled(resultSet->getInt(6));        // sms_enabled
		data.setSmsTemplate(resultSet->getString(7));    // sms_template
		data.setForceEnable(resultSet->getInt(8));       // force_enable
		data.setDescription(resultSet->getString(9));    // description
		data.setSort(resultSet->getInt(10));             // sort
		data.setReceiverType(resultSet->getString(11));  // receiver_type
		data.setWxTemplateDesc(resultSet->getString(12)); // wx_template_desc
		return data;
	}
};

/**
 * 通知设置表字段匹配映射 - 创建智能指针对象
 */
class PtrNoticeMapper : public Mapper<PtrNoticeSettingDO>
{
public:
	PtrNoticeSettingDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<NoticeDO>();
		data->setId(resultSet->getInt(1));                // id
		data->setName(resultSet->getString(2));           // name
		data->setCode(resultSet->getString(3));           // code
		data->setEnabled(resultSet->getInt(4));           // enabled
		data->setWxTemplateId(resultSet->getString(5));   // wx_template_id
		data->setSmsEnabled(resultSet->getInt(6));        // sms_enabled
		data->setSmsTemplate(resultSet->getString(7));    // sms_template
		data->setForceEnable(resultSet->getInt(8));       // force_enable
		data->setDescription(resultSet->getString(9));    // description
		data->setSort(resultSet->getInt(10));             // sort
		data->setReceiverType(resultSet->getString(11));  // receiver_type
		data->setWxTemplateDesc(resultSet->getString(12)); // wx_template_desc
		return data;
	}
};

#endif // !_NOTICE_MAPPER_