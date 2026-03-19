package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 通用接口响应VO
 *
 *
 */
@Data
@ApiModel(description = "通用接口响应VO")
public class CommonResponseVO<T> {

    @ApiModelProperty(value = "响应码（200-成功 500-失败，默认值：200）", example = "200")
    private Integer code = 200;

    @ApiModelProperty(value = "响应消息（默认值：操作成功）", example = "操作成功")
    private String msg = "操作成功";

    @ApiModelProperty(value = "响应数据")
    private T data;

    // 快捷构造方法
    public static <T> CommonResponseVO<T> success(T data) {
        CommonResponseVO<T> response = new CommonResponseVO<>();
        response.setData(data);
        return response;
    }

    public static <T> CommonResponseVO<T> fail(String msg) {
        CommonResponseVO<T> response = new CommonResponseVO<>();
        response.setCode(500);
        response.setMsg(msg);
        return response;
    }
}