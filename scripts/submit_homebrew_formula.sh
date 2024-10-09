#!/bin/bash
set -e

# Defina as variáveis
REPO="kovarike/homebrew-formulas"
FORMULA_PATH="homebrew-formula/uuid.rb"

# Faça o commit e o push da fórmula para o repositório Homebrew
git add $FORMULA_PATH
git commit -m "Add new formula for uuid for c"
git push

# Crie o pull request automaticamente usando GitHub CLI (gh)
gh pr create --repo $REPO --title "uuid for c" --body "This PR adds uuid formula."
