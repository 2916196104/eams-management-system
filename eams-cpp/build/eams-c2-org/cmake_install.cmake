# Install script for directory: C:/Users/huang/Desktop/work_/eams/zero-one-eams2603/eams-cpp/eams-c2-org

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/zero-one-eams")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/mingw/w64devkit/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/eams-c2-org" TYPE EXECUTABLE FILES "C:/Users/huang/Desktop/work_/eams/zero-one-eams2603/eams-cpp/build/eams-c2-org/eams-c2-org.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/eams-c2-org/eams-c2-org.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/eams-c2-org/eams-c2-org.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/mingw/w64devkit/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/eams-c2-org/eams-c2-org.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/eams-c2-org" TYPE FILE FILES "C:/Users/huang/Desktop/work_/eams/zero-one-eams2603/eams-cpp/eams-c2-org/public.pem")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/eams-c2-org" TYPE DIRECTORY FILES "C:/Users/huang/Desktop/work_/eams/zero-one-eams2603/eams-cpp/lib-oatpp/include/oatpp-swagger/res")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/eams-c2-org" TYPE FILE FILES "C:/Users/huang/Desktop/work_/eams/zero-one-eams2603/eams-cpp/eams-c2-org/zh-dict.yaml")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/eams-c2-org" TYPE DIRECTORY FILES "C:/Users/huang/Desktop/work_/eams/zero-one-eams2603/eams-cpp/eams-c2-org/tpl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/eams-c2-org" TYPE DIRECTORY FILES "C:/Users/huang/Desktop/work_/eams/zero-one-eams2603/eams-cpp/eams-c2-org/fonts")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/eams-c2-org" TYPE DIRECTORY FILES "C:/Users/huang/Desktop/work_/eams/zero-one-eams2603/eams-cpp/lib-dy/lib64/debug/" FILES_MATCHING REGEX "/[^/]*\\.dll$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/eams-c2-org" TYPE DIRECTORY FILES "C:/Users/huang/Desktop/work_/eams/zero-one-eams2603/eams-cpp/eams-c2-org/conf")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/huang/Desktop/work_/eams/zero-one-eams2603/eams-cpp/build/eams-c2-org/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
