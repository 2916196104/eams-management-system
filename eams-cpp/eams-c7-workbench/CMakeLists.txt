# CMakeList.txt: eams-c7-workbench 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 设置文件名称
set (appName eams-c7-workbench)

# 包含库目录
include_directories ("./")
include_directories ("../lib-oatpp/include")
include_directories ("../lib-mysql/include")
include_directories ("../lib-common/include")

# 链接库路径，程序运行的时候也在这里找
link_directories (${PROJECT_BINARY_DIR}/lib-oatpp)
link_directories (${PROJECT_BINARY_DIR}/lib-mysql)
link_directories (${PROJECT_BINARY_DIR}/lib-common)
# 如果是Linux环境
if(UNIX)
	link_directories (${PROJECT_SOURCE_DIR}/lib-common/lib64)
	link_directories (${PROJECT_SOURCE_DIR}/lib-oatpp/lib64)
	link_directories (${PROJECT_SOURCE_DIR}/lib-dy/lib64)
# 如果是Windows环境
elseif(WIN32)
	link_directories (${PROJECT_SOURCE_DIR}/lib-common/${ZO_LB_NAME}/${ZO_LBT_NAME})
	link_directories (${PROJECT_SOURCE_DIR}/lib-oatpp/${ZO_LB_NAME}/openssl)
	link_directories (${PROJECT_SOURCE_DIR}/lib-oatpp/${ZO_LB_NAME}/${ZO_LBT_NAME})
	link_directories (${PROJECT_SOURCE_DIR}/lib-mysql/${ZO_LB_NAME}/vs14/${ZO_LBT_NAME})
endif()

