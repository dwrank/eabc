#!/bin/bash
fastboot flash system system.img && fastboot flash userdata userdata.img && fastboot flash cache cache.img && fastboot reboot
