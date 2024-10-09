#!/bin/bash
set -e

VERSION="1.0.0"
PACKAGE_NAME="uuid"
RPMBUILD_DIR="/tmp/rpmbuild"

# Cria as pastas necessárias para o rpmbuild
rpmdev-setuptree
mkdir -p $RPMBUILD_DIR/SOURCES

# Compila o código
cmake -S . -B build
cmake --build build

# Gera o arquivo tar.gz da fonte
tar czvf $RPMBUILD_DIR/SOURCES/$PACKAGE_NAME-$VERSION.tar.gz .

# Gera o .spec dinâmico
cat <<EOF > $RPMBUILD_DIR/SPECS/$PACKAGE_NAME.spec
Name:           $PACKAGE_NAME
Version:        $VERSION
Release:        1%{?dist}
Summary:        Biblioteca de uuid para C.

License:        MIT
Source0:        %{name}-%{version}.tar.gz
BuildRequires:  cmake, gcc
Requires:       libc.so.6

%description
Biblioteca de uuid para C.

%prep
%setup -q

%build
cmake .
make

%install
make install DESTDIR=%{buildroot}

%files
/usr/lib/libuuid.so
/usr/include/uuid.h
EOF

# Compilar o pacote RPM
rpmbuild -ba $RPMBUILD_DIR/SPECS/$PACKAGE_NAME.spec
