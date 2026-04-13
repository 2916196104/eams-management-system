package com.zeroone.star.j5.studentleave.controller;

import com.zeroone.star.j5.studentleave.service.IStudentLeaveService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.studentleave.StudentLeaveListDTO;
import com.zeroone.star.project.j5.studentleave.StudentLeaveApis;
import com.zeroone.star.project.query.j5.studentleave.StudentLeaveQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
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
@RequestMapping("/j5-student-leave")
@EnableDiscoveryClient
@Api(tags = "学生请假管理")
public class StudentLeaveController implements StudentLeaveApis {

    @Autowired
    private IStudentLeaveService studentLeaveService;

    @Override
    @ApiOperation("撤销请假")
    @PutMapping("cancel")
    public JsonVO<Integer> cancelLeaveRequest(@RequestBody List<Long> ids) {
        return studentLeaveService.cancelLeaveRequest(ids);
    }

    @Override
    @ApiOperation("获取请假列表 （条件+分页）")
    @GetMapping("list")
    public JsonVO<PageDTO<StudentLeaveListDTO>> queryStudentLeaveList(StudentLeaveQuery studentLeaveQuery) {
        return JsonVO.success(studentLeaveService.listStudentLeave(studentLeaveQuery));
    }
}
