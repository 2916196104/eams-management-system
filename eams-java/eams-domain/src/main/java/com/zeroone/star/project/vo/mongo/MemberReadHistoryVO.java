package com.zeroone.star.project.vo.mongo;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.util.Date;

/**
 * <p>
 * 描述：用户商品浏览历史记录数据显示对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Data
@ApiModel("浏览记录数据传输对象")
public class MemberReadHistoryVO {
    @ApiModelProperty(value = "数据唯一编号", example = "1")
    private String id;
    @ApiModelProperty(value = "会员编号", example = "2")
    private Long memberId;
    @ApiModelProperty(value = "会员名称", example = "王麻子")
    private String memberNickname;
    @ApiModelProperty(value = "会员图标", example = "2.icon")
    private String memberIcon;
    @ApiModelProperty(value = "浏览商品编号", example = "1")
    private Long productId;
    @ApiModelProperty(value = "浏览商品名称", example = "洗面奶")
    private String productName;
    @ApiModelProperty(value = "浏览商品图片", example = "5.png")
    private String productPic;
    @ApiModelProperty(value = "浏览商品描述", example = "这是一个神奇的洗面奶")
    private String productSubTitle;
    @ApiModelProperty(value = "浏览商品价格", example = "199")
    private String productPrice;
    @ApiModelProperty(value = "创建时间", example = "2024-01-11 11:11:11")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date createTime;
}
