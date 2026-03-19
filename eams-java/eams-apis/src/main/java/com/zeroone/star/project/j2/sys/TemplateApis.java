package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.TemplateDTO;
import com.zeroone.star.project.query.j2.sys.TemplateQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.http.ResponseEntity;

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
}
