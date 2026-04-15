package com.zeroone.star.project.query.j5.studentleave;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

/**
 * <p>
 * 描述：获取学生请假列表分页查询参数对象
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/15 15:59
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@ApiModel("获取学生请假列表分页查询参数")
public class StudentLeaveQuery extends PageQuery {

    @ApiModelProperty(value = "学生姓名/电话", example = "小明")
    private String nameOrPhone;

    @ApiModelProperty(value = "教师 id", example = "2008418408985583617")
    private Long teacherId;

    @ApiModelProperty(value = "开始时间", example = "2026-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束时间", example = "2026-04-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;

}
