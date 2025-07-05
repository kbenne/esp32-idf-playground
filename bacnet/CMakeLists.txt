idf_component_register(SRCS 
    # Core BACnet Protocol
    "npdu.c"
    "bacaddr.c"
    "bacapp.c"
    "bacdcode.c"
    "bacint.c"
    "bacreal.c"
    "bacstr.c"
    "bactext.c"
    "iam.c"
    "whois.c"
    "rp.c"
    "memcopy.c"
    "reject.c"
    "abort.c"
    "bacerror.c"

    # BACnet/IP Datalink Layer
    "datalink/datalink.c"
    "datalink/bvlc.c"
    "datalink/dlenv.c"

    # Service Handlers
    "basic/service/h_whois.c"
    "basic/service/h_iam.c"
    "basic/service/h_rp.c"
    "basic/service/h_apdu.c"
    "basic/service/h_noserv.c"
    "basic/service/s_whois.c"
    "basic/service/s_iam.c"
    "basic/service/s_rp.c"
    "basic/service/s_error.c"

    # Device Object
    "basic/object/device.c"
    "basic/object/objects.c"
    "basic/object/netport.c"

    # Core Utilities
    "basic/binding/address.c"
    "basic/sys/keylist.c"
    "basic/sys/mstimer.c"
    "basic/tsm/tsm.c"
    "basic/sys/fifo.c"
    "basic/sys/ringbuf.c"
    "basic/sys/sbuf.c"

    # Server Implementation
    "basic/server/bacnet_basic.c"
    "basic/server/bacnet_port.c"
    "basic/server/bacnet_port_ipv4.c"

    INCLUDE_DIRS "."
    REQUIRES lwip
)
