# Custom Leak-Detection PCB

A safety-critical, 4-channel moisture detection and automated emergency shutdown system designed for subsea robotics (AUVs/ROVs). This project features a custom-engineered printed circuit board (PCB) paired with non-blocking, zero-latency microcontroller firmware to protect high-power electronics from catastrophic water ingress.

---

## 🚀 Key Features
* **Custom Hardware Design:** Built a multi-channel leak-detection sensor interface in Altium Designer, featuring discrete transistor signal conditioning, status indicators, and secure JST connectors.
* **Zero-Latency Safety Interrupts:** Replaced blocking polling loops with a hardware Interrupt Service Routine (`RISING` edge ISR) on a Teensy microcontroller to execute immediate emergency shutdowns.
* **Automated System Arming:** Implements a controlled 5-second startup boot sequence with automated pull-up/pull-output switching to safely transition the system from disabled to armed (`KS_PIN`).

---

## ⚡ Hardware Architecture & Theory of Operation

1. **Sensing Frontend:** The PCB accepts up to 4 moisture probe leads connected via white JST headers. 
2. **Signal Conditioning:** When water bridges the probe tips, resistance drops, allowing current to bias the onboard N-channel MOSFET (`Q1`).
3. **Interrupt Trigger:** The transition pulls the `LEAK` output line `HIGH` ($3.3\text{V}/5\text{V}$), generating a rising-edge signal routed directly to the microcontroller's interrupt pin (`WATER_PIN`).
4. **Kill-Switch Actuation:** The microcontroller instantly jumps to the ISR, driving the system kill switch (`KS_PIN`) `HIGH` to isolate power and kill thrusters within microseconds.

### Pin Mapping Overview
| Pin Name | Direction | Function |
| :--- | :--- | :--- |
| `WATER_PIN` | Input (Pull-down) | Connected to PCB leak output; triggers ISR on `RISING` edge |
| `KS_PIN` | Output | System Kill Switch line (`LOW` = Armed, `HIGH` = Killed/Disarmed) |
| `LED_PIN` | Output | System status indicator |

---

## 💻 Firmware Implementation
Developed using **PlatformIO** and **C++**, utilizing fast digital I/O macros (`digitalWriteFast.h`) to ensure deterministic execution speed during emergency states.

* **Non-Blocking Architecture:** Eliminates `delay()` calls inside interrupt vectors to prevent watchdog timer resets or sluggish response times.
* **Boot Sequence:** Configures pins on startup, pauses for a 5-second safety stabilization window, arms the kill switch (`KS_PIN` set to `LOW`), attaches the water sensor interrupt, and initializes thrusters.

---

## 🛠️ Tech Stack & Tools
* **EDA Tool:** Altium Designer (Schematic Capture, Multi-Layer PCB Layout)
* **Microcontroller:** Teensy (C++ / PlatformIO)
* **Assembly:** Surface-Mount Device (SMD) Soldering, Multimeters, Oscilloscopes
