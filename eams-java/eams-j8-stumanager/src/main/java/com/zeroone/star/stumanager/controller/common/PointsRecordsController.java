package com.zeroone.star.stumanager.controller.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.AdjustPointsDTO;
import com.zeroone.star.project.j8.stumanager.common.PointsRecordsApis;
import com.zeroone.star.project.query.j8.stumanager.common.PointsRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.common.PointsRecordVO;
import com.zeroone.star.stumanager.service.IStudentCreditLogService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
@Validated
@RequestMapping("/stu/common/points-records")
@Api(tags = "公用接口 - 积分记录")
public class PointsRecordsController implements PointsRecordsApis {

    @Resource
    private IStudentCreditLogService studentCreditLogService;

    @ApiOperation("获取积分记录")
    @GetMapping("/query-points-records")
    @Override
    public JsonVO<PageDTO<PointsRecordVO>> queryPointsRecords(@Validated PointsRecordQuery query) {
        try {
            return JsonVO.success(studentCreditLogService.queryPointsRecords(query));
        } catch (IllegalArgumentException exception) {
            return JsonVO.fail(exception.getMessage());
        }
    }

    @ApiOperation("调整积分")
    @PostMapping("/adjust-points")
    @Override
    public JsonVO<Boolean> adjustPoints(@Validated @RequestBody AdjustPointsDTO dto) {
        try {
            return JsonVO.success(studentCreditLogService.adjustPoints(dto));
        } catch (IllegalArgumentException | IllegalStateException exception) {
            return JsonVO.fail(exception.getMessage());
        }
    }
}
