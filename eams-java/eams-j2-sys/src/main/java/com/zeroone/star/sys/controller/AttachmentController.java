package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentAddDTO;
import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentDTO;
import com.zeroone.star.project.j2.sys.AttachmentApis;
import com.zeroone.star.project.query.j2.sys.AttachmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.AttachmentUploadVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

/**
 * <p>
 * 描述：附件控制器
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author belief
 * @version 1.0.0
 */

@Api(tags= "附件管理")
@RequestMapping("/sys/attach")
@RestController
public class AttachmentController implements AttachmentApis{

    /**
     * 负责人：Belief
     */
    @GetMapping("/list")
    @ApiOperation("获取附件列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<AttachmentDTO>> queryAttachmentList(AttachmentQuery query) {
        return null;
    }

    @GetMapping("/{id}")
    @ApiOperation("根据ID获取附件详情")
    @Override
    public JsonVO<AttachmentDTO> queryAttachmentById(String id) {
        return null;
    }

    @PostMapping("/upload")
    @ApiOperation("上传附件")
    @Override
    public JsonVO<AttachmentUploadVO> uploadAttachment(AttachmentAddDTO addDto) {
        return null;
    }

    @PostMapping("/remove")
    @ApiOperation("删除附件（逻辑删除）")
    @Override
    public JsonVO<Boolean> removeAttachment(String id) {
        return null;
    }

    @PostMapping("/remove/batch")
    @ApiOperation("批量删除附件")
    @Override
    public JsonVO<Boolean> removeAttachmentsBatch(List<String> ids) {
        return null;
    }
}
