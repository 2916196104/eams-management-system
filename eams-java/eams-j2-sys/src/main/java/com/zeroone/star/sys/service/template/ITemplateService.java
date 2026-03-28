package com.zeroone.star.sys.service.template;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateAttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateDTO;
import com.zeroone.star.project.query.j2.sys.template.TemplateQuery;
import com.zeroone.star.sys.entity.Attachment;
import com.baomidou.mybatisplus.extension.service.IService;
import org.springframework.http.ResponseEntity;

import java.util.List;

/**
 * <p>
 * 系统设置表 服务类
 * </p>
 *
 * @author 斗气化码
 * @since 2026-03-27
 */
public interface ITemplateService extends IService<Attachment> {

    /**
     * 获取指定模板文件
     * @param templateId 模板id
     * @return 模板文件
     */
    ResponseEntity<byte[]> downloadFile(String templateId);

    /**
     * 获取模板列表（条件+分页）
     * @param query 查询条件
     * @return 查询结果
     */
    PageDTO<TemplateAttachmentDTO> queryAll(TemplateQuery query);

    /**
     * 新增模板列表
     * @return 新增结果是否成功
     */
    public boolean addTemplateList(TemplateDTO templateDTO);

    /**
     * 删除模板列表
     * @return 删除结果是否成功
     */
    public boolean deleteTemplateList(List<String> templateIds);

    /**
     * 修改模板列表
     * @return 修改结果是否成功
     */
    public boolean updateTemplateList(TemplateDTO templateDTO);

}
