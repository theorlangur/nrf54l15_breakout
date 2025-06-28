/*
 * Copyright (c) 2023, Meta
 *
 * SPDX-License-Identifier: Apache-2.0
 */

//#include <iostream>
#include <memory>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#define UART_DEVICE_NODE DT_CHOSEN(zephyr_console)
static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void print_uart(const char *buf)
{
	while(*buf)
		uart_poll_out(uart_dev, *buf++);
}

int main(void)
{
	int ret;
	bool led_state = true;

	 if (!gpio_is_ready_dt(&led)) {
	 	return 0;
	 }
	 ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	 if (ret < 0) {
	 	return 0;
	 }

	while (1) {
		 ret = gpio_pin_toggle_dt(&led);
		 if (ret < 0) return 0;

		led_state = !led_state;
		if (led_state)
			print_uart("LED state: ON\r\n");
		else
			print_uart("LED state: OFF\r\n");
		k_msleep(SLEEP_TIME_MS);
	}

	//std::unique_ptr<int> ptr;
	//std::shared_ptr<char> ptr2;
	//std::cout << "Hello, C++ world! " << CONFIG_BOARD << std::endl;
	//return (int)ptr.get();
	return 0;
}
