#ifndef SPIKEBOOT_COM_H
#define SPIKEBOOT_COM_H

/* Communication interface with the USB host for controlling the spike hardware,
 * it supports the following things:
 *
 * - Flash the second-stage bootloader (operating system).
 * - Flash the current cartridge.
 * - Print (debug) messages to the host.
 *
 * It achieves this by defining the following endpoints:
 *
 * EP0 (CTRL)     - Control endpoint.
 * EP1 (BULK OUT) - Transfers the data needed for flashing.
 * */

void com_init(void);

#endif /* SPIKEBOOT_COM_H */
