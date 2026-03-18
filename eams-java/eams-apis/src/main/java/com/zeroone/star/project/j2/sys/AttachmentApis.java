package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;

import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentAddDTO;
import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentDTO;
import com.zeroone.star.project.query.j2.sys.AttachmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.AttachmentUploadVO;

import java.util.List;


/**
 * <p>
 * 描述：附件管理API接口定义
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author belief
 * @version 1.0.0
 */
public interface AttachmentApis {
    
    /**
     * 上传附件
     * @param addDto 附件上传参数
     * @return 上传结果（包含FastDFS存储信息）
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
    JsonVO<AttachmentDTO> queryAttachmentById(String id);
    
    /**
     * 删除附件（逻辑删除）
     * @param id 附件ID
     * @return 删除结果
     */
    JsonVO<Boolean> removeAttachment(String id);
    
    /**
     * 批量删除附件
     * @param ids 附件ID列表
     * @return 删除结果
     */
    JsonVO<Boolean> removeAttachmentsBatch(List<String> ids);
}