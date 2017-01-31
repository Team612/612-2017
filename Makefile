all:
	bash script/build.sh

verbose:
	bash script/build.sh -v

deploy:
	bash script/deploy.sh

update:
	sh script/.wpilib-download.sh
	sh script/.get-ctre.sh

clean:
	rm -rf .build/CMakeFiles/ .build/cmake_install.cmake .build/CMakeCache.txt .build/FRCUserProgram .build/Makefile
