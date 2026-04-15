package com.zeroone.star.project.j2.sys;

//import com.baomidou.mybatisplus.extension.plugins.pagination.PageDTO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentAddDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentUpdateDTO;
import com.zeroone.star.project.vo.j2.sys.Attachment.AttachmentUploadVO;
import com.zeroone.star.project.query.j2.sys.attachment.AttachmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Attachment.AttachmentUpdateVO;
import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
 * 附件管理接口
 * @author belief
 */
public interface AttachmentApis {


    /**
     * 上传附件
     * @param addDto 附件上传参数
     * @return 上传结果（包含存储信息）
     */
    JsonVO<AttachmentUploadVO> uploadAttachment(AttachmentAddDTO addDto);

    /**
     * 获取附件列表（条件+分页）
     * @param query 查询条件
     * @return 分页附件列表
     */
    JsonVO<PageDTO<AttachmentDTO>> queryAttachmentList(AttachmentQuery query);

    /**
     * 根据ID获取附件详情
     * @param id 附件ID
     * @return 附件详情
     */
    JsonVO<AttachmentDTO> queryAttachmentById(Long id);

    /**
     * 修改附件信息（仅修改附件名称）
     * @param updateDTO 修改请求
     * @return 操作结果
     */
    JsonVO<AttachmentUpdateVO> updateAttachment(@Valid AttachmentUpdateDTO updateDTO);

    /**
     * 删除附件（物理删除，同时删除文件和数据库记录）
     * @param id 附件ID
     * @return 操作结果
     */
    JsonVO<String> removeAttachment(@NotNull Long id);

    /**
     * 批量删除附件
     * @param ids 附件ID列表
     * @return 操作结果
     */
    JsonVO<String> removeAttachmentsBatch(@NotNull List<Long> ids);
}
