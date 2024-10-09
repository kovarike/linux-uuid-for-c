#!/bin/bash
set -e

# Caminhos e variáveis
VERSION="1.0.0"
PACKAGE_NAME="uuid"
BUILD_DIR="build"

# Limpa o diretório de build e cria as pastas necessárias
rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR/DEBIAN
mkdir -p $BUILD_DIR/usr/lib/
mkdir -p $BUILD_DIR/usr/include/

# Compila o código usando CMake
cmake -S . -B $BUILD_DIR
cmake --build $BUILD_DIR

# Copia os arquivos compilados para as pastas necessárias
cp $BUILD_DIR/libuuid.so $BUILD_DIR/usr/lib/
cp include/uuid.h $BUILD_DIR/usr/include/

# Cria o arquivo de controle Debian
cat <<EOF > $BUILD_DIR/DEBIAN/control
Package: $PACKAGE_NAME
Version: $VERSION
Section: libs
Priority: optional
Architecture: amd64
Depends: libc6 (>= 2.14)
Maintainer: Danilo Silva <danilokovarike@gmail.com>
Description: Biblioteca de uuid para C.
EOF

# Gera o pacote .deb
dpkg-deb --build $BUILD_DIR $PACKAGE_NAME-$VERSION.deb
