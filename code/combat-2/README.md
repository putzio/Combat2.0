# _Combat2.0_

## Przed kompilacją

Trzeba dodać w pliku `.vscode/c_cpp_properties.json`, w `"includePath"` ścieżkę do przykładowej konfiguracji Wi-Fi: `"${config:idf.espIdfPath}/examples/common_components/protocol_examples_common/**",`

To samo do `"browse": { "path": [`. Zwróć uwagę, czy ścieżka w Twoim przypadku jest taka sama.

## Competition Rules:
- Robot must include a mechanism allowing to turn off its drive and weapon safely after loosing connection with a transmitter.
- Robot must be equipped with a clearly visible, durable weapon lock (e.g. a safety pin crippling a blade)
- Robot must be equipped with ON/OFF state indicator, clearly visible for a referee in any robot's position and orientation (e.g. high power LED).
