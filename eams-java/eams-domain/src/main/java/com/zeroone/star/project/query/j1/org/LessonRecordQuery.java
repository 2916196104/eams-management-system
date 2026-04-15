package com.zeroone.star.project.query.j1.org;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

/**
 * <p>
 * 描述：员工授课记录查询对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author chichu
 * @version 1.0.0
 */
@Data
public class LessonRecordQuery extends PageQuery {
    @ApiModelProperty(value = "员工ID", example = "1")
    private Integer staffId;

    @ApiModelProperty(value = "开始日期", example = "2026-03-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期", example = "2026-03-18")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;
}