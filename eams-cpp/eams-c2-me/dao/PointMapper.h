#pragma once
#include "Mapper.h"
#include "../domain/do/PointDO.h"

/**
 * 示例表字段匹配映射
 */
class PointMapper : public Mapper<PointDO>
{
public:
	PointDO mapper(ResultSet* resultSet) const override
	{
		PointDO data;
        data.setId(resultSet->getInt(1));
        // 2. 学生ID (BIGINT → long long)
        data.setStudentId(resultSet->getInt(2));
        // 3. 用户ID (BIGINT → long long)
        data.setUserId(resultSet->getInt(3));
        // 4. 本次变动积分 (INT → int)
        data.setCredit(resultSet->getInt(4));
        // 5. 变动后剩余积分 (INT → int)
        data.setCurrentCredit(resultSet->getInt(5));
        // 6. 变动类型 (TINYINT → int)
        data.setChangeType(resultSet->getInt(6));
        // 7. 变动时间 (DATETIME → string，直接取格式化字符串)
        data.setAddTime(resultSet->getString(7));
        // 8. 变动备注 (VARCHAR → string)
        data.setRemark(resultSet->getString(8));
        // 9. 来源ID (BIGINT → long long)
        data.setSourceId(resultSet->getInt(9));
        // 10. 操作员工ID (BIGINT → long long)
        data.setStaffId(resultSet->getInt(10));
        // 11. 学校ID (BIGINT → long long)
        data.setSchoolId(resultSet->getInt(11));
		return data;
	}
};