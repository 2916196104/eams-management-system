package com.zeroone.star.project.j5.classmanager;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j5.classmanager.ClassDTO;
import com.zeroone.star.project.dto.j5.classmanager.ClassStudentDTO;
import com.zeroone.star.project.dto.j5.classmanager.TransClassStudentDTO;
import com.zeroone.star.project.query.j5.classmanager.ClassOptionsQuery;
import com.zeroone.star.project.query.j5.classmanager.ClassPageQuery;
import com.zeroone.star.project.query.j5.classmanager.ClassStudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassOptionsVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassStudentVO;

import java.util.List;

public interface ClassStudentApis {
    JsonVO<Page<ClassOptionsVO>> queryClassOptions(ClassOptionsQuery query);


    JsonVO<IPage<ClassListVO>> pageClass(ClassPageQuery query);
    JsonVO<ClassListVO> getClassDetail(Long id);
    JsonVO<IPage<ClassStudentVO>> pageStudent(Long classId, ClassStudentQuery query);


    JsonVO<Integer> addClassStudent(ClassStudentDTO classStudentDTO);

    JsonVO<Integer> removeClassStudent(ClassStudentDTO classStudentDTO);

    JsonVO<Integer> transferClassBatch(TransClassStudentDTO transClassStudentDTO);


    //保存班级
    JsonVO<Long> addClass(ClassDTO classDTO);

    //删除班级
    JsonVO<Long> removeClass(List<Long> ids);

    //结业班级
    JsonVO<Long> endClass(List<Long> ids);
}
