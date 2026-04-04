package com.zeroone.star.eamsj3data.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3data.entity.Student;
import com.zeroone.star.eamsj3data.mapper.StudentMapper;
import com.zeroone.star.eamsj3data.service.StudentService;
import com.zeroone.star.project.vo.j3.data.NewStudentsVO;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@Service
public class StudentServiceImpl extends ServiceImpl<StudentMapper, Student> implements StudentService {
    @Override
    public List<NewStudentsVO> getNewStudentsStagesInfo(
            LocalDateTime beginTime,
            LocalDateTime endTime) {
        QueryWrapper<Student> wrapper = new QueryWrapper<>();
        wrapper.select("DATE(edit_time) as day","stage","count(*) as count")
                .ge(beginTime!=null,"edit_time",beginTime)
                .le(endTime!=null,"edit_time",endTime)
                .eq("stage",0)
                .groupBy("day")
                .orderByAsc("day");

        List<Map<String,Object>> maps = this.baseMapper.selectMaps(wrapper);

        return maps.stream().map(m ->{
            return BeanUtil.
                    fillBeanWithMap(m,new NewStudentsVO(),false);
        }).collect(Collectors.toList());
    }
}
