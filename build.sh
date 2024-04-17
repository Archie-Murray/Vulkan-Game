glslc ./shaders/shader.vert -o ./shaders/vert.spv
glslc ./shaders/shader.frag -o ./shaders/frag.spv
glslc ./shaders/shader.comp -o ./shaders/comp.spv

cd ./build/
cmake .. -GNinja --fresh
ninja
cp VulkanGame ../
cp compile_commands.json ../
cd ..
./VulkanGame
