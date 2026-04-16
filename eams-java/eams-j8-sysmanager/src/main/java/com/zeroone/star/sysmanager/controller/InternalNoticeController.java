package com.zeroone.star.sysmanager.controller;

import com.zeroone.star.project.dto.j8.sysmanager.delInternalNoticeDTO;
import cn.hutool.db.PageResult;
import com.zeroone.star.project.j8.sysmanager.InternalNoticeApis;
import com.zeroone.star.project.dto.j8.sysmanager.NoticeDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.query.j8.sysmanager.NoticeQuery;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import javax.annotation.Resource;
import com.zeroone.star.project.vo.j8.sysmanager.NoticeVO;

import com.zeroone.star.sysmanager.service.InternalNoticeService;

import org.springframework.web.bind.annotation.*;
/**
 * 内部公告 Controller
 * 实现 InternalNoticeApis 接口，统一规范
 */
@Api(tags = "内部公告管理")
@RequestMapping("/j8-sys/internal-notice")
@RestController
public class InternalNoticeController implements InternalNoticeApis {

    @Resource
    private InternalNoticeService internalNoticeService;

    @PostMapping("/del")
    @ApiOperation("删除选定的公告")
    @Override
    public JsonVO<Void> deleteNotice(@Validated @RequestBody delInternalNoticeDTO dto) {
        boolean result = internalNoticeService.removeByIds(dto.getIds());
        if (result)
            return JsonVO.success(null);
        return JsonVO.fail(null);
    }

    @Override
    @ApiOperation("1. 获取公告列表（条件 + 分页）")
    @PostMapping("/list")
    public JsonVO<PageResult<NoticeVO>> getNoticeList(@RequestBody NoticeQuery query) {
        // 调用 Service 获取数据
        PageResult<NoticeVO> data = internalNoticeService.getNoticeList(query);
        // 统一返回 JsonVO
        return JsonVO.success(data);
    }

    @Override
    @ApiOperation("2. 获取公告详情（用于编辑/查看）")
    @GetMapping("/detail/{id}")
    public JsonVO<NoticeVO> getNoticeDetail(@PathVariable("id") Long id) {
        NoticeVO data = internalNoticeService.getNoticeDetail(id);
        return JsonVO.success(data);
    }

    @Override
    @ApiOperation("3. 保存公告（新增/修改）")
    @PostMapping("/save")
    public JsonVO<Boolean> saveNotice(@RequestBody @Validated NoticeDTO dto) {
        boolean success = internalNoticeService.saveNotice(dto);
        return success ? JsonVO.success(true) : JsonVO.fail("保存失败");
    }
}