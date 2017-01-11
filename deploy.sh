#!/bin/bash
#!/usr/bin/expect -f

make

echo "deploy.sh: Beginning deploy process..."
team=$(cat TEAM_NAME)
printf "Team $team\n"
team_ip=""

if [ ${#team} -eq 4 ]; then
    team_ip="${team:0:2}.${team:2}"
    printf "Team IP 10.$team_ip.2\n"
elif [ ${#team} -eq 3 ]; then
    team_ip="${team:0:1}.${team:1}"
    printf "Team IP 10.$team_ip.2\n"
fi

ping -c 4 "roboRIO-$team-FRC.local" ; mDNS=$?
if [ $mDNS -ne 0 ]; then
    echo "roboRIO not found on mDNS, falling back to static USB..."
    ping -c 4 "172.22.11.2" ; static=$?
    if [ $static -ne 0 ] ; then
        echo "Failed to connect via static USB, falling back to static ethernet..."
        ping -c 4 "10.$team_ip.2" ; ethernet=$?
        if [ $ethernet -ne 0 ] ; then
            echo "Connection to roboRIO failed on all points!"
        else
            ssh "lvuser@10.$team_ip.2" "rm ~/FRCUserProgram && exit"
            expect "assword:"
            send "\r"
            interact

            scp "FRCUserProgram" "lvuser@10.$team_ip.2:~/FRCUserProgram"
            expect "assword:"
            send "\r"
            send "exit"
            interact
        fi
    else
        ssh "lvuser@172.22.11.2" "rm ~/FRCUserProgram && exit"
        expect "assword:"
        send "\r"
        interact

        scp "FRCUserProgram" "lvuser@172.22.11.2:~/FRCUserProgram"
        expect "assword:"
        send "\r"
        send "exit"
        interact
    fi
else
    ssh "lvuser@roboRIO-$team-FRC.local" "rm ~/FRCUserProgram && exit"
    expect "assword:"
    send "\r"
    interact

    scp "FRCUserProgram" "lvuser@roboRIO-$team-FRC.local:~/FRCUserProgram"
    expect "assword:"
    send "\r"
    send "exit"
    interact
fi
echo "deploy.sh: Exiting deploy process..."
