package com.zeroone.star.sys.controller;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.OptlogDTO;
import com.zeroone.star.project.j2.sys.OptlogApis;
import com.zeroone.star.project.query.j2.sys.OptlogQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;

import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * <p>
 * 系统用户日志 前端控制器
 * </p>
 *
 * @author isme
 * @since 2026-03-15
 */
@RestController
@RequestMapping("/sys/optlog")
@Api(tags = "操作日志")
public class OptlogController implements OptlogApis {

    @GetMapping
    @ApiOperation("获取操作日志(条件+分页）")
    @Override
    public JsonVO<PageDTO<OptlogDTO>> queryOptlog(OptlogQuery query) {
        return null;
    }
}

