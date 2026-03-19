package com.zeroone.star.sysmanager.controller;

import com.zeroone.star.project.dto.notice.delInternalNoticeDTO;
import com.zeroone.star.project.j8.sysmanager.InternalNoticeApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.sysmanager.service.INoticeService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import javax.annotation.Resource;
/**
 * 内部公告
 */
@RestController
@RequestMapping("/notice")
@Api("内部公告")
public class InternalNoticeController implements InternalNoticeApis {

    @Resource
    INoticeService noticeService;

    @PostMapping("/del")
    @ApiOperation("删除选定的公告")
    @Override
    public JsonVO<Void> deleteNotice(@Validated @RequestBody delInternalNoticeDTO dto) {
        boolean result = noticeService.removeByIds(dto.getIds());
        if (result)
            return JsonVO.success(null);
        return JsonVO.fail(null);
    }
}
