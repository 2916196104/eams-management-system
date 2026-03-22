#pragma once

#ifndef _GETALLANNOUNCEMENT_VO_
#define _GETALLANNOUNCEMENT_VO_

#include "../../../GlobalInclude.h"
// 引入适配homework表的DTO头文件（路径需根据实际项目调整）
#include "../../../dto/home/announcement/AnnouncementDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 单条作业数据返回VO：适配AnnouncementDTO,获取显示通知公告
class AnnouncementJsonVO : public JsonVO<AnnouncementDTO::Wrapper> {
    DTO_INIT(AnnouncementJsonVO, JsonVO<AnnouncementDTO::Wrapper>)
};

// 作业分页数据返回VO：适配AnnouncementPageDTO，获取所有通知公告(分页)
class AnnouncementPageJsonVO : public JsonVO<AnnouncementPageDTO::Wrapper> {
    DTO_INIT(AnnouncementPageJsonVO, JsonVO<AnnouncementPageDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_GETALLANNOUNCEMENT_VO_