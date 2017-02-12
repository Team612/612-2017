#!/bin/bash

# This script downloads the latest (known) file of the WPI C++ plugin.
# The .jar file (really a .zip) contains a cpp.zip that has the
# include/ and lib/ folders necessary to build/link an executable FRC robot.

# The resulting wpilib/include/ folder should be used as a g++ -I statement
# The wpilib/lib folder should be used as a g++ -L statement

# TODO: script determining the latest .jar file based on the date string
# rather than a hard coded file name.
# The latest version can be determined from
# http://first.wpi.edu/FRC/roborio/release/eclipse/site.xml

# most recent version available from the internet
version="$(wget --quiet http://first.wpi.edu/FRC/roborio/release/eclipse/plugins/ && cat index.html | grep wpilib.plugins.cpp | sed -r 's/^.*wpilib.plugins.cpp_(.*).jar.*$/\1/')"
# most recent downloaded version (for usage outside of Travis CI)
version=$(echo $version | tr -d '\n')
downloaded_version=$(cat wpilib/versions.txt)

printf "Version: $version Current: $downloaded_version\n"

echo "WPILib Download: $PWD"

if [ ! "$version" = "$downloaded_version" ] ; then
	wget -r -nd --progress=bar http://first.wpi.edu/FRC/roborio/release/eclipse/plugins/edu.wpi.first.wpilib.plugins.cpp_2017.1.1.jar
    rm -rf wpilib/
	mkdir wpilib
	unzip -q $PWD/edu.wpi.first.wpilib.plugins.cpp_2017.1.1.jar -d $PWD/wpilib/
	rm -rf wpilib/edu
	rm -rf wpilib/META-INF
	rm -rf wpilib/plugin.xml
	unzip -q $PWD/wpilib/resources/cpp.zip -d $PWD/wpilib/
	rm -rf wpilib/resources
	#rm -rf cpp.zip
	rm -rf edu.wpi.first.wpilib.plugins.cpp_2017.1.1.jar

	#cp -r allwpilib/wpilibc/athena/shared wpilib/athena/shared
else
	echo "Already at latest WPILIB version"
fi
rm index.html
echo "WPILIB Version = $version"
echo $version >> wpilib/versions.txt
