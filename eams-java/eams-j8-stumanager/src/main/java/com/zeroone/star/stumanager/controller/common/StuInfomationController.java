package com.zeroone.star.stumanager.controller.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j8.stumanager.common.StuInformationApis;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.query.j8.stumanager.common.StudentListQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * 学员信息
 */
@Api(tags = "共用接口-学员信息")
@RequestMapping("/common/student")
@RestController
public class StuInfomationController implements StuInformationApis {
    @Override
    public JsonVO<Void> saveStudent() {
        return null;
    }

    @Override
    public JsonVO<Void> setStudentStage() {
        return null;
    }

    @Override
    public JsonVO<Void> enrollCourse() {
        return null;
    }
    @GetMapping("/query-studentlist")
    @ApiOperation(value = "获取学员列表")
    @Override
    public JsonVO<PageDTO<StudentListVO>> queryStudents(StudentListQuery query) {
        return null;
    }
    @GetMapping("/query-listByCourse")
    @ApiOperation(value = "获取学员课程数据列表")
    @Override
    public JsonVO<PageDTO<StudentCourseVO>> queryStudentsByCourse(StudentCourseQuery condition) {
        return null;
    }
}
