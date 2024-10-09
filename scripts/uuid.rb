require 'fileutils'

VERSION = "1.0.0"
FORMULA_DIR = "homebrew-formula"

# Executa o comando shasum para calcular o SHA256 do arquivo e captura o valor
SHA256_CHECKSUM = `shasum -a 256 ./homebrew-formula/uuid-#{VERSION}.tar.gz | awk '{ print $1 }'`.strip

# Cria o diretório para a fórmula Homebrew
FileUtils.mkdir_p(FORMULA_DIR)

# Gera o arquivo Ruby da fórmula Homebrew
File.open("#{FORMULA_DIR}/uuid.rb", "w") do |file|
  file.write <<-EOF
class Uuid < Formula
  desc "Biblioteca de uuid para C"
  homepage "https://github.com/kovarike/uuid-for-c"
  url "https://github.com/kovarike/uuid-for-c/archive/v#{VERSION}.tar.gz"
  sha256 "#{SHA256_CHECKSUM}"  # O checksum gerado é inserido aqui

  def install
    system "cmake", ".", *std_cmake_args
    system "make"
    system "make", "install"
  end
end
EOF
end
