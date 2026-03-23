package com.zeroone.star.eamsj3class.utils;

import com.zeroone.star.eamsj3class.entity.Course;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

import java.math.BigDecimal;
import java.util.List;
import java.util.Map;

/**
 * <p>
 * 描述：保存分页查询之后产生的临时参数
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
@Setter
@Getter
@AllArgsConstructor
public class PageTmpParam {
    // 课程记录
    List<Course> coursesRecords;
    // 科目记录
    Map<Long, String> subjectMap;
    // 关联数
    Map<Long, Integer> linkCountMap;
    // 销售量
    Map<Long, Integer> saleCountMap;
    // 销售额
    Map<Long, BigDecimal> saleAmountMap;
    // 分页参数
    Long current;
    Long size;
    Long pages;
}
