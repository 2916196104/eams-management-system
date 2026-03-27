package com.zeroone.star.sys.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateDTO;
import com.zeroone.star.project.query.j2.sys.template.TemplateQuery;
import com.zeroone.star.sys.entity.Attachment;
import com.baomidou.mybatisplus.extension.service.IService;
import org.springframework.http.ResponseEntity;

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
    PageDTO<TemplateDTO> queryAll(TemplateQuery query);

}
