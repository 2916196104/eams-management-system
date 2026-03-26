package com.zeroone.star.classmanager.controller;


import com.baomidou.mybatisplus.core.metadata.IPage;
import com.zeroone.star.classmanager.service.ClassStudentService;
import com.zeroone.star.classmanager.service.IClassService;
import com.zeroone.star.project.Do.j5.classmanager.ClassDO;
import com.zeroone.star.project.j5.classmanger.ClassStudentApis;
import com.zeroone.star.project.query.j5.classmanager.ClassPageQuery;
import com.zeroone.star.project.query.j5.classmanager.ClassStudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassStudentVO;
import io.swagger.annotations.*;
import org.springframework.beans.factory.annotation.Autowired;
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
@RequestMapping("/j5/class-manager")
@Api(tags = "班级管理")
public class ClassManagerController implements ClassStudentApis {
    @Autowired
    private IClassService classService;
    @Autowired
    private ClassStudentService classStudentService;
    @PostMapping("/page")
    @ApiOperation(value = "条件分页查询班级（支持按名称模糊查询）",
            notes = "根据班级名称、课程名称、班主任姓名、教室名称、年级名称进行分页查询，每页默认30条")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "className", value = "班级名称（模糊匹配）", dataType = "string", paramType = "form", example = "三年二班"),
            @ApiImplicitParam(name = "courseName", value = "课程名称（模糊匹配）", dataType = "string", paramType = "form", example = "数学"),
            @ApiImplicitParam(name = "teacherName", value = "班主任姓名（模糊匹配）", dataType = "string", paramType = "form", example = "张老师"),
            @ApiImplicitParam(name = "classroomName", value = "教室名称（模糊匹配）", dataType = "string", paramType = "form", example = "A101"),
            @ApiImplicitParam(name = "gradeName", value = "年级名称（模糊匹配）", dataType = "string", paramType = "form", example = "三年级"),
            @ApiImplicitParam(name = "pageIndex", value = "当前页码", dataType = "int", paramType = "form", example = "1", defaultValue = "1"),
            @ApiImplicitParam(name = "pageSize", value = "每页条数", dataType = "int", paramType = "form", example = "30", defaultValue = "30")
    })
    @ApiResponses({
            @ApiResponse(code = 200, message = "OK", response = JsonVO.class),
            @ApiResponse(code = 401, message = "Unauthorized"),
            @ApiResponse(code = 403, message = "Forbidden"),
            @ApiResponse(code = 404, message = "Not Found")
    })
    @Override
    public JsonVO<IPage<ClassListVO>> pageClass(
            @ModelAttribute ClassPageQuery queryDTO
    ) {
        // 实际业务中需调用 service 进行关联查询，此处模拟返回
        IPage<ClassListVO> page = classService.queryClassPage(queryDTO);
        // 设置列表数据（略）
        return JsonVO.success(page);
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
    public JsonVO<ClassListVO> getClassDetail(
            @PathVariable("id") Long id
    ) {
        ClassListVO detail = classService.getClassDetail(id);
        if (detail == null) {
            return JsonVO.fail("班级不存在");
        }
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
            @ApiImplicitParam(name = "gender", value = "性别 1男 2女", dataType = "int", paramType = "form", example = "1"),
            @ApiImplicitParam(name = "pageIndex", value = "当前页码", dataType = "int", paramType = "form", example = "1", defaultValue = "1"),
            @ApiImplicitParam(name = "pageSize", value = "每页条数", dataType = "int", paramType = "form", example = "30", defaultValue = "30")
    })
    @ApiResponses({
            @ApiResponse(code = 200, message = "OK", response = JsonVO.class),
            @ApiResponse(code = 404, message = "班级不存在")
    })
    @Override
    public JsonVO<IPage<ClassStudentVO>> pageStudent(
            @PathVariable("classId") Long classId,
            @ModelAttribute ClassStudentQuery queryDTO
    ) {
        // 可选：检查班级是否存在
        ClassDO clazz = classService.getById(classId);
        if (clazz == null) {
            return JsonVO.fail("班级不存在");
        }
        IPage<ClassStudentVO> page = classStudentService.queryClassStudentPage(classId, queryDTO);
        return JsonVO.success(page);
    }
}


