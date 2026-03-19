package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.TemplateDTO;
import com.zeroone.star.project.query.j2.sys.TemplateQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.List;

/**
 * 描述：模板管理
 * @author 斗气化码
 * @version 1.0.0
 */
public interface TemplateApis {

    /**
     * 获取指定模板文件
     * @param group 组名
     * @param storageId storageId
     * @return 模板文件
     */
    ResponseEntity<byte[]> downloadFile(String group, String storageId);

    /**
     * 获取模板列表（条件+分页）
     * @param condition 查询条件
     * @return 查询结果
     */
    JsonVO<PageDTO<TemplateDTO>> queryAll(TemplateQuery condition);
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



