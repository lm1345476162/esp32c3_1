import time, socket, serial, clr
from pathlib import Path
# clr.AddReference(str(Path(__file__).parent.absolute() / 'LibreHardwareMonitorLib.dll'))
import os

newpath = os.path.dirname(os.path.abspath("LibreHardwareMonitorLib.dll"))
# os.path.append(newpath)
clr.AddReference('LibreHardwareMonitorLib.dll')
from LibreHardwareMonitor.Hardware import Computer
computer = Computer()
computer.IsCpuEnabled = True
computer.IsGpuEnabled = True
computer.Open()
observe_types = (
    ('cpu load', 'CPU Total', 'load'),
    ('cpu temp', 'Core (Tctl/Tdie)', 'temperature'),
    ('gpu load', 'GPU Core', 'load'),
    ('gpu temp', 'GPU Core', 'temperature'),
)
