package com.zeroone.star.eamsj3data.controller;

import com.zeroone.star.eamsj3data.service.IBaseAnalysisService;
import com.zeroone.star.project.dto.j3.data.SalesFunnelDTO;
import com.zeroone.star.project.dto.j3.data.StudentAgeCompositionDTO;
import com.zeroone.star.project.j3.data.BaseAnalysisApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * 描述：学员统计基础分析接口实现类
 * </p>
 * @author yeyue
 * @version 1.0.0
 */
@RestController
@RequestMapping("/j3-statis")
@Api(tags = "学员统计")
public class BaseAnalysisController implements BaseAnalysisApis {

    @Resource
    private IBaseAnalysisService baseAnalysisService;

    @GetMapping("/sales-funnel")
    @ApiOperation("销售漏斗模型接口")
    @Override
    public JsonVO<List<SalesFunnelDTO>> querySalesFunnelModel() {
        return JsonVO.success(baseAnalysisService.getSalesFunnelStats());
    }

    @GetMapping("/student-age-composition")
    @ApiOperation("在学学员年龄构成接口")
    @Override
    public JsonVO<List<StudentAgeCompositionDTO>> queryStudentAgeComposition() {
        return JsonVO.success(baseAnalysisService.getStudentAgeComposition());
    }
}
