# import module
import os
import sys
import inspect
import time
import datetime
import typing
import math

def utilSleep(second, unit):
    if second < 0:
        second = 0

    if unit == "s":
        second /= 1
    elif unit == "m":
        second /= 1000
    elif unit == "u":
        second /= 1000000
    elif unit == "n":
        second /= 1000000000
    else:
        return None

    return time.sleep(second)

def utilIntervalCallback(callback, arguments, interval, timeout):
    if callback is None:
        return -1

    intime  = time.time()
    subtime = 0
    stime   = 0
    etime   = 0
    while (time.time() - intime) < timeout:
        stime = time.time()

        rtn = callback(arguments)
        if rtn != 0:
            break

        etime = time.time()
        subtime = etime - stime;
        if interval > subtime:
            subtime = interval - subtime
            utilSleep(subtime, "s")

    return rtn 

def callback(args):
    i = args[0] + 1
    args[0] = i
    return i

def main():
    utilIntervalCallback(

