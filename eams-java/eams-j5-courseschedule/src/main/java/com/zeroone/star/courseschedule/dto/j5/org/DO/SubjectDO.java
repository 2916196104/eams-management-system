package com.zeroone.star.courseschedule.dto.j5.org.DO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("subject")
public class SubjectDO {
    @TableId(type = IdType.AUTO)
    private Long id;
    private String name;            // 科目名称
}
