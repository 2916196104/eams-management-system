#pragma once
#include "DoInclude.h"

class GradeDO : public BaseDO
{
    // ========== 数据库字段定义（智能指针+get/set方法） ==========
    MYSQL_SYNTHESIZE(string, name, Name);

public:
    /**
     * 构造函数
     * 参数：数据库表名（替换为实际表名）
     */
    GradeDO() : BaseDO("class_grade")
    {
        // ========== 绑定数据库字段与DO成员变量 ==========
        // 主键字段（id）
        //MYSQL_ADD_FIELD_PK("id", "ll", id);
        // 普通字段
        MYSQL_ADD_FIELD("name", "s", name);   
        
    }
};