package com.zeroone.star.eamsj3system.controller;

import com.zeroone.star.eamsj3system.service.INoticeService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.notice.NoticeDTO;
import com.zeroone.star.project.query.j3.notice.NoticeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.notice.NoticeVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 内部公告 控制器
 * </p>
 * @author 阿伟
 */
@RestController
@RequestMapping("/j3-system")
@Api(tags = "内部公告")
public class NoticeController {

    @Autowired
    private INoticeService noticeService;

    @GetMapping("/detail_list")
    @ApiOperation(value = "分页查询公告列表", notes = "支持条件查询和分页")
    public JsonVO<PageDTO<NoticeVO>> pageList(NoticeQuery query) {
        return JsonVO.success(PageDTO.create(noticeService.pageList(query)));
    }

    @GetMapping("/detail/{id}")
    @ApiOperation(value = "获取公告详情")
    public JsonVO<NoticeVO> getById(@PathVariable Long id) {
        return JsonVO.success(noticeService.getById(id));
    }

    @PostMapping("/save")
    @ApiOperation(value = "保存公告")
    public JsonVO<String> save(@RequestBody NoticeDTO noticeDTO) {
        return JsonVO.success(noticeService.saveNotice(noticeDTO));
    }

    @DeleteMapping("/delete")
    @ApiOperation(value = "删除公告")
    public JsonVO<String> delete(@RequestParam("ids") List<Long> ids) {
        return JsonVO.success(noticeService.deleteByIds(ids));
    }
}
