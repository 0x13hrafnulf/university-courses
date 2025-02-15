#!/bin/bash

# for each downlink interface...

LOGFILE=/var/log/dibbler/client.sh-log

set >> $LOGFILE

echo "-----------" >> $LOGFILE

downlink_prefixes=($DOWNLINK_PREFIXES)
ifn=1
for iface in $DOWNLINK_PREFIX_IFACES; do
    echo "----------- $iface ----------" >> $LOGFILE
    pref=${downlink_prefixes[$ifn]}
    preflen=${pref##*/}
    pref=${pref%/*}
    echo "downlink prefix = $pref" >> $LOGFILE
    ifn=$(( $ifn + 2 ))
    echo $ifn >> $LOGFILE
    # remove all global ipv6 addresses on the iface
    ip -6 addr flush dev $iface scope global
    echo "${pref}1/${preflen}" >> $LOGFILE
    echo "1 = $1" >> $LOGFILE
    if [ "$1" == "add" -o "$1" == "update" ]; then
        # set the first IP from the prefix
        ip addr add "${pref}1/${preflen}" dev $iface
    fi
done


<<COMMENT
# for each downlink interface...
ifn=0
for iface in $DOWNLINK_PREFIX_IFACES; do
    ifn=$(( $ifn + 1 ))
    prefix=`printenv PREFIX$ifn`
    prefixlen=`printenv PREFIX${ifn}LEN`

    # remove all global ipv6 addresses on the iface
    ip -6 addr flush dev $iface scope global

    if [ "$1" == "add" -o "$1" == "update" ]; then
        # set the first IP from the prefix
        ip addr add "${prefix}1/${prefixlen}" dev $iface
    fi
done
COMMENT