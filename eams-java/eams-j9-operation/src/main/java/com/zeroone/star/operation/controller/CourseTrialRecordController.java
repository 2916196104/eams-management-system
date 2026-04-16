package com.zeroone.star.operation.controller;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.zeroone.star.operation.service.ICourseTrialRecordService;
import com.zeroone.star.project.j9.operation.CourseTrialRecordApis;
import com.zeroone.star.project.query.j9.operation.CourseTrialRecordPageQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.operation.CourseTrialRecordVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.Valid;
import java.util.List;

/**
 * 课程体验卡领取记录Controller（适配JsonVO规范）
 */
@Api(tags = "课程体验卡领取记录管理")
@RestController
@RequestMapping("trial-record")
public class CourseTrialRecordController implements CourseTrialRecordApis {

    // 注入Service层依赖
    @Autowired
    private ICourseTrialRecordService courseTrialRecordService;

    @GetMapping("list")
    @Override
    @ApiOperation(
            value = "课程体验卡领取记录条件分页查询",
            notes = "支持按卡ID（trialId）、学生ID（studentId）、课程ID（courseId）、学校ID（schoolId）、领取时间范围（addTimeStart/addTimeEnd）、到期时间范围（expiredDateStart/expiredDateEnd）、顾问ID（counselor）筛选"
    )
    public JsonVO<List<CourseTrialRecordVO>> queryTrialRecordPage(
            @ApiParam(value = "分页查询参数（含分页信息+筛选条件）", required = true)
            @Valid CourseTrialRecordPageQuery pageQuery) {
        // 1. 调用Service执行分页查询（返回IPage类型的VO数据）
        IPage<CourseTrialRecordVO> pageResult = courseTrialRecordService.listTrialRecordPage(pageQuery);

        // 2. 按照项目JsonVO规范封装成功结果
        // 调用JsonVO的success静态方法，自动填充成功状态码和提示语
        return JsonVO.success(pageResult.getRecords());
    }
}