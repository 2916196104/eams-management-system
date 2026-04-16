package com.zeroone.star.project.dto.j8.sysmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotEmpty;
import java.util.List;

@Data
@ApiModel("删除公告")
public class delInternalNoticeDTO {

    @NotEmpty(message = "至少删除一个公告")
    @ApiModelProperty("删除操作")
    private List<Long> ids; // 因为删除的id可能不唯一
}