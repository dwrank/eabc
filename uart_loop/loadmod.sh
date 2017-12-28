#!/bin/bash
adb shell rmmod uart_loop && adb shell rm /uart_loop.ko && adb push uart_loop.ko / && adb shell insmod /uart_loop.ko
