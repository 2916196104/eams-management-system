#include "stdafx.h"
// 引入作业控制器头文件（匹配类名）
#include "HomeworkController.h"
// 引入作业服务层头文件（路径需根据项目实际结构调整）
#include "../../../service/home/homework/HomeworkService.h"

/**
 * @brief 执行作业列表查询逻辑
 * @param query 作业查询参数（含分页+class_id/deleted等条件）
 * @return HomeworkPageJsonVO::Wrapper 作业分页结果VO（封装JSON响应）
 */
HomeworkPageJsonVO::Wrapper HomeworkController::executeQueryHomework(const HomeworkQuery::Wrapper& query)
{
    // 1. 实例化作业服务类，调用分页查询方法
    HomeworkService homeworkService;
    HomeworkPageDTO::Wrapper pageResult = homeworkService.listAll(query);

    // 2. 实例化分页VO对象（用于封装最终JSON响应）
    HomeworkPageJsonVO::Wrapper resultVO = HomeworkPageJsonVO::createShared();

    // 3. 封装成功响应（包含作业表分页数据，遵循项目统一响应规范）
    resultVO->success(pageResult);

    // 4. 返回封装后的VO（自动序列化为JSON）
    return resultVO;
}