package com.zeroone.star.project.query.j8.stumanager.common;


import com.zeroone.star.project.eums.StudentStageEnum;
import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(description = "学员列表查询参数")
public class StudentListQuery extends PageQuery {

    @ApiModelProperty(value = "学员状态")
    private StudentStageEnum stage;

    @ApiModelProperty(value = "搜索关键词：姓名/手机号",example = "张三")
    private String keyword;

    @ApiModelProperty(value = "年级ID",example = "2025")
    private Long gradeId;


}
