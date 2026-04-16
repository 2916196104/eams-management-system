package com.zeroone.star.operation.controller;

import com.zeroone.star.operation.service.IPointsRecordService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.PointsRecordDTO;
import com.zeroone.star.project.dto.j7.operation.PointsRecordUpdateDTO;
import com.zeroone.star.project.query.j7.operation.PointsRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

@RestController
@RequestMapping("/j7-operation/j7-pointsRecord")
@Api(tags = "积分记录管理")
public class PointsRecordController {

    @Resource
    private IPointsRecordService IPointsRecordService;

    @GetMapping("/query-list-points-record")
    @ApiOperation("获取积分记录列表")
    public JsonVO<PageDTO<PointsRecordDTO>> queryAllPointsRecord(PointsRecordQuery condition) {
        return IPointsRecordService.queryAllPointsRecord(condition);
    }

    @PostMapping("/update-points")
    @ApiOperation("调整积分")
    public JsonVO<String> updatePointsRecord(@RequestBody List<PointsRecordUpdateDTO> updateDtos) {
        return IPointsRecordService.updatePointsRecord(updateDtos);
    }
}
