package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.TemplateDTO;
import com.zeroone.star.project.j2.sys.TemplateApis;
import com.zeroone.star.project.query.j2.sys.TemplateQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

/**
 * <p>
 * 模板文件控制器
 * </p>
 * @author 斗气化码
 * @since 2026-03-18
 */
@Controller
@RequestMapping("/sys/template")
@Api(tags = "模板管理")
@Validated
public class TemplateController implements TemplateApis {
    /**
     * 负责人：斗气化码
     */
    @GetMapping(value = "/import", produces = "application/octet-stream")
    @ApiOperation(value = "获取指定模板文件")
    @Override
    public ResponseEntity<byte[]> downloadFile(String group, String storageId) {
        return null;
    }

    @GetMapping
    @ApiOperation(value = "获取模板列表（条件+分页）")
    @ResponseBody
    @Override
    public JsonVO<PageDTO<TemplateDTO>> queryAll(@Validated TemplateQuery condition) {
        return JsonVO.success(null);
    }
}
