idf_component_register(SRCS 
    # Core BACnet Protocol - Implements the fundamental BACnet protocol stack components
    # including data encoding/decoding, service handling, and message formatting
    "bacnet-stack/src/bacnet/abort.c"                          # Abort service for terminating transactions
    "bacnet-stack/src/bacnet/access_rule.c"                    # Access control rules
    "bacnet-stack/src/bacnet/alarm_ack.c"                      # Alarm acknowledgment
    "bacnet-stack/src/bacnet/arf.c"                            # Atomic Read File service
    "bacnet-stack/src/bacnet/assigned_access_rights.c"         # Access rights assignment
    "bacnet-stack/src/bacnet/authentication_factor.c"          # Authentication factors for security
    "bacnet-stack/src/bacnet/authentication_factor_format.c"   # Authentication factor formatting
    "bacnet-stack/src/bacnet/awf.c"                            # Atomic Write File service
    "bacnet-stack/src/bacnet/bacaction.c"                      # BACnet actions
    "bacnet-stack/src/bacnet/bacaddr.c"                        # BACnet addressing
    "bacnet-stack/src/bacnet/bacapp.c"                         # BACnet application layer
    "bacnet-stack/src/bacnet/bacdcode.c"                       # BACnet data encoding/decoding
    "bacnet-stack/src/bacnet/bacdest.c"                        # BACnet destination handling
    "bacnet-stack/src/bacnet/bacdevobjpropref.c"               # Device object property references
    "bacnet-stack/src/bacnet/bacerror.c"                       # BACnet error handling
    "bacnet-stack/src/bacnet/bacint.c"                         # BACnet integer handling
    "bacnet-stack/src/bacnet/baclog.c"                         # BACnet logging
    "bacnet-stack/src/bacnet/bacprop.c"                        # BACnet property handling
    "bacnet-stack/src/bacnet/bacpropstates.c"                  # BACnet property states
    "bacnet-stack/src/bacnet/bacreal.c"                        # BACnet real number handling
    "bacnet-stack/src/bacnet/bacstr.c"                         # BACnet string handling
    "bacnet-stack/src/bacnet/bactext.c"                        # BACnet text utilities
    "bacnet-stack/src/bacnet/bactimevalue.c"                   # BACnet time value handling
    "bacnet-stack/src/bacnet/calendar_entry.c"                 # Calendar entries for scheduling
    "bacnet-stack/src/bacnet/channel_value.c"                  # Channel value objects
    "bacnet-stack/src/bacnet/cov.c"                            # Change of Value reporting
    "bacnet-stack/src/bacnet/create_object.c"                  # Dynamic object creation
    "bacnet-stack/src/bacnet/credential_authentication_factor.c" # Credential authentication
    "bacnet-stack/src/bacnet/dailyschedule.c"                  # Daily scheduling
    "bacnet-stack/src/bacnet/datetime.c"                       # Date and time handling
    "bacnet-stack/src/bacnet/dcc.c"                            # Device Communication Control
    "bacnet-stack/src/bacnet/delete_object.c"                  # Dynamic object deletion
    "bacnet-stack/src/bacnet/event.c"                          # Event handling
    "bacnet-stack/src/bacnet/get_alarm_sum.c"                  # Get Alarm Summary service
    "bacnet-stack/src/bacnet/getevent.c"                       # Get Event Information service
    "bacnet-stack/src/bacnet/hostnport.c"                      # Host and port handling for IP
    "bacnet-stack/src/bacnet/iam.c"                            # I-Am service for device discovery
    "bacnet-stack/src/bacnet/ihave.c"                          # I-Have service for object discovery
    "bacnet-stack/src/bacnet/indtext.c"                        # Index to text conversion
    "bacnet-stack/src/bacnet/lighting.c"                       # Lighting output object
    "bacnet-stack/src/bacnet/list_element.c"                   # List element handling
    "bacnet-stack/src/bacnet/lso.c"                            # Life Safety Operation service
    "bacnet-stack/src/bacnet/memcopy.c"                        # Memory copying utilities
    "bacnet-stack/src/bacnet/npdu.c"                           # Network Protocol Data Unit
    "bacnet-stack/src/bacnet/property.c"                       # Property handling
    "bacnet-stack/src/bacnet/proplist.c"                       # Property list management
    "bacnet-stack/src/bacnet/ptransfer.c"                      # Private Transfer service
    "bacnet-stack/src/bacnet/rd.c"                             # Reinitialize Device service
    "bacnet-stack/src/bacnet/readrange.c"                      # ReadRange service
    "bacnet-stack/src/bacnet/reject.c"                         # Reject service
    "bacnet-stack/src/bacnet/rp.c"                             # ReadProperty service
    "bacnet-stack/src/bacnet/rpm.c"                            # ReadPropertyMultiple service
    "bacnet-stack/src/bacnet/secure_connect.c"                 # Secure connection handling
    "bacnet-stack/src/bacnet/special_event.c"                  # Special event handling
    "bacnet-stack/src/bacnet/timestamp.c"                      # Timestamp handling
    "bacnet-stack/src/bacnet/timesync.c"                       # Time synchronization service
    "bacnet-stack/src/bacnet/weeklyschedule.c"                 # Weekly scheduling
    "bacnet-stack/src/bacnet/whohas.c"                         # Who-Has service
    "bacnet-stack/src/bacnet/whois.c"                          # Who-Is service
    "bacnet-stack/src/bacnet/wp.c"                             # WriteProperty service
    "bacnet-stack/src/bacnet/wpm.c"                            # WritePropertyMultiple service
    "bacnet-stack/src/bacnet/write_group.c"                    # WriteGroup service

    # BACnet/IP Datalink Layer - Handles the network communication layer
    # responsible for transmitting and receiving BACnet messages over IP networks
    "bacnet-stack/src/bacnet/datalink/datalink.c"              # Generic datalink interface
    "bacnet-stack/src/bacnet/datalink/bvlc.c"                  # BACnet Virtual Link Control for IPv4
    "bacnet-stack/src/bacnet/datalink/bvlc6.c"                 # BACnet Virtual Link Control for IPv6
    "bacnet-stack/src/bacnet/datalink/dlenv.c"                 # Datalink environment
    "bacnet-stack/src/bacnet/basic/bbmd/h_bbmd.c"              # BACnet/IP Broadcast Management Device

    # Service Handlers - Provides both client and server-side handling of BACnet services
    # Prefix 'h_' indicates handlers (server side), 's_' indicates service initiators (client side)
    
    # Handler files (server-side) - Process incoming requests and generate responses
    "bacnet-stack/src/bacnet/basic/service/h_apdu.c"           # Handle Application Protocol Data Units (main entry point)
    # "bacnet-stack/src/bacnet/basic/service/h_alarm_ack.c"      # Handle alarm acknowledgment requests
    # "bacnet-stack/src/bacnet/basic/service/h_arf.c"            # Handle Atomic Read File requests
    # "bacnet-stack/src/bacnet/basic/service/h_arf_a.c"          # Process Atomic Read File ACK responses
    # "bacnet-stack/src/bacnet/basic/service/h_awf.c"            # Handle Atomic Write File requests
    # "bacnet-stack/src/bacnet/basic/service/h_ccov.c"           # Handle confirmed Change of Value notifications
    # "bacnet-stack/src/bacnet/basic/service/h_cov.c"            # Handle Change of Value subscription requests
    # "bacnet-stack/src/bacnet/basic/service/h_create_object.c"  # Handle dynamic object creation requests
    # "bacnet-stack/src/bacnet/basic/service/h_dcc.c"            # Handle Device Communication Control requests
    # "bacnet-stack/src/bacnet/basic/service/h_delete_object.c"  # Handle dynamic object deletion requests
    # "bacnet-stack/src/bacnet/basic/service/h_gas_a.c"          # Process Get Alarm Summary ACK responses
    # "bacnet-stack/src/bacnet/basic/service/h_get_alarm_sum.c"  # Handle Get Alarm Summary requests
    # "bacnet-stack/src/bacnet/basic/service/h_getevent.c"       # Handle Get Event Information requests
    # "bacnet-stack/src/bacnet/basic/service/h_getevent_a.c"     # Process Get Event Information ACK responses
    "bacnet-stack/src/bacnet/basic/service/h_iam.c"            # Handle I-Am responses (device discovery)
    # "bacnet-stack/src/bacnet/basic/service/h_ihave.c"          # Handle I-Have notifications
    # "bacnet-stack/src/bacnet/basic/service/h_list_element.c"   # Handle Add/Remove List Element requests
    # "bacnet-stack/src/bacnet/basic/service/h_lso.c"            # Handle Life Safety Operation requests
    "bacnet-stack/src/bacnet/basic/service/h_noserv.c"         # Handle unsupported services
    # "bacnet-stack/src/bacnet/basic/service/h_rd.c"             # Handle Reinitialize Device requests
    "bacnet-stack/src/bacnet/basic/service/h_rp.c"             # Handle ReadProperty requests
    "bacnet-stack/src/bacnet/basic/service/h_rp_a.c"           # Process ReadProperty ACK responses
    # "bacnet-stack/src/bacnet/basic/service/h_rpm.c"            # Handle ReadPropertyMultiple requests
    # "bacnet-stack/src/bacnet/basic/service/h_rpm_a.c"          # Process ReadPropertyMultiple ACK responses
    # "bacnet-stack/src/bacnet/basic/service/h_rr.c"             # Handle ReadRange requests
    # "bacnet-stack/src/bacnet/basic/service/h_rr_a.c"           # Process ReadRange ACK responses
    # "bacnet-stack/src/bacnet/basic/service/h_ts.c"             # Handle TimeSynchronization requests
    # "bacnet-stack/src/bacnet/basic/service/h_ucov.c"           # Handle unconfirmed Change of Value notifications
    # "bacnet-stack/src/bacnet/basic/service/h_upt.c"            # Handle Unconfirmed Private Transfer requests
    # "bacnet-stack/src/bacnet/basic/service/h_whohas.c"         # Handle Who-Has requests (object discovery)
    "bacnet-stack/src/bacnet/basic/service/h_whois.c"          # Handle Who-Is requests (device discovery)
    "bacnet-stack/src/bacnet/basic/service/h_wp.c"             # Handle WriteProperty requests
    # "bacnet-stack/src/bacnet/basic/service/h_wpm.c"            # Handle WritePropertyMultiple requests
    # "bacnet-stack/src/bacnet/basic/service/h_write_group.c"    # Handle WriteGroup requests
    
    # Service files (client-side) - Initiate requests to other BACnet devices
    "bacnet-stack/src/bacnet/basic/service/s_abort.c"          # Send Abort service messages
    "bacnet-stack/src/bacnet/basic/service/s_ack_alarm.c"      # Send alarm acknowledgments
    "bacnet-stack/src/bacnet/basic/service/s_arfs.c"           # Send Atomic Read File requests
    "bacnet-stack/src/bacnet/basic/service/s_awfs.c"           # Send Atomic Write File requests
    "bacnet-stack/src/bacnet/basic/service/s_cevent.c"         # Send confirmed event notifications
    "bacnet-stack/src/bacnet/basic/service/s_cov.c"            # Send Change of Value notifications
    "bacnet-stack/src/bacnet/basic/service/s_create_object.c"  # Send object creation requests
    "bacnet-stack/src/bacnet/basic/service/s_dcc.c"            # Send Device Communication Control requests
    "bacnet-stack/src/bacnet/basic/service/s_delete_object.c"  # Send object deletion requests
    "bacnet-stack/src/bacnet/basic/service/s_error.c"          # Send error responses
    "bacnet-stack/src/bacnet/basic/service/s_get_alarm_sum.c"  # Send Get Alarm Summary requests
    "bacnet-stack/src/bacnet/basic/service/s_get_event.c"      # Send Get Event Information requests
    "bacnet-stack/src/bacnet/basic/service/s_getevent.c"       # Alternative Get Event Information service
    "bacnet-stack/src/bacnet/basic/service/s_iam.c"            # Send I-Am responses (device announcements)
    "bacnet-stack/src/bacnet/basic/service/s_ihave.c"          # Send I-Have notifications
    "bacnet-stack/src/bacnet/basic/service/s_list_element.c"   # Send Add/Remove List Element requests
    "bacnet-stack/src/bacnet/basic/service/s_lso.c"            # Send Life Safety Operation requests
    "bacnet-stack/src/bacnet/basic/service/s_rd.c"             # Send Reinitialize Device requests
    "bacnet-stack/src/bacnet/basic/service/s_readrange.c"      # Send ReadRange requests
    "bacnet-stack/src/bacnet/basic/service/s_rp.c"             # Send ReadProperty requests
    "bacnet-stack/src/bacnet/basic/service/s_rpm.c"            # Send ReadPropertyMultiple requests
    "bacnet-stack/src/bacnet/basic/service/s_ts.c"             # Send TimeSynchronization requests
    "bacnet-stack/src/bacnet/basic/service/s_uevent.c"         # Send unconfirmed event notifications
    "bacnet-stack/src/bacnet/basic/service/s_upt.c"            # Send Unconfirmed Private Transfer requests
    "bacnet-stack/src/bacnet/basic/service/s_whohas.c"         # Send Who-Has requests (object discovery)
    "bacnet-stack/src/bacnet/basic/service/s_whois.c"          # Send Who-Is requests (device discovery)
    "bacnet-stack/src/bacnet/basic/service/s_wp.c"             # Send WriteProperty requests
    "bacnet-stack/src/bacnet/basic/service/s_wpm.c"            # Send WritePropertyMultiple requests
    "bacnet-stack/src/bacnet/basic/service/s_write_group.c"    # Send WriteGroup requests

    # BACnet Object Implementations - Each file implements a specific BACnet object type
    # These objects represent the standardized data models in BACnet
    "bacnet-stack/src/bacnet/basic/object/access_credential.c" # Access Credential object for access control
    "bacnet-stack/src/bacnet/basic/object/access_door.c"       # Access Door object for physical door control
    "bacnet-stack/src/bacnet/basic/object/access_point.c"      # Access Point object for entry/exit points
    "bacnet-stack/src/bacnet/basic/object/access_rights.c"     # Access Rights object for permissions
    "bacnet-stack/src/bacnet/basic/object/access_user.c"       # Access User object for user credentials
    "bacnet-stack/src/bacnet/basic/object/access_zone.c"       # Access Zone object for secured areas
    "bacnet-stack/src/bacnet/basic/object/acc.c"               # Accumulator object for counting
    "bacnet-stack/src/bacnet/basic/object/ai.c"                # Analog Input object
    "bacnet-stack/src/bacnet/basic/object/ao.c"                # Analog Output object
    "bacnet-stack/src/bacnet/basic/object/av.c"                # Analog Value object
    "bacnet-stack/src/bacnet/basic/object/bacfile.c"           # File object for file transfer
    "bacnet-stack/src/bacnet/basic/object/bi.c"                # Binary Input object
    "bacnet-stack/src/bacnet/basic/object/bitstring_value.c"   # Bitstring Value object
    "bacnet-stack/src/bacnet/basic/object/blo.c"               # Binary Lighting Output object
    "bacnet-stack/src/bacnet/basic/object/bo.c"                # Binary Output object
    "bacnet-stack/src/bacnet/basic/object/bv.c"                # Binary Value object
    # "bacnet-stack/src/bacnet/basic/object/calendar.c"          # Calendar object for scheduling
    # "bacnet-stack/src/bacnet/basic/object/channel.c"           # Channel object for routing communications
    # "bacnet-stack/src/bacnet/basic/object/color_object.c"      # Color object for lighting control
    # "bacnet-stack/src/bacnet/basic/object/color_temperature.c" # Color Temperature object for lighting
    # "bacnet-stack/src/bacnet/basic/object/command.c"           # Command object for sequenced operations
    # "bacnet-stack/src/bacnet/basic/object/credential_data_input.c" # Credential Data Input object
    # "bacnet-stack/src/bacnet/basic/object/csv.c"               # CharacterString Value object
    # "bacnet-stack/src/bacnet/basic/object/device.c"            # Device object (main object in all devices)
    # "bacnet-stack/src/bacnet/basic/object/iv.c"                # Integer Value object
    # "bacnet-stack/src/bacnet/basic/object/lc.c"                # Load Control object for demand response
    # "bacnet-stack/src/bacnet/basic/object/lo.c"                # Lighting Output object
    # "bacnet-stack/src/bacnet/basic/object/lsp.c"               # Life Safety Point object
    # "bacnet-stack/src/bacnet/basic/object/lsz.c"               # Life Safety Zone object
    # "bacnet-stack/src/bacnet/basic/object/ms-input.c"          # Multi-state Input object
    # "bacnet-stack/src/bacnet/basic/object/mso.c"               # Multi-state Output object
    # "bacnet-stack/src/bacnet/basic/object/msv.c"               # Multi-state Value object
    # "bacnet-stack/src/bacnet/basic/object/nc.c"                # Notification Class object for alarms
    # "bacnet-stack/src/bacnet/basic/object/netport.c"           # Network Port object for comm settings
    "bacnet-stack/src/bacnet/basic/object/objects.c"           # Object table and management core
    # "bacnet-stack/src/bacnet/basic/object/osv.c"               # OctetString Value object
    # "bacnet-stack/src/bacnet/basic/object/piv.c"               # Positive Integer Value object
    # "bacnet-stack/src/bacnet/basic/object/program.c"           # Program object for executable logic
    # "bacnet-stack/src/bacnet/basic/object/sc_netport.c"        # Secure Connect Network Port object
    # "bacnet-stack/src/bacnet/basic/object/schedule.c"          # Schedule object for time-based control
    # "bacnet-stack/src/bacnet/basic/object/structured_view.c"   # Structured View for organizing objects
    # "bacnet-stack/src/bacnet/basic/object/time_value.c"        # Time Value object
    # "bacnet-stack/src/bacnet/basic/object/trendlog.c"          # Trend Log object for data recording

    # Core Utilities - Essential utilities and data structures for BACnet stack operation
    "bacnet-stack/src/bacnet/basic/binding/address.c"          # Address binding and caching
    "bacnet-stack/src/bacnet/basic/sys/keylist.c"              # Key-value pair lists
    "bacnet-stack/src/bacnet/basic/sys/mstimer.c"              # Millisecond timer
    "bacnet-stack/src/bacnet/basic/tsm/tsm.c"                  # Transaction State Machine
    "bacnet-stack/src/bacnet/basic/sys/fifo.c"                 # First-In-First-Out buffer
    "bacnet-stack/src/bacnet/basic/sys/ringbuf.c"              # Ring buffer implementation
    "bacnet-stack/src/bacnet/basic/sys/sbuf.c"                 # Static buffer implementation

    # BACnet Network Layer Processing - NPDU handling for routing and network layer
    "bacnet-stack/src/bacnet/basic/npdu/h_npdu.c"              # Handler for NPDU (Network Layer PDU)
    "bacnet-stack/src/bacnet/basic/npdu/h_routed_npdu.c"       # Handler for routed network messages
    "bacnet-stack/src/bacnet/basic/npdu/s_router.c"            # Router service implementation

    # BACnet/IPv6 BBMD - BACnet Broadcast Management Device for IPv6
    "bacnet-stack/src/bacnet/basic/bbmd6/h_bbmd6.c"            # BBMD handler for IPv6
    "bacnet-stack/src/bacnet/basic/bbmd6/vmac.c"               # Virtual MAC address handling for IPv6
    
    # Client-side Object Implementation
    "bacnet-stack/src/bacnet/basic/object/client/device-client.c" # Client-side device object implementation
    
    # Gateway Object Implementation
    "bacnet-stack/src/bacnet/basic/object/gateway/gw_device.c" # Gateway device object implementation
    
    # BACnet Client Functions - For initiating requests to other devices
    "bacnet-stack/src/bacnet/basic/client/bac-data.c"          # Client-side data handling
    "bacnet-stack/src/bacnet/basic/client/bac-discover.c"      # Device discovery functions
    "bacnet-stack/src/bacnet/basic/client/bac-rw.c"            # Read/Write client functions
    "bacnet-stack/src/bacnet/basic/client/bac-task.c"          # Client task management
    
    # UCI Configuration Support - For OpenWrt-based systems
    # "bacnet-stack/src/bacnet/basic/ucix/ucix.c"              # UCI configuration interface (disabled - requires OpenWrt UCI)
    
    # Server Implementation - Provides core server functionality to respond to client requests
    "bacnet-stack/src/bacnet/basic/server/bacnet_basic.c"      # Basic server implementation
    "bacnet-stack/src/bacnet/basic/server/bacnet_port.c"       # Generic port implementation
    "bacnet-stack/src/bacnet/basic/server/bacnet_port_ipv4.c"  # IPv4 port implementation
    
    # Add datetime helper functions to fix linking errors
    "bacnet-stack/src/bacnet/basic/sys/days.c"                 # Days and date helpers
    "bacnet-stack/src/bacnet/basic/sys/linear.c"               # Linear interpolation functions
    "bacnet-stack/src/bacnet/basic/sys/debug.c"                # Debug functions
    "bacnet-stack/src/bacnet/basic/sys/datetime_mstimer.c"     # Datetime with timer
    "bacnet-stack/src/bacnet/basic/sys/dst.c"                  # Daylight saving time
    "bacnet-stack/src/bacnet/basic/sys/color_rgb.c"            # Color functions
    "bacnet-stack/src/bacnet/basic/sys/lighting_command.c"     # Lighting commands

    # ESP32-specific BACnet Port - Adapter for BACnet on ESP32 platform
    # "esp32/bacnet.c"                                        # BACnet/IP implementation for ESP32
    "esp32/bacnet_port_esp32.c"                             # ESP32 port interface
    "esp32/bip_esp32.c"                                     # BACnet/IP stub implementations
    "esp32/device_esp32.c"                                  # Device object with reduced object table

    PRIV_INCLUDE_DIRS "./bacnet-stack/src/" "./esp32/"
    REQUIRES lwip esp_timer esp_netif
)

# Disable format warnings for BACnet stack - ESP32 treats uint32_t as long unsigned int
# which causes format string warnings when using %u with uint32_t
target_compile_options(${COMPONENT_LIB} PRIVATE 
    -Wno-format            # Disable format warnings
    -Wno-error=format      # Don't treat format warnings as errors
)
