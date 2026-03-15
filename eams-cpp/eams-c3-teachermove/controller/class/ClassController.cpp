#include "stdafx.h"
#include "ClassController.h"

/*
 * ClassController 班级列表接口 /classList 查询参数说明：
 *
 * 分页参数（由 API_DEF_ADD_PAGE_PARAMS 定义）：
 *   - pageIndex: 当前页码
 *   - pageSize:  每页条数
 *
 * 业务查询参数（与 ClassQuery 对应）：
 *   - teacher_id: 班级负责人/老师ID，筛选该老师负责的班级
 *   - name:       班级名，支持模糊查询
 *   - course_id:  课程ID，按课程筛选
 *   - school_id:   学校ID，按学校筛选
 *   - org_id:     组织ID，按组织筛选
 *   - be_over:    是否完结，0-未完结，1-已完结
 */