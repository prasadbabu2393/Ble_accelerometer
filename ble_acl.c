#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#ifndef BLUETOOTH_H
#include"header.h"
#define BLUETOOTH_H
#define TAG_ADDRESS "your_BLE_tag_address"

int main() {
    inquiry_info* devices = NULL;
    int numDevices;

    // Set up Bluetooth adapter
    int device = hci_open_dev(hci_get_route(NULL));
    if (device < 0) {
        perror("Error opening HCI device");
        exit(1);
    }

    // Set up BLE scan parameters
    inquiry_info* ii = NULL;
    numDevices = hci_inquiry(device, 8, 255, NULL, &ii, IREQ_CACHE_FLUSH);
    if (numDevices < 0) {
        perror("Error during inquiry");
        close(device);
        exit(1);
    }

    // Find the BLE tag in the list
    bdaddr_t targetAddr;
    str2ba(TAG_ADDRESS, &targetAddr);
    for (int i = 0; i < numDevices; i++) {
        if (bacmp(&ii[i].bdaddr, &targetAddr) == 0) {
            // BLE tag found, extract and process data
            AccelerometerData(ii[i].data, ii[i].length);
        }
    }

void AccelerometerData(uint8_t* rawData, int length) {
    char temp[5]="%02x";
    for (int i = 0; i < length; i++) {
        printf("%02X ", rawData[i]);
    if(temp == rawData[i])
	printf("object is stationary\n");
	else 
	printf("object is moving\n");
	}
    printf("\n");
}

    free(ii);
    close(device);

    return 0;
}
