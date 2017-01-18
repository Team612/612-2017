all:
	sh script/build.sh

deploy:
	bash script/deploy.sh

update:
	sh script/.wpilib-download.sh
	sh script/.get_ctre.sh

clean:
	rm -rf .build/CMakeFiles/ .build/cmake_install.cmake .build/CMakeCache.txt .build/FRCUserProgram .build/Makefile
