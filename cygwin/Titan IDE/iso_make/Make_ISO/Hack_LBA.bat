@Echo off
SET PATH=sys
copy sys\katana\IP.BIN IP.BIN
binhack32.exe < sys\hack_params.txt
del IP.BIN
