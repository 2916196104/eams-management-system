package com.zeroone.star.sys.service.attachment;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentAddDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentUpdateDTO;
import com.zeroone.star.project.query.j2.sys.attachment.AttachmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Attachment.AttachmentUploadVO;
import com.zeroone.star.project.vo.j2.sys.Attachment.AttachmentUpdateVO;
import com.zeroone.star.sys.entity.Attachment;
import com.baomidou.mybatisplus.extension.service.IService;

import java.util.List;

/**
 * <p>
 * 附件管理表 服务类
 * </p>
 *
 * @author dapeng
 * @since 2026-03-22
 */
public interface IAttachmentService extends IService<Attachment> {

    /**
     * 上传附件到FastDFS并记录到数据库
     * @param addDto 附件上传参数
     * @return 上传结果
     */
    AttachmentUploadVO uploadAttachment(AttachmentAddDTO addDto) throws Exception;

    /**
     * 查询附件列表（条件+分页）
     * @param query 查询条件
     * @return 分页附件列表
     */
    JsonVO<PageDTO<AttachmentDTO>> queryAttachmentList(AttachmentQuery query);

    /**
     * 根据ID获取附件详情
     * @param id 附件ID
     * @return 附件详情
     */
    AttachmentDTO queryAttachmentById(Long id);

    /**
     * 删除附件（物理删除）
     * @param id 附件ID
     * @return 是否成功
     */
    void removeAttachment(Long id);

    /**
     * 批量删除附件
     * @param ids 附件ID列表
     * @return 是否成功
     */
    void removeAttachmentsBatch(List<Long> ids);

    /**
     * 获取附件下载URL
     * @param id 附件ID
     * @return 下载URL
     */
    String getDownloadUrl(Long id);

    /**
     * 增加下载次数
     * @param id 附件ID
     */
    void incrementDownloadCount(Long id);

    /**
     * 验证附件是否存在且可访问
     * @param id 附件ID
     * @return 是否可访问
     */
    Boolean validateAttachmentAccess(Long id);

    /**
     * 修改附件信息
     * @param updateDTO 修改参数
     * @return 修改结果
     */
    public AttachmentUpdateVO updateAttachment(AttachmentUpdateDTO updateDTO);
}
