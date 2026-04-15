package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateAttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateDTO;
import com.zeroone.star.project.j2.sys.TemplateApis;
import com.zeroone.star.project.query.j2.sys.template.TemplateQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.sys.service.template.ITemplateService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * 模板文件控制器
 * </p>
 * @since 2026-03-18
 */
@RestController
@RequestMapping("/j2-sys/template")
@Api(tags = "模板管理")
@Validated
public class TemplateController implements TemplateApis {
    /**
     * 负责人：斗气化码
     */

    @Resource
    ITemplateService templateService;

    @GetMapping(value = "/import", produces = "application/octet-stream")
    @ApiOperation(value = "获取指定模板文件")
    @Override
    public ResponseEntity<byte[]> downloadFile(String templateId) {
        return templateService.downloadFile(templateId);
    }

    @GetMapping(value = "/list")
    @ApiOperation(value = "获取模板列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<TemplateAttachmentDTO>> queryAll(@Validated TemplateQuery condition) {
        return JsonVO.success(templateService.queryAll(condition));
    }

    /**
     * 负责人：Emanon
     */
    @PostMapping("/add")
    @ApiOperation(value = "新增模版")
    @Override
    public JsonVO<String> addTemplate(@RequestBody TemplateDTO dto) {
        if(dto == null){
            return JsonVO.fail("请选择要添加的模版数据");
        }
        if(templateService.addTemplateList(dto)){
            return JsonVO.success("新增模版数据成功");
        }
        return JsonVO.fail("新增模版数据失败");
    }

    @PostMapping("/update")
    @ApiOperation(value = "修改模版")
    @Override
    public JsonVO<String> modifyTemplate(@RequestBody TemplateDTO dto) {
        if(dto.getId() == null){
            return JsonVO.fail("请选择要修改的模版数据");
        }
        if(templateService.updateTemplateList(dto)){
            return JsonVO.success("修改模版数据成功");
        }
        return JsonVO.fail("修改模版数据失败");
    }

    @DeleteMapping("")
    @ApiOperation(value = "删除模版")
    @Override
    public JsonVO<String> removeTemplate(List<String> ids) {
        if(ids.isEmpty()){
            return JsonVO.fail("请选择要删除的模版数据");
        }
        if (templateService.deleteTemplateList(ids)){
            return JsonVO.success("删除模版数据成功");
        }
        return JsonVO.fail("删除模版数据失败");
    }
}
