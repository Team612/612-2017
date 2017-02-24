#!/bin/bash
#!/usr/bin/expect -f

#make

echo "deploy.sh: Beginning deploy process..."
echo "Enter team name: "
read team
printf "Team $team\n"
team_ip=""
os=$(uname | tr '[:upper:]' '[:lower:]')

if [ ${#team} -eq 4 ]; then
    team_ip="${team:0:2}.${team:2}"
    printf "Team IP 10.$team_ip.2\n"
    printf "Operating system: $os\n"
elif [ ${#team} -eq 3 ]; then
    team_ip="${team:0:1}.${team:1}"
    printf "Team IP 10.$team_ip.2\n"
    printf "Operating system: $os\n"
else
    printf "Invalid team name!"
    exit 1
fi

if [ ! -f ".build/FRCUserProgram" ]; then
    echo "FRCUserProgram not found!"
    exit 1
fi

if [[ ! "$os" == *"cygwin"* || ! "$os" == *"nt"* ]]; then
    ping -c 4 "roboRIO-$team-FRC.local" ; mDNS=$?
    if [ $mDNS -ne 0 ]; then
        echo "roboRIO not found on mDNS, falling back to static USB..."
        ping -c 4 "172.22.11.2" ; static=$?
        if [ $static -ne 0 ] ; then
            echo "Failed to connect via static USB, falling back to guessing static ethernet..."
            ping -c 4 "10.$team_ip.2" ; ethernet=$?
            if [ $ethernet -ne 0 ] ; then
                echo "Connection failed on guess: 10.$team_ip.2!"
                echo "Connection to roboRIO failed on all points!"
            else
                ssh "lvuser@10.$team_ip.2" "killall -9 FRCUserProgram && rm ~/FRCUserProgram && exit"

                scp ".build/FRCUserProgram" "lvuser@10.$team_ip.2:~/FRCUserProgram"
            fi
        else
            ssh "lvuser@172.22.11.2" "killall -9 FRCUserProgram && rm ~/FRCUserProgram && exit"

            scp ".build/FRCUserProgram" "lvuser@172.22.11.2:~/FRCUserProgram"
        fi
    else
        ssh "lvuser@roboRIO-$team-FRC.local" "killall -9 FRCUserProgram && rm ~/FRCUserProgram && exit"

        scp ".build/FRCUserProgram" "lvuser@roboRIO-$team-FRC.local:~/FRCUserProgram"
    fi
else
    ping -n 4 "roboRIO-$team-FRC.local" ; mDNS=$?
    if [ $mDNS -ne 0 ]; then
        echo "roboRIO not found on mDNS, falling back to static USB..."
        ping -n 4 "172.22.11.2" ; static=$?
        if [ $static -ne 0 ] ; then
            echo "Failed to connect via static USB, falling back to guessing static ethernet..."
            ping -n 4 "10.$team_ip.2" ; ethernet=$?
            if [ $ethernet -ne 0 ] ; then
                echo "Connection failed on guess: 10.$team_ip.2!"
                echo "Connection to roboRIO failed on all points!"
            else
                ssh "lvuser@10.$team_ip.2" "killall -9 FRCUserProgram && rm ~/FRCUserProgram && exit"

                scp ".build/FRCUserProgram" "lvuser@10.$team_ip.2:~/FRCUserProgram"
            fi
        else
            ssh "lvuser@172.22.11.2" "killall -9 FRCUserProgram && rm ~/FRCUserProgram && exit"

            scp ".build/FRCUserProgram" "lvuser@172.22.11.2:~/FRCUserProgram"
        fi
    else
        ssh "lvuser@roboRIO-$team-FRC.local" "killall -9 FRCUserProgram && rm ~/FRCUserProgram && exit"

        scp ".build/FRCUserProgram" "lvuser@roboRIO-$team-FRC.local:~/FRCUserProgram"
    fi
fi
echo "deploy.sh: Exiting deploy process..."
