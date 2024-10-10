cmake_minimum_required(VERSION 3.10)
project(uuid VERSION 1.0 LANGUAGES C)

# Definir diretórios de include
include_directories(include)

# Adicionar as bibliotecas
add_library(uuid_dll SHARED src/winid.c)
add_library(uuid_lib STATIC src/winid.c)

# Definir os nomes de saída para uuid.dll e uuid.lib
set_target_properties(uuid_dll PROPERTIES 
    OUTPUT_NAME "uuid" 
    PREFIX ""  
    SUFFIX ".dll"  
)

set_target_properties(uuid_lib PROPERTIES 
    OUTPUT_NAME "uuid" 
    PREFIX ""  
    SUFFIX ".lib"  
)

# Instalar bibliotecas e arquivos de cabeçalho
install(TARGETS uuid_dll uuid_lib
        LIBRARY DESTINATION lib  # Instalar a uuid.dll
        ARCHIVE DESTINATION lib  # Instalar a uuid.lib
)

install(FILES include/winid.h DESTINATION include)

# Configurar o arquivo de pacote para que o CMake saiba como usar a biblioteca
include(CMakePackageConfigHelpers)

# Escrever o arquivo de versão do pacote
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/uuidConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Escrever o arquivo de configuração do pacote
configure_file(uuidConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/uuidConfig.cmake" @ONLY
)


# Instalar arquivos de configuração do pacote
install(FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/uuidConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/uuidConfigVersion.cmake"
    DESTINATION lib/cmake/uuid
)
