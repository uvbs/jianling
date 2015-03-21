COPY %1.dll %1.save
PREP /OM %1.dll
COPY %1._ll %1.dll
PROFILE /I %1 /O %1 %2 %3
COPY %1.save %1.dll
PREP /M %1
PLIST %1 >%1.txt
notepad %1.txt