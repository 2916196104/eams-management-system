package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
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
        return null;
    }

    @PostMapping("/follow-up")
    @ApiOperation("添加/修改跟进记录")
    @Override
    public JsonVO<Long> saveFollowUp(@RequestBody FollowUpDTO followUpDTO) {
        // TODO: 调用 Service 层实现业务逻辑
        // 如果 DTO 中有 ID 则更新，无 ID 则新增
        return null;
    }

    @DeleteMapping("/follow-up")
    @ApiOperation("删除跟进记录（支持批量删除）")
    @ApiImplicitParam(name = "ids", value = "跟进记录ID列表", type = "Array", paramType = "body", required = true, example = "[\"1\",\"2\"]")
    @Override
    public JsonVO<List<Long>> deleteFollowUp(@RequestBody List<Long> ids) {
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
}