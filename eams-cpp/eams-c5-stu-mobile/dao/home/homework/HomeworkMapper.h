#pragma once

#ifndef _HOMEWORK_MAPPER_
#define _HOMEWORK_MAPPER_
#include "Mapper.h"
#include "../../../domain/do/home/homework/HomeworkDO.h"  // 路径改为HomeworkDO

// 类名改为HomeworkMapper，泛型绑定HomeworkDO
class HomeworkMapper : public Mapper<HomeworkDO>
{
public:
    // 返回值和实例化对象均替换为HomeworkDO，严格按homework表字段顺序映射
    HomeworkDO mapper(ResultSet* resultSet) const override
    {
        HomeworkDO data;  // 实例化作业表DO对象
        // ========== 严格对应homework表字段顺序+类型 ==========
        data.setId(resultSet->getUInt64(1));                // 1. 主键id (bigint unsigned → uint64_t)
        data.setClassId(resultSet->getUInt64(2));           // 2. 班级ID class_id (bigint → uint64_t)
        data.setTitle(resultSet->getString(3));             // 3. 标题 title (varchar(255) → string)
        data.setContent(resultSet->getString(4));           // 4. 内容 content (text → string)
        data.setCreator(resultSet->getUInt64(5));           // 5. 创建人 creator (bigint → uint64_t)
        data.setEditor(resultSet->getUInt64(6));            // 6. 编辑人 editor (bigint → uint64_t)
        data.setAddTime(resultSet->getString(7));           // 7. 添加时间 add_time (datetime → string)
        data.setEditTime(resultSet->getString(8));          // 8. 编辑时间 edit_time (datetime → string)
        data.setDeleted(resultSet->getInt(9));              // 9. 删除标记 deleted (tinyint(1) → int)
        data.setOrgId(resultSet->getUInt64(10));            // 10. 创建者所属组织ID org_id (bigint → uint64_t)

        return data;
    }
};

#endif // !_HOMEWORK_MAPPER_