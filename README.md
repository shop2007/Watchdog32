# Watchdog32 (adm1232)

Arduino library to easily manage an **external watchdog** through the **Watchdog32 breakout board** with ADM1232.

Watchdog32 enhances the reliability of Arduino projects by automatically forcing a reset if the microcontroller becomes unresponsive, even when the internal watchdog cannot recover the system.

---

## 🔥 Features

- Simple management of the external Watchdog32
- Functions to reset the watchdog timer (`retrigger()`)
- Ability to enable or disable the watchdog
- Compatible with most Arduino boards

---

## 🛠️ Installation

### Method 1: Manual Installation
1. Download or clone this repository.
2. Copy the `Watchdog32` folder into your Arduino `libraries` directory:
   - Windows: `Documents/Arduino/libraries`
   - Linux/Mac: `~/Arduino/libraries`

### Method 2: Install from ZIP
1. Download the ZIP file of this repository.
2. In Arduino IDE: **Sketch** → **Include Library** → **Add .ZIP Library...**

*(In the future, you may also install it directly through the Arduino Library Manager.)*

---

## ⚡ How Watchdog32 Works

The Watchdog32 breakout sends a reset signal to Arduino if it does not receive a periodic pulse (`retrigger()`) from the microcontroller.  
If Arduino crashes or freezes, the module forces a reboot, keeping the system running reliably.

Typical applications:
- Remote monitoring systems
- Weather stations
- Autonomous IoT devices

---

## 📚 How to Use

### 1. Basic Wiring


| Watchdog32 Pin | Arduino Pin |
| :------------- | :---------- |
| ENABLE         | D8           |
| RETRIGGER      | D9           |
| OUT            | RESET        |
| VCC            | 5V           |
| GND            | GND          |

*(You can change the RETRIGGER and ENABLE pin in the code if needed.)*

---

### 2. Insights


https://www.realmeteo.com/arduino-english/internal-or-external-watchdog/
https://www.realmeteo.com/arduino/watchdog-interno-o-esterno/
https://www.analog.com/media/en/technical-documentation/data-sheets/adm1232.pdf
https://www.analog.com/en/products/adm1232.html

---

### 2. Purchase



https://www.ebay.it/itm/235363182136
