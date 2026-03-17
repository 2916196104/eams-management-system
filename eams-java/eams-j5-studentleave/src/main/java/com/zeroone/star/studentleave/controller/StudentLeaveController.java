package com.zeroone.star.studentleave.controller;

import com.zeroone.star.project.j5.academicaffairs.StudentLeaveApis;
import com.zeroone.star.project.query.j5.academicaffairs.StudentLeaveQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.academicaffairs.StudentLeaveListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 描述：学生请假管理 Controller
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/16 20:00
 */
@RestController
@RequestMapping("/j5/student-leave")
@Api(tags = "学生请假管理")
public class StudentLeaveController implements StudentLeaveApis {

    @Override
    @ApiOperation("撤销请假")
    @PutMapping("cancel")
    public JsonVO<String> cancelLeaveRequest(@RequestBody List<Long> ids) {
        return null;
    }

    @Override
    @ApiOperation("获取请假列表 （条件+分页）")
    @GetMapping("list")
    public JsonVO<List<StudentLeaveListVO>> queryStudentLeaveList(StudentLeaveQuery studentLeaveQuery) {
        return null;
    }
}
