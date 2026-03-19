package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentAddDTO;
import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentDeleteDTO;
import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentUpdateDTO;
import com.zeroone.star.project.j2.sys.AttachmentApis;
import com.zeroone.star.project.query.j2.sys.AttachmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Attach.AttachmentUpdateVO;
import com.zeroone.star.project.vo.j2.sys.AttachmentUploadVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;

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
    /**
     * 负责人：大鹏
     */

    /**
     * 单个删除附件
     * @param attachmentId 附件ID
     * @return 删除是否成功
     */
    @Override
    @PostMapping("/delete-attachment")
    @ApiOperation("删除单个附件")
    public JsonVO<Boolean> deleteAttachment(@RequestParam String attachmentId) {
        // TODO 实现单个删除逻辑
        // 1. 参数校验：attachmentId 不能为空
        // 2. 调用Service层执行删除
        // 3. 返回删除结果
        return null;
    }

    /**
     * 更新附件信息
     * @param updateDTO 更新参数
     * @return 更新后的附件信息
     */
    @Override
    @ApiOperation("修改附件")
    @PostMapping("/update-attachment")
    public JsonVO<AttachmentUpdateVO> updateAttachment(@RequestBody @Valid AttachmentUpdateDTO updateDTO) {
        // TODO 实现更新逻辑
        // 1. 参数校验（@Valid 会自动校验）
        // 2. 调用Service层执行更新
        // 3. 返回更新后的数据
        return null;
    }

    /**
     * 批量删除附件
     * @param deleteDTO 批量删除参数（包含ID列表和删除原因）
     * @return 实际删除的数量
     */
    @Override
    @ApiOperation("批量删除附件附件")
    @PostMapping("/batch-delete-attachment")
    public JsonVO<Integer> batchDeleteAttachment(@RequestBody @Valid AttachmentDeleteDTO deleteDTO) {
        return null;
    }
}
