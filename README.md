# LoRa <-> Serial Client

A client which can send LoRa messages by given serial output
and can send serial messages by given LoRa output.

I use this repo personally on a Wemos D1 mini Pro with the Lora module
of Hallard https://github.com/hallard/WeMos-Lora.

I also created an Elixir Nerves project which can communicate with this
project over a Raspberry Pi. Which can be found: https://github.com/sjoulbak/serial_lora_communicator

## Requirements

- LoRa (https://github.com/sandeepmistry/arduino-LoRa)
- Xxtea-lib (https://github.com/boseji/xxtea-lib)
- TaskScheduler (https://github.com/arkhipenko/TaskScheduler)

### Arduino

- Servo (https://www.arduino.cc/en/Reference/Servo)

## Questions

For any question please contact `@sjoulbak` on the Elixir slack.

## Contributing

Any contribution is welcome :)
