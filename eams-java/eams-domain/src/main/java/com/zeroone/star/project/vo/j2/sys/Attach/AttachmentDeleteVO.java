// src/main/java/com/zeroone/star/project/vo/j2/sys/AttachmentDeleteVO.java
package com.zeroone.star.project.vo.j2.sys.Attach;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;
import java.util.Map;
/**
 * @Author: 大鹏
 * @Date: 2026/3/18 16:06
 * @Description:
**/

@Data
@ApiModel("附件删除结果")
public class AttachmentDeleteVO {

    @ApiModelProperty(value = "成功删除的ID列表", example = "[\"att_001\", \"att_002\"]")
    private List<String> successIds;

    @ApiModelProperty(value = "删除失败的ID及原因", example = "{\"att_003\": \"附件不存在\"}")
    private Map<String, String> failedIds;

    @ApiModelProperty(value = "删除总数", example = "3")
    private Integer totalCount;

    @ApiModelProperty(value = "成功数量", example = "2")
    private Integer successCount;

    @ApiModelProperty(value = "失败数量", example = "1")
    private Integer failCount;

    @ApiModelProperty(value = "操作结果描述", example = "成功删除2个附件，1个删除失败")
    private String resultMessage;
}
