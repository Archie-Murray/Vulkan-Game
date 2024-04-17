dev-shell
glslc ./shaders/shader.frag -o ./shaders/frag.spv
glslc ./shaders/shader.vert -o ./shaders/vert.spv
glslc ./shaders/shader.comp -o ./shaders/comp.spv
cmake -S . -B ./build/ -GNinja
set-location ./build/
ninja
cp ./compile_commands.json ../
cp ./VulkanGame.exe ../
set-location ../
.\VulkanGame.exe
