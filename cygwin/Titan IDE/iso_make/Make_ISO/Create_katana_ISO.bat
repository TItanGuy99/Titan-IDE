@Echo off
SET PATH=sys
echo Creating ISO...
mkisofs -V DC_GAME -G sys/katana/IP.BIN -joliet -rock -l -o image.iso ./cd
echo Complete!