uuid/
├──.github/workflows/ci.yml
├── include/
│    ├── uuid.h
├── src/
│    ├── id
│        ├── is_unique.c
│        ├── log.c
│        ├── tbl_hash.c
│        ├── uuid.c
│        
├── build/
├── log/
├── CMakeLists.txt
├── scripts/
│   ├── build_deb.sh
│   ├── build_rpm.sh
│   ├── build_choco.ps1
│   ├── uuid.rb
│   ├── submit_rpm_to_copr.sh
│   ├── submit_choco_package.ps1
│   ├── submit_homebrew_formula.sh
│   ├── upload_to_ppa.sh    
├── LICENSE   
│   
└── README.md







echo "# uuid-for-c" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/kovarike/uuid-for-c.git
git push -u origin main