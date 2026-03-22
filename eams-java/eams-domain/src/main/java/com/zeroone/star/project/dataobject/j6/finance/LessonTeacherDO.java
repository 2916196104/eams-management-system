package com.zeroone.star.project.dataobject.j6.finance;

import lombok.Data;

@Data
public class LessonTeacherDO {

    int id;
    int lessonId;
    int teacherId;
    Double commission;
    int type;

}
