package com.zeroone.star.classmanager.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.Do.j5.classmanager.ClassStudentDO;
import com.zeroone.star.project.query.j5.classmanager.ClassStudentQuery;
import com.zeroone.star.project.vo.j5.classmanager.ClassStudentVO;
import org.springframework.stereotype.Service;


public interface ClassStudentService extends IService<ClassStudentDO> {
    public IPage<ClassStudentVO> queryClassStudentPage(Long classId, ClassStudentQuery query) ;
}
