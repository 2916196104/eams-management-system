package com.zeroone.star.project.dto.j6.interact;


import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class AdvertisementQuery extends PageQuery {
    @ApiModelProperty(value = "公告标题")
    private String title;

}
