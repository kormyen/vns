# VNS (Van Nervous System)

'Tiny House' IoT system.

[Power Distribution Unit (PDU)](https://github.com/kormyen/VNS/tree/master/PDU)

<img src='https://raw.githubusercontent.com/kormyen/VNS/master/000.jpg' width="600"/>

## History
- 12018-07-05 : PDU main light control active.

## How I justified this madness:
- I "require" multiple switch panels for the lights. 
- I dislike when toggle switches get out of sync "so I'll use momentum buttons!". 
- ...Multiple momentum buttons as toggle switches done in just hardware/wiring seems quite complex... "surely this would be easier in software!". 
- Every light is also dimable... "if I do it in software I can just use a single dimmer per switch panel and switch light group some how~". 
- Arduino or similar would also allow for easy(tm) future expansion like web control, phone control, monitoring etc.
- "It's the obvious choice!"