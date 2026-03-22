#pragma once
#ifndef _NOTICE_DO_H_
#define _NOTICE_DO_H_

#include "../DoInclude.h"

/**
 * 通知设置实体类（对应数据库表：notice）
 */
class NoticeDO : public BaseDO
{
	//ID（主键）
	MYSQL_SYNTHESIZE(int, id, Id);
	//通知名称（如：学员上课提醒）
	MYSQL_SYNTHESIZE(std::string, name, Name);
	//通知编码
	MYSQL_SYNTHESIZE(std::string, code, Code);
	//是否启用（1-启用，0-禁用）
	MYSQL_SYNTHESIZE(int, enabled, Enabled);
	//微信模板ID（公众号消息模板ID）
	MYSQL_SYNTHESIZE(std::string, wxTemplateId, WxTemplateId);
	//是否支持短信（1-支持，0-不支持）
	MYSQL_SYNTHESIZE(int, smsEnabled, SmsEnabled);
	//短信模板内容（当前为"无"）
	MYSQL_SYNTHESIZE(std::string, smsTemplate, SmsTemplate);
	//是否强制开启（1-不可关闭，0-可由用户配置）
	MYSQL_SYNTHESIZE(int, forceEnable, ForceEnable);
	//描述说明
	MYSQL_SYNTHESIZE(std::string, description, Description);
	//排序序号
	MYSQL_SYNTHESIZE(int, sort, Sort);
	//接收人类型（'student' 或 'teacher'）
	MYSQL_SYNTHESIZE(std::string, receiverType, ReceiverType);
	//微信模板说明（含标题、行业、编号）
	MYSQL_SYNTHESIZE(std::string, wxTemplateDesc, WxTemplateDesc);

public:
	NoticeDO() : BaseDO("setting_notice")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("code", "s", code);
		MYSQL_ADD_FIELD("enabled", "i", enabled);
		MYSQL_ADD_FIELD("wx_template_id", "s", wxTemplateId);
		MYSQL_ADD_FIELD("sms_enabled", "i", smsEnabled);
		MYSQL_ADD_FIELD("sms_template", "s", smsTemplate);
		MYSQL_ADD_FIELD("force_enable", "i", forceEnable);
		MYSQL_ADD_FIELD("description", "s", description);
		MYSQL_ADD_FIELD("sort", "i", sort);
		MYSQL_ADD_FIELD("receiver_type", "s", receiverType);
		MYSQL_ADD_FIELD("wx_template_desc", "s", wxTemplateDesc);
	}
};

// 智能指针别名
typedef std::shared_ptr<NoticeDO> PtrNoticeSettingDO;

#endif // !_NOTICE_DO_H_