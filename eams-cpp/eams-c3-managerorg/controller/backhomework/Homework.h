#pragma once

#ifndef __HOMEWORK_H__
#define __HOMEWORK_H__

#include "domain/GlobalInclude.h"
#include "ApiHelper.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/backhomework/backhomeworkDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("Homework.backhomework")

/*作业控制器（处理老师布置的作业主数据操作）*/
class Homework : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(Homework);
public:     // 定义接口：
    // 删除作业
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("Homework.delHomework"), DeleteHomework,ListJsonVO<String>::Wrapper,API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_DEL,"/c3/org/backhomework/Homework", DeleteHomework,BODY_DTO(DeleteHomework::Wrapper, dto), executeDelHomework(dto));

private:    // 定义接口执行函数
    // 删除作业
    ListJsonVO<String>::Wrapper executeDelHomework(const DeleteHomework::Wrapper& dto);
};

#include OATPP_CODEGEN_END(ApiController)

#endif /*__HOMEWORK_H__*/