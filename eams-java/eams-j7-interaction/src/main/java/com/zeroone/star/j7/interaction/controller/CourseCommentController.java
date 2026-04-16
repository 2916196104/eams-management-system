package com.zeroone.star.j7.interaction.controller;

import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import com.zeroone.star.j7.interaction.service.CourseCommentService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.CourseCommentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.interaction.CourseCommentVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;


/**
 * 教师评价学生（教评学）控制器
 * 完全贴合：数据库结构 + 原型图筛选/展示逻辑 + API文档规范（mapper未实现，不影响接口定义）
 */
@Api(tags = "教评学")  // API文档统一分类（教评学）
@RestController
@RequestMapping("/j7-interaction/j7-teacher-student")  // 统一接口路径（教评学模块）
public class CourseCommentController {

    private final CourseCommentService courseCommentService;

    // 构造器注入（Spring最佳实践）
    public CourseCommentController(CourseCommentService courseCommentService) {
        this.courseCommentService = courseCommentService;
    }

    /**
     * 分页查询教师评价学生列表
     * 筛选条件：评价内容（模糊）、课次ID、点评老师ID、学生ID、点评时间区间
     * 分页支持：30/50/100/200条/页（默认30）
     * 展示字段：序号、学员、课次标题、点评得分、点评内容、点评老师、点评时间
     */
    @ApiOperation(value = "获取教师点评列表（条件+分页）",
            notes = "1. 筛选条件：评价内容（模糊匹配）、课次ID、点评老师ID（creator）、学生ID、点评时间区间（add_time）；" +
                    "2. 分页支持：30/50/100/200条/页（默认30）；" +
                    "3. 展示字段：序号、学员姓名、课次标题、点评得分（score）、点评内容（content）、点评老师（关联creator）、点评时间（add_time）；" +
                    "4. orderId/state/editor/editTime/deleted为非展示字段，仅保留数据完整性")
    @ApiOperationSupport(author = "开发人员", order = 2)  // API文档排序（教评学模块第2个接口）
    @GetMapping("/list")  // 统一列表接口路径
    public JsonVO<PageDTO<CourseCommentVO>> pageList(
            @ApiParam(value = "查询条件（分页+筛选），默认页码1，每页30条，支持切换50/100/200条",
                    example = "{\"pageIndex\":1,\"pageSize\":30,\"content\":\"课堂表现\",\"courseId\":1001,\"creator\":2001,\"studentId\":3001,\"addTimeStart\":\"2026-03-01 00:00:00\",\"addTimeEnd\":\"2026-03-31 23:59:59\"}")
            CourseCommentQuery query) {
        // 1. 分页参数兜底（防止null导致Service层报错）
        if (query == null) {
            query = new CourseCommentQuery();
        }
        if (query.getPageIndex() < 1) {
            query.setPageIndex(1L);
        }
        if (query.getPageSize() < 1) {
            query.setPageSize(30L);
        }
        // 2. 调用Service层查询
        PageDTO<CourseCommentVO> pageDTO = courseCommentService.pageList(query);
        // 3. 按项目规范返回JsonVO
        return JsonVO.success(pageDTO);
    }
}