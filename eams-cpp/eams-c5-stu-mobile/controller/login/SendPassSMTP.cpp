#include "SendPassSMTP.h"
#include "stdafx.h"

#include "Macros.h"
#include "NacosClient.h"
#include "EmailSender.h"

#include "gtest/gtest.h"

//StringJsonVO::Wrapper SendPassSMTPControl::executeSendSMTP(const PageQuery::Wrapper& query)
//{
//	//创建一个响应结果
//	//指针
//	//ZO_CREATE_MAIL_SENDER()
//	auto vo = StringJsonVO::createShared();
//	//传参
//	/*for (auto i : query)
//	{
//
//	}
//	vo->success(ZH_WORDS_GETTER("test.resp"));*/
//	return vo;
//}

StringJsonVO::Wrapper SendPassSMTPControl::execsendSMTPByMail(const String& mail_addr)
{
	auto vo = StringJsonVO::createShared();
	std::string body = ZH_WORDS_GETTER("mail.body2");
	ZO_CREATE_MAIL_SENDER(MAILL);
	MAILL.addRecvEmailAddr(mail_addr, "01星球");
	MAILL.setEmailContent(ZH_WORDS_GETTER("mail.topic"), body);
	auto result = MAILL.send();
	vo->success("resul");
	return vo;
}
