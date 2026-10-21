g++ *.cpp -o main.exe -lglfw3 -lopengl32 -lgdi32 -->compile command windows

compile command mac
clang++ -std=c++17 main.cpp LineEncoding.cpp modulation.cpp \
  demodulation.cpp plot.cpp \
  $(pkg-config --cflags --libs glfw3) \
  -framework OpenGL -o main
