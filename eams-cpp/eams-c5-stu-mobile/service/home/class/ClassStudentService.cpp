#include "stdafx.h"
#include "ClassStudentService.h"       
#include "../../../dao/home/class/ClassStudentDAO.h"  
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
#include <stdexcept>   // 异常处理头文件
#include <iostream>    // 日志输出头文件

// 方法适配：返回值/参数替换为ClassStudent相关，字段映射仅保留class_student表字段
ClassStudentPageDTO::Wrapper ClassStudentService::listAll(const ClassStudentQuery::Wrapper& query)
{
    // 1. 防护：query为空时返回默认空分页对象，避免空指针
    if (!query) {
        auto emptyPages = ClassStudentPageDTO::createShared();
        emptyPages->pageIndex = 1;  // 无参数时默认页码1
        emptyPages->pageSize = 10;  // 无参数时默认页大小10

        return emptyPages;
    }

    // 2. 构建返回对象，防护分页对象创建失败
    auto pages = ClassStudentPageDTO::createShared();
    if (!pages) {
        throw std::runtime_error("创建ClassStudentPageDTO分页对象失败（内存不足/初始化异常）");
    }
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;


    // 3. 查询数据总条数，捕获DAO层异常
    ClassStudentDAO dao;
    uint64_t count = 0;
    try {
        count = dao.count(query);
    }
    catch (const std::exception& e) {
        std::cerr << "【ClassStudentService】查询总条数异常：" << e.what() << std::endl;
        return pages;  // 异常时返回空分页
    }

    // 4. 无数据时直接返回空分页
    if (count <= 0) {
        return pages;
    }

    // 5. 填充分页总数并计算总页数
    pages->total = count;
    pages->calcPages();

    // 6. 分页查询数据，捕获查询异常
    std::list<ClassStudentDO> result;
    try {
        result = dao.selectWithPage(query);
    }
    catch (const std::exception& e) {
        std::cerr << "【ClassStudentService】分页查询数据异常：" << e.what() << std::endl;
        return pages;
    }

    // 7. 防护：总条数>0但分页结果为空（分页参数越界/数据不一致）
    if (result.empty()) {
        std::cout << "【ClassStudentService】警告：总条数=" << count << "，但分页查询结果为空（分页参数越界？）" << std::endl;
        return pages;
    }

    // 8. 遍历DO列表，转换为DTO（仅映射class_student表的核心字段）
    for (ClassStudentDO& sub : result)
    {
        // 8.1 空值校验：核心字段为空时跳过，避免DTO赋值异常（示例：student_id为空）
        if (sub.getStudentId() <= 0) {  // 假设student_id是数值类型，根据实际类型调整
            std::cout << "【ClassStudentService】警告：发现学生ID为空的记录，跳过该条数据（ID=" << sub.getId() << "）" << std::endl;
            continue;
        }

        // 8.2 防护：DTO对象创建失败
        auto dto = ClassStudentDTO::createShared();
        if (!dto) {
            std::cerr << "【ClassStudentService】警告：创建ClassStudentDTO对象失败，跳过该条数据（ID=" << sub.getId() << "）" << std::endl;
            continue;  // 跳过单条失败数据，不影响整体查询
        }

        // 8.3 核心：仅保留class_student表的字段映射，删除所有无关字段
  // 8.3 核心：逐条映射class_student表的字段（拆分后更易调试）
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id);                  // 主键ID
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, class_id, ClassId);       // 班级ID（对应DO的classId）
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, student_id, StudentId);   // 学生ID（对应DO的studentId）
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, add_time, AddTime);       // 添加时间
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, creator, Creator);        // 创建人
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, reason, Reason);          // 加入原因
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, deleted, Deleted);        // 删除标记
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, remark, Remark);          // 备注信息
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, consume_course_id, ConsumeCourseId);  // 默认消费课程ID

        // 8.4 添加DTO到分页对象
        pages->addData(dto);
    }

    return pages;
}