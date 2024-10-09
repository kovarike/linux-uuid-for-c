#!/bin/bash
set -e

VERSION="1.0.0"
FORMULA_DIR="homebrew-formula"

# Cria o diretório para a fórmula Homebrew
mkdir -p $FORMULA_DIR

# Cria a fórmula Homebrew
cat <<EOF > $FORMULA_DIR/uuid.rb
class Uuid  < Formula
  desc "Biblioteca de uuid para C"
  homepage "https://github.com/kovarike/uuid-for-c"
  url "https://github.com/kovarike/uuid-for-c/archive/v$VERSION.tar.gz"
  sha256 "$(shasum -a 256 $FORMULA_DIR/uuid-$VERSION.tar.gz | awk '{ print $1 }')"
  version "$VERSION"

  def install
    system "cmake", ".", *std_cmake_args
    system "make"
    system "make", "install"
  end
end
EOF
