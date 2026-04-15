package com.zeroone.star.project.query.j3.notice;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class NoticeSettingQuery extends PageQuery {
    @ApiModelProperty(value = "设置名称",required = true,example = "weixingtongzhi")
    private String name;

}
