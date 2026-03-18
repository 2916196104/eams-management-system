package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.ClassDTO;
import com.zeroone.star.project.dto.j4.student.ClassStudentDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.ClassQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 描述：学员管理及跟进记录接口实现类
 */
@RestController
@RequestMapping("/j4/student")
@Api(tags = "学员管理")
public class StudentController implements StudentApis {
    @GetMapping("/follow-up/page")
    @ApiOperation("获取跟进记录列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<FollowUpDTO>> queryFollowUpPage(FollowUpQuery condition) {
        // TODO: 调用 Service 层实现业务逻辑
        // 模拟返回，实际需替换为 service.queryFollowUpPage(condition)
        return null;
    }

    @PostMapping("/follow-up")
    @ApiOperation("添加/修改跟进记录")
    @Override
    public JsonVO<Long> saveFollowUp(@RequestBody FollowUpDTO followUpDTO) {
        // TODO: 调用 Service 层实现业务逻辑
        // 如果 followUpDTO.getId() != null 则更新，否则新增
        return null;
    }

    @DeleteMapping("/follow-up/{id}")
    @ApiOperation("删除跟进记录（单个删除）")
    @Override
    public JsonVO<Long> deleteFollowUp(@PathVariable Long id) {
        // TODO: 调用 Service 层实现业务逻辑
        return null;
    }

    @GetMapping("/follow-up/{id}")
    @ApiOperation("获取跟进记录详情")
    @Override
    public JsonVO<FollowUpDTO> getFollowUpDetail(@PathVariable Long id) {
        // TODO: 调用 Service 层实现业务逻辑
        return null;
    }


    @Override
    @GetMapping("/page")
    @ApiOperation("获取班级列表（条件 + 分页）")
    public JsonVO<PageDTO<ClassDTO>> queryClassPage(ClassQuery condition) {
        // TODO: 调用 Service 层实现业务逻辑
        return null;
    }

    @Override
    @PostMapping("/join")
    @ApiOperation("加入班级")
    public JsonVO<Long> joinClass(@RequestBody ClassStudentDTO dto) {
        // TODO: 调用 Service 层实现业务逻辑
        return null;
    }

    @Override
    @DeleteMapping("/quit")
    @ApiOperation("退出班级")
    public JsonVO<List<Long>> quitClass(
            @ApiParam(value = "班级ID", required = true, example = "2008418408985583620") @RequestParam Long classId,
            @ApiParam(value = "学生ID", required = true, example = "2008418408985583617") @RequestParam Long studentId) {
        // TODO: 调用 Service 层
        // 模拟返回删除成功的记录 ID
        return null;
    }
}