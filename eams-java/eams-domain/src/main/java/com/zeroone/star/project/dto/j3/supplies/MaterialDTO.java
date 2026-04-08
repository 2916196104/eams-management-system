package com.zeroone.star.project.dto.j3.supplies;

import com.zeroone.star.project.dto.PageDTO;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class MaterialDTO  {

    @ApiModelProperty("物料ID")
    private Long materialId;
    @ApiModelProperty("名称")
    private String materialName;
    @ApiModelProperty("分类")
    private String materialCode;
    @ApiModelProperty("所属学校")
    private String materialBelong2;
    @ApiModelProperty("库存")
    private Integer materialnums;
    @ApiModelProperty("最后编辑时间")
    private String materialstime;
    @ApiModelProperty("状态")
    private boolean materialstatus;



}
