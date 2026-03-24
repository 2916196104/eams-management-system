package com.zeroone.star.project.j5.classmanger;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j5.classmanager.ClassPageQuery;
import com.zeroone.star.project.query.j5.classmanager.ClassStudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassStudentVo;

public interface ClassStudentApis {
    JsonVO<Page<ClassListVO>> pageClass(ClassPageQuery query);
    JsonVO<ClassListVO> getClassDetail(Long id);
    JsonVO<Page<ClassStudentVo>> pageStudent(Long classId, ClassStudentQuery query);

}
