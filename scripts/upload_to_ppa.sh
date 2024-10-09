#!/bin/bash
set -e

# Defina as variáveis
PPA="ppa:kovarike/uuid"
PACKAGE_NAME="uuid"
VERSION="1.0.0"
BUILD_DIR="build"

# Gere os arquivos necessários para o PPA
cd $BUILD_DIR/debian
debuild -S -sa
debuild -S -sa -b $BUILD_DIR/debian

# Use dput para subir o pacote para o PPA
dput $PPA ../$PACKAGE_NAME_$VERSION-0_source.changes
