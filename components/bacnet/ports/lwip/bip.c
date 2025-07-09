#include "bacnet/datalink/bip.h"
#include "bacnet/bacdef.h"
#include <stdbool.h> /* for the standard bool type. */
#include <stdint.h>  /* for standard integer types uint8_t etc. */

/**
 * @brief Receive a packet from the BACnet/IP socket (Annex J)
 * @param src [out] Source of the packet - BACnet address
 * @param pdu [out] Buffer to hold the PDU
 * @param max_pdu [in] Size of the PDU buffer
 * @param timeout [in] Milliseconds to wait for a packet
 * @return Number of bytes received, or 0 if none or timeout.
 */
uint16_t bip_receive(BACNET_ADDRESS *src, uint8_t *pdu, uint16_t max_pdu,
                     unsigned timeout) {
  /* In the LwIP implementation, packet reception is handled by the callback
     function bip_server_callback() which is triggered by the LwIP stack
     when UDP packets arrive. This function simply returns 0 as the reception
     happens asynchronously. */
  return 0;
}
