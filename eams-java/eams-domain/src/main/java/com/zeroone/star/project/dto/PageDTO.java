package com.zeroone.star.project.dto;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class PageDTO<T> implements Serializable {
    @ApiModelProperty(value = "Current page index", example = "1")
    protected Long pageIndex;

    @ApiModelProperty(value = "Page size", example = "10")
    protected Long pageSize;

    @ApiModelProperty(value = "Total records", example = "100000")
    protected Long total;

    @ApiModelProperty(value = "Total pages", example = "100")
    protected Long pages;

    @ApiModelProperty(value = "Page rows")
    protected List<T> rows;

    public static <T> PageDTO<T> create(Page<T> page) {
        PageDTO<T> pageResult = new PageDTO<>();
        pageResult.setTotal(page.getTotal());
        pageResult.setRows(page.getRecords());
        pageResult.setPageIndex(page.getCurrent());
        pageResult.setPageSize(page.getSize());
        pageResult.setPages(page.getPages());
        return pageResult;
    }

    public static <T, D> PageDTO<T> create(Page<D> page, DataTransCallBack<T, D> callback) {
        PageDTO<T> pageResult = new PageDTO<>();
        pageResult.setTotal(page.getTotal());
        pageResult.setPageIndex(page.getCurrent());
        pageResult.setPageSize(page.getSize());
        pageResult.setPages(page.getPages());
        List<D> records = page.getRecords();
        if (records != null && !records.isEmpty()) {
            List<T> rows = new ArrayList<>();
            for (D sub : records) {
                try {
                    T t = callback.executeTrans(sub);
                    rows.add(t);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
            pageResult.setRows(rows);
        }
        return pageResult;
    }

    public static <T, D> PageDTO<T> create(Page<D> page, Class<T> tClass) {
        DataTransCallBack<T, D> defaultTransCallBack = src -> {
            try {
                T t = tClass.newInstance();
                BeanUtil.copyProperties(src, t);
                return t;
            } catch (InstantiationException | IllegalAccessException e) {
                throw new RuntimeException(e);
            }
        };
        return create(page, defaultTransCallBack);
    }
}
