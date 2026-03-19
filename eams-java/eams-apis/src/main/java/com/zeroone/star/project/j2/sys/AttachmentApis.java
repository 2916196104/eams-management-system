package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;

import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentAddDTO;
import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentDeleteDTO;
import com.zeroone.star.project.dto.j2.sys.Attach.AttachmentUpdateDTO;
import com.zeroone.star.project.query.j2.sys.AttachmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Attach.AttachmentUpdateVO;
import com.zeroone.star.project.vo.j2.sys.AttachmentUploadVO;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;

import javax.validation.Valid;


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
     * 上传附件
     * @param addDto 附件上传参数
     * @return 上传结果（包含FastDFS存储信息）
     */
    JsonVO<AttachmentUploadVO> uploadAttachment(AttachmentAddDTO addDto);



    /**
     * @Author: 大鹏
     * @Date: 2026/3/18 15:21
     * @Param: attachmentId 附件ID
     * @Return: JsonVO<Boolean> true-删除成功 false-删除失败
     * @Description: 删除附件（单条逻辑删除）
     **/
    @ApiOperation("删除附件")
    JsonVO<Boolean> deleteAttachment(@PathVariable("attachmentId") String attachmentId);


    /**
     * @Author: 大鹏
     * @Date: 2026/3/18 15:22
     * @Param: updateDTO 附件修改参数
     * @Return: JsonVO<String> 修改后的附件ID
     * @Description: 修改附件信息
     **/
    @ApiOperation("修改附件")

    JsonVO<AttachmentUpdateVO> updateAttachment(@Valid @RequestBody AttachmentUpdateDTO updateDTO);


    /**
     * @Author: 大鹏
     * @Date: 2026/3/18 15:23
     * @Param: deleteDTO 批量删除参数
     * @Return: JsonVO<Integer> 成功删除的数量
     * @Description: 批量删除附件
     **/
    @ApiOperation("批量删除附件")
    JsonVO<Integer> batchDeleteAttachment(@Valid @RequestBody AttachmentDeleteDTO deleteDTO);
}