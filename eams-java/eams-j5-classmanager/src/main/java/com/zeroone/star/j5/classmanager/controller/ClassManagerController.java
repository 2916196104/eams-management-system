package com.zeroone.star.j5.classmanager.controller;

import com.zeroone.star.project.dto.j5.classmanager.ClassStudentDTO;
import com.zeroone.star.project.j5.classmanager.ClassStudentApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

/**
 * 描述：班级管理控制器
 * @author j5-luohan
 *
 */

@RestController("j5/classManager/classStudent")
@Api(tags = "班级管理")
public class ClassManagerController implements ClassStudentApis {


    @PostMapping
    @ApiOperation("添加班级学员，支持批量添加")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "studentIds", value = "待添加学员ID列表", required = true, example = "1,2,3", dataType = "List<Integer>"),
            @ApiImplicitParam(name = "classId", value = "班级ID", required = true, example = "1", dataType = "int")
    })
    @Override
    public JsonVO<Integer> addClassStudent(List<Integer> studentIds, int classId) {
        return null;
    }

    @DeleteMapping
    @ApiOperation("删除班级学员，支持批量删除")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "studentIds", value = "待删除学员ID列表", required = true, example = "1,2,3", dataType = "List<Integer>"),
            @ApiImplicitParam(name = "classId", value = "班级ID", required = true, example = "1", dataType = "int")
    })
    @Override
    public JsonVO<Integer> removeClassStudent(List<Integer> studentIds, int classId) {
        return null;
    }

    @PutMapping
    @Override
    @ApiOperation("批量调班，将多个学员从一个班级调到另一个班级")
    public JsonVO<Integer> transferClassBatch(List<ClassStudentDTO> classStudentDTOs, int targetClassId) {
        return null;
    }
}
