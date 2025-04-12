#include <Arduino.h>

#include "main.hpp"
#include "RgbLed.hpp"
#include "Screen.hpp"

#include <ArduinoBLE.h>

RgbLed rgbLed(RGB_LED_PIN);
Screen i2cScreen(SCREEN_WIDTH, SCREEN_HEIGHT, I2C_SDA_PIN, I2C_SCL_PIN, OLED_RESET);

void setup()
{
    rgbLed.setColor(16, 0, 16);

    if (!i2cScreen.begin())
    {
        rgbLed.setColor(32, 0, 0); // Red color
        delay(500);
        return;
    }

    rgbLed.setColor(0, 32, 0); // Green color

    delay(2000);

    i2cScreen.clear();
    i2cScreen.drawBitmap(zhong_bmp, (SCREEN_WIDTH - CHAR_WIDTH) / 2, (SCREEN_HEIGHT - CHAR_HEIGHT) / 2, CHAR_WIDTH, CHAR_HEIGHT);
    i2cScreen.drawBitmap(wen_bmp, (SCREEN_WIDTH - CHAR_WIDTH) / 2 + 18, (SCREEN_HEIGHT - CHAR_HEIGHT) / 2, CHAR_WIDTH, CHAR_HEIGHT);
    i2cScreen.scrollRight();

    Serial.begin(9600);
    while (!Serial) {}

    // Initialize BLE
    if (!BLE.begin()) {
        Serial.println("starting Bluetooth® Low Energy module failed!");

        while (1);
    }

    Serial.println("Bluetooth® Low Energy Central - Peripheral Explorer");

    // start scanning for peripherals
    BLE.scan();
}


void printData(const unsigned char data[], int length) {
    for (int i = 0; i < length; i++) {
        unsigned char b = data[i];

        if (b < 16) {
            Serial.print("0");
        }

        Serial.print(b, HEX);
    }
}


void exploreDescriptor(BLEDescriptor descriptor) {
    // print the UUID of the descriptor
    Serial.print("\t\tDescriptor ");
    Serial.print(descriptor.uuid());

    // read the descriptor value
    descriptor.read();

    // print out the value of the descriptor
    Serial.print(", value 0x");
    printData(descriptor.value(), descriptor.valueLength());

    Serial.println();

}

void exploreCharacteristic(BLECharacteristic characteristic) {
    // print the UUID and properties of the characteristic
    Serial.print("\tCharacteristic ");
    Serial.print(characteristic.uuid());
    Serial.print(", properties 0x");
    Serial.print(characteristic.properties(), HEX);

    // check if the characteristic is readable
    if (characteristic.canRead()) {
        // read the characteristic value
        characteristic.read();

        if (characteristic.valueLength() > 0) {
            // print out the value of the characteristic
            Serial.print(", value 0x");
            printData(characteristic.value(), characteristic.valueLength());
        }
    }
    Serial.println();

    // loop the descriptors of the characteristic and explore each
    for (int i = 0; i < characteristic.descriptorCount(); i++) {
        BLEDescriptor descriptor = characteristic.descriptor(i);

        exploreDescriptor(descriptor);
    }
}

void exploreService(const BLEService& service) {
    // print the UUID of the service
    Serial.print("Service ");
    Serial.println(service.uuid());

    // loop the characteristics of the service and explore each
    for (int i = 0; i < service.characteristicCount(); i++) {
        BLECharacteristic characteristic = service.characteristic(i);

        exploreCharacteristic(characteristic);
    }
}

void explorerPeripheral(BLEDevice peripheral) {
    // connect to the peripheral
    Serial.println("Connecting ...");

    if (peripheral.connect()) {
        Serial.println("Connected");
    } else {
        Serial.println("Failed to connect!");
        return;
    }

    // discover peripheral attributes
    Serial.println("Discovering attributes ...");
    if (peripheral.discoverAttributes()) {
        Serial.println("Attributes discovered");
    } else {
        Serial.println("Attribute discovery failed!");
        peripheral.disconnect();
        return;
    }

    // read and print device name of peripheral
    Serial.println();
    Serial.print("Device name: ");
    Serial.println(peripheral.deviceName());
    Serial.print("Appearance: 0x");
    Serial.println(peripheral.appearance(), HEX);
    Serial.println();

    // loop the services of the peripheral and explore each
    for (int i = 0; i < peripheral.serviceCount(); i++) {
        BLEService service = peripheral.service(i);

        exploreService(service);
    }

    Serial.println();

    // we are done exploring, disconnect
    Serial.println("Disconnecting ...");
    peripheral.disconnect();
    Serial.println("Disconnected");
}

void loop()
{
    // check if a peripheral has been discovered
    const BLEDevice peripheral = BLE.available();

    if (peripheral) {
        // discovered a peripheral, print out address, local name, and advertised service
        Serial.print("Found ");
        Serial.print(peripheral.address());
        Serial.print(" '");
        Serial.print(peripheral.localName());
        Serial.print("' ");
        Serial.print(peripheral.advertisedServiceUuid());
        Serial.println();

        // see if peripheral is a LED
        if (peripheral.localName() == "") {
            // stop scanning
            BLE.stopScan();

            explorerPeripheral(peripheral);

            // the peripheral disconnected, we are done
            while (1) {
                // Set the RGB LED to blue
                rgbLed.setColor(0, 0, 32);
                delay(1000);

                // Set the RGB LED to purple
                rgbLed.setColor(16, 0, 16);
                delay(1000);

                rgbLed.turnOff();
                delay(1000);
            }
        }
    }

}


