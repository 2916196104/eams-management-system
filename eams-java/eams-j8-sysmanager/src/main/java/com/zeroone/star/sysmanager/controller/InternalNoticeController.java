package com.zeroone.star.sysmanager.controller;

import com.zeroone.star.project.dto.j8.sysmanager.NoticeDTO;
import com.zeroone.star.project.j8.sysmanager.InternalNoticeApis;
import com.zeroone.star.project.query.j8.sysmanager.NoticeQuery;
import com.zeroone.star.project.result.PageResult;
import com.zeroone.star.project.vo.j8.sysmanager.NoticeVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import com.zeroone.star.project.result.Result;

import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.security.PrivateKey;
import java.util.List;

/**
 * 内部公告
 */
@RestController
@RequestMapping("/j1/notice")
@Api("j8-内部公告")
public class InternalNoticeController {

    @Resource
    private InternalNoticeApis internalNoticeapis;


    @ApiOperation(value = "获取公告列表（条件 + 分页）")
    @PostMapping("/list")
    public Result<PageResult<NoticeVO>> getNoticeList(@RequestBody NoticeQuery query) {
        return Result.success(internalNoticeapis.getNoticeList(query));
    }

    @ApiOperation(value = "获取公告详情")
    @GetMapping("/detail/{id}")
    public Result<NoticeVO> getNoticeDetail(@PathVariable Long id) {
        return Result.success(internalNoticeapis.getNoticeDetail(id));
    }

    @ApiOperation(value = "保存公告")
    @PostMapping("/save")
    public Result<Boolean> saveNotice(@RequestBody @Validated NoticeDTO dto) {
        return Result.success(internalNoticeapis.saveNotice(dto));
    }

 /*   @ApiOperation(value = "删除公告（支持批量）")
    @PostMapping("/delete")
    public Result<Boolean> deleteNotice(@RequestBody List<Long> ids) {
        return Result.success(internalNoticeapis.deleteNotice(ids));
    }

    @ApiOperation(value = "增加浏览量")
    @PostMapping("/incrementView/{id}")
    public Result<Boolean> incrementView(@PathVariable Long id) {
        return Result.success(internalNoticeapis.incrementViewNum(id));*/
}
