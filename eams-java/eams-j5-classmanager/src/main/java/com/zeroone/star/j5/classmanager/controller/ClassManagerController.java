package com.zeroone.star.j5.classmanager.controller;

import com.zeroone.star.project.dto.j5.classmanager.ClassDTO;
import com.zeroone.star.project.dto.j5.classmanager.ClassStudentDTO;
import com.zeroone.star.project.j5.classmanager.ClassStudentApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * 描述：班级管理控制器
 * @author j5-luohan
 *
 */

@RestController
@RequestMapping("j5/classManager")
@Api(tags = "班级管理")
public class ClassManagerController implements ClassStudentApis {
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

    @GetMapping
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
