package com.zeroone.star.project.j5.classes;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j5.classes.ClassPageQuery;
import com.zeroone.star.project.query.j5.classes.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.classes.ClassDetailVO;
import com.zeroone.star.project.vo.j5.classes.ClassPageVo;
import com.zeroone.star.project.vo.j5.student.StudentVo;

public interface ClassApis {
    JsonVO<Page<ClassDetailVO>> pageClass(ClassPageQuery query);
    JsonVO<ClassDetailVO> getClassDetail(Long id);
    JsonVO<Page<StudentVo>> pageStudent(Long classId, StudentQuery query);

}
