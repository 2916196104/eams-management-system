package com.zeroone.star.courseschedule.dto.j5.org.DO;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("course")
public class CourseDo {
        @TableId(type = IdType.AUTO)
        private Long id;
        private String name;            // 课程名称
        private Integer lessonType;             //课堂类型
        private Integer bookable;               //是否可以预约

}
