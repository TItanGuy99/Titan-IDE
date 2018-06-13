if [ -f /etc/pki/nssdb/cert8.db ] && cmp -s /etc/defaults/etc/pki/nssdb/cert8.db /etc/pki/nssdb/cert8.db
then
    rm /etc/pki/nssdb/cert8.db
fi

if [ -f /etc/pki/nssdb/cert9.db ] && cmp -s /etc/defaults/etc/pki/nssdb/cert9.db /etc/pki/nssdb/cert9.db
then
    rm /etc/pki/nssdb/cert9.db
fi

if [ -f /etc/pki/nssdb/key3.db ] && cmp -s /etc/defaults/etc/pki/nssdb/key3.db /etc/pki/nssdb/key3.db
then
    rm /etc/pki/nssdb/key3.db
fi

if [ -f /etc/pki/nssdb/key4.db ] && cmp -s /etc/defaults/etc/pki/nssdb/key4.db /etc/pki/nssdb/key4.db
then
    rm /etc/pki/nssdb/key4.db
fi

if [ -f /etc/pki/nssdb/pkcs11.txt ] && cmp -s /etc/defaults/etc/pki/nssdb/pkcs11.txt /etc/pki/nssdb/pkcs11.txt
then
    rm /etc/pki/nssdb/pkcs11.txt
fi

if [ -f /etc/pki/nssdb/secmod.db ] && cmp -s /etc/defaults/etc/pki/nssdb/secmod.db /etc/pki/nssdb/secmod.db
then
    rm /etc/pki/nssdb/secmod.db
fi

