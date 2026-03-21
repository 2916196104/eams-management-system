#pragma once  // 防止头文件重复包含（编译器级别的保护）
/*
 * 学生信息查询/新增数据传输对象（DTO）头文件
 * 功能适配：
 *  1. 获取学生信息：作为查询条件的封装（支持分页+多字段筛选）
 *  2. 新增学生信息：作为前端参数的接收载体（PUSH新增数据）
 *  新手备注：DTO的核心作用是统一Controller和Service之间的参数传递格式，
 *            OATPP框架会自动完成HTTP参数/JSON与DTO对象的互转
 */
#ifndef _STUDENTQUERY_H_  // 传统头文件保护宏（兼容旧编译器）
#define _STUDENTQUERY_H_

 // 引入全局通用头文件（包含OATPP基础类型、宏定义等）
#include "../../GlobalInclude.h"
// 引入分页查询基础类（自动包含pageIndex/页码、pageSize/每页条数字段）
#include "domain/query/PageQuery.h"

// 启动OATPP的DTO代码生成器（必需：自动生成序列化/反序列化代码）
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 学生信息查询/新增DTO类
 * 继承PageQuery：自动拥有分页能力（无需重复定义pageIndex/pageSize）
 * 字段设计：完全对齐student数据库表的字段，兼顾"查询条件"和"新增参数"场景
 */
class StudentQuery : public PageQuery
{
    // 初始化DTO（关联当前类和父类PageQuery，OATPP框架核心宏）
    // 新手备注：这行必须写在类内第一行，否则框架无法识别DTO
    DTO_INIT(StudentQuery, PageQuery);

    /************************ 核心字段定义（对齐student数据库表） ************************/
    /**
     * 学生主键ID
     * 类型：UInt64 → 对应MySQL的bigint UNSIGNED
     * 场景1（查询）：根据ID精准查询单个学生
     * 场景2（新增）：数据库自增，新增时可传空（默认值nullptr）
     */
    API_DTO_FIELD_DEFAULT(UInt64, id, "学生主键ID", false, nullptr);

    /**
     * 家长ID
     * 类型：UInt64 → 对应MySQL的bigint
     * 场景1（查询）：筛选指定家长下的所有学生
     * 场景2（新增）：指定学生所属的家长
     */
    API_DTO_FIELD_DEFAULT(UInt64, userId, "家长ID", false, nullptr);

    /**
     * 家庭关系（如父子/母子等）
     * 类型：Int32 → 对应MySQL的tinyint
     * 默认值：0（对齐数据库默认值）
     * 场景1（查询）：筛选指定家庭关系的学生
     * 场景2（新增）：设置学生与家长的关系
     */
    API_DTO_FIELD_DEFAULT(Int32, familyRel, "家庭关系", false, 0);

    /**
     * 是否为家长默认查看的学员
     * 类型：Bool → 对应MySQL的tinyint(1)
     * 默认值：true（对应数据库的1）
     * 场景1（查询）：筛选家长默认/非默认查看的学生
     * 场景2（新增）：设置是否为家长默认查看的学员
     */
    API_DTO_FIELD_DEFAULT(Bool, asDefault, "是否家长默认查看的学员", false, true);

    /**
     * 所属分校ID
     * 类型：UInt64 → 对应MySQL的bigint
     * 场景1（查询）：筛选指定分校的学生
     * 场景2（新增）：指定学生所属的分校
     */
    API_DTO_FIELD_DEFAULT(UInt64, schoolId, "所属分校ID", false, nullptr);

    /**
     * 学生姓名（必填）
     * 类型：String → 对应MySQL的varchar(20)
     * 场景1（查询）：模糊查询姓名包含指定字符的学生（如LIKE '%张三%'）
     * 场景2（新增）：设置学生姓名（数据库NOT NULL，新增时必须传值）
     */
    API_DTO_FIELD_DEFAULT(String, name, "学生姓名", false, nullptr);

    /**
     * 逻辑删除标记
     * 类型：Int32 → 对应MySQL的int
     * 默认值：0（0=未删除，非0=已删除）
     * 场景1（查询）：仅查询未删除的学生（deleted=0）
     * 场景2（新增）：默认新增未删除的学生
     */
    API_DTO_FIELD_DEFAULT(Int32, deleted, "逻辑删除标记", false, 0);

    /**
     * 阶段状态（0=意向学员）
     * 类型：Int32 → 对应MySQL的tinyint
     * 场景1（查询）：筛选指定阶段的学生（如仅查意向学员stage=0）
     * 场景2（新增）：设置学生的阶段状态
     */
    API_DTO_FIELD_DEFAULT(Int32, stage, "阶段状态（0=意向学员）", false, nullptr);

    /**
     * 性别
     * 类型：Int32 → 对应MySQL的tinyint
     * 默认值：0（可自定义：0=男，1=女，2=未知）
     * 场景1（查询）：筛选指定性别的学生
     * 场景2（新增）：设置学生性别
     */
    API_DTO_FIELD_DEFAULT(Int32, gender, "性别（0=男，1=女）", false, 0);

    /**
     * 生日
     * 类型：Date → 对应MySQL的date
     * 场景1（查询）：筛选指定生日/生日范围的学生
     * 场景2（新增）：设置学生生日
     */
    API_DTO_FIELD_DEFAULT(Date, birthday, "生日", false, nullptr);

    /**
     * 头像地址
     * 类型：String → 对应MySQL的varchar(255)
     * 场景1（查询）：筛选指定头像的学生（极少用）
     * 场景2（新增）：设置学生头像的URL地址
     */
    API_DTO_FIELD_DEFAULT(String, headImg, "头像地址", false, nullptr);

    /**
     * 学生积分
     * 类型：Int32 → 对应MySQL的int
     * 默认值：0（对齐数据库默认值）
     * 场景1（查询）：筛选积分范围的学生（如credit >= 100）
     * 场景2（新增）：设置学生初始积分
     */
    API_DTO_FIELD_DEFAULT(Int32, credit, "学生积分", false, 0);

    /**
     * 身份证号
     * 类型：String → 对应MySQL的varchar(30)
     * 场景1（查询）：根据身份证号精准查询学生
     * 场景2（新增）：设置学生身份证号
     */
    API_DTO_FIELD_DEFAULT(String, idcard, "身份证号", false, nullptr);

    /**
     * 入学日期
     * 类型：Date → 对应MySQL的date
     * 场景1（查询）：筛选指定入学日期的学生
     * 场景2（新增）：设置学生入学日期
     */
    API_DTO_FIELD_DEFAULT(Date, joinDate, "入学日期", false, nullptr);
};

// 结束OATPP的DTO代码生成器
#include OATPP_CODEGEN_END(DTO)

#endif // !_STUDENTQUERY_H_