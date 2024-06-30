@echo off

copy /Y src\motors.h tests\motorTest\motors.h
copy /Y src\motors.h tests\qtrTest\motors.h
copy /Y src\pins.h tests\motorTest\pins.h
copy /Y src\pins.h tests\qtrTest\pins.h
copy /Y src\buzzer.h tests\qtrTest\buzzer.h
copy /Y src\buzzer.h tests\buzzTest\buzzer.h
copy /Y src\qtr.h tests\irs\qtr.h
copy /Y src\qtr.h tests\qtrTest\qtr.h
copy /Y src\tcs.h tests\colorTest\tcs.h
copy /Y src\tcs.h tests\freertos\tcs.h
