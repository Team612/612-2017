all:
	bash script/unix/build.sh

competition:
	bash script/unix/compbuild.sh

verbose:
	bash script/unix/build.sh -v

deploy:
	bash script/unix/deploy.sh

update:
	sh script/unix/.wpilib-download.sh
	sh script/unix/.get-ctre.sh

clean:
	rm -rf .build/CMakeFiles/ .build/cmake_install.cmake .build/CMakeCache.txt .build/FRCUserProgram .build/Makefile
