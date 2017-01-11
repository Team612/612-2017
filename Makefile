all:
	sh build.sh

deploy:
	sh deploy.sh

update:
	sh .wpilib-download.sh

clean:
	rm .build/cmake_install.cmake .build/CMakeCache.txt .build/FRCUserProgram .build/Makefile
