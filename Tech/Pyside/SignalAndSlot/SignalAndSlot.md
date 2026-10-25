# Signals & Slots

## 🔹 Signal (Definition)

A signal is a function-like notification emitted by an object when its internal state changes or when something important happens.

Key ideas:
- It does not contain logic (no implementation)
- It announces: “Something happened”
- It can send data (arguments) to receivers
- It does not know who is listening

## 🔹 Slot (Definition)

A slot is a function that is executed in response to a signal.

Key ideas:
- It contains logic
- It receives and handles data
- It can be connected to one or multiple signals
- It behaves like a normal C++ function, but can also be triggered by Qt

## Key properties

### Type-safe

- Signal and slot signatures must match
- Checked at compiler-time

### Loosely coupled

- Sender does not know receiver
- Receiver does not know sender

### Flexible connections

- 1 signal → multiple slots
- multiple signals → 1 slot
- signal → signal

### Data passing

- Signals can carry arguments
- Slots can ignore extra arguments

## Requirements

- Class must inherit from QObject

