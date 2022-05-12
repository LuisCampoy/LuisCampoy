Hi all. This is code to add a third brake light to my motorbike
Still needs debugging
when brake is applied, LED si supposed to flash, then blink and then go solid at full brightness
Otherwise, it is supposed to be in riding mode at 50% brightness (or whatever parameter I end up with)
Problem: it only does it the first time. Subsequent times goes from riding mode to full brightness skipping the other two steps in the state machine
