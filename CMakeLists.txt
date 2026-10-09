cmake_minimum_required(VERSION 3.20)
project(cpp-chat LANGUAGES CXX)

# Executável do servidor
add_executable(cpp-chat
    src/main.cpp
    src/server.cpp
)

# Executável do cliente
add_executable(cpp-chat-cliente
    src/cliente_main.cpp
    src/cliente.cpp
)

# Diretório dos arquivos .hpp
target_include_directories(cpp-chat PRIVATE include)
target_include_directories(cpp-chat-cliente PRIVATE include)

# Biblioteca de rede do Windows
if(WIN32)
    target_link_libraries(cpp-chat PRIVATE ws2_32)
    target_link_libraries(cpp-chat-cliente PRIVATE ws2_32)
endif()
