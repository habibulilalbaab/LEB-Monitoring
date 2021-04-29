from infi.systray import SysTrayIcon
import time
import requests

with SysTrayIcon("assets/level-2.ico", "") as systray:
    while True:
        ip_address = "192.168.5.5"

        battery_percentage = "http://{}/api/percentage".format(ip_address)
        battery_percentage = requests.get(battery_percentage)
        battery_percentage = battery_percentage.text

        battery_voltage = "http://{}/api/voltage".format(ip_address)
        battery_voltage = requests.get(battery_voltage)
        battery_voltage = battery_voltage.text

        battery_status = "http://{}/api/status".format(ip_address)
        battery_status = requests.get(battery_status)
        battery_status = battery_status.text

        battery_level = "http://{}/api/level".format(ip_address)
        battery_level = requests.get(battery_level)
        battery_level = battery_level.text

        battery_data = "{}% Battery Percentage\n{}V Battery Voltage\nStatus is {}".format(battery_percentage, battery_voltage, battery_status)
        if battery_level == "1":
            systray.update(icon="assets/level-1.ico", hover_text=battery_data)
        elif battery_level == "2":
            systray.update(icon="assets/level-2.ico", hover_text=battery_data)
        elif battery_level == "3":
            systray.update(icon="assets/level-3.ico", hover_text=battery_data)
        elif battery_level == "4":
            systray.update(icon="assets/level-4.ico", hover_text=battery_data)
        time.sleep(1)