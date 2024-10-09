#!/bin/bash
set -e

# Copiar o pacote RPM para o diretório de origem do fedpkg
PACKAGE_NAME="uuid"
VERSION="1.0.0"
SPEC_FILE="uuid.spec"

# Inicializar o repositório Copr
fedpkg clone $PACKAGE_NAME  # Removi a parte com "(remover --module)", pois estava incorreta
cd $PACKAGE_NAME
cp ../$SPEC_FILE .
cp ../$PACKAGE_NAME-$VERSION.tar.gz .

# Enviar o pacote RPM para Copr
fedpkg build --nowait
