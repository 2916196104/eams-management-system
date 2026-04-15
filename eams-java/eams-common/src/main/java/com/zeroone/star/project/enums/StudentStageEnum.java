package com.zeroone.star.project.enums;
import com.baomidou.mybatisplus.annotation.EnumValue;
import lombok.AllArgsConstructor;
import lombok.Getter;
/**
 * <p>
 * 描述：学生阶段枚举类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Getter
@AllArgsConstructor
public enum StudentStageEnum {
    INTENTION(1,"意向学员"),
    STUDYING(2,"在学学员"),
    GRADUATION(3,"毕业学员");

@EnumValue
    private final Integer code;
    private final String desc;


}
