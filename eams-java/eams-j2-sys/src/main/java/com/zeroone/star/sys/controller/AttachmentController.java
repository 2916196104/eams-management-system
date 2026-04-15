package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;

import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentAddDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentUpdateDTO;
import com.zeroone.star.project.j2.sys.AttachmentApis;
import com.zeroone.star.project.query.j2.sys.attachment.AttachmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Attachment.AttachmentUpdateVO;
import com.zeroone.star.project.vo.j2.sys.Attachment.AttachmentUploadVO;
import com.zeroone.star.sys.service.attachment.IAttachmentService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
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
@Api(tags = "附件管理")
@Slf4j
@RequestMapping("/j2-sys/attach")
@RestController
public class AttachmentController implements AttachmentApis {

    @Resource
    private IAttachmentService attachmentService;

    /**
     * 上传附件
     * @param addDto 附件信息
     * @return 上传结果
     */
    @PostMapping("/upload")
    @ApiOperation("上传附件")
    @Override
    public JsonVO<AttachmentUploadVO> uploadAttachment( @Valid AttachmentAddDTO addDto) {
        try {
            return JsonVO.success(attachmentService.uploadAttachment(addDto));
        } catch (Exception e) {
            log.error("上传附件失败", e);
            return JsonVO.fail(e.getMessage());
        }
    }

    /**
     * 修改附件信息（支持修改附件名称和文件名）
     * @param updateDTO 修改参数
     * @return 修改结果
     */
    @PutMapping("/update")
    @ApiOperation("修改附件")
    @Override
    public JsonVO<AttachmentUpdateVO> updateAttachment(@RequestBody @Valid AttachmentUpdateDTO updateDTO) {
        try {
            AttachmentUpdateVO result = attachmentService.updateAttachment(updateDTO);
            return JsonVO.success(result);
        } catch (IllegalArgumentException e) {
            log.warn("修改附件参数异常: {}", e.getMessage());
            return JsonVO.fail(e.getMessage());
        } catch (Exception e) {
            log.error("修改附件失败", e);
            return JsonVO.fail("修改失败: " + e.getMessage());
        }
    }

    /**
     * 获取附件列表（条件+分页）
     * @param query 查询条件
     * @return 附件列表
     */
    @GetMapping("/list")
    @ApiOperation("获取附件列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<AttachmentDTO>> queryAttachmentList(AttachmentQuery query) {
        return attachmentService.queryAttachmentList(query);
    }

    /**
     * 根据ID获取附件详情
     * @param id 附件ID
     * @return 附件详情
     */
    @GetMapping("/{id}")
    @ApiOperation("根据ID获取附件详情")
    @Override
    public JsonVO<AttachmentDTO> queryAttachmentById(@PathVariable Long id) {
        try {
            AttachmentDTO result = attachmentService.queryAttachmentById(id);
            if (result != null) {
                return JsonVO.success(result);
            } else {
                return JsonVO.fail("附件不存在");
            }
        } catch (Exception e) {
            log.error("查询附件详情失败，ID: {}", id, e);
            return JsonVO.fail("查询失败: " + e.getMessage());
        }
    }

    /**
     * 删除附件（物理删除）
     * @param id 附件ID
     * @return 删除结果
     */
    @DeleteMapping("/remove/{id}")
    @ApiOperation("删除附件")
    @Override
    public JsonVO<String> removeAttachment(@PathVariable Long id) {
        try {
            attachmentService.removeAttachment(id);
            return JsonVO.success("删除成功");
        } catch (IllegalArgumentException e) {
            log.warn("删除附件参数异常: {}", e.getMessage());
            return JsonVO.fail(e.getMessage());
        } catch (Exception e) {
            log.error("删除附件失败，ID: {}", id, e);
            return JsonVO.fail("删除失败: " + e.getMessage());
        }
    }

    /**
     * 批量删除附件
     * @param ids 附件ID列表
     * @return 删除结果
     */
    @DeleteMapping("/remove/batch")
    @ApiOperation("批量删除附件")
    @Override
    public JsonVO<String> removeAttachmentsBatch(@RequestBody List<Long> ids) {
        try {
            if (ids == null || ids.isEmpty()) {
                return JsonVO.fail("请选择要删除的附件");
            }
            attachmentService.removeAttachmentsBatch(ids);
            return JsonVO.success("批量删除成功");
        } catch (IllegalArgumentException e) {
            log.warn("批量删除附件参数异常: {}", e.getMessage());
            return JsonVO.fail(e.getMessage());
        } catch (Exception e) {
            log.error("批量删除附件失败，IDs: {}", ids, e);
            return JsonVO.fail("批量删除失败: " + e.getMessage());
        }
    }
}
