package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateAttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateDTO;
import com.zeroone.star.project.query.j2.sys.template.TemplateQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.List;

/**
 * 描述：模板管理接口声明
 */
public interface TemplateApis {

    /**
     * 获取指定模板文件
     * @param templateId 模板id
     * @return 模板文件
     */
    ResponseEntity<byte[]> downloadFile(String templateId);

    /**
     * 获取模板列表（条件+分页）
     * @param condition 查询条件
     * @return 查询结果
     */
    JsonVO<PageDTO<TemplateAttachmentDTO>> queryAll(TemplateQuery condition);

    /**
     * 新增模版
     * @param dto 新增模版数据
     * @return
     */
    JsonVO<String> addTemplate(@RequestBody TemplateDTO dto);

    /**
     * 修改模版
     * @param dto 修改模版数据
     * @return
     */
    JsonVO<String> modifyTemplate(@RequestBody TemplateDTO dto);

    /**
     * 删除模版
     * @param ids 删除模版主键集合
     * @return
     */
    JsonVO<String> removeTemplate(List<String> ids);

}



