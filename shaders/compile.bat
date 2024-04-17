:: Compile our shader code

@echo off
set BASE_PATH=%~dp0
set VULKAN_SDK_PATH=C:\VulkanSDK\1.3.280.0\
set SHADER_COMPILER=%VULKAN_SDK_PATH%Bin\glslangValidator.exe

if exist %BASE_PATH%frag.spv goto COMPILED_SHADER_EXISTS
echo.
echo Compiling shader files:
call %SHADER_COMPILER% -V %BASE_PATH%shader.vert -o %BASE_PATH%vert.spv
call %SHADER_COMPILER% -V %BASE_PATH%shader.frag -o %BASE_PATH%frag.spv
call %SHADER_COMPILER% -V %BASE_PATH%shader.comp -o %BASE_PATH%comp.spv
exit /b ERRORLEVEL

:COMPILED_SHADER_EXISTS
echo.
echo Compiled shader files already exist. Skipping....
