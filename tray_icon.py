from infi.systray import SysTrayIcon
import time
import requests
import datetime

with SysTrayIcon("assets/level-1.ico", "") as systray:
    while True:
        try:
            ip_address = "192.168.5.5"
            battery_percentage = "http://{}/api/percentage".format(ip_address)
            battery_voltage = "http://{}/api/voltage".format(ip_address)
            battery_status = "http://{}/api/status".format(ip_address)
            battery_level = "http://{}/api/level".format(ip_address)
            battery_percentage = requests.get(battery_percentage, timeout=3)
            battery_voltage = requests.get(battery_voltage, timeout=3)
            battery_status = requests.get(battery_status, timeout=3)
            battery_level = requests.get(battery_level, timeout=3)
            battery_percentage = battery_percentage.text
            battery_voltage = battery_voltage.text
            battery_status = battery_status.text
            battery_level = battery_level.text
            print("[200] Success Get Data")
        except:
            print("[500] Failed Get Data")
        battery_data = "{}% Battery Percentage\n{}V Battery Voltage\nStatus is {}\nUpdated at {}".format(battery_percentage, battery_voltage, battery_status, datetime.datetime.now().strftime("%d-%m-%Y %H:%I:%S"))
        if battery_level == "1":
            systray.update(icon="assets/level-1.ico", hover_text=battery_data)
        elif battery_level == "2":
            systray.update(icon="assets/level-2.ico", hover_text=battery_data)
        elif battery_level == "3":
            systray.update(icon="assets/level-3.ico", hover_text=battery_data)
        elif battery_level == "4":
            systray.update(icon="assets/level-4.ico", hover_text=battery_data)
        time.sleep(1)