#pragma once
#pragma once
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "ServerInfo.h"
#include "Macros.h"

//引入头文件用来使用架构宏定义-类似stl
#include "ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin ApiController codegen section

class SendPassSMTPControl :public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(SendPassSMTPControl);
public:		//定义接口
	

	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("spsmtp.summary"), SendSMTP1, StringJsonVO::Wrapper, ZH_WORDS_GETTER("credit_mall.tags.t4"), // 单条VO（无分页）
		API_DEF_ADD_QUERY_PARAMS(String, "mail_addr", ZH_WORDS_GETTER("spsmtp.mail"), "13999999999@163.com", true); // id必传，唯一标识
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c5/login/sendpass", SendSMTP1, QUERY(String, mail_addr), execsendSMTPByMail(mail_addr));


private:	 //定义接口执行函数
	StringJsonVO::Wrapper execsendSMTPByMail(const String& mail_addr);
};




#include OATPP_CODEGEN_END(ApiController) ///< End ApiController codegen section