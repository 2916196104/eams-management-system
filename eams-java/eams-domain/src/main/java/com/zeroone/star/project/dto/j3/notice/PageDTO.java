package com.zeroone.star.project.dto.j3.notice;

import lombok.Data;

import java.util.List;

@Data
public class PageDTO<T> {
    private long total;
    private List<T> records;
    private int current;
    private int size;

    public PageDTO(long total, List<T> records, int current, int size) {
        this.total = total;
        this.records = records;
        this.current = current;
        this.size = size;
    }

    public PageDTO() {
    }

}
