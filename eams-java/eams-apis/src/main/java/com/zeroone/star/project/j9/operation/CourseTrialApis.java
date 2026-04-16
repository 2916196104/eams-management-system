package com.zeroone.star.project.j9.operation;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.CourseTrialDTO;
import com.zeroone.star.project.query.j9.operation.CourseTrialQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.operation.CourseTrialVO;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.List;

/**
 * 描述：试听卡接口声明
 * @author paopao
 * @version 1.0.0
 */
public interface CourseTrialApis {

    /**
     * 获取试听卡列表（条件+分页）
     * @param condition 查询条件
     * @return 试听卡分页列表
     */
    JsonVO<PageDTO<CourseTrialVO>> queryTrialList(CourseTrialQuery condition);

    /**
     * 获取试听卡详情
     * @param id 试听卡ID
     * @return 试听卡详情
     */
    JsonVO<CourseTrialVO> queryTrialDetail(
            @ApiParam(value = "试听卡ID", required = true) @PathVariable Long id);

    /**
     * 保存试听卡（新增或修改，有id则修改，无id则新增）
     * @param dto 试听卡数据
     * @return 保存结果
     */
    JsonVO<String> addCourseTrial(@RequestBody CourseTrialDTO dto);

    /**
     * 删除试听卡（支持批量删除）
     * @param ids 试听卡ID列表
     * @return 删除结果
     */
    JsonVO<String> removeCourseTrial(
            @ApiParam(value = "试听卡ID列表", required = true) @RequestBody List<Long> ids);
}
