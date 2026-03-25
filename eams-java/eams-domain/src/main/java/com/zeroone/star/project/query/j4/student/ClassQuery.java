package com.zeroone.star.project.query.j4.student;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

/**
 * 描述：班级查询对象
 */
@Data
@Setter
@Getter
public class ClassQuery extends PageQuery {

    @ApiModelProperty(value = "班级名称 (模糊查询，可选)", example = "qaweq")
    private String name;
}