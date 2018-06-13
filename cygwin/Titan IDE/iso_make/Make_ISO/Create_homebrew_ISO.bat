@Echo off
SET PATH=sys
copy cd\1ST_READ.BIN sys\1ST_READ.BIN
echo Descrambling 1ST_READ.BIN ...
scramble -d cd\1ST_READ.BIN cd\unscrambled.bin
del cd\1ST_READ.BIN
move cd\unscrambled.bin cd\1ST_READ.BIN
echo Creating ISO...
mkisofs -V DC_APP -G sys/homebrew/IP.BIN -joliet -rock -l -o image.iso ./cd
del cd\1ST_READ.BIN
move sys\1ST_READ.BIN cd\1ST_READ.BIN
echo Complete!