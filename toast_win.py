from win10toast import ToastNotifier

toaster = ToastNotifier()
battery_percentage = "100%"
battery_voltage = "11.9V"

if battery_voltage > "11.4V":
    battery_icon = "assets/level-1.ico"
elif battery_voltage < "11.4V" and battery_voltage >= "11.2V":
    battery_icon = "assets/level-2.ico"
elif battery_voltage < "11.0V" and battery_voltage >= "10.8V":
    battery_icon = "assets/level-3.ico"
elif battery_voltage < "10.8V":
    battery_icon = "assets/level-4.ico"
toaster.show_toast("{} Battery Percentage".format(battery_percentage),
                    "Battery Voltage is {}\nCritical Battery, Please Charging".format(battery_voltage),
                    icon_path="{}".format(battery_icon))