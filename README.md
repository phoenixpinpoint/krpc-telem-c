# KRPC Telemetry Wrapper for C-Nano

This is a modular project for KSP telemetry using C-Nano. It is designed to be a lightweight and efficient way to collect telemetry data from KSP.

With this module we are using the NASA Power of 10 Rules for developing safety-critical code. More details can be found at https://www.perforce.com/blog/kw/NASA-rules-for-developing-safety-critical-code

## Basic Concept

As with the NASA rules we are trying to make this realistic. We are not exposing the coordinates as this is stored in the game logic. Instead we are focusing on distance traveled, velocity, heading, etc to provie a more realistic telemetry data set. The goal is to provide a lightweight and efficient way to collect telemetry data from KSP.

The realism is limited in some sense based on what is available. 

## Usage

The main.c file of this project is mostly a wrapper and includes some code I wrote for a test flight computer in KSP as a proof of concept. The module has an initialization function,
and polling function. The time interval code is up to you to develop for your specific use case.

