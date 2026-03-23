package com.zeroone.star.eamsj3class.service.impl;


import com.alibaba.nacos.common.utils.StringUtils;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3class.entity.Course;
import com.zeroone.star.eamsj3class.entity.CourseImage;
import com.zeroone.star.eamsj3class.mapper.CourseMapper;
import com.zeroone.star.eamsj3class.service.ICourseImageService;
import com.zeroone.star.eamsj3class.service.ICourseLinkService;
import com.zeroone.star.eamsj3class.service.ICourseService;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.j3.course.AddCourseDTO;
import com.zeroone.star.project.vo.JsonVO;
import lombok.extern.slf4j.Slf4j;
import net.sf.cglib.core.Local;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.ZoneId;


/**
 * <p>
 * 课程套餐表 服务实现类
 * </p>
 *
 * @author heavydrink
 * @since 2026-03-23
 */
@Service
@Slf4j
public class CourseServiceImpl extends ServiceImpl<CourseMapper, Course> implements ICourseService {

    @Resource
    private ICourseImageService courseImageService;
    @Resource
    private UserHolder userHolder;

    @Override
    @Transactional
    public JsonVO<String> addCourse(AddCourseDTO addCourseDTO) {
        try{
            // 添加course
            Course course = new Course();
            BeanUtils.copyProperties(addCourseDTO, course);
            // 补充部分信息
            try{
                Long creator = Long.parseLong(userHolder.getCurrentUser().getId());
                // TODO 补充org_id
                course.setCreator(creator);
            }catch (Exception e){
                e.printStackTrace();
                log.info("获取当前用户id失败");
            }
            course.setAddTime(LocalDateTime.now(ZoneId.of("Asia/Shanghai")));
            // 添加price
            BigDecimal price = new BigDecimal(addCourseDTO.getPrice()).setScale(2, BigDecimal.ROUND_HALF_UP);
            course.setPrice(price);
            // 添加unitPrice
            int unitPrice_int = (int) Math.ceil(Double.parseDouble(addCourseDTO.getPrice()) / addCourseDTO.getLessonCount());
            BigDecimal unitPrice = new BigDecimal(unitPrice_int).setScale(2, BigDecimal.ROUND_HALF_UP);
            course.setUnitPrice(unitPrice);
            // 添加salary
            BigDecimal salary = new BigDecimal(addCourseDTO.getSalary()).setScale(2, BigDecimal.ROUND_HALF_UP);
            course.setSalary(salary);
            // 添加closeDate
            LocalDate closeDate = LocalDate.parse(addCourseDTO.getCloseDate());
            course.setCloseDate(closeDate);
            this.save(course);

            // 添加courseImage
            if(StringUtils.isNotBlank(addCourseDTO.getImages())){
                CourseImage courseImage = new CourseImage();
                courseImage.setCourseId(course.getId());
                courseImage.setImageUrl(addCourseDTO.getImages());
                courseImage.setCreator(course.getCreator());
                courseImage.setAddTime(course.getAddTime());
                courseImageService.save(courseImage);
            }
            return JsonVO.success("添加成功");
        }catch (Exception e){
            e.printStackTrace();
            return JsonVO.fail("添加失败");
        }
    }

}
