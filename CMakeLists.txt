cmake_minimum_required(VERSION 3.10)
project(uuid VERSION 1.0 LANGUAGES C)

# Definir diretórios de include e src
include_directories(include)
add_library(uuid SHARED src/id/uuid.c  src/id/is_unique.c src/id/tbl_hash.c src/id/log.c)

# Instalar a biblioteca e o arquivo de cabeçalho
install(TARGETS uuid DESTINATION lib)
install(FILES include/uuid.h DESTINATION include)

# Configurar o arquivo de pacote para que o CMake saiba como usar a biblioteca
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/uuidConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)
