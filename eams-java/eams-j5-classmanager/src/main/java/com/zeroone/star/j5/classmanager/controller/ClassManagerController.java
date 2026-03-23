package com.zeroone.star.j5.classmanager.controller;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j5.classmanager.ClassDTO;
import com.zeroone.star.project.dto.j5.classmanager.ClassStudentDTO;
import com.zeroone.star.project.j5.classmanager.ClassStudentApis;
import com.zeroone.star.project.query.j5.classmanager.ClassOptionsQuery;
import com.zeroone.star.project.query.j5.classmanager.ClassPageQuery;
import com.zeroone.star.project.query.j5.classmanager.ClassStudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassOptionsVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassStudentVO;
import io.swagger.annotations.*;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * 描述：班级管理控制器
 * @author j5-luohan
 *
 */

@RestController
@RequestMapping("j5/class-manager")
@Api(tags = "班级管理")
public class ClassManagerController implements ClassStudentApis {
    @GetMapping("/class-options")
    @ApiOperation(value = "获取班级下拉选项", notes = "获取所有班级的下拉选项，用于表单选择")
    public JsonVO<Page<ClassOptionsVO>> queryClassOptions(ClassOptionsQuery classOptionsQuery) {
        // 实际业务中调用 service 获取班级下拉选项
        return JsonVO.success(null);
    }



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
    public JsonVO<Page<ClassListVO>> queryClassByPage(
            @ModelAttribute ClassPageQuery queryDTO
    ) {
        // 实际业务中需调用 service 进行关联查询，此处模拟返回
        Page<ClassListVO> pageInfo = new Page<>();
        pageInfo.setTotal(58L);
        // 设置列表数据（略）
        return JsonVO.success(pageInfo);
    }

    // ... 已有的 pageQuery 方法 ...

    // ================== 新增接口 ==================

    /**
     * 获取班级详情
     */
    @GetMapping("/class-detail/{id}")
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
        // 实际业务中调用 service 查询班级详情并组装关联名称
        // 此处模拟返回
        ClassListVO detail = new ClassListVO();
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
            @ApiImplicitParam(name = "gender", value = "性别 1 男 2 女", dataType = "int", paramType = "form", example = "1"),
            @ApiImplicitParam(name = "pageNum", value = "当前页码", dataType = "int", paramType = "form", example = "1", defaultValue = "1"),
            @ApiImplicitParam(name = "pageSize", value = "每页条数", dataType = "int", paramType = "form", example = "30", defaultValue = "30")
    })
    @ApiResponses({
            @ApiResponse(code = 200, message = "OK", response = JsonVO.class),
            @ApiResponse(code = 404, message = "班级不存在")
    })
    @Override
    public JsonVO<Page<ClassStudentVO>> pageStudent(
            @PathVariable("classId") Long classId,
            @ModelAttribute ClassStudentQuery queryDTO
    ) {
        // 实际业务中需根据 classId 和 queryDTO 条件查询学员
        // 模拟返回
        Page<ClassStudentVO> pageInfo = new Page<>();
        pageInfo.setTotal(30L);
        // 设置学员列表（略）
        return JsonVO.success(pageInfo);
    }

    @PostMapping
    @ApiOperation("保存班级")
    @Override
    public JsonVO<Long> saveClass(@RequestBody ClassDTO classDTO) {
        return null;
    }

    @DeleteMapping
    @ApiOperation("删除班级")
    @ApiImplicitParam(name = "ids", value = "班级id列表")
    @Override
    public JsonVO<List<Long>> deleteClass(List<Long> ids) {
        return null;
    }

    @PutMapping
    @ApiOperation("结业班级")
    @ApiImplicitParam(name = "ids", value = "班级已结业")
    @Override
    public JsonVO<List<Long>> endClass(List<Long> ids) {
        return null;
    }



    @PostMapping("class-student")
    @ApiOperation("添加班级学员，支持批量添加")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "studentIds", value = "待添加学员ID列表", required = true, example = "1,2,3", dataType = "List<Integer>"),
            @ApiImplicitParam(name = "classId", value = "班级ID", required = true, example = "1", dataType = "int")
    })
    @Override
    public JsonVO<Integer> addClassStudent(List<Integer> studentIds, int classId) {

        return null;
    }

    @DeleteMapping("class-student")
    @ApiOperation("删除班级学员，支持批量删除")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "studentIds", value = "待删除学员ID列表", required = true, example = "1,2,3", dataType = "List<Integer>"),
            @ApiImplicitParam(name = "classId", value = "班级ID", required = true, example = "1", dataType = "int")
    })
    @Override
    public JsonVO<Integer> removeClassStudent(List<Integer> studentIds, int classId) {
        return null;
    }

    @PutMapping("/class-student")
    @Override
    @ApiOperation("批量调班，将多个学员从一个班级调到另一个班级")
    public JsonVO<Integer> transferClassBatch(List<ClassStudentDTO> classStudentDTOs, int targetClassId) {
        return null;
    }

}
