import xarm

arm = xarm.Controller('USB')

battery_voltage = arm.getBatteryVoltage()
print('Battery voltage (volts):', battery_voltage)
