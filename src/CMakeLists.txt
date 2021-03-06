cmake_minimum_required(VERSION 3.2)
set($TARGET kkmeans)

add_executable(${TARGET} main.cpp)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# максимально строгие настройки компилятора
if (MSVC)
    target_compile_options(${TARGET} PRIVATE
        /W4
    )
else ()
    target_compile_options(${TARGET} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

target_link_libraries(${TARGET}
    dlib::dlib
    blas
    lapack
    Threads::Threads
)

# бинарник кладем в каталог bin
install(TARGETS ${TARGET} RUNTIME DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/data DESTINATION bin)

# генерить будем deb пакет
set(CPACK_GENERATOR DEB)

# конфигурируем deb пакет
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT oshuev.valery@yandex.ru)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libdlib")

# подключем генератор пакетов
include(CPack)
