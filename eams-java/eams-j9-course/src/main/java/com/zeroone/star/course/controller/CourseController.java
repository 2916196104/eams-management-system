package com.zeroone.star.course.controller;

import com.zeroone.star.course.service.ICourseService;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.CourseSaveDTO;
import com.zeroone.star.project.j9.course.CourseApis;
import com.zeroone.star.project.query.j9.course.CourseQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.course.CourseDetailVO;
import com.zeroone.star.project.vo.j9.course.CourseExportVO;
import com.zeroone.star.project.vo.j9.course.CourseListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletResponse;
import java.net.URLEncoder;
import java.util.List;

/**
 * 课程管理 Controller
 */
@RestController
@RequestMapping("course")
@Api(tags = "course")
public class CourseController implements CourseApis {

    @Resource
    private ICourseService courseService;

    @Resource
    private EasyExcelComponent easyExcel;

    @ApiOperation("获取课程列表（条件+分页）")
    @GetMapping("list")
    @Override
    public JsonVO<PageDTO<CourseListVO>> queryCourseList(CourseQuery query) {
        return JsonVO.success(courseService.listCourseList(query));
    }

    @ApiOperation("获取课程详情")
    @GetMapping("detail/{id}")
    @Override
    public JsonVO<CourseDetailVO> queryCourseDetail(
            @ApiParam(value = "课程ID", required = true) @PathVariable Long id) {
        return JsonVO.success(courseService.getCourseDetail(id));
    }

    @ApiOperation("保存课程（新增或更新）")
    @PostMapping("save")
    @Override
    public JsonVO<Long> addCourse(@RequestBody CourseSaveDTO dto) {
        Long id = courseService.saveCourse(dto);
        if (id != null) {
            return JsonVO.success(id);
        }
        return JsonVO.fail(null);
    }

    @DeleteMapping
    @ApiOperation("删除课程（支持批量删除）")
    @Override
    public JsonVO<String> removeCourse(
            @ApiParam(value = "课程ID列表", required = true)
            @RequestBody List<Long> ids) {
        int affectRows = courseService.removeBatch(ids);
        if(affectRows > 0) {
            return JsonVO.success("删除成功");
        }
        return JsonVO.fail("删除失败");
    }

    @PutMapping("enable-disable")
    @ApiOperation("启/禁用课程（支持批量）")
    @Override
    public JsonVO<String> modifyCourseState(
            @ApiParam(value = "课程ID列表", required = true) @RequestBody List<Long> ids,
            @ApiParam(value = "状态：0禁用 1启用", required = true) @RequestParam Integer state) {
        boolean result = courseService.updateCourseState(ids, state);
        return result ? JsonVO.success("操作成功") : JsonVO.fail("操作失败");
    }

    @GetMapping("export")
    @ApiOperation("导出课程")
    @Override
    public void exportCourse(CourseQuery query, HttpServletResponse response) throws Exception {
        response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
        response.setCharacterEncoding("utf-8");
        String fileName = URLEncoder.encode("课程列表", "UTF-8").replaceAll("\\+", "%20");
        response.setHeader("Content-Disposition", "attachment;filename=" + fileName + ".xlsx");
        List<CourseExportVO> dataList = courseService.listExportData(query);
        easyExcel.export("课程列表", response.getOutputStream(), CourseExportVO.class, dataList);
    }
}