# 获取要编译的源代码
file (GLOB_RECURSE SC_FILES ./*.cpp)
list (REMOVE_ITEM SC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/./stdafx.cpp")

# 设置预编译标头
if(WIN32)
	ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" SC_FILES)
endif()

# 编译可执行文件
add_executable(${appName}
    ${SC_FILES}
    "controller/UserRelated/ChangePictureController.cpp"
    "controller/UserRelated/UserInformationController.cpp"
    "controller/UserRelated/UserProfileController.cpp"
    "controller/Course/CourseController.cpp"
    "controller/MyCustomers/GetMyCustomersController.cpp"
    "controller/MyCustomers/GetStudentCoursesController.cpp"
    "controller/MyCustomers/GetStudentDetailController.cpp"
    "controller/SignAndRemark/Controller.cpp"
    "controller/Homework/HomeworkController.cpp"
    "controller/UserRelated/MonthlyDataController.cpp"
    "controller/Schedule/SelectClassController.cpp"
    "controller/Schedule/SelectTeacherController.cpp"
    "controller/Schedule/ClassroomController.cpp"
    "controller/Schedule/freeCoursesArrangeController.cpp"
    "controller/Schedule/repeatCoursesArrangeController.cpp"
    "controller/StudentRecord/StclassRecordController.cpp"
    "controller/StudentRecord/StlistController.cpp"
    "controller/StudentRecord/StprofileDetailsController.cpp"
    "controller/AddStudent/PostStudentInfo.cpp"
    "controller/RegistRecord/GetRegistRecordDetailsController.cpp"
    "controller/RegistRecord/GetRegistRecordListController.cpp"
    "controller/StudentRecord/student_coursecontroller.cpp"
    "dao/StudentRecord/student_courseDAO.cpp" 
    "controller/AddStudent/PostStudentInfo.h"
    "controller/RegistRecord/GetRegistRecordDetailsController.h"
    "controller/RegistRecord/GetRegistRecordListController.h"
    "controller/StudentRecord/student_coursecontroller.h"
    "dao/StudentRecord/student_courseDAO.h"
    "dao/StudentRecord/student_courseMapper.h"
    "domain/do/StudentRecord/classroom/classroomdo.h"
    "domain/do/StudentRecord/student_course/student_coursedo.h"
    "domain/do/StudentRecord/view/student_courseviewdo.h"
    "domain/dto/StudentRecord/student_courseDTO.h"
    "domain/dto/AddStudent/AddStudentDTO.h"
    "domain/dto/RegistRecord/RegistRecordDTO.h"
    "domain/query/StudentRecord/studentinformation.h"
    "domain/query/AddStudent/AddStudentQuery.h"
    "domain/query/RegistRecord/RegistRecordQuery.h"
    "domain/vo/StudentRecord/student_courseVO.h"
    "domain/vo/AddStudent/AddStudentVO.h"
    "domain/vo/RegistRecord/RegistRecordVO.h"
 "dao/StudentRecord/StclassRecordDAO.cpp" "dao/StudentRecord/StclassRecordDAO.h" "dao/StudentRecord/StclassRecordMapper.h" "dao/StudentRecord/StlistDAO.cpp" "dao/StudentRecord/StlistDAO.h" "dao/StudentRecord/StlistMapper.h" "dao/StudentRecord/StprofileDetailsDAO.cpp" "dao/StudentRecord/StprofileDetailsDAO.h" "dao/StudentRecord/StprofileDetailsMapper.h" "domain/do/StudentRecord/stclassrecord/StclassRecordDO.h" "domain/do/StudentRecord/stlist/StlistDO.h" "domain/do/StudentRecord/stprofiledetails/StprofileDetailsDO.h" "service/StudentRecord/stclassrecord/StclassRecordService.cpp" "service/StudentRecord/stclassrecord/StclassRecordService.h" "service/StudentRecord/stlist/StlistService.cpp" "service/StudentRecord/stlist/StlistService.h" "service/StudentRecord/stprofiledetails/StprofileDetailsService.cpp" "service/StudentRecord/stprofiledetails/StprofileDetailsService.h" "dao/UserRelated/AttachmentDAO.cpp" "dao/UserRelated/AttachmentDAO.h" "dao/UserRelated/AttachmentMapper.h" "dao/UserRelated/PermissionDAO.cpp" "dao/UserRelated/PermissionDAO.h" "dao/UserRelated/PermissionMapper.h" "dao/UserRelated/RoleDAO.cpp" "dao/UserRelated/RoleDAO.h" "dao/UserRelated/RoleMapper.h" "dao/UserRelated/UserProfileDAO.cpp" "dao/UserRelated/UserProfileDAO.h" "dao/UserRelated/UserProfileMapper.h" "domain/do/UserRelated/AttachmentDO.h" "domain/do/UserRelated/SysPermissionDO.h" "domain/do/UserRelated/SysRoleDO.h" "domain/do/UserRelated/SysRolePermissionDO.h" "domain/do/UserRelated/SysUserRoleDO.h" "domain/do/UserRelated/UserRelatedDO.h" "service/UserRelated/UpdateHeadImgService.cpp" "service/UserRelated/UpdateHeadImgService.h" "service/UserRelated/UserInformationService.cpp" "service/UserRelated/UserInformationService.h" "service/UserRelated/UserProfileService.cpp" "service/UserRelated/UserProfileService.h" "controller/Course/RegisterController.cpp" "controller/Course/RegisterController.h" "dao/Course/CourseDAO.cpp" "dao/Course/CourseDAO.h" "dao/Course/CourseMapper.h" "dao/Course/RegisterDAO.cpp" "dao/Course/RegisterDAO.h" "dao/Course/RegisterMapper.h" "domain/do/Course/CourseDO.h" "domain/do/Course/RegisterDO.h" "domain/dto/Course/RegisterDTO.h" "service/Course/CourseService.cpp" "service/Course/CourseService.h" "service/Course/RegisterService.cpp" "service/Course/RegisterService.h" "dao/Mycustomers/StudentCourseDAO.cpp" "dao/Mycustomers/StudentCourseDAO.h" "dao/Mycustomers/StudentCourseMapper.h" "dao/Mycustomers/StudentDAO.cpp" "dao/Mycustomers/StudentDAO.h" "dao/Mycustomers/StudentMapper.h" "domain/do/Mycustomers/StudentCourseDo.h" "domain/do/Mycustomers/StudentDo.h" "service/Mycustomers/MyCustomersService.cpp" "service/Mycustomers/MyCustomersService.h")
# 发布Swagger文档包宏定义
if(DEFINED _RELEASE_DOC_)
	target_compile_definitions(${appName} PRIVATE _RELEASE_DOC_)
endif()

# 添加/bigobj选项
if(MSVC)
	target_compile_options(${appName} PRIVATE /bigobj)
endif()

# 链接自定义静态库模块
target_link_libraries (${appName} "lib-common" "lib-oatpp" "lib-mysql")

# 链接其他库依赖库，如：你要链接libpthread直接写成pthread
if (UNIX)
	target_link_libraries (${appName} jsoncpp pthread stdc++fs OpenSSL::SSL CURL::libcurl uuid)
else()
	target_link_libraries (${appName} libcrypto libssl ws2_32)
endif()
target_link_libraries (${appName} oatpp-websocket oatpp-swagger oatpp )
target_link_libraries (${appName} mysqlcppconn )
# 链接xlnt
if(USE_XLNT)
	if(ZO_BT STREQUAL "r" OR UNIX)
		target_link_libraries (${appName} xlnt )
	else()
		target_link_libraries (${appName} xlntd )
	endif()
	message (STATUS "${appName}: link xlnt lib")
endif()
# 链接fastdfs
if(USE_DFS)
	if (UNIX)
		target_link_libraries (${appName} fdfsclient fastcommon )
	endif()
	message (STATUS "${appName}: link fdfsclient lib")
endif()
# 链接ymal
if(USE_YML)
	if(ZO_BT STREQUAL "r" OR UNIX)
		target_link_libraries (${appName} yaml-cpp )
	else()
		target_link_libraries (${appName} yaml-cppd )
	endif()
	message (STATUS "${appName}: link yamlcpp lib")
endif()
# 链接nacos
if(USE_NACOS)
	if (UNIX)
		target_link_libraries (${appName} nacos-cli )
	endif()
	message (STATUS "${appName}: link nacos lib")
endif()
# 链接redis
if(USE_REDIS)
	target_link_libraries (${appName} redis++ hiredis )
	message (STATUS "${appName}: link redis lib")
endif()
# 链接RocketMQ
if(USE_ROCKETMQ)
	if (WIN32)
		target_link_libraries (${appName} rocketmq-client-cpp )
	else()
		target_link_libraries (${appName} rocketmq )
	endif()
	message (STATUS "${appName}: link rocketmq lib")
endif()
# 链接MongoDB
if(USE_MONGO)
	if (WIN32)
		target_link_libraries (${appName} bsoncxx mongocxx )
	else()
		target_link_libraries (${appName} bsoncxx bson-1.0 mongocxx mongoc-1.0 )
	endif()
	message (STATUS "${appName}: link mongodb lib")
endif()
# 链接AliyunSms
if(USE_ALISMS)
	if (UNIX)
		target_link_libraries (${appName} alibabacloud-sdk-core alibabacloud-sdk-dysmsapi )
	endif()
	message (STATUS "${appName}: link aliyun sms lib")
endif()
# 链接PDF库
if(USE_PDF)
	if (UNIX)
		target_link_libraries (${appName} hpdf png16 z ZXing)
	else()
		target_link_libraries (${appName} hpdf ZXing)
		if(ZO_BT STREQUAL "r")
			target_link_libraries (${appName} libpng16 )
		else()
			target_link_libraries (${appName} libpng16d )
		endif()
	endif()
	message (STATUS "${appName}: link hpdf lib")
endif()

# 复制配置到调试时可执行文件所在的目录
# RSA公钥证书
file (COPY "public.pem" DESTINATION ${PROJECT_BINARY_DIR}/${appName})
# Swagger资源
if (NOT DEFINED CLOSE_SWAGGER_DOC)
	file (GLOB swaggerRes "../lib-oatpp/include/oatpp-swagger/res/*")
	file (COPY ${swaggerRes} DESTINATION ${PROJECT_BINARY_DIR}/${appName}/res)
endif()
# 中文词典
file (COPY "zh-dict.yaml" DESTINATION ${PROJECT_BINARY_DIR}/${appName})
# 模板文件目录
file (GLOB tplDir "tpl/*")
file (COPY ${tplDir} DESTINATION "${PROJECT_BINARY_DIR}/${appName}/tpl")
# 字体文件目录
file (GLOB fontsDir "fonts/*")
file (COPY ${fontsDir} DESTINATION "${PROJECT_BINARY_DIR}/${appName}/fonts")
# Ubuntu系统特殊处理
if(IS_UBUNTU)
	# 复制动态库到可执行文件目录
	file (GLOB dylibdir "${PROJECT_SOURCE_DIR}/lib-dy/lib64/*")
	file (COPY ${dylibdir} DESTINATION "${PROJECT_BINARY_DIR}/${appName}")
endif()
# Windows平台特殊处理
if(WIN32)
	# 复制dll文件到可执行文件目录
	file (GLOB_RECURSE dycopy ${ZO_DY_DIR}/*.dll)
	file (COPY ${dycopy} DESTINATION "${PROJECT_BINARY_DIR}/${appName}")
	# 复制项目配置到可执行文件目录
	file (GLOB conf "conf/*")
	file (COPY ${conf} DESTINATION ${PROJECT_BINARY_DIR}/${appName}/conf)
endif()

# 安装文件
# 可执行文件
install (TARGETS ${appName} RUNTIME DESTINATION ${appName})
# RSA公钥证书
install (FILES "public.pem" DESTINATION ${appName})
# Swagger资源
if (NOT DEFINED CLOSE_SWAGGER_DOC)
	install (DIRECTORY "${PROJECT_SOURCE_DIR}/lib-oatpp/include/oatpp-swagger/res" DESTINATION ${appName})
endif()
# 中文词典
install (FILES "zh-dict.yaml" DESTINATION ${appName})
# 模板文件目录
install (DIRECTORY "tpl" DESTINATION ${appName})
# 字体文件目录
install (DIRECTORY "fonts" DESTINATION ${appName})
# UNIX平台特殊处理
if(UNIX)
	# 复制第三方动态链接库
	install (DIRECTORY "${PROJECT_SOURCE_DIR}/lib-dy/lib64/" DESTINATION lib FILES_MATCHING PATTERN "*.so*")
	# 复制启动脚本
	install (PROGRAMS ${PROJECT_SOURCE_DIR}/run-front.sh ${PROJECT_SOURCE_DIR}/run-back.sh DESTINATION ${appName})
endif()
# Windows平台特殊处理
if(WIN32)
	# 复制dll文件到可执行文件目录
	install (DIRECTORY "${ZO_DY_DIR}/" DESTINATION ${appName} FILES_MATCHING PATTERN "*.dll")
	# 复制项目配置到可执行文件目录
	install (DIRECTORY "conf" DESTINATION ${appName})
endif()