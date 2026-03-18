#include "stdafx.h"
#include "HomeworkService.h"       // 替换为HomeworkService头文件
#include "../../../dao/home/homework/HomeworkDAO.h"  // 替换为HomeworkDAO头文件
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

// 方法适配：返回值/参数替换为Homework相关，字段映射严格匹配homework表所有字段
HomeworkPageDTO::Wrapper HomeworkService::listAll(const HomeworkQuery::Wrapper& query)
{
    auto pages = HomeworkPageDTO::createShared();
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    HomeworkDAO dao;  // 替换为HomeworkDAO（操作作业表）
    uint64_t count = dao.count(query);
    if (count <= 0)
    {
        return pages;
    }

    pages->total = count;
    pages->calcPages();
    list<HomeworkDO> result = dao.selectWithPage(query);  // 替换为HomeworkDO（作业表DO）

    // 遍历作业DO列表，转换为DTO（严格映射homework表所有字段，无冗余/缺失）
    for (HomeworkDO& sub : result)
    {
        auto dto = HomeworkDTO::createShared();  // 替换为HomeworkDTO（作业表DTO）
        // 核心：按homework表字段顺序映射，匹配数据库规范
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
            id, Id,                  // 1. 主键ID（bigint unsigned）
            class_id, ClassId,       // 2. 班级ID（bigint，NOT NULL）
            title, Title,            // 3. 标题（varchar(255)，NOT NULL）
            content, Content,        // 4. 内容（text，NOT NULL）
            creator, Creator,        // 5. 创建人（bigint）
            editor, Editor,          // 6. 编辑人（bigint）
            add_time, AddTime,       // 7. 添加时间（datetime）
            edit_time, EditTime,     // 8. 编辑时间（datetime）
            deleted, Deleted,        // 9. 删除标记（tinyint(1)）
            org_id, OrgId            // 10. 创建者所属组织ID（bigint）
        );
        pages->addData(dto);
    }
    return pages;
}