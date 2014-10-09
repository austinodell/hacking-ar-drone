#!/bin/sh

MAX_TRIES=10

# Kill the processes
killall factory_reset_cb
killall inetd
killall memory_check.sh

# Wait for mods not beeing used

IS_OPMAP_USED=`lsmod | grep omap3_isp | sed -r 's/omap3_isp\s*[0-9]+\s*([0-9])/\1/g'`

COUNTER=0
while [ $IS_OPMAP_USED == 1 ]
do
	if [ $COUNTER -ge $MAX_TRIES ]; then
		echo "opmap is still in use - exit";
		exit 1
	fi
	echo "Waiting because opmap is still in use"
	sleep 2
	IS_OPMAP_USED=`lsmod | grep omap3_isp | sed -r 's/omap3_isp\s*[0-9]+\s*([0-9])/\1/g'`
	COUNTER=$(($COUNTER+1))
done

rmmod omap3_isp
rmmod soc1040
rmmod ov7670

/bin/dspbridge/cexec.out -T /system/lib/dsp/baseimage.dof
/bin/dspbridge/dynreg.out -r /system/lib/dsp/720p_h264venc_sn.dll64P
/bin/dspbridge/dynreg.out -r /system/lib/dsp/usn.dll64P

parallel-stream.sh
inetd
