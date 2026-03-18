package com.zeroone.star.stumanager.controller.common;

import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.j8.stumanager.AddFollowRecordDTO;
import com.zeroone.star.project.j8.stumanager.common.FollowRecordsApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

/**
 * 跟进记录
 */
@RestController
@RequestMapping("follow-records")
@Api(tags = "跟进记录")
public class FollowRecordsController implements FollowRecordsApis {

    @GetMapping
    @ApiOperation(value = "获取跟进记录列表")
    @Override
    public JsonVO<ExtendPageDTO> getFollowRecords(
            @ApiParam(value = "学员ID", required = true) @RequestParam Long studentId,
            @ApiParam(value = "页码", defaultValue = "1") @RequestParam(defaultValue = "1") Integer page,
            @ApiParam(value = "每页大小", defaultValue = "10") @RequestParam(defaultValue = "10") Integer size) {
        return JsonVO.success(null);
    }

    @PostMapping
    @ApiOperation(value = "添加跟进记录")
    @Override
    public JsonVO<Void> addFollowRecord(@RequestBody AddFollowRecordDTO dto) {
        return JsonVO.success(null);
    }

    @DeleteMapping("/{id}")
    @ApiOperation(value = "删除跟进记录")
    @Override
    public JsonVO<Void> deleteFollowRecord(@ApiParam(value = "跟进记录ID", required = true) @PathVariable Long id) {
        return JsonVO.success(null);
    }
}
