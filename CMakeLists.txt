cmake_minimum_required(VERSION 2.8) # Проверка версии CMake.
				    # Если версия установленой программы
				    # старее указаной, произайдёт аварийный выход.

add_executable(m_server main.c)		# Создает исполняемый файл с именем m_server из исходника main.cpp
add_executable(m_client main_client.c)		# Создает исполняемый файл с именем m_server из исходника main.cpp

add_library(socket STATIC socket.c)	# Создание статической библиотеки с именем socket
add_library(packet STATIC packet.c)	# Создание статической библиотеки с именем packet

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(m_server PUBLIC "-pthread")
  #/target_compile_options(m_client PUBLIC "-pthread")
  target_compile_options(socket PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(m_server "${CMAKE_THREAD_LIBS_INIT}")
  target_link_libraries(socket "${CMAKE_THREAD_LIBS_INIT}")
  #target_link_libraries(m_client "${CMAKE_THREAD_LIBS_INIT}")
endif()



target_link_libraries(m_server socket packet m)
target_link_libraries(m_client socket packet m)
