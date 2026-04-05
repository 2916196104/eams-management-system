package com.zeroone.star.project.query.j6.finance;
import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;
import java.time.LocalDateTime;

/*
描述：月课时费查询条件构造
作者：j6-yu
*/
@Data
@ApiModel("月课时费查询条件")
public class MonthlyClassFeeQuery extends PageQuery {
    /*
    老师姓名，用来指定查询，不必须
     */
    @ApiModelProperty(value = "姓名", example = "赵")
    private String name;
    /*
    开始时间
     */
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    @ApiModelProperty(value = "开始时间", example = "2023-01-01")
    private LocalDate startTime;
    /*
    结束时间
     */
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    @ApiModelProperty(value = "结束时间", example = "2023-01-31")
    private LocalDate endTime;


}
