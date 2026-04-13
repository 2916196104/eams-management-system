package com.zeroone.star.j5.classmanager.controller;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.classmanager.service.ClassService;
import com.zeroone.star.j5.classmanager.service.ClassStudentService;
import com.zeroone.star.project.DO.j5.classmanager.ClassDO;
import com.zeroone.star.project.dto.j5.classmanager.ClassDTO;
import com.zeroone.star.project.dto.j5.classmanager.ClassStudentDTO;
import com.zeroone.star.project.dto.j5.classmanager.TransClassStudentDTO;
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

import javax.annotation.Resource;
import java.util.List;

/**
 * 描述：班级管理控制器
 * @author j5-luohan
 *
 */

@RestController
//@RequestMapping("j5/class-manager")
@RequestMapping("/j5-class-manager")
@Api(tags = "班级管理")
public class ClassManagerController implements ClassStudentApis {
    @Resource
    private ClassStudentService classStudentService;
    @Resource
    private ClassService classService;

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
        IPage<ClassListVO> page = classService.queryClassPage(queryDTO);
        // 设置列表数据（略）
        return JsonVO.success(page);
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
            @ApiImplicitParam(name = "gender", value = "性别 1 男 2 女", dataType = "int", paramType = "form", example = "1"),
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
        ClassDO clazz = classService.getById(classId);
        if (clazz == null) {
            return JsonVO.fail("班级不存在");
        }
        IPage<ClassStudentVO> page = classStudentService.queryClassStudentPage(classId, queryDTO);
        return JsonVO.success(page);
    }

    @PostMapping
    @ApiOperation("保存班级")
    @Override
    public JsonVO<Long> addClass(@RequestBody ClassDTO classDTO) {
        Long addClassCount = classService.saveClass(classDTO);
        return JsonVO.success(addClassCount);
    }

    @DeleteMapping
    @ApiOperation("删除班级")
    @ApiImplicitParam(name = "ids", value = "班级id列表")
    @Override
    public JsonVO<Long> removeClass(@RequestBody List<Long> ids) {
        Long removeClassCount = classService.removeClass(ids);
        return JsonVO.success(removeClassCount);
    }

    @PutMapping
    @ApiOperation("结业班级")
    @ApiImplicitParam(name = "ids", value = "班级已结业")
    @Override
    public JsonVO<Long> endClass(@RequestBody List<Long> ids) {
        Long endClassCount = classService.endClass(ids);
        return JsonVO.success(endClassCount);
    }



    @PostMapping("class-student")
    @ApiOperation("添加班级学员，支持批量添加")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "studentIds", value = "待添加学员ID列表", required = true, example = "1,2,3", dataType = "List<Integer>"),
            @ApiImplicitParam(name = "classId", value = "班级ID", required = true, example = "1", dataType = "int")
    })
    @Override
    public JsonVO<Integer> addClassStudent(@RequestBody ClassStudentDTO classStudentDTO) {
        Integer addClassStudentNum = classStudentService.addClassStudent(classStudentDTO.getStudentIds(), classStudentDTO.getClassId());
        return JsonVO.success(addClassStudentNum);
    }

    @DeleteMapping("class-student")
    @ApiOperation("删除班级学员，支持批量删除")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "studentIds", value = "待删除学员ID列表", required = true, example = "1,2,3", dataType = "List<Integer>"),
            @ApiImplicitParam(name = "classId", value = "班级ID", required = true, example = "1", dataType = "int")
    })
    @Override
    public JsonVO<Integer> removeClassStudent(@RequestBody ClassStudentDTO classStudentDTO) {
        Integer deleteClassStudentNum = classStudentService.batchDeleteClassStudent(classStudentDTO.getStudentIds(), classStudentDTO.getClassId());
        return JsonVO.success(deleteClassStudentNum);
    }

    @PutMapping("/class-student")
    @Override
    @ApiOperation("批量调班，将多个学员从一个班级调到另一个班级")
    public JsonVO<Integer> transferClassBatch(@RequestBody TransClassStudentDTO transClassStudentDTO) {
        Integer transferClassBatchNum = classStudentService.batchTransClassStudents
                (transClassStudentDTO.getStudentIds(),transClassStudentDTO.getClassId(), transClassStudentDTO.getTargetClassId());
        return JsonVO.success(transferClassBatchNum);
    }

}
