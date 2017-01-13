all:
	sh build.sh

deploy:
	bash deploy.sh

update:
	sh .wpilib-download.sh
	sh .get_ctre.sh

clean:
	rm -rf CMakeFiles/ .build/cmake_install.cmake .build/CMakeCache.txt .build/FRCUserProgram .build/Makefile
