package com.zeroone.star.classes.controller;


import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.Do.j5.classes.student.Student;
import com.zeroone.star.project.j5.classes.ClassApis;
import com.zeroone.star.project.query.j5.classes.ClassPageQuery;
import com.zeroone.star.project.query.j5.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.classes.ClassDetailVO;
import com.zeroone.star.project.vo.j5.student.StudentVo;
import io.swagger.annotations.*;
import org.springframework.web.bind.annotation.*;

/**
 * <p>
 * 班级 前端控制器
 * </p>
 *
 * @author 阿伟
 * @since 2026-03-19
 */
@RestController
@RequestMapping("/j5/class")
@Api(tags = "班级管理")
public class ClassController implements ClassApis {
    @PostMapping("/page")
    @ApiOperation(value = "条件分页查询班级（支持按名称模糊查询）",
            notes = "根据班级名称、课程名称、班主任姓名、教室名称、年级名称进行分页查询，每页默认30条")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "className", value = "班级名称（模糊匹配）", dataType = "string", paramType = "form", example = "三年二班"),
            @ApiImplicitParam(name = "courseName", value = "课程名称（模糊匹配）", dataType = "string", paramType = "form", example = "数学"),
            @ApiImplicitParam(name = "teacherName", value = "班主任姓名（模糊匹配）", dataType = "string", paramType = "form", example = "张老师"),
            @ApiImplicitParam(name = "classroomName", value = "教室名称（模糊匹配）", dataType = "string", paramType = "form", example = "A101"),
            @ApiImplicitParam(name = "gradeName", value = "年级名称（模糊匹配）", dataType = "string", paramType = "form", example = "三年级"),
            @ApiImplicitParam(name = "pageNum", value = "当前页码", dataType = "int", paramType = "form", example = "1", defaultValue = "1"),
            @ApiImplicitParam(name = "pageSize", value = "每页条数", dataType = "int", paramType = "form", example = "30", defaultValue = "30")
    })
    @ApiResponses({
            @ApiResponse(code = 200, message = "OK", response = JsonVO.class),
            @ApiResponse(code = 401, message = "Unauthorized"),
            @ApiResponse(code = 403, message = "Forbidden"),
            @ApiResponse(code = 404, message = "Not Found")
    })
    @Override
    public JsonVO<Page<ClassDetailVO>> pageClass(
            @ModelAttribute ClassPageQuery queryDTO
    ) {
        // 实际业务中需调用 service 进行关联查询，此处模拟返回
        Page<ClassDetailVO> pageInfo = new Page<>();
        pageInfo.setTotal(58L);
        // 设置列表数据（略）
        return JsonVO.success(pageInfo);
    }

    // ... 已有的 pageQuery 方法 ...

    // ================== 新增接口 ==================

    /**
     * 获取班级详情
     */
    @GetMapping("/{id}")
    @ApiOperation(value = "获取班级详情", notes = "根据班级ID查询班级详细信息，包括关联的课程、教室、班主任、年级名称")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "id", value = "班级ID", required = true, dataType = "long", paramType = "path", example = "1")
    })
    @ApiResponses({
            @ApiResponse(code = 200, message = "OK", response = JsonVO.class),
            @ApiResponse(code = 404, message = "班级不存在")
    })
    @Override
    public JsonVO<ClassDetailVO> getClassDetail(
            @PathVariable("id") Long id
    ) {
        // 实际业务中调用 service 查询班级详情并组装关联名称
        // 此处模拟返回
        ClassDetailVO detail = new ClassDetailVO();
        detail.setId(id);
        detail.setName("三年二班");
        detail.setCourseId(5L);
        detail.setCourseName("数学");
        detail.setClassroomId(10L);
        detail.setClassroomName("A101");
        detail.setTeacherId(3L);
        detail.setTeacherName("张老师");
        detail.setGradeId(2);
        detail.setGradeName("三年级");
        // ... 其他字段
        return JsonVO.success(detail);
    }

    /**
     * 分页查询班级学员列表
     */
    @PostMapping("/{classId}/student/page")
    @ApiOperation(value = "分页查询班级学员", notes = "根据班级ID查询学员列表，支持按学员姓名、学号、性别条件分页查询")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "classId", value = "班级ID", required = true, dataType = "long", paramType = "path", example = "1"),
            @ApiImplicitParam(name = "studentName", value = "学员姓名（模糊匹配）", dataType = "string", paramType = "form", example = "张"),
            @ApiImplicitParam(name = "studentNo", value = "学号（模糊匹配）", dataType = "string", paramType = "form", example = "2023"),
            @ApiImplicitParam(name = "gender", value = "性别 1男 2女", dataType = "int", paramType = "form", example = "1"),
            @ApiImplicitParam(name = "pageNum", value = "当前页码", dataType = "int", paramType = "form", example = "1", defaultValue = "1"),
            @ApiImplicitParam(name = "pageSize", value = "每页条数", dataType = "int", paramType = "form", example = "30", defaultValue = "30")
    })
    @ApiResponses({
            @ApiResponse(code = 200, message = "OK", response = JsonVO.class),
            @ApiResponse(code = 404, message = "班级不存在")
    })
    @Override
    public JsonVO<Page<StudentVo>> pageStudent(
            @PathVariable("classId") Long classId,
            @ModelAttribute StudentQuery queryDTO
    ) {
        // 实际业务中需根据 classId 和 queryDTO 条件查询学员
        // 模拟返回
        Page<StudentVo> pageInfo = new Page<>();
        pageInfo.setTotal(30L);
        // 设置学员列表（略）
        return JsonVO.success(pageInfo);
    }
}


