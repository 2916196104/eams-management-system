package com.zeroone.star.project.j8.sysmanager;

import com.zeroone.star.project.dto.j8.sysmanager.delInternalNoticeDTO;
import cn.hutool.db.PageResult;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.dto.j8.sysmanager.NoticeDTO;
import com.zeroone.star.project.query.j8.sysmanager.NoticeQuery;

import com.zeroone.star.project.vo.j8.sysmanager.NoticeVO;

// Swagger 注解
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;

// Spring 注解
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

/**
 * 内部公告
 */
@Api(tags = "内部公告")
@RequestMapping("/sys/ninternal-notice")
public interface InternalNoticeApis {

    @ApiOperation("删除内部公告")
    JsonVO<Void> deleteNotice(delInternalNoticeDTO delInternalNoticeDTO);

    @ApiOperation("1. 获取公告列表（条件 + 分页）")
    @PostMapping("/list")
    JsonVO<PageResult<NoticeVO>> getNoticeList(@RequestBody NoticeQuery query);

    @ApiOperation("2. 获取公告详情（用于编辑/查看）")
    @GetMapping("/detail/{id}")
    JsonVO<NoticeVO> getNoticeDetail(@PathVariable("id") Long id);

    @ApiOperation("3. 保存公告（新增/修改）")
    @PostMapping("/save")
    JsonVO<Boolean> saveNotice(@RequestBody @Validated NoticeDTO dto);
}