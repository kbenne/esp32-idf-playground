idf_component_register(SRCS 
    # Core BACnet Protocol
    "bacnet-stack/src/bacnet/npdu.c"
    "bacnet-stack/src/bacnet/bacaddr.c"
    "bacnet-stack/src/bacnet/bacapp.c"
    "bacnet-stack/src/bacnet/bacdcode.c"
    "bacnet-stack/src/bacnet/bacint.c"
    "bacnet-stack/src/bacnet/bacreal.c"
    "bacnet-stack/src/bacnet/bacstr.c"
    "bacnet-stack/src/bacnet/bactext.c"
    "bacnet-stack/src/bacnet/iam.c"
    "bacnet-stack/src/bacnet/whois.c"
    "bacnet-stack/src/bacnet/rp.c"
    "bacnet-stack/src/bacnet/memcopy.c"
    "bacnet-stack/src/bacnet/reject.c"
    "bacnet-stack/src/bacnet/abort.c"
    "bacnet-stack/src/bacnet/bacerror.c"

    # BACnet/IP Datalink Layer
    "bacnet-stack/src/bacnet/datalink/datalink.c"
    "bacnet-stack/src/bacnet/datalink/bvlc.c"
    "bacnet-stack/src/bacnet/datalink/dlenv.c"

    # Service Handlers
    "bacnet-stack/src/bacnet/basic/service/h_whois.c"
    "bacnet-stack/src/bacnet/basic/service/h_iam.c"
    "bacnet-stack/src/bacnet/basic/service/h_rp.c"
    "bacnet-stack/src/bacnet/basic/service/h_apdu.c"
    "bacnet-stack/src/bacnet/basic/service/h_noserv.c"
    "bacnet-stack/src/bacnet/basic/service/s_whois.c"
    "bacnet-stack/src/bacnet/basic/service/s_iam.c"
    "bacnet-stack/src/bacnet/basic/service/s_rp.c"
    "bacnet-stack/src/bacnet/basic/service/s_error.c"

    # Device Object
    "bacnet-stack/src/bacnet/basic/object/device.c"
    "bacnet-stack/src/bacnet/basic/object/objects.c"
    "bacnet-stack/src/bacnet/basic/object/netport.c"

    # Core Utilities
    "bacnet-stack/src/bacnet/basic/binding/address.c"
    "bacnet-stack/src/bacnet/basic/sys/keylist.c"
    "bacnet-stack/src/bacnet/basic/sys/mstimer.c"
    "bacnet-stack/src/bacnet/basic/tsm/tsm.c"
    "bacnet-stack/src/bacnet/basic/sys/fifo.c"
    "bacnet-stack/src/bacnet/basic/sys/ringbuf.c"
    "bacnet-stack/src/bacnet/basic/sys/sbuf.c"

    # Server Implementation
    "bacnet-stack/src/bacnet/basic/server/bacnet_basic.c"
    "bacnet-stack/src/bacnet/basic/server/bacnet_port.c"
    "bacnet-stack/src/bacnet/basic/server/bacnet_port_ipv4.c"

    INCLUDE_DIRS "./bacnet-stack/src/"
    REQUIRES lwip
)
