#!/bin/bash
set -e

VERSION="1.0.0"
FORMULA_DIR="homebrew-formula"

# Cria o diretório para a fórmula Homebrew
mkdir -p $FORMULA_DIR

# Cria a fórmula Homebrew
cat <<EOF > $FORMULA_DIR/uuid.rb
class Uuid < Formula
  desc "Biblioteca de uuid para C"
  homepage "https://github.com/kovarike/uuid-for-c"
  url "https://github.com/kovarike/uuid-for-c/archive/v#{VERSION}.tar.gz"
  sha256 "#{SHA256_CHECKSUM}"  # Você deve gerar o checksum antes de usar

  def install
    system "cmake", ".", *std_cmake_args
    system "make"
    system "make", "install"
  end
end

EOF
