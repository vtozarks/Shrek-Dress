# Shrek_Dress_Nano
Arduino Nano code for Shrek wedding dress LED control.

D2 controls operating mode

- Pull D2 low to initiate a ramp up from off to max brightness random sequence
- Continue to hold D2 low to to maintain random sequence at max brightness
- Allow D2 to pull-up to ramp dowm to off with random sequence

D3 to D12 used to drive data lines on 10 Neopixel 60 LED strips

- All strips oputput same random sequence

