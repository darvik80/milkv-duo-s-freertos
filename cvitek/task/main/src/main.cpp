/* Standard includes. */
#include <stdio.h>
#include <bsp/csi/csi_pin.h>
#include <bsp/hal/dw/dw_uart_ll.h>

extern "C" {
#include "dump_uart.h"
void pre_system_init(void);

void post_system_init(void);

void main_cvirtos(void);



}

extern dev_pin_map_t uart_rx_map[];
extern dev_pin_map_t uart_tx_map[];

#include "bsp/csi/csi_uart.h"

csi_uart_t _uart;

void uart_arduino() {
	const dev_pin_map_t* rx_pin = target_pin_number_to_dev(PIN_UART3_RX, uart_rx_map, UART3);
	const dev_pin_map_t* tx_pin = target_pin_number_to_dev(PIN_UART3_TX, uart_tx_map, UART3);

	if (rx_pin == NULL || tx_pin == NULL) {
		pr_err("pin GPIO %d or %d are not used as Uart func\n", PIN_UART3_RX, PIN_UART3_TX);
		return;
	}

	if (csi_pin_set_mux(rx_pin->name, rx_pin->func)) {
		pr_err("pin GPIO %d fails to config as Uart_rx func\n", PIN_UART3_RX);
		return;
	}

	if (csi_pin_set_mux(tx_pin->name, tx_pin->func)) {
		pr_err("pin GPIO %d fails to config as Uart_tx func\n", PIN_UART3_TX);
		return;
	}

	csi_uart_init(&_uart, UART3);
}

int main(void) {
	uart_arduino();
	pre_system_init();
	printf("CVIRTOS Build Date:%s  (Time :%s) \n", __DATE__, __TIME__);
	//prvSetupHardware();
	post_system_init();

	main_cvirtos();
	return 0;
}

