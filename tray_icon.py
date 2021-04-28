from infi.systray import SysTrayIcon
import time
import fetch_data

with SysTrayIcon("assets/level-2.ico", "") as systray:
    while True:
        battery_data = "{}% Battery Percentage\n{}V Battery Voltage\nStatus is {}".format(fetch_data.battery_percentage, fetch_data.battery_voltage, fetch_data.battery_status)
        if fetch_data.battery_level == "1":
            systray.update(icon="assets/level-1.ico", hover_text=battery_data)
        elif fetch_data.battery_level == "2":
            systray.update(icon="assets/level-2.ico", hover_text=battery_data)
        elif fetch_data.battery_level == "3":
            systray.update(icon="assets/level-3.ico", hover_text=battery_data)
        elif fetch_data.battery_level == "4":
            systray.update(icon="assets/level-4.ico", hover_text=battery_data)
        time.sleep(1)