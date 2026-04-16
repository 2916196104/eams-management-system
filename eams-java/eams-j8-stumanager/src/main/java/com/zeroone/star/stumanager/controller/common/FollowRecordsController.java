package com.zeroone.star.stumanager.controller.common;

import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.j8.stumanager.AddFollowRecordDTO;
import com.zeroone.star.project.j8.stumanager.common.FollowRecordsApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.FollowRecordVO;
import com.zeroone.star.stumanager.service.IContactRecordService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

/**
 * 跟进记录
 */

@Api(tags = "共用接口-跟进记录")
@RequestMapping("/stu/common/follow-records")
@RestController
public class FollowRecordsController implements FollowRecordsApis {

    @Autowired
    private IContactRecordService contactRecordService;

    @GetMapping
    @ApiOperation(value = "获取跟进记录列表")
    @Override
    public JsonVO<ExtendPageDTO<FollowRecordVO>> getFollowRecords(
            @ApiParam(value = "学员ID", required = true) @RequestParam Long studentId,
            @ApiParam(value = "页码", defaultValue = "1") @RequestParam(defaultValue = "1") Integer page,
            @ApiParam(value = "每页大小", defaultValue = "10") @RequestParam(defaultValue = "10") Integer size) {
        try {
            ExtendPageDTO<FollowRecordVO> result = contactRecordService.getFollowRecords(studentId, page, size);
            return JsonVO.success(result);
        } catch (IllegalArgumentException e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    @PostMapping
    @ApiOperation(value = "添加跟进记录")
    @Override
    public JsonVO<Void> addFollowRecord(@RequestBody AddFollowRecordDTO dto) {
        try {
            Boolean success = contactRecordService.addFollowRecord(dto);
            if (success) {
                return JsonVO.success(null);
            } else {
                return JsonVO.fail("添加跟进记录失败");
            }
        } catch (IllegalArgumentException e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    @DeleteMapping("/{id}")
    @ApiOperation(value = "删除跟进记录")
    @Override
    public JsonVO<Void> deleteFollowRecord(@ApiParam(value = "跟进记录ID", required = true) @PathVariable Long id) {
        try {
            Boolean success = contactRecordService.deleteFollowRecord(id);
            if (success) {
                return JsonVO.success(null);
            } else {
                return JsonVO.fail("删除跟进记录失败");
            }
        } catch (IllegalArgumentException e) {
            return JsonVO.fail(e.getMessage());
        }
    }
}

