#include "stdafx.h"
#include "ClassStudentService.h"       // 替换为ClassStudentService头文件
#include "../../../dao/home/class/ClassStudentDAO.h"  // 替换为ClassStudentDAO头文件
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

// 方法适配：返回值/参数替换为ClassStudent相关，字段映射仅保留class_student表字段
ScheduleTimeablePageDTO::Wrapper ClassStudentService::listAll(const ClassStudentQuery::Wrapper& query)
{
    auto pages = ClassStudentPageDTO::createShared();
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    ClassStudentDAO dao;  // 替换为ClassStudentDAO
    uint64_t count = dao.count(query);
    if (count <= 0)
    {
        return pages;
    }

    pages->total = count;
    pages->calcPages();
    list<ClassStudentDO> result = dao.selectWithPage(query);  // 替换为ClassStudentDO

    // 遍历DO列表，转换为DTO（仅映射class_student表的核心字段）
    for (ClassStudentDO& sub : result)
    {
        auto dto = ClassStudentDTO::createShared();  // 替换为ClassStudentDTO
        // 核心：仅保留class_student表的字段映射，删除所有无关字段
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
            id, Id,                  // 主键ID
            class_id, ClassId,       // 班级ID（对应DO的classId）
            student_id, StudentId,   // 学生ID（对应DO的studentId）
            add_time, AddTime,       // 添加时间
            creator, Creator,        // 创建人
            reason, Reason,          // 加入原因
            deleted, Deleted,        // 删除标记
            remark, Remark,          // 备注信息
            consume_course_id, ConsumeCourseId  // 默认消费课程ID
        );
        pages->addData(dto);
    }
    return pages;
}