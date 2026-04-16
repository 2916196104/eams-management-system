package com.zeroone.star.project.dto.j7.operation;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel("试听卡相关分页返回对象")
public class TrialPageDTO<T> implements Serializable {

    @ApiModelProperty(value = "当前页码", example = "1")
    private Long page;

    @ApiModelProperty(value = "每页显示条数", example = "30")
    private Long pageSize;

    @ApiModelProperty(value = "总条数", example = "100")
    private Long total;

    @ApiModelProperty(value = "总页数", example = "10")
    private Long pageCount;

    @ApiModelProperty(value = "当前页数据列表")
    private List<T> records;

    public static <T> TrialPageDTO<T> create(Page<T> page) {
        TrialPageDTO<T> dto = new TrialPageDTO<>();
        dto.setPage(page.getCurrent());
        dto.setPageSize(page.getSize());
        dto.setTotal(page.getTotal());
        dto.setPageCount(page.getPages());
        dto.setRecords(page.getRecords());
        return dto;
    }
}