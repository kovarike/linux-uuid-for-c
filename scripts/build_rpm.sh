set -e


VERSION="1.0.0"
PACKAGE_NAME="uuid"
RPMBUILD_DIR="$HOME/rpmbuild"

sudo apt-get update
sudo apt-get install -y cmake gcc make rpm 

rm -rf $RPMBUILD_DIR/SOURCES/*
rm -rf $RPMBUILD_DIR/SPECS/*

# Cria as pastas necessárias para o rpmbuild
mkdir -p $RPMBUILD_DIR/SOURCES
mkdir -p $RPMBUILD_DIR/SPECS  # Certifique-se de criar o diretório SPECS

# Compila o código
cmake -S . -B build
cmake --build build

# cd /home/runner/work/uuid-for-c
# Gera o arquivo tar.gz da fonte
tar czvf $RPMBUILD_DIR/SOURCES/$PACKAGE_NAME-$VERSION.tar.gz .

if [[ ! -f $RPMBUILD_DIR/SOURCES/$PACKAGE_NAME-$VERSION.tar.gz ]]; then
    echo "Erro: O arquivo $PACKAGE_NAME-$VERSION.tar.gz não foi criado."
    exit 1
fi

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
