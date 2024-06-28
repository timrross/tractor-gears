# Peg Perego John Deere Ground Force tractor motor controller

This is code implements a PWM control for the motors of a Ground force tractor. 

## Background

I have upgraded my kids tractor with [ML Toys Stage V. 775 motors](https://www.mltoys.com/collections/peg-perego-john-deere-ground-force-tractor/products/stage-v-speed-motors-for-peg-perego-rzr-900-and-ground-force) and 24v batteries.
I decided to go for two 12v 10AH LiFePO4 batteries over SLA, despite the directions on the ML Toys website, because they are superior; they will last for years, and they can do a 100% discharge so the run time is much better. 

Unfortunately they also deliver a much greater current when the tractor starts, and this was too much for the 12v switches when starting the tractor in speed 2, and they would trip and that would mean 
disconnecting and reconnecting the battery to get it going again. 

I tried replacing the accelerator switch, in case it was old and corroded, and I also bought a [cheap PWM Controller with soft start](https://amzn.to/3zhxnsm) from amazon and ran that for a bit, but it still couldn't 
handle the full current at start. As I'd already invested a good bit of cash in the motor upgrades, I figured a bit more would be worth it to get full power.
I decided that I would remove the switches from the motor loop, and run the wires straight to the motor, and control the motors with an Arduino Nano Every. 

## Solution

I purchased two [BTS7960B PWM Motor Drivers](https://amzn.to/3VZQlwF) from amazon, which are controlled using pwm signals from the Nano Every. The Gear Shifter and the Accelerator Pedal 
are now wired to inputs on the Arduino, so there is no issue of overload.
The battery is connected to the motor drivers in parallel, and then each motor driver is connected to a motor, so each motor can pull as much current as it needs. (The controllers have peak current of 43A!).

I have connected the two batteries with a DPDT switch and I can switch them between parallel for  pure 24V power or in to series for a slower 12V but double the run time. 

The arduino is powered from the batteries via a [LM317 DC-DC step down convertor](https://www.aliexpress.com/item/1005005996170388.html).

I made a custom break out board with screw terminals and dupont connectors to hold the arduino. 

I'll add a frizting and some photos when I get a moment. 